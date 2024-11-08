#pragma once
#include "string"

class Resource
{
public:
	Resource(const wchar_t* fullPath);
	~Resource();

protected:
	std::wstring fullPath;
};

