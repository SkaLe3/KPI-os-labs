#pragma once
#include <vector>
#include "Partition.h"
#include <memory>
#include <map>

class Process;

class Memory
{
public:
	Memory(uint32_t capacity);

	bool CreatePartition(std::shared_ptr<Process> process);
	bool AddToPartition(std::shared_ptr<Process> process, uint32_t partition);
	uint32_t Compress();
	bool ShiftPartitionOn(uint32_t id, uint32_t amount);
	void Unload(uint32_t partition, uint32_t process);
	void DeletePartition(uint32_t partition);

	uint32_t GetPartitionCount();
	uint32_t GetCapacity();

	Partition& operator[](uint32_t index);

	std::map<uint32_t, std::shared_ptr<Process>> GetMemoryMap();
private:
private:
	uint32_t m_Capacity;
	std::vector<Partition> m_Partitions;
};