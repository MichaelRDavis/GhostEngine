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

	int32_t bSuccess;
	char log[512];

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

	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
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
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
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

	uint32_t vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
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

void COpenGLRDI::SubmitVertexBuffer(const VertexBuffer& buffer)
{
	
}

void COpenGLRDI::SubmitVertexAttribute()
{

}

void COpenGLRDI::SubmitShader(const char* vertexSrc, const char* fragSrc)
{

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