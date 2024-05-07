#include "Memory.h"
#include <iostream>


Memory::Memory(uint32_t capacity)
{
	m_Capacity = capacity;
}

bool Memory::CreatePartition(std::shared_ptr<Process> process)
{
	uint32_t offset = 0;
	if (!m_Partitions.empty())
		offset = m_Partitions.back().Base + m_Partitions.back().GetSize();
	if (process->Size + offset > m_Capacity)
	{
		offset = Compress();
		if (process->Size + offset > m_Capacity)
			return false;
	}

	Partition newPartition(offset);
	newPartition.AddProcess(process);
	m_Partitions.push_back(newPartition);
	return true;
}

bool Memory::AddToPartition(std::shared_ptr<Process> process, uint32_t partition)
{
	if (partition >= m_Partitions.size())
		return false;

	if (partition + 1 < m_Partitions.size()) // Not the last
	{
		if (process->Size + m_Partitions[partition].Base + m_Partitions[partition].GetSize() <= m_Partitions[partition + 1].Base) // If fits
		{
			m_Partitions[partition].AddProcess(process);
		}
		else
		{
			Compress();
			bool success = ShiftPartitionOn(partition, process->Size);
			if (!success)
				return false;
			m_Partitions[partition].AddProcess(process);
		}
	}
	else // The last
	{
		if (process->Size + m_Partitions[partition].Base + m_Partitions[partition].GetSize() <= m_Capacity)
		{
			m_Partitions[partition].AddProcess(process);
		}
		else
		{
			uint32_t offset = Compress();
			if (offset + process->Size > m_Capacity)
				return false;
			m_Partitions[partition].AddProcess(process);
		}
	}
	return true;
}

uint32_t Memory::Compress()
{
	for (uint32_t i = 1; i < m_Partitions.size(); i++)
	{
		if (m_Partitions[i].Base > (m_Partitions[i - 1].Base + m_Partitions[i - 1].GetSize()))
		{
			uint32_t diff = m_Partitions[i].Base - (m_Partitions[i - 1].Base + m_Partitions[i - 1].GetSize());
			m_Partitions[i].Base -= diff;
		}
	}
	uint32_t offset = m_Partitions.back().Base + m_Partitions.back().GetSize();
	std::cout << "--> Compressed!\n";
	return offset;
}

uint32_t Memory::GetPartitionCount()
{
	return m_Partitions.size();
}

uint32_t Memory::GetCapacity()
{
	return m_Capacity;
}

Partition& Memory::operator[](uint32_t index)
{
	return m_Partitions[index];
}

std::map<uint32_t, std::shared_ptr<Process>> Memory::GetMemoryMap()
{
	std::map<uint32_t, std::shared_ptr<Process>> memoryMap;

	for (uint32_t i = 0; i < m_Partitions.size(); i++)
	{
		Partition& cp = m_Partitions[i];
		for (uint32_t j = 0; j < cp.GetProcessCount(); j++)
		{
			uint32_t address = cp.GetAdress(j);
			memoryMap[address] = cp[j];
		}
	}
	return memoryMap;
}

bool Memory::ShiftPartitionOn(uint32_t id, uint32_t amount)
{
	if (m_Partitions.back().Base + m_Partitions.back().GetSize() + amount > m_Capacity)
		return false;

	for (uint32_t i = id + 1; i < m_Partitions.size(); i++)
	{
		m_Partitions[i].Base += amount;
	}
	return true;
}

std::shared_ptr<Process> Memory::Unload(uint32_t partition, uint32_t process)
{
	Partition& part = m_Partitions[partition];
	std::shared_ptr<Process> proc;
	if (part.GetProcessCount() == 1)
	{
		proc = DeletePartition(partition);
	}
	else
	{
		proc = part.DeleteProcess(process);
	}
	return proc;
}

std::shared_ptr<Process> Memory::DeletePartition(uint32_t partition)
{
	std::shared_ptr<Process> process = m_Partitions[partition][0];
	m_Partitions.erase(m_Partitions.begin() + partition);
	return process;
}
