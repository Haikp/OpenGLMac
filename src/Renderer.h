#pragma once

#include <iostream>
#include <glad/glad.h>
// #include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) std::cout << "just 15 it on line: " << __LINE__ << std::endl;
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawCircle(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
