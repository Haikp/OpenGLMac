#ifndef MESH_CLASS_H
#define MESH_CLASS_H
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };
class Mesh
{
    public:
        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indicies;
        std::vector<Texture>        textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures);
        void Draw(Shader &shader);

    private:
        VertexArray va;
        void setupMesh();
};

#endif