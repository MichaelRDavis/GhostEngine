#include "OpenGLGDI.h"

#ifdef GE_OPENGL_RENDERER
#include <glad/glad.h>

COpenGLGDI::COpenGLGDI()
{
	mContext = nullptr;
	mRenderSurface = {};
}

COpenGLGDI::~COpenGLGDI()
{
	Destroy();
}

void COpenGLGDI::Init(const FRenderSurface& surface)
{
	mRenderSurface = surface;

	mContext = SDL_GL_CreateContext(surface.surfaceWindow);
	if (mContext == nullptr)
	{
		printf("SDL OpenGL context creation failed! Error: %s\n", SDL_GetError());
		return;
	}

	SDL_GL_MakeCurrent(surface.surfaceWindow, mContext);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("glad failed to intialize!\n");
		return;
	}
}

void COpenGLGDI::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(mRenderSurface.surfaceWindow);
}

void COpenGLGDI::Destroy()
{
	SDL_GL_DestroyContext(mContext);
}

void COpenGLGDI::SubmitMesh(const FMesh& mesh)
{
	std::vector<F32> meshData;

	for (I32 i = 0; i < mesh.vertices.size(); ++i)
	{
		meshData.push_back(mesh.vertices[i].x);
		meshData.push_back(mesh.vertices[i].y);
		meshData.push_back(mesh.vertices[i].z);
	}

	CreateVertexArray();

	CreateVertexBuffer(meshData.size() * sizeof(F32), &meshData[0], EBufferUsage::Static);

	if (mesh.indices.size() > 0)
	{
		CreateIndexBuffer(mesh.indices.size() * sizeof(F32), (void*)&mesh.indices[0], EBufferUsage::Static);
	}

	AddVertexAttribute(0, 3, 3 * sizeof(F32), 0);
}

void COpenGLGDI::CreateVertexArray()
{
	U32 vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
}

void COpenGLGDI::CreateVertexBuffer(U32 size, void* data, EBufferUsage usage)
{
	FVeretxBuffer buffer;
	buffer.size = size;
	buffer.data = data;

	GLenum bufferUsage = 0;
	if (usage == EBufferUsage::Static)
	{
		bufferUsage = GL_STATIC_DRAW;
	}
	else if (usage == EBufferUsage::Dynamic)
	{
		bufferUsage = GL_DYNAMIC_DRAW;
	}

	glGenBuffers(1, &buffer.bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.bufferID);
	glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, bufferUsage);
}

void COpenGLGDI::CreateIndexBuffer(U32 size, void* data, EBufferUsage usage)
{
	FIndexBuffer buffer;
	buffer.size = size;
	buffer.data = data;

	GLenum bufferUsage = 0;
	if (usage == EBufferUsage::Static)
	{
		bufferUsage = GL_STATIC_DRAW;
	}
	else if (usage == EBufferUsage::Dynamic)
	{
		bufferUsage = GL_DYNAMIC_DRAW;
	}

	glGenBuffers(1, &buffer.bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size, buffer.data, bufferUsage);
}

void COpenGLGDI::AddVertexAttribute(U32 index, U32 size, U32 stride, U32 offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
}
#endif