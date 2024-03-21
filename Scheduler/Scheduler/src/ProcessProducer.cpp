#include "ProcessProducer.h"
#include "CPU.h"

ProcessProducer::ProcessProducer(ProducerProperties& props, std::weak_ptr<CPU> _cpu) : 
	m_Properties(props), m_NextID(1), m_CPU(_cpu)
{
	if (m_Properties.Seed == 0)
	{
		m_RandomProcessSpawn.seed(std::random_device{}());
		m_RandomBurstTime.seed(std::random_device{}());
	}
	else
	{
		m_RandomProcessSpawn.seed(m_Properties.Seed);
		m_RandomBurstTime.seed(m_Properties.Seed);
	}
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
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	float randomNum = distribution(m_RandomProcessSpawn);

	if (randomNum < m_Properties.SpawnChance)
	{
		return CreateProcess();
	}
	else 
	{
		return false;
	}
}


bool ProcessProducer::CreateProcess()
{
	std::uniform_real_distribution<float> processTimeDist(m_Properties.MinExpectedTime, m_Properties.MaxExpectedTime);

	float currentTick;
	if (auto lockedCPU = m_CPU.lock()) {
		currentTick = lockedCPU->GetCurrentTick();
	}
	auto process = std::make_unique<Process>(m_NextID++, processTimeDist(m_RandomBurstTime), currentTick);
	m_Queue->PushProcess(std::move(process));
	m_Properties.ProcessesQuantity--;

	if (!m_Properties.ProcessesQuantity == 0)
	{
		// Not last process
		return false;
	}
	// last process
	return true;
}
