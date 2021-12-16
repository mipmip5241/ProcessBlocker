#pragma once
#include <ntddk.h>

class Blacklist
{
public:
	Blacklist();
	~Blacklist();

	void add(const wchar_t* image_name, const size_t len);
	void remove(const wchar_t* remove_image, const size_t len);
	bool is_blacklisted(const wchar_t* image_name, const size_t len);
	
private:
	static constexpr int LIMIT = 1024;

	LIST_ENTRY head_;
	int count_;

};

