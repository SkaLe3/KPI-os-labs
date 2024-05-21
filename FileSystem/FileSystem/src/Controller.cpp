#include "Controller.h"
#include <string>


void Controller::Run()
{
	uint32_t choice = 0;
	while (choice != 5)
	{
		m_UI.DisplayMenu();
		choice = m_UI.RequestOption();

		NodeData data = { 'a', 'a', '0' };

		std::string response;

		switch (choice)
		{
		case  1:
			m_UI.DisplayTree(m_Tree);
			response = "Tree printed";
			break;
		case 2:
			m_UI.RequestData(data);
			m_Tree.Insert(data);
			response = "Added";
			break;
		case 3:
			// Delete
			response = "Deleted";
			break;
		case 4:
			// Find
			response = "Found";
			break;
		case 5:
			m_UI.Exit();
			break;
		default:

			response = "Invalid option. Please select option between 1 and 5\n";
			break;

		}
		if (!response.empty())
			m_UI.Notify(response);
	}

}

