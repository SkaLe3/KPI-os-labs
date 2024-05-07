#pragma once
#include "SystemUI.h"
#include "MemoryManager.h"
#include "Memory.h"

#include <memory>

class SystemController
{
public:
	SystemController(uint32_t memoryCapacity);
	void Run();

private:

private:
	SystemUI m_UI;
	MemoryManager m_Manager;
	std::shared_ptr<Memory> m_Memory;
	
};