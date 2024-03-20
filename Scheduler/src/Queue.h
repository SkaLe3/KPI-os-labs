#pragma once
#include "Process.h"
#include <queue>
#include <memory>


class Queue
{
public:
	void PushProcess(std::unique_ptr<Process> process);
	std::unique_ptr<Process> PopProcess();

	bool Empty();

protected:
	std::queue<std::unique_ptr<Process>> m_ActiveProcesses;
};