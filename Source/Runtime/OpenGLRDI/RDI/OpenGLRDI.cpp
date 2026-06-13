#include "OpenGLRDI.h"
#include <glad/glad.h>
#include <cstdio>

COpenGLRDI::COpenGLRDI()
{
	mContext = nullptr;
}

COpenGLRDI::~COpenGLRDI()
{
	Destroy();
}

void COpenGLRDI::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("glad OpenGL loader failed!\n");
		return;
	}

	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	SubmitShader(vertexShaderSource, fragmentShaderSource);

	VertexBuffer vertexBuffer;
	vertexBuffer.data = vertices;
	vertexBuffer.size = sizeof(vertices);
	vertexBuffer.id = 1;

	VertexArray vertexArray;
	vertexArray.id = 1;

	VertexAttribute vertexAtrrib;
	vertexAtrrib.index = 0;
	vertexAtrrib.size = 3;
	vertexAtrrib.stride = 3 * sizeof(float);

	SubmitVertexArray(vertexArray);
	SubmitVertexBuffer(vertexBuffer);
	SubmitVertexAttribute(vertexAtrrib);
}

void COpenGLRDI::Render()
{
	Color color;
	color.r = 0.39f;
	color.g = 0.58f;
	color.b = 0.93f;
	color.a = 1.0f;

	ClearColor(color);
	Clear();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SwapBuffers();
}

void COpenGLRDI::Destroy()
{
	if (mContext != nullptr)
	{
		SDL_GL_DestroyContext(mContext);
		mContext = nullptr;
	}
}

void COpenGLRDI::CreateViewport(const RenderViewport& viewport)
{
	mViewport = viewport;

	mContext = SDL_GL_CreateContext((SDL_Window*)mViewport.windowSurface);
	if (mContext == nullptr)
	{
		printf("SDL OpenGL context creation failed! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	SDL_GL_MakeCurrent((SDL_Window*)mViewport.windowSurface, mContext);
}

void COpenGLRDI::SubmitVertexBuffer(VertexBuffer& buffer)
{
	glGenBuffers(buffer.id, &buffer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_STATIC_DRAW);
}

void COpenGLRDI::SubmitVertexArray(VertexArray& vertexArray)
{
	glGenVertexArrays(vertexArray.id, &vertexArray.vao);
	glBindVertexArray(vertexArray.vao);
}

void COpenGLRDI::SubmitVertexAttribute(VertexAttribute& vertexAttribute)
{
	glVertexAttribPointer(vertexAttribute.index, vertexAttribute.size, GL_FLOAT, GL_FALSE, vertexAttribute.stride, (void*)0);
	glEnableVertexAttribArray(vertexAttribute.index);
}

void COpenGLRDI::SubmitShader(const char* vertexSrc, const char* fragSrc)
{
	int32_t bSuccess;
	char log[512];

	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, log);
		printf("Vertex shader compilation failed! Error: %s\n", log);
		return;
	}

	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
		printf("Fragment shader compilation failed! Error: %s\n", log);
		return;
	}

	uint32_t shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
		printf("Shader linkage failed! Error: %s\n", log);
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

void COpenGLRDI::SwapBuffers()
{
	SDL_GL_SwapWindow((SDL_Window*)mViewport.windowSurface);
}

void COpenGLRDI::ClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void COpenGLRDI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}