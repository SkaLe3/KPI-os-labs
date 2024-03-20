#pragma once
#include "Process.h"
#include <functional>
#include <memory>

using DelegateFunction = std::function<void(std::unique_ptr<Process>)>;

class CPUDelegate
{
public:
	void Subscribe(DelegateFunction func)
	{
		function_ = func;
	}
	void operator()(std::unique_ptr<Process> process) const {
		function_(std::move(process));
	}
private:
	DelegateFunction function_;
};

	
class CPU
{
public:
	void Tick();
	float GetCurrentTick();
	bool IsIdle();
	void ActivateQuantum(float qunatum);

	void Execute(std::unique_ptr<Process> process);

	CPUDelegate OnExecutionBreak;
private:
	float m_Tick;
	std::unique_ptr<Process> m_ActiveProcess;
	float m_QuantumLeft;
	float m_Quantum;
	bool bUseQuantum;
};