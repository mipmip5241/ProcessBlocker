#pragma once
#include "Blacklist.h"
#include "FastMutex.h"

namespace constants
{
	constexpr auto DRIVER_PREFIX = "ProcBlocker: ";
	constexpr auto DRIVER_TAG = 'prb';
}

inline Blacklist* g_blacklist;
inline FastMutex g_mutex;

