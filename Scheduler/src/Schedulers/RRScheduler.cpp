#include "RRScheduler.h"

RRScheduler::RRScheduler(std::weak_ptr<CPU> _cpu, float quantum) : Scheduler(_cpu), m_Quantum(quantum)
{
	if (auto lockedCPU = m_CPU.lock()) {
		lockedCPU->ActivateQuantum(m_Quantum);
	}
}



void RRScheduler::PassNextProcess()
{
	if (auto lockedCPU = m_CPU.lock()) {
		if (!m_ActiveQueue->Empty())
		{
			lockedCPU->Execute(m_ActiveQueue->PopProcess());
		}
	}
	else
	{
		// @TODO: make error about invalid CPU while binding to it
	}
}
