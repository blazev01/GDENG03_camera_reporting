#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "filesystem"
#include "VertexMesh.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/ShaderLibrary.h"

Mesh::Mesh(const wchar_t* fullPath) : Resource(fullPath)
{
	std::cout << "Loading mesh..." << "\n";

	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto inputFile = std::filesystem::path(fullPath).string();

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputFile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created.");
	if (!res) throw std::exception("Mesh not created.");

	std::vector<VertexMesh> vertexList;
	std::vector<unsigned int> indexList;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		size_t indexOffset = 0;
		vertexList.reserve(shapes[i].mesh.indices.size());
		indexList.reserve(shapes[i].mesh.indices.size());

		for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); j++)
		{
			unsigned char numFaceVerts = shapes[i].mesh.num_face_vertices[j];
			for (unsigned char k = 0; k < numFaceVerts; k++)
			{
				tinyobj::index_t index = shapes[i].mesh.indices[indexOffset + k];

				Vector3D position;
				tinyobj::real_t x = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t y = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t z = attribs.vertices[index.vertex_index * 3 + 2];
				position = Vector3D(x, y, z);

				Vector2D texcoord;
				if (!attribs.texcoords.empty())
				{
					tinyobj::real_t u = attribs.texcoords[index.texcoord_index * 2 + 0];
					tinyobj::real_t v = attribs.texcoords[index.texcoord_index * 2 + 1];
					texcoord = Vector2D(u, v);
				}

				VertexMesh vertex(position, texcoord);
				vertexList.push_back(vertex);
				indexList.push_back(indexOffset + k);
			}

			indexOffset += numFaceVerts;
		}
	}

	void* shaderBytes = nullptr;
	size_t shaderSize = 0;

	ShaderLibrary::GetMeshLayout(&shaderBytes, &shaderSize);

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	this->vertexBuffer->Load(&vertexList[0], sizeof(VertexMesh), vertexList.size(), shaderBytes, shaderSize);
	this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
	this->indexBuffer->Load(&indexList[0], indexList.size());

	std::cout << "Mesh loaded." << "\n";
}

Mesh::~Mesh()
{
	if (this->vertexBuffer) this->vertexBuffer->Release();
	if (this->indexBuffer) this->indexBuffer->Release();
}

VertexBuffer* Mesh::GetVertexBuffer()
{
	return this->vertexBuffer;
}

IndexBuffer* Mesh::GetIndexBuffer()
{
	return this->indexBuffer;
}
