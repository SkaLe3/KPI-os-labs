#pragma once
#include "Schedulers/RRScheduler.h"
#include "Schedulers/FCFSScheduler.h"
#include "ProcessProducer.h"
#include "CPU.h"

#include <memory>


struct Options
{
	ESchedulerAlgorithm Algorithm = ESchedulerAlgorithm::None;

	size_t Quantity;
	size_t InitialQuantity;
	float MinExpectedTime;
	float MaxExpectedTime;

	float QuantumTime = 3.0f;
};



class SystemController
{
public:
	SystemController(Options& options);
	void Run();

private:
	std::shared_ptr<CPU> m_CPU;
	std::unique_ptr<Scheduler> m_Scheduler;
	std::unique_ptr<ProcessProducer> m_Producer;

	bool bNoMoreProcesses = false;
	bool bActive = true;
};