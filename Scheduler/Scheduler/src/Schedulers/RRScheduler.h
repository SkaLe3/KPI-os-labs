#pragma once
#include "Scheduler.h"

class RRScheduler : public Scheduler
{
public:
	RRScheduler(std::weak_ptr<CPU> _cpu, float quantum);
	virtual void PassNextProcess() override;

private:
	float m_Quantum;
};