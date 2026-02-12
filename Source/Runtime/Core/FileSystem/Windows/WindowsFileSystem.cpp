#include "FileSystem/IFileSystem.h"

std::vector<char> IFileSystem::ReadFile(const char* path)
{
	// TODO: Replace with Win32 API 
	std::ifstream file(path, std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}