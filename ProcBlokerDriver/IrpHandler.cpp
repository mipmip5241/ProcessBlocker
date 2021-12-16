#include "IrpHandler.h"

#include "ProcBlockerCommon.h"

IrpHandler::IrpHandler(PIRP& irp)
: irp_(irp), stack_(IoGetCurrentIrpStackLocation(irp)), status_(STATUS_SUCCESS), info_(0) {}

IrpHandler::~IrpHandler()
{
    this->irp_->IoStatus.Status = this->status_;
    this->irp_->IoStatus.Information = this->info_;
    IoCompleteRequest(this->irp_,IO_NO_INCREMENT);
}

NTSTATUS IrpHandler::get_status() const
{
	return this->status_;
}

PIO_STACK_LOCATION IrpHandler::get_stack() const
{
	return this->stack_;
}

ULONG IrpHandler::get_ioctl() 
{
	if ((this->stack_->Parameters.DeviceIoControl.IoControlCode != IOCTL_BLOCK_PROCESS)
		&& (this->stack_->Parameters.DeviceIoControl.IoControlCode != IOCTL_UNBLOCK_PROCESS))
	{
		this->status_ = STATUS_INVALID_DEVICE_REQUEST;
	}

	return this->stack_->Parameters.DeviceIoControl.IoControlCode;
}

void IrpHandler::set_status(const NTSTATUS status)
{
	this->status_ = status;
}

void IrpHandler::set_info(const ULONG_PTR info)
{
	this->info_ = info;
}
