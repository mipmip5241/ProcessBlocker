#include "Device.h"

Device::Device(PDRIVER_OBJECT driver_object): device_(nullptr), sym_link_()
{
	UNICODE_STRING device_name;
	RtlInitUnicodeString(&device_name, Device::DEVICE_NAME);

	auto status = IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, 0, TRUE, &this->device_);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create device fail"));
		ExRaiseStatus(status);
	}

	RtlInitUnicodeString(&this->sym_link_, Device::SYM_LINK_NAME);

	status = IoCreateSymbolicLink(&this->sym_link_, &device_name);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Sym link creation fail"));
		IoDeleteDevice(this->device_);
		ExRaiseStatus(status);
	}

}

Device::~Device()
{
	IoDeleteSymbolicLink(&this->sym_link_);
	IoDeleteDevice(this->device_);
}
