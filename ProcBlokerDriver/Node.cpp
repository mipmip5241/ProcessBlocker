#include "Node.h"

Node::Node(const wchar_t* image_name, const size_t size) : entry(), image_len(size)
{
	this->image_name = new wchar_t[image_len + 1];
	memcpy(this->image_name, image_name, image_len + 1);
}

Node::~Node()
{
	delete this->image_name;
}

