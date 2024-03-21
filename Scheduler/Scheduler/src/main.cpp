#include "SystemController.h"
#include "Log/Logger.h"
#include <string>



int main(int argc, char* argv[])
{
	Log::GetLogger()->Init();
	Options options;
	options.Quantity = 30;
	options.InitialQuantity = 3;
	options.MinExpectedTime = 0.5f;
	options.MaxExpectedTime = 10.0f;
	options.QuantumTime = 3.0f;
	options.SpawnChance = 0.5f;
	options.Seed = 5;
	options.Algorithm = ESchedulerAlgorithm::RR;

	for (size_t i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-sa" && i != argc-1)
		{
			options.Algorithm = Scheduler::scheduler_string_to_enum(argv[++i]);
		}
		else if (std::string(argv[i]) == "-pq")
		{
			options.Quantity = atoi(argv[++i]);
		}
		else if (std::string(argv[i]) == "-piq")
		{
			options.InitialQuantity = atoi(argv[++i]);
		}
		else if (std::string(argv[i]) == "-qt")
		{
			options.QuantumTime = atof(argv[++i]);
		}
		else if (std::string(argv[i]) == "-mint")
		{
			options.MinExpectedTime = atof(argv[++i]);
		}
		else if (std::string(argv[i]) == "-maxt")
		{
			options.MaxExpectedTime = atof(argv[++i]);
		}
		else if (std::string(argv[i]) == "-c")
		{
			options.SpawnChance = atof(argv[++i]);
		}
		else if (std::string(argv[i]) == "--seed")
		{
			options.Seed = atoi(argv[++i]);
		}
		else if (std::string(argv[i]) == "--help")
		{
			LOG_INFO("-sa [RR, FCFS]\t		- Scheduler algorithm");
			LOG_INFO("-pq <number>\t		- Processes quantity");
			LOG_INFO("-piq <number>\t		- Initial Processes quantity");
			LOG_INFO("-qt <number>\t		- Quantum time (RR)");
			LOG_INFO("-mint <number>\t		- Minimum burst time");
			LOG_INFO("-maxt <number>\t		- Maximum burst time");
			LOG_INFO("-c <number>\t			- Process spawn chance");
			LOG_INFO("--seed <number>\t		- Process spawn seed");
			LOG_INFO("--help \t				- Help");
		}
		else
		{
			LOG_INFO("-sa [RR, FCFS]\t		- Scheduler algorithm");
			LOG_INFO("-pq <number>\t		- Processes quantity");
			LOG_INFO("-piq <number>\t		- Initial Processes quantity");
			LOG_INFO("-qt <number>\t		- Quantum time (RR)");
			LOG_INFO("-mint <number>\t		- Minimum burst time");
			LOG_INFO("-maxt <number>\t		- Maximum burst time");
			LOG_INFO("-c <number>\t			- Process spawn chance");
			LOG_INFO("--seed <number>\t		- Process spawn seed");
			LOG_INFO("--help \t				- Help");
		}
	}
	SystemController systemController(options);
	systemController.Run();

	return 0;
}