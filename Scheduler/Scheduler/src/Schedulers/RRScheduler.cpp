#include "RRScheduler.h"
#include "Log/Logger.h"
#include "CPU.h"

RRScheduler::RRScheduler(std::weak_ptr<CPU> _cpu, float quantum) : Scheduler(_cpu), m_Quantum(quantum)
{
	if (auto lockedCPU = m_CPU.lock()) {
		lockedCPU->ActivateQuantum(m_Quantum);
	}
	else
	{
		LOG_ERROR("Invalid CPU on Scheduler initialization");
	}
}

void RRScheduler::PassNextProcess()
{
	if (m_ActiveQueue->Empty())
	{
		return;
	}
	if (auto lockedCPU = m_CPU.lock()) {
		if (!m_ActiveQueue->Empty())
		{
			lockedCPU->Execute(m_ActiveQueue->PopProcess());
		}
	}
	else
	{
		LOG_ERROR("Invalid CPU while trying to pass process");
	}
}
