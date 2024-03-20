#include "SystemController.h"

#include <string>
#include <iostream>



int main(int argc, char* argv[])
{
	Options options;
	options.Quantity = 30;
	options.InitialQuantity = 3;
	options.MinExpectedTime = 0.5f;
	options.MaxExpectedTime = 10.0f;
	options.QuantumTime = 3.0f;

	for (size_t i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-sa" && i != argc-1)
		{
			options.Algorithm = Scheduler::scheduler_string_to_enum(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "-pq")
		{
			options.Quantity = atoi(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "-piq")
		{
			options.InitialQuantity = atoi(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "-qt")
		{
			options.QuantumTime = atoi(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "-mint")
		{
			options.MinExpectedTime = atoi(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "-maxt")
		{
			options.MaxExpectedTime = atoi(argv[i + 1]);
			++i;
		}
		else if (std::string(argv[i]) == "--help")
		{
			// @TODO: Help output
		}
		else
		{
			// @TODO: Create help output for wrong flags
		}
	}

	options.Algorithm = ESchedulerAlgorithm::FCFS;
	SystemController systemController(options);
	systemController.Run();

	return 0;
}