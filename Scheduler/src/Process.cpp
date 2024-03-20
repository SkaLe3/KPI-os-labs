#include "Process.h"


Process::Process(size_t id, float burstTime, float creationTime)
	: ID(id), BurstTime(burstTime), RemainingTime(burstTime),
	State(EProcessState::Waiting), CreationTime(creationTime),
	StartTime(-1), FinishTime(-1), WorkTime(0), WaitTime(0)
{

}

void Process::Execute()
{
	if (RemainingTime > 0)
	{
		RemainingTime = RemainingTime - 1;
		WorkTime = WorkTime + 1;
	}
	
	if (RemainingTime <= 0)
	{
		State = EProcessState::Finished;
	}
}
