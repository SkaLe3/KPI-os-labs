#pragma once
#include "Queue.h"
#include "Schedulers/Scheduler.h"

#include <vector>
#include <string>


class Printer
{
public:
	Printer(std::vector<std::string> headers, uint32_t width = 12);
	void PrintProcessLog(std::unique_ptr<Queue> queue);
	void PrintAlgorithm(ESchedulerAlgorithm algo);

private:
	void HorizontalLine() const;
	void Row(const std::string& first,  const std::vector<std::string>& row) const;
	void Row(size_t id, const std::vector<float>& row)const;
	void Header() const;

private:
	std::vector<std::string> m_Headers;
	uint32_t m_Width;
};