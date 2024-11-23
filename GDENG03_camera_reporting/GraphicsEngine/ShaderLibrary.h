#pragma once
#include "string"
#include "unordered_map"
#include "VertexShader.h"
#include "PixelShader.h"

class ShaderLibrary
{
	typedef std::unordered_map<std::wstring, VertexShader*> VSTable;
	typedef std::unordered_map<std::wstring, PixelShader*> PSTable;

public:
	static void Initialize();
	static void Destroy();

	static void RequestVertexShaderData(std::wstring vsPath, void** shaderBytes, size_t* shaderSize);
	static void GetMeshLayout(void** shaderBytes, size_t* shaderSize);

	static VertexShader* GetVertexShader(std::wstring vsPath);
	static PixelShader* GetPixelShader(std::wstring psPath);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	ShaderLibrary& operator=(ShaderLibrary const&) {};

	static ShaderLibrary* instance;

	VSTable activeVS;
	PSTable activePS;

	unsigned char meshLayoutBytes[1024];
	size_t meshLayoutSize = 0;
};

