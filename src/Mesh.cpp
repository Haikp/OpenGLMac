// #include <glad/glad.h>
// #include "Mesh.h"

// Mesh::Mesh(std::vector<Vertex>& verticies, std::vector<GLuint>& indicies, std::vector<Texture>& textures)
// {
//     Mesh::verticies = verticies;
//     Mesh::indicies = indicies;
//     Mesh::textures = textures;

//     VertexArray va;
//     va.Bind();

//     VertexBuffer vb(verticies);
//     vb.Bind();
//     IndexBuffer ib(indicies);
//     ib.Bind();

//     VertexBufferLayout layout; 
//     layout.Push<Vertex>(3);
//     layout.Push<Vertex>(3);
//     layout.Push<Vertex>(3);
//     layout.Push<Vertex>(2);

//     va.AddBuffer(vb, layout);

//     va.Unbind();
//     vb.Unbind();
//     ib.Unbind();
// }

// void Mesh::Draw(Shader &shader, Camera &camera)
// {
//     shader.Bind();
//     va.Bind();

//     for (unsigned int i = 0; i < textures.size(); i++)
//     {
//         // implement textures here
//     }

//     glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
// }
