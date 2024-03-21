#pragma once
#include "Process.h"

#include <functional>
#include <memory>

using DelegateFunctionParams1 = std::function<void(std::unique_ptr<Process>)>;
using DelegateFunctionParams0 = std::function<void()>;

class CPUDelegate
{
public:
	void Subscribe(DelegateFunctionParams1 func, int i)
	{
		functionParam = func;

	}
	void Subscribe(DelegateFunctionParams0 func)
	{
		functionNoParam = func;
	}
	void operator()(std::unique_ptr<Process> process) const {
		functionParam(std::move(process));
	}
	void operator()() const {
		functionNoParam();
	}
private:
	DelegateFunctionParams1 functionParam;
	DelegateFunctionParams0 functionNoParam;
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