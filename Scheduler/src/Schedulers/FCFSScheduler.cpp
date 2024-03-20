#include "FCFSScheduler.h"

FCFSScheduler::FCFSScheduler(std::weak_ptr<CPU> _cpu) : Scheduler(_cpu)
{

}

void FCFSScheduler::PassNextProcess()
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
