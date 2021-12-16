#include <iostream>
#include <Windows.h>
#include "../ProcBlokerDriver/ProcBlockerCommon.h"

int print_error(const char* msg);


int main(int arc , char** argv)
{
	if (arc < 3)
	{
		std::cout << "Usage: -b = block , -u = unblock; image path" << std::endl;
	}
	std::string image_path("\\??\\");
	image_path += argv[2];
	std::wstring image_path_wide(image_path.begin(), image_path.end());
	if ((strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-u") == 0) && !image_path_wide.empty())
	{
		HANDLE file_handle = CreateFile(L"\\\\.\\procblock", FILE_ANY_ACCESS, 0, nullptr, OPEN_EXISTING, 0, nullptr);
		if (file_handle == INVALID_HANDLE_VALUE)
			return print_error("Failed to open file");

		BOOL res = FALSE;
		std::cout << image_path << std::endl;
		std::wcout << image_path_wide << std::endl;
		if (strcmp(argv[1], "-b") == 0)
		{
			res = DeviceIoControl(file_handle, IOCTL_BLOCK_PROCESS, image_path_wide.data(), image_path_wide.length()*2, nullptr, NULL, nullptr, nullptr);

			if (res)
				std::cout << "process block succeeded!" << std::endl;
			else
				print_error("process block failed!");
		}
		if (strcmp(argv[1], "-u") == 0)
		{
			res = DeviceIoControl(file_handle, IOCTL_UNBLOCK_PROCESS, image_path_wide.data(), image_path_wide.length()*2, nullptr, NULL, nullptr, nullptr);

			if (res)
				std::cout << "process unblock succeeded!" << std::endl;
			else
				print_error("process unblock failed!");
		}

		CloseHandle(file_handle);
	}
	else
	{
		std::cout << "Usage: -b = block , -u = unblock; image path" << std::endl;
	}
}


int print_error(const char* msg)
{
	printf("%s error code = %lu\n", msg, GetLastError());
	return 1;
}