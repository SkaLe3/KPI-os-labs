#include "SystemController.h"
#include <iostream>
#include <string>
void print_usage()
{
	std::cout << "Usage: memforge [OPTIONS]\n"
		<< "Options:\n"
		<< "  -c, --capacity  <value>    Set capacity\n";
}

bool parse_args(int argc, char* argv[], int32_t& capacity)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "-c" || arg == "--capacity")
		{
			if (i + 1 < argc)
			{
				capacity = std::stoi(argv[i + 1]);
				if (capacity <= 0)
				{
					std::cerr << "Capacity must be a positive integer.\n";
					return false;
				}
				i++; 
			}
			else
			{
				std::cerr << "Missing value for capacity.\n";
				return false;
			}
		}
		else
		{
			std::cerr << "Unknown option: " << arg << "\n";
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	int32_t capacity = 256;

	if (!parse_args(argc, argv, capacity))
	{
		print_usage();
		return 1;
	}
	SystemController system(capacity);
	system.Run();

	return 0;
}