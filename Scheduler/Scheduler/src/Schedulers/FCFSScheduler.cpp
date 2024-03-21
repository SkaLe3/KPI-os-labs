#include "FCFSScheduler.h"
#include "Log/Logger.h"
#include "CPU.h"

FCFSScheduler::FCFSScheduler(std::weak_ptr<CPU> _cpu) : Scheduler(_cpu)
{

}

void FCFSScheduler::PassNextProcess()
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
