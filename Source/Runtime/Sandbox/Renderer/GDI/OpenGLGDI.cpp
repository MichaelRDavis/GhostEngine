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

	U32 vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	FVeretxBuffer buffer;
	buffer.size = meshData.size() * sizeof(F32);
	buffer.data = &meshData[0];
	glGenBuffers(1, &buffer.bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.bufferID);
	glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_STATIC_DRAW);

	U32 stride = 3 * sizeof(F32);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
}
#endif