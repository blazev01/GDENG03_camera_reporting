#include "Resource.h"

Resource::Resource(const wchar_t* fullPath)
{
	this->fullPath = fullPath;
}

Resource::~Resource()
{

}

std::wstring Resource::GetFilePath()
{
	return this->fullPath;
}
