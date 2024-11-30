#pragma once
#include "string"

class Resource
{
public:
	Resource(const wchar_t* fullPath);
	virtual ~Resource();

	std::wstring GetFilePath();

protected:
	std::wstring fullPath;
};

