#pragma once

class TestAndSetLock
{
public:
	TestAndSetLock() : flag(false) {}

	void lock()
	{
		while (testAndSet(&flag))
		{
			// Spin until the lock is acquired
		}
	}

	void unlock()
	{
		flag.store(false, std::memory_order_release);
	}

private:
	bool testAndSet(std::atomic<bool>* target)
	{
		bool expected = false;
		return !target->compare_exchange_strong(expected, true);
		// if common == false : local = false; common = true
		// else local = true
		
		// if target == expected : target = true; return false;
		// else return true 

		// which is --> local = common; common = true
	}

	std::atomic<bool> flag;
};