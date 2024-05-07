#include "Partition.h"



Partition::Partition(uint32_t offset) : Base(offset)
{

}

void Partition::AddProcess(std::shared_ptr<Process> process)
{
	m_Processes.push_back(process);
}

void Partition::DeleteProcess(uint32_t process)
{
	m_Processes.erase(m_Processes.begin() + process);
}

uint32_t Partition::GetSize()
{
	uint32_t fullSize = 0;
	for (auto& process : m_Processes)
	{
		fullSize += process->Size;
	}

	return fullSize;
}

uint32_t Partition::GetProcessCount()
{
	return m_Processes.size();
}

uint32_t Partition::GetAdress(uint32_t process)
{
	uint32_t offset = 0;
	for (uint32_t i = 0; i < process; i++)
	{
		offset += m_Processes[i]->Size;
	}
	return Base + offset;
}

std::shared_ptr<Process> Partition::operator[](uint32_t index)
{
	return m_Processes[index];
}

std::vector<std::shared_ptr<Process>>::iterator Partition::begin()
{
	return m_Processes.begin();
}

