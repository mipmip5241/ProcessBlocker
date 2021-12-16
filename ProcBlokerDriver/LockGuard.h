#pragma once

template<typename TLock>
class LockGuard
{
public:

	LockGuard(TLock& lock)
		: _lock(lock)
	{
		this->_lock.lock();
	}

	~LockGuard()
	{
		this->_lock.unlock();
	}

private:
	TLock& _lock;
};
