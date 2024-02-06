#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

struct Vertex {
    glm::vec2 position;
    glm::vec2 texcoord;
    // glm::vec3 color;
};

//must always be divisible by a certain number depending on context
//in this case for quads, size must be divisible by 4
int const SIZE = 4;

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw." << std::endl;
        return -1;
    }
    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    unsigned int width = 800;
    unsigned int height = 800;

    GLFWwindow* window = glfwCreateWindow(width, height, "Prototype", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    glfwSwapInterval(1);

    {
        
        Vertex positions[SIZE];

        for (int i = 0; i < SIZE/4;)
        {
            positions[i].position = glm::vec2(0.5f, 0.5f);
            positions[i].texcoord = glm::vec2(1.0f, 1.0f);
            i++;

            positions[i].position = glm::vec2(-0.5f, 0.5f);
            positions[i].texcoord = glm::vec2(0.0f, 1.0f);
            i++;

            positions[i].position = glm::vec2(-0.5f, -0.5f);
            positions[i].texcoord = glm::vec2(0.0f, 0.0f);
            i++;

            positions[i].position = glm::vec2(0.5f, -0.5f);
            positions[i].texcoord = glm::vec2(1.0f, 0.0f);
            i++;
        }

        
        // float positions[] =
        // {
        //     // VERTICIES  //TEXCOORDS

        //      0.5f,  0.5f,  1.0f,  1.0f, // 0
        //     -0.5f,  0.5f,  0.0f,  1.0f, // 1
        //     -0.5f, -0.5f,  0.0f,  0.0f, // 2
        //      0.5f, -0.5f,  1.0f,  0.0f, // 3

        //     //  1.0f,  1.0f,  1.0f,  1.0f, // 0
        //     // -1.0f,  1.0f,  0.0f,  1.0f, // 1
        //     // -1.0f, -1.0f,  0.0f,  0.0f, // 2
        //     //  1.0f, -1.0f,  1.0f,  0.0f, // 3
        // };

        unsigned int indicies[6] =
        {
            0, 1, 2,
            0, 2, 3,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        va.Bind();

        // VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBuffer vb(sizeof(Vertex) * SIZE);
        vb.Bind();
        IndexBuffer ib(indicies, 6);
        ib.Bind();

        VertexBufferLayout layout; 
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        Shader shader("../res/shaders/WindowTest.shader");
        shader.Bind();
        shader.SetUniform2f("u_ScreenSize", frameBufferWidth, frameBufferHeight);

        Renderer renderer;

        Texture texture("../res/textures/PogO.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        while(!glfwWindowShouldClose(window))
        {
            renderer.Draw(va, ib, shader);
            shader.SetUniform2f("u_ScreenSize", width, height);
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
