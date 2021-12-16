#include "FastMutex.h"

void FastMutex::init()
{
	ExInitializeFastMutex(&this->_mutex);
}

void FastMutex::lock()
{
	ExAcquireFastMutex(&this->_mutex);
}

void FastMutex::unlock()
{
	ExReleaseFastMutex(&this->_mutex);
}
