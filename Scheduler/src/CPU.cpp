#include "CPU.h"


void CPU::Tick()
{
	m_Tick += 1;
	m_QuantumLeft -= 1;

	m_ActiveProcess->Execute();

	if (m_ActiveProcess->State == EProcessState::Finished)
	{
		m_ActiveProcess->FinishTime = m_Tick;
		m_ActiveProcess->WaitTime = m_ActiveProcess->FinishTime - m_ActiveProcess->StartTime - m_ActiveProcess->WorkTime;
		OnExecutionBreak(std::move(m_ActiveProcess));
	}
	if (bUseQuantum && m_QuantumLeft <= 0)
	{
		m_ActiveProcess->State = EProcessState::Waiting;
		OnExecutionBreak(std::move(m_ActiveProcess));
	}

}

float CPU::GetCurrentTick()
{
	return m_Tick;
}

bool CPU::IsIdle()
{
	return (m_ActiveProcess == nullptr);
}

void CPU::ActivateQuantum(float quantum)
{
	bUseQuantum = true;
	m_Quantum = quantum;
}

void CPU::Execute(std::unique_ptr<Process> process)
{
	m_ActiveProcess = std::move(process);
	m_ActiveProcess->State = EProcessState::Working;
	if (m_ActiveProcess->StartTime < 0)
	{
		m_ActiveProcess->StartTime = m_Tick;
	}
	m_QuantumLeft = m_Quantum;

}
