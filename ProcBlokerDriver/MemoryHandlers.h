#pragma once

void* __cdecl  operator new(size_t size);

void* __cdecl operator new[](size_t size);


void __cdecl operator delete(void* block) noexcept;

void __cdecl operator delete(void* block, size_t) noexcept;

void __cdecl operator delete[](void* block) noexcept;
