#pragma once

enum class EProcessState
{
	Waiting, Working, Finished
};

class Process
{
public:
	Process(size_t id, float burstTime, float creationTime);
	void Execute();

	size_t ID;
	float BurstTime;
	float RemainingTime;
	float WaitTime;
	float WorkTime;
	float StartTime;
	float FinishTime;
	float CreationTime;

	EProcessState State;
};