#include <ntddk.h>
#include <ntstrsafe.h>
#include "ProcBlock.h"

#include "Blacklist.h"
#include "Device.h"
#include "FastMutex.h"
#include "MemoryHandlers.h"
#include "Notifications.h"
#include "IrpHandler.h"
#include "ProcBlockerCommon.h"

DRIVER_UNLOAD proc_blocker_unload;

DRIVER_DISPATCH proc_blocker_create_close, proc_blocker_device_control;

Device* g_device;

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING)
{
	__try
	{
		g_device = new Device(driver_object);
		g_blacklist = new Blacklist();
		g_mutex.init();
		create_proc_notification();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	driver_object->DriverUnload = proc_blocker_unload;
	driver_object->MajorFunction[IRP_MJ_CREATE] = proc_blocker_create_close;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = proc_blocker_create_close;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = proc_blocker_device_control;

	KdPrint(("%s driver loaded\n", constants::DRIVER_PREFIX));
	return STATUS_SUCCESS;
}


void proc_blocker_unload(PDRIVER_OBJECT)
{
	delete g_device;
	delete g_blacklist;
	delete_proc_notification();
	KdPrint(("%s driver unloaded\n", constants::DRIVER_PREFIX));
}

NTSTATUS proc_blocker_create_close(PDEVICE_OBJECT, PIRP irp)
{
	return IrpHandler(irp).get_status();
}

NTSTATUS proc_blocker_device_control(PDEVICE_OBJECT, PIRP irp)
{
	IrpHandler handler(irp);
	switch (handler.get_stack()->Parameters.DeviceIoControl.IoControlCode)
	{
		case IOCTL_BLOCK_PROCESS:
			g_blacklist->add(static_cast<wchar_t*>(handler.get_stack()->Parameters.DeviceIoControl.Type3InputBuffer), handler.get_stack()->Parameters.DeviceIoControl.InputBufferLength);
			handler.set_info(handler.get_stack()->Parameters.DeviceIoControl.InputBufferLength);
			break;
		
		case IOCTL_UNBLOCK_PROCESS:
			g_blacklist->remove(static_cast<wchar_t*>(handler.get_stack()->Parameters.DeviceIoControl.Type3InputBuffer), handler.get_stack()->Parameters.DeviceIoControl.InputBufferLength);
			handler.set_info(handler.get_stack()->Parameters.DeviceIoControl.InputBufferLength);
			break;
		
		default:
			break;
	}
	return handler.get_status();
}