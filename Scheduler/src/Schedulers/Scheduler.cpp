#include "Scheduler.h"



Scheduler::Scheduler(std::weak_ptr<CPU> _cpu) : m_CPU(_cpu)
{
	m_FinishedLog = std::make_unique<Queue>();

	if (auto lockedCPU = m_CPU.lock()) {
		lockedCPU->OnExecutionBreak.Subscribe(std::bind(&Scheduler::OnExecutionBreak, this, std::placeholders::_1));
	}
	else
	{
		// @TODO: make error about invalid CPU while binding to it
	}
}

void Scheduler::SetQueue(std::shared_ptr<Queue> queue)
{
	m_ActiveQueue = queue;
}


void Scheduler::OnExecutionBreak(std::unique_ptr<Process> process)
{
	if (process->State == EProcessState::Finished)
	{
		m_FinishedLog->PushProcess(std::move(process));
	}
	else
	{
		m_ActiveQueue->PushProcess(std::move(process));
	}
	PassNextProcess();
}

bool Scheduler::IsActiveQueueEmpty()
{
	return m_ActiveQueue->Empty();
}

std::unique_ptr<Queue> Scheduler::GetFinishedProcessesLog()
{
	return std::move(m_FinishedLog);
}

ESchedulerAlgorithm Scheduler::scheduler_string_to_enum(const std::string& algo)
{
	if (algo == "RR")
	{
		return ESchedulerAlgorithm::RR;
	}
	else if (algo == "FCFS")
	{
		return ESchedulerAlgorithm::FCFS;
	}
	else
	{
		return ESchedulerAlgorithm::None;
	}
}
