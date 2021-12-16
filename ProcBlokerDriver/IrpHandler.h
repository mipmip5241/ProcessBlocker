#pragma once

#include <ntddk.h>

class IrpHandler
{
public:
	IrpHandler(PIRP& irp);
	~IrpHandler();

	NTSTATUS get_status() const;
	PIO_STACK_LOCATION get_stack() const;
	ULONG get_ioctl();
	void set_status(NTSTATUS status);
	void set_info(ULONG_PTR info);

private:
	PIRP& irp_;
	PIO_STACK_LOCATION stack_;
	NTSTATUS status_;
	ULONG_PTR info_;
};

