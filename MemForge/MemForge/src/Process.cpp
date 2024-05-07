#include "Process.h"
#include <random>
#include <cmath>


std::shared_ptr<Process> Process::Create()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(2, 6);
	uint32_t size = std::pow(2, distribution(gen));

	return std::make_shared<Process>(Count++, size);
}

uint32_t Process::Count = 0;
