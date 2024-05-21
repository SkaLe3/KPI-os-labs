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

void SystemUI::DisplayTree()
{

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
	uint32_t choice;
	std::cin >> choice;
	return choice;
}

void SystemUI::RequestData(NodeData& data)
{
	std::cout << "Enter identifier:\n";
	ReadCharacter(data.Letter1, [](int c)-> bool { return std::isalpha(c); });
	ReadCharacter(data.Letter2, [](int c)-> bool { return std::isalpha(c); });
	ReadCharacter(data.Digit, [](int c)-> bool { return std::isdigit(c); });
	std::cout << "Data filled!\n";
	data.Digit -= '0';
}

void SystemUI::ReadCharacter(char& c, const std::function<bool(int)>& function)
{
	do
	{
		if (c != ' ' && c != '\n')
		{
			if (!function(c))
				std::cout << "Incorrect character type\n";
		}
		c = getchar();
	} while (!function(c));
}
