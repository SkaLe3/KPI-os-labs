#pragma once
#include <cstdint>
#include <memory>

class Process
{
public:
	static std::shared_ptr<Process> Create();

public:
	uint32_t Id;
	uint32_t Size;

	static uint32_t Count;
};