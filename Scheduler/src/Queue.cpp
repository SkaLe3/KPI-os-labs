#include "Queue.h"


void Queue::PushProcess(std::unique_ptr<Process> process)
{
	m_ActiveProcesses.push(std::move(process));
}

std::unique_ptr<Process> Queue::PopProcess()
{
	std::unique_ptr<Process> process = std::move(m_ActiveProcesses.front());
	m_ActiveProcesses.pop();
	return process;

}

bool Queue::Empty()
{
	return m_ActiveProcesses.empty();
}

