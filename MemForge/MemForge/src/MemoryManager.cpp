#include "MemoryManager.h"
#include "Memory.h"

MemoryManager::MemoryManager(uint32_t capacity) : m_Capacity(capacity)
{}

void MemoryManager::CreateProcesses(uint32_t count)
{

	for (uint32_t i = 0; i < count; i++)
	{
		m_Processes.push_back(Process::Create());
	}
}

std::string MemoryManager::LoadNew()
{
	if (!m_Processes.empty())
	{
		std::shared_ptr<Process> loadedProcess = m_Processes[m_NextProcess];
		if (loadedProcess->Size < GetFreeMemorySize())
		{
			bool success = m_ManagedMemory->CreatePartition(loadedProcess);
			if (success)
			{
				m_Used += loadedProcess->Size;
				m_NextProcess++;
				return "Process loaded successfully";
			}
			else
				return "Failed to load a process";
		}
		else
			return "Not enough memory to load a process";
	}
	else
		return "Need to create new processes";
}

std::string MemoryManager::LoadExisting(uint32_t partition)
{
	if (partition < m_ManagedMemory->GetPartitionCount())
	{
		if (!m_Processes.empty())
		{
			std::shared_ptr<Process> loadedProcess = m_Processes[m_NextProcess];
			if (loadedProcess->Size < GetFreeMemorySize())
			{
				bool success = m_ManagedMemory->AddToPartition(loadedProcess, partition);
				if (success)
				{
					m_Used += loadedProcess->Size;
					m_NextProcess++;
					return "Process loaded successfully";
				}
				else
					return "Failed to load a process";
			}
			else
				return "Not enough memory to load a process";
		}
		else
			return "Need to create new processes";
	}
	else
		return "Invalid partition ID";
}

std::string MemoryManager::Unload(uint32_t partition, uint32_t process)
{
	if (partition >= m_ManagedMemory->GetPartitionCount())
		return "Invalid partition id";
	if (process >=(* m_ManagedMemory)[partition].GetProcessCount())
		return "Invalid process id";

	m_Used -= (*m_ManagedMemory)[partition][process]->Size;
	m_ManagedMemory->Unload(partition, process);
	return "Process unloaded";
}

void MemoryManager::SetMemory(std::shared_ptr<Memory> memory)
{
	m_ManagedMemory = memory;
}

uint32_t MemoryManager::GetFreeMemorySize()
{
	return m_Capacity - m_Used;
}
