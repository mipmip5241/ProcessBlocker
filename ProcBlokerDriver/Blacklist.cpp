#include "Blacklist.h"

#include "LockGuard.h"
#include "Node.h"
#include "ProcBlock.h"

Blacklist::Blacklist() : head_(), count_(0)
{
	InitializeListHead(&this->head_);
}

Blacklist::~Blacklist()
{
	while (!IsListEmpty(&this->head_))
		delete CONTAINING_RECORD(RemoveHeadList(&this->head_), Node, entry);
	

}

void Blacklist::add(const wchar_t* image_name,  const size_t len)
{
	LockGuard lock(g_mutex);
	if (count_ > LIMIT)
	{
		delete CONTAINING_RECORD(RemoveHeadList(&this->head_), Node, entry);
		this->count_--;
	}

	if(!this->is_blacklisted(image_name, len))
	{
		auto info = new Node(image_name, len);
		InsertHeadList(&this->head_, &info->entry);
		this->count_++;
	}
}

void Blacklist::remove(const wchar_t* remove_image,  const size_t len)
{
	LockGuard lock(g_mutex);
	LIST_ENTRY* current_node = head_.Flink;
	while (current_node != &head_) 
	{
		auto data = CONTAINING_RECORD(current_node, Node, entry);
		if((len == data->image_len) && (memcmp(remove_image, data->image_name, data->image_len) == 0))
		{
			RemoveEntryList(current_node);
			delete data;
			break;
		}
		current_node = current_node->Flink;
	}
}

bool Blacklist::is_blacklisted(const wchar_t* image_name, const size_t len)
{
	LIST_ENTRY* current_node = head_.Flink;
	while (current_node != &head_)
	{
		auto data = CONTAINING_RECORD(current_node, Node, entry);
		if ((len == data->image_len) && (memcmp(image_name, data->image_name, data->image_len) == 0))
		{
			return true;
		}
		current_node = current_node->Flink;
	}
	return false;
}
