#include "SystemController.h"
#include "Schedulers/RRScheduler.h"
#include "Schedulers/FCFSScheduler.h"
#include "CPU.h"
#include "Process.h"
#include "Log/Logger.h"

#include <vector>
#include <algorithm>
#include <deque>

SystemController::SystemController(Options& options)
{
	m_CPU = std::make_shared<CPU>();
	switch (options.Algorithm)
	{
	case ESchedulerAlgorithm::RR:
		m_Scheduler = std::make_unique<RRScheduler>(m_CPU, options.QuantumTime);
		break;
	case ESchedulerAlgorithm::FCFS:
		m_Scheduler = std::make_unique<FCFSScheduler>(m_CPU);
		break;
	default:
		LOG_ASSERT(false, "Provided invalid scheduler algorithm");
	}
	
	ProducerProperties props = {options.Quantity, options.InitialQuantity, options.MinExpectedTime, options.MaxExpectedTime, options.SpawnChance, options.Seed };


	m_Producer = std::make_unique<ProcessProducer>(props, m_CPU);

	std::shared_ptr<Queue> queue = std::make_shared<Queue>();
	m_Producer->SetQueue(queue);
	m_Scheduler->SetQueue(queue);

	std::vector<std::string> headers = {"Created", "Started", "Finished","Elapsed", "Burst", "Work", "Wait"};
	m_Printer = std::make_unique<Printer>(headers, 8);
	m_Printer->PrintAlgorithm(options.Algorithm);
}

void SystemController::Run()
{
	m_Producer->Run();
	m_Scheduler->PassNextProcess();
	while (bActive)
	{
		m_CPU->Tick();
		if (!bNoMoreProcesses)
		{
			bNoMoreProcesses |= m_Producer->Tick();
		}
		if (m_Scheduler->IsActiveQueueEmpty() && bNoMoreProcesses && m_CPU->IsIdle())
		{
			bActive = false;
		}

	}
	std::unique_ptr<Queue> log = m_Scheduler->GetFinishedProcessesLog();

	std::sort(log->begin(), log->end(), [](const std::unique_ptr<Process>& ptr1, const std::unique_ptr<Process>& ptr2) {
		return ptr1->ID < ptr2->ID;
		}
	);
	m_Printer->PrintProcessLog(std::move(log));
}