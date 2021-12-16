#pragma once

#include <ntddk.h>

class Device
{
public:
	Device(PDRIVER_OBJECT driver_object);
	~Device();

private:
	static inline const wchar_t* const DEVICE_NAME = L"\\Device\\procblock";
	static inline const wchar_t* const SYM_LINK_NAME = L"\\??\\procblock";

	PDEVICE_OBJECT device_;
	UNICODE_STRING sym_link_;
};

