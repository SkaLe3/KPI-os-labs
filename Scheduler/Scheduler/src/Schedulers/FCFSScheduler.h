#pragma once
#include "Scheduler.h"


class FCFSScheduler : public Scheduler
{
public:
	FCFSScheduler(std::weak_ptr<CPU> _cpu);
	virtual void PassNextProcess() override;
};