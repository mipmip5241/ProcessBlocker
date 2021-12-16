#pragma once

#include <ntddk.h>

class Node
{
public:
	Node(const wchar_t* image_name, const size_t size);
	~Node();

	LIST_ENTRY entry;
	size_t image_len;
	wchar_t* image_name;
};


