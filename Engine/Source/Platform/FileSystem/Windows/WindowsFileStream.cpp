#include "Platform/FileSystem/IFileStream.h"

#ifdef GE_WINDOWS_PLATFORM
IFileStream::IFileStream()
{
	m_fileHandle = nullptr;
}

IFileStream::~IFileStream()
{	
	if (m_fileHandle != nullptr)
	{
		Close();
		m_fileHandle = nullptr;
	}
}

void IFileStream::Open(const char* path, EFileAccess fileAccess, EFileProperties props)
{
	DWORD accessFlag = 0;
	switch (fileAccess)
	{
	case EFileAccess::Read:
		accessFlag = GENERIC_READ;
		break;
	case EFileAccess::Write:
		accessFlag = GENERIC_WRITE;
		break;
	}

	DWORD creationFlag = 0;
	switch (props)
	{
	case EFileProperties::Overwrite:
		creationFlag = CREATE_ALWAYS;
		break;
	case EFileProperties::New:
		creationFlag = CREATE_NEW;
		break;
	case EFileProperties::Existing:
		creationFlag = OPEN_EXISTING;
		break;
	}

	m_fileHandle = CreateFileA(path, accessFlag, 0, nullptr, creationFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "Unable to create file", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}
}

void IFileStream::Read(char* buffer)
{
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "Unable to read file", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}

	DWORD bytesToRead = (DWORD)strlen(buffer);
	DWORD bytesRead = 0;
	if (ReadFile(m_fileHandle, buffer, bytesToRead, &bytesRead, nullptr))
	{
		MessageBoxA(nullptr, "Failed to read file", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}
}

void IFileStream::Write(const char* buffer)
{
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "Unable to write file", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}

	DWORD bytesToWrite = (DWORD)strlen(buffer);
	DWORD bytesWritten = 0;
	WriteFile(m_fileHandle, buffer, bytesToWrite, &bytesWritten, nullptr);
}

void IFileStream::Close()
{
	if (m_fileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_fileHandle);
	}
}
#endif