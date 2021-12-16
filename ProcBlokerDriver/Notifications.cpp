#include <ntddk.h>
#include "Notifications.h"
#include "LockGuard.h"
#include "ProcBlock.h"

void on_process_notify(PEPROCESS, HANDLE, PPS_CREATE_NOTIFY_INFO create_info);

void create_proc_notification()
{
	const auto status = PsSetCreateProcessNotifyRoutineEx(on_process_notify, FALSE);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("%s Process create notification routine fail", constants::DRIVER_PREFIX));
		ExRaiseStatus(status);
	}
}

void delete_proc_notification()
{
	PsSetCreateProcessNotifyRoutineEx(on_process_notify, TRUE);
}

void on_process_notify(PEPROCESS, HANDLE, PPS_CREATE_NOTIFY_INFO create_info)
{
	LockGuard lock(g_mutex);
	if((create_info && create_info->FileOpenNameAvailable) && (g_blacklist->is_blacklisted(create_info->ImageFileName->Buffer, create_info->ImageFileName->Length)))
	{
		create_info->CreationStatus = STATUS_ACCESS_DENIED;
	}
}
