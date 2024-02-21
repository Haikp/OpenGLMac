#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Camera.h"
#include "Model.h"

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
        
        
        float positions[] =
        { 
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
        };

        unsigned int indicies[18] =
        {
	        0, 1, 2,
	        0, 2, 3,
	        0, 1, 4,
	        1, 2, 4,
	        2, 3, 4,
	        3, 0, 4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        va.Bind();

        VertexBuffer vb(positions, 5 * 8 * sizeof(float));
        vb.Bind();
        IndexBuffer ib(indicies, 18);
        ib.Bind();

        VertexBufferLayout layout; 
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();

        Renderer renderer;

        // Texture texture("../res/textures/PogO.png");
        // texture.Bind();
        // shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Model model("../res/models/grass.dae");

        glEnable(GL_DEPTH_TEST);

        // Variables that help the rotation of the pyramid
	    float rotation = 0.0f;
	    double prevTime = glfwGetTime();

        Camera camera(frameBufferWidth, frameBufferHeight, glm::vec3(0.0f   , 0.0f, 2.0f));

        while(!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

            double crntTime = glfwGetTime();
		    if (crntTime - prevTime >= 1 / 60)
		    {
			    rotation += 0.5f;
			    prevTime = crntTime;
		    }
            
            shader.Bind();
            va.Bind();

            camera.Inputs(window);
            camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", rotation);

            // renderer.Draw(va, ib, shader);
            model.Draw(shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
