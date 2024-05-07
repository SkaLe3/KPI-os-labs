#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Memory;

class SystemUI
{
public:
	void DisplayMenu();
	void Notify(const std::string& message);

	uint32_t RequestOption();
	uint32_t RequestPartitionId();
	uint32_t RequestProcessId();

	void DisplayMemory(std::shared_ptr<Memory> memory, uint32_t free);


private:

	std::string StringifyAddress(uint32_t address, uint32_t capacity);
	uint32_t MakeRequest(const std::string& object);
};