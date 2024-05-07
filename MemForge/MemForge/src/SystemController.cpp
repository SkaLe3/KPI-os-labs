#include "SystemController.h"
#include <iostream>



SystemController::SystemController(uint32_t memoryCapacity, uint32_t procs) : m_Manager(memoryCapacity), m_ProcsNumber(procs), m_Memory(std::make_shared<Memory>(memoryCapacity))
{

}

void SystemController::Run()
{
	m_Manager.SetMemory(m_Memory);
	m_Manager.CreateProcesses(m_ProcsNumber);

	uint32_t choice = 0;
	while (choice != 5)
	{
		m_UI.DisplayMenu();
		choice = m_UI.RequestOption();

		std::string response;

		switch (choice)
		{
		case 1:
		{
			m_UI.DisplayMemory(m_Memory, m_Manager.GetFreeMemorySize());
			response = "Memory printed";
			break;
		}
		case 2:
		{
			response = m_Manager.LoadNew();
			break;
		}
		case 3:
		{
			uint32_t partitionID = m_UI.RequestPartitionId();
			response = m_Manager.LoadExisting(partitionID);
			break;
		}
		case 4:
		{
			uint32_t partitionID = m_UI.RequestPartitionId();
			uint32_t processID = m_UI.RequestProcessId();
			response = m_Manager.Unload(partitionID, processID);
			break;
		}
		case 5:
		{
			std::cout << "Exiting program. Goodbye!\n\n";
			break;
		}
		default:
		{
			std::cout << "Invalid option. Please enter a number between 1 and 5.\n\n";
		}
		}
		if (!response.empty())
		{
			m_UI.Notify(response);
		}
	}
}

