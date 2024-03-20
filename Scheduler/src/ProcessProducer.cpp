#include "ProcessProducer.h"
#include "CPU.h"
#include <random>


ProcessProducer::ProcessProducer(ProducerProperties& props, std::weak_ptr<CPU> _cpu) : m_Properties(props), m_NextID(1), m_CPU(_cpu)
{

}


void ProcessProducer::SetQueue(std::shared_ptr<Queue> queue)
{
	m_Queue = queue;
}

void ProcessProducer::Run()
{
	for (size_t i = 0; i < m_Properties.InitialProcessesQuantity; i++)
	{
		CreateProcess();
	}
}



bool ProcessProducer::Tick()
{
	// @TODO: Make random
// Possibility of process spawn  (from 1 spawn on 5 ticks to 3 spawns on 1 tick)
	return CreateProcess();
}


bool ProcessProducer::CreateProcess()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> processTimeDist(m_Properties.MinExpectedTime, m_Properties.MaxExpectedTime);

	float currentTick;
	if (auto lockedCPU = m_CPU.lock()) {
		currentTick = lockedCPU->GetCurrentTick();
	}
	auto process = std::make_unique<Process>(m_NextID++, processTimeDist(mt), currentTick);
	m_Queue->PushProcess(std::move(process));
	m_Properties.ProcessesQuantity--;

	if (!m_Properties.ProcessesQuantity == 0)
	{
		// Not last process
		return false;
	}
	// Not last process
	return true;
}
