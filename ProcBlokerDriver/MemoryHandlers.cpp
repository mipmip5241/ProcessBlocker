#include <ntddk.h>

#include "MemoryHandlers.h"
#include "ProcBlock.h"

void* __cdecl operator new(size_t size)
{
	return ExAllocatePoolWithTag(PagedPool, size, constants::DRIVER_TAG);
}

void* __cdecl operator new[](size_t size)
{
	return ExAllocatePoolWithTag(PagedPool, size, constants::DRIVER_TAG);
}

void __cdecl operator delete(void* block) noexcept
{
	ExFreePool(block);
}

void __cdecl operator delete(void* block, size_t) noexcept
{
	ExFreePool(block);
}

void __cdecl operator delete[](void* block) noexcept
{
	ExFreePool(block);
}
