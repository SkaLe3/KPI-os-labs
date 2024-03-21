#pragma once
#include "ProcessProducer.h"
#include "Schedulers/Scheduler.h"
#include "Log/Printer.h"

#include <memory>

struct Options
{
	ESchedulerAlgorithm Algorithm = ESchedulerAlgorithm::None;

	size_t Quantity;
	size_t InitialQuantity;
	float MinExpectedTime;
	float MaxExpectedTime;

	float QuantumTime;

	float SpawnChance;
	int32_t Seed;
	bool RandomSeed;
};

class CPU;

class SystemController
{
public:
	SystemController(Options& options);
	void Run();

private:
	std::shared_ptr<CPU> m_CPU;
	std::unique_ptr<Scheduler> m_Scheduler;
	std::unique_ptr<ProcessProducer> m_Producer;
	std::unique_ptr<Printer> m_Printer;

	bool bNoMoreProcesses = false;
	bool bActive = true;
};