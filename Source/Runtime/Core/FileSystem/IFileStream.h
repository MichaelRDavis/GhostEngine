#pragma once

#include "Core.h"

enum EFileAccess
{
	Read,
	Write, 
};

enum EFileProperties
{
	Overwrite,
	New,
	Existing
};

class IFileStream
{
public:
	IFileStream();
	~IFileStream();

	void Open (const char* path, EFileAccess fileAccess, EFileProperties props);

	void Read(char* buffer);

	void Write(const char* buffer);

	void Close();

	GE_INLINE void* GetFileHandle() const { return m_fileHandle; }

private:
	void* m_fileHandle = nullptr;
};