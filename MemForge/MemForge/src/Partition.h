#pragma once
#include "Process.h"

#include <memory>
#include <vector>

class Partition
{
public:
	Partition(uint32_t offset);

	void AddProcess(std::shared_ptr<Process> process);
	void DeleteProcess(uint32_t process);

	uint32_t GetSize();
	uint32_t GetProcessCount();

	uint32_t GetAdress(uint32_t process);

	std::shared_ptr<Process> operator[](uint32_t index);
	std::vector<std::shared_ptr<Process>>::iterator begin();
public:
	uint32_t Base = 0;

	std::vector<std::shared_ptr<Process>> m_Processes;
};