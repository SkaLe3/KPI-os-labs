#include "SystemController.h"
#include <iostream>

// temp
#include "Process.h"

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
		std::cout << "ERROR: Provided invalid scheduler algorithm" << std::endl;
		// @TODO: Make error logging
		break;
	}
	
	ProducerProperties props = {options.Quantity, options.InitialQuantity, options.MinExpectedTime, options.MaxExpectedTime };


	m_Producer = std::make_unique<ProcessProducer>(props, m_CPU);

	std::shared_ptr<Queue> queue = std::make_shared<Queue>();
	m_Producer->SetQueue(queue);
	m_Scheduler->SetQueue(queue);
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
	// @TODO: steal implementations of iterators from Game Engine Layer class
	for (int i = 0; i < 30; i++)
	{
		std::unique_ptr<Process> process = log->PopProcess();
		std::cout << "ID " << process->ID << "\tBurst " << process->BurstTime
			<< "\tWait " << process->WaitTime << "\tWork " << process->WorkTime
			<< "\tStart " << process->StartTime << "\tFinish " << process->FinishTime
			<< "\tCreation " << process->CreationTime << std::endl;
	}
}
