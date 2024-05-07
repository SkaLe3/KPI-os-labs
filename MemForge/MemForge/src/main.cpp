#include "SystemController.h"
#include <iostream>
#include <string>
void print_usage()
{
	std::cout << "Usage: memforge [OPTIONS]\n"
		<< "Options:\n"
		<< "  -c, --capacity  <value>    Set capacity\n"
		<< "  -p, --procs  <value>    Set processes number\n";
}

bool parse_args(int argc, char* argv[], int32_t& capacity, int32_t& procs)
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
		else if (arg == "-p" || arg == "--procs")
		{
			if (i + 1 < argc)
			{
				procs = std::stoi(argv[i + 1]);
				if (procs <= 0)
				{
					std::cerr << "Processes number must be a positive integer.\n";
					return false;
				}
				i++;
			}
			else
			{
				std::cerr << "Missing value for processes number.\n";
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
	int32_t processesNumber = 10;

	if (!parse_args(argc, argv, capacity, processesNumber))
	{
		print_usage();
		return 1;
	}
	SystemController system(capacity, processesNumber);
	system.Run();

	return 0;
}