#include "Controller.h"
#include <string>


void Controller::Run()
{
	uint32_t choice = 0;
	while (choice != 5)
	{
		m_UI.DisplayMenu();
		choice = m_UI.RequestOption();

		NodeData data;

		std::string response;
		bool success;
		switch (choice)
		{
		case  1:
			m_UI.DisplayTree(m_Tree);
			response = "Tree printed";
			break;
		case 2:
			success = m_UI.RequestData(data);
			if (!success)
				break;
			m_Tree.Insert(data);
			response = "Added";
			break;
		case 3:
			success = m_UI.RequestData(data);
			if (!success)
				break;
			m_Tree.Remove(data);
			response = "Deleted";
			break;
		case 4:
			success = m_UI.RequestData(data);
			if (!success)
				break;
			SearchResult result = m_Tree.Search(data);
			response = "Search completed";
			m_UI.DisplaySearchResult(result);
			break;
		case 5:
			m_UI.Exit();
			break;
		default:

			response = "Invalid option. Please select option between 1 and 5\n";
			choice = 0;
			break;

		}
		if (!response.empty())
		{
			m_UI.Notify(response);
			response.clear();
		}
	}

}

