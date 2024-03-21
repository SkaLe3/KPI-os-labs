#include "Printer.h"
#include "Log/Logger.h"

#include <iostream>
#include <iomanip>

Printer::Printer(std::vector<std::string> headers, uint32_t width) : m_Headers(headers), m_Width(width)
{
}

void Printer::PrintProcessLog(std::unique_ptr<Queue> queue)
{
	std::cout << std::fixed << std::setprecision(3);
	Header();

	size_t queueSize = queue->Size();
	float waitTime = 0;
	float elapsedTime = 0;

	while (queue->Size() > 0)
	{
		std::unique_ptr<Process> process = queue->PopProcess();
		size_t id = process->ID;
		float created = process->CreationTime;
		float started = process->StartTime;
		float finished = process->FinishTime;
		float elapsed = process->FinishTime - process->CreationTime;
		float burst = process->BurstTime;
		float work = process->WorkTime;
		float wait = process->WaitTime;
		Row(id, {created, started, finished, elapsed, burst, work, wait});
		waitTime += wait;
		elapsedTime += elapsed;
	}
	HorizontalLine();

	std::cout << "\n";
	std::cout << "Average Wait time: " << waitTime / (float)queueSize << "\n";
	std::cout << "Average Elapsed time: " << elapsedTime / (float)queueSize << "\n";

}

void Printer::PrintAlgorithm(ESchedulerAlgorithm algo)
{
	std::cout << "\n";
	switch (algo)
	{
	case ESchedulerAlgorithm::FCFS:
		std::cout << "Scheduler Algorithm: FCFS\n";
		break;
	case ESchedulerAlgorithm::RR:
		std::cout << "Scheduler Algorithm: RR\n";
		break;
	default:
		LOG_ERROR("Scheduler Algorithm isn't selected");
	}
}

void Printer::HorizontalLine() const
{
	std::cout << "+";
	std::cout << std::setw(3) << std::right << "---" << "+";
	for (int i = 0; i < m_Headers.size(); ++i) {
		std::cout << std::string(m_Width, '-') << "+";
	}
	std::cout << std::endl;
}

void Printer::Row(const std::string& first, const std::vector<std::string>& row) const
{
	std::cout << "|";
	std::cout << std::setw(3) << std::right << first << "|";
	for (const auto& cell : row) {
		std::cout << std::setw(m_Width) << std::right << cell << "|";
	}
	std::cout << std::endl;
}
void Printer::Row(size_t id, const std::vector<float>& row) const
{
	std::cout << "|";
	std::cout << std::setw(3) << std::right << id << "|";
	for (const auto& cell : row) {
		if (std::fabs(cell - std::trunc(cell)) < 0.000001)
			std::cout << std::fixed << std::setprecision(1);
		else
			std::cout << std::fixed << std::setprecision(3);
		std::cout << std::setw(m_Width) << std::right << cell << "|";
	}
	std::cout << std::endl;
}

void Printer::Header() const
{
	HorizontalLine();
	Row("ID", m_Headers);
	HorizontalLine();
}
