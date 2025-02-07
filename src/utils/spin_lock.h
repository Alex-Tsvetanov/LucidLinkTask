#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include <atomic>
#include <thread>

class spin_lock {
public:
	spin_lock() : flag() {}

	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));  // Spin until lock is acquired
	}

	void unlock() { flag.clear(std::memory_order_release); }

private:
	std::atomic_flag flag;
};

#endif  // SPIN_LOCK_H