#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/glm/gtx/rotate_vector.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

#include "Shader.h"

class Camera
{
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width;
        int height;

        float speed = 0.1f;
        float sensitivity = 100.0f;

        bool firstClick = true;

        Camera(int width, int height, glm::vec3 position);

        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform, float rotation);
        void Inputs(GLFWwindow* window);
};

#endif