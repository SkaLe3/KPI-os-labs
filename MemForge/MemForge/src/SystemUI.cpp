#include "SystemUI.h"
#include "Memory.h"
#include <iostream>
#include <sstream>
#include <iomanip>

void SystemUI::DisplayMenu()
{
	std::cout << "\n";
	std::cout << "================================\n";
	std::cout << "           MAIN MENU            \n";
	std::cout << "================================\n";
	std::cout << "1. Memory info\n";
	std::cout << "2. Load process to new partition\n";
	std::cout << "3. Load process to existing partition\n";
	std::cout << "4. Unload process\n";
	std::cout << "5. Exit\n";
	std::cout << "================================\n";

}

uint32_t SystemUI::RequestOption()
{
	return MakeRequest("your choice");
}

void SystemUI::Notify(const std::string& message)
{
	std::cout << "\n--> " << message << "\n";
}

uint32_t SystemUI::RequestPartitionId()
{
	return MakeRequest("partition ID");
}

uint32_t SystemUI::RequestProcessId()
{
	return MakeRequest("process ID");
}

uint32_t SystemUI::MakeRequest(const std::string& object)
{
	std::cout << "Enter " << object << ": ";
	uint32_t choice;
	std::cin >> choice;
	return choice;
}

void SystemUI::DisplayMemory(std::shared_ptr<Memory> memory, uint32_t free)
{
	std::string ind = "\t";

	std::cout << "\nMemory image:\n";

	std::map<uint32_t, std::shared_ptr<Process>> memoryMap = memory->GetMemoryMap();

	uint32_t addressDigits = std::log2(memory->GetCapacity()) / 4;
	std::cout << ind << std::left << std::setw(10) << "Process ID" << " | ";
	std::cout << std::left << std::setw(addressDigits + 2 + 7) << "Address" << " | ";
	std::cout << std::left << std::setw(6) << "Size" << std::endl;

	for (std::pair<uint32_t, std::shared_ptr<Process>> process : memoryMap)
	{
		std::cout << ind << std::left << std::setw(10) << process.second->Id << " | ";
		std::cout << std::left << std::setw(addressDigits + 2 + 7) << StringifyAddress(process.first, memory->GetCapacity()) << " | ";
		std::cout << std::left << std::dec << std::setw(6) << process.second->Size << std::endl;
	}

	std::cout << ind << "-------------------------------------------\n";


	ind = "";
	std::cout << ind << "\nMemory info: \n";
	std::cout << ind << "Capacity: " << memory->GetCapacity() << "\n";
	std::cout << ind << "Used: " << memory->GetCapacity() - free << "\n";
	std::cout << ind << "Free: " << free << "\n";
	std::cout << ind << "Partitions: " << memory->GetPartitionCount() << "\n";
	ind = "\t";

	for (uint32_t i = 0; i < memory->GetPartitionCount(); i++)
	{
		Partition& cp = (*memory)[i];
		std::cout << ind << "========== Partition [" << i << "] ==========\n";
		ind = "\t\t";
		std::cout << ind << "Base: " << cp.Base << "\n";
		std::cout << ind << "Size: " << cp.GetSize() << "\n";
		std::cout << ind << "Processes: " << cp.GetProcessCount() << "\n\n";

		for (uint32_t j = 0; j < cp.GetProcessCount(); j++)
		{
			std::cout << ind << "========== Process [" << j << "] ==========\n";
			ind = "\t\t\t";
			uint32_t address = cp.GetAdress(j);
			std::cout << ind << "Address: " << StringifyAddress(address, memory->GetCapacity()) << "\n";
			std::cout << ind << "Id: " << cp[j]->Id << "\n";
			std::cout << ind << "Size: " << cp[j]->Size << "\n\n";
			ind = "\t\t";
		}
		ind = "\t";

	}
}

std::string SystemUI::StringifyAddress(uint32_t address, uint32_t capacity)
{
	uint32_t power = std::log2(capacity);
	int digits = power / 4;
	if (power % 4 != 0)
		digits++;

	std::stringstream ss;
	ss << "0x" << std::setfill('0') << std::setw(digits) << std::hex << address;
	return ss.str();
}
