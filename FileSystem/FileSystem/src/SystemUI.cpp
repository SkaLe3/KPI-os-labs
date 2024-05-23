#include "SystemUI.h"
#include <iostream>
#include <cctype>


void SystemUI::DisplayMenu()
{
	std::cout << "\n";
	std::cout << "================================\n";
	std::cout << "           MAIN MENU            \n";
	std::cout << "================================\n";
	std::cout << "1. Display Tree\n";
	std::cout << "2. Add node\n";
	std::cout << "3. Delete node\n";
	std::cout << "4. Find node\n";
	std::cout << "5. Exit\n";
	std::cout << "================================\n";
}


void SystemUI::DisplayTree(Tree& tree)
{
	tree.InOrder();
}

void SystemUI::DisplaySearchResult(SearchResult res)
{
	std::cout << "Search result:\n";
	std::cout << "Depth: " << res.Depth << "\n";
	std::cout << res.Data << "\n";

}

void SystemUI::Exit()
{
	std::cout << "Exiting program\n\n";
}

void SystemUI::Notify(const std::string& message)
{
	std::cout << "\t >>" << message << "\n";
}

uint32_t SystemUI::RequestOption()
{
	std::cout << "Enter your choice: ";
	char choice;
	std::cin >> choice;
	return (uint32_t)(choice - '0');
}

bool SystemUI::RequestData(NodeData& data)
{
	uint32_t letters = 0;
	uint32_t digits = 0;
	std::cout << "Enter identifier:\n";
	bool success = true;
	if (success)
		success &= ReadCharacter(data.C1, letters, digits);
	if (success)
		success &= ReadCharacter(data.C2, letters, digits);
	if (success)
		success &= ReadCharacter(data.C3, letters, digits);
	if (success)
	{
		std::cout << "Data filled!\n";
		return true;
	}
	else
	{
		std::cout << "Failed to fill data!\n";
		return false;
	}
}

bool SystemUI::ReadCharacter(char& c, uint32_t& lets, uint32_t& digs)
{
	do
	{
		c = getchar();
		if (c != ' ' && c != '\n')
		{
			if (!std::isalpha(c) && !std::isdigit(c))
				std::cout << "Incorrect character type\n";
		}
		if (std::isalpha(c))
			lets++;
		if (std::isdigit(c))
			digs++;
		if (lets > 2 || digs > 1)
		{
			std::cout << "Incorrect identifier\n";
			return false;
		}
		
	} while (!std::isalpha(c) && !std::isdigit(c));
	return true;
}
