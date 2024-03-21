#pragma once
#include "Queue.h"

#include <memory>
#include <random>

class CPU;

struct ProducerProperties
{
	size_t ProcessesQuantity;
	size_t InitialProcessesQuantity;
	float MinExpectedTime;
	float MaxExpectedTime;

	float SpawnChance;
	int32_t Seed;
};


class ProcessProducer
{
public:
	ProcessProducer(ProducerProperties& props, std::weak_ptr<CPU> _cpu);

	void SetQueue(std::shared_ptr<Queue> queue);
	void Run();
	bool Tick();

private:
	bool CreateProcess();

private:
	std::shared_ptr<Queue> m_Queue;
	std::weak_ptr<CPU> m_CPU;

	ProducerProperties m_Properties;
	size_t m_NextID;

	std::mt19937 m_RandomProcessSpawn;
	std::mt19937 m_RandomBurstTime;


};