#pragma once
#include "Process.h"

#include <deque>
#include <memory>
#include <string>

class Memory;

class MemoryManager
{
public:
	MemoryManager(uint32_t capacity);

	void CreateProcesses(uint32_t count);

	std::string LoadNew();
	std::string LoadExisting(uint32_t partition);
	std::string Unload(uint32_t partition, uint32_t process);

	void SetMemory(std::shared_ptr<Memory> memory);
	uint32_t GetFreeMemorySize();
private:
	uint32_t m_Capacity;
	uint32_t m_Used = 0;

	std::deque<std::shared_ptr<Process>> m_Processes;

	std::shared_ptr<Memory> m_ManagedMemory;

};