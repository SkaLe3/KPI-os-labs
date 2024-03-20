#pragma once
#include "Queue.h"
#include "CPU.h"
#include <memory>
#include <string>

enum class ESchedulerAlgorithm
{
	None, RR, FCFS
};



class Scheduler
{
public:
	Scheduler(std::weak_ptr<CPU> _cpu);

	void SetQueue(std::shared_ptr<Queue> queue);
	void OnExecutionBreak(std::unique_ptr<Process> process);
	bool IsActiveQueueEmpty();

	virtual void PassNextProcess() = 0;


	std::unique_ptr<Queue> GetFinishedProcessesLog();


	static ESchedulerAlgorithm scheduler_string_to_enum(const std::string& algo);

protected:
	std::shared_ptr<Queue> m_ActiveQueue;
	std::unique_ptr<Queue> m_FinishedLog;

	std::weak_ptr<CPU> m_CPU;

};