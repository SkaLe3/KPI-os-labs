#pragma once
#include "Process.h"

#include <deque>
#include <memory>


class Queue
{
public:
	void PushProcess(std::unique_ptr<Process> process);
	std::unique_ptr<Process> PopProcess();

	bool Empty();
	size_t Size();

	std::deque<std::unique_ptr<Process>>::iterator begin() { return m_ActiveProcesses.begin(); }
	std::deque<std::unique_ptr<Process>>::iterator end() { return m_ActiveProcesses.end(); }

protected:
	std::deque<std::unique_ptr<Process>> m_ActiveProcesses;
};