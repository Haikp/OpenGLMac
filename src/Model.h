#pragma once
#define MODEL_CLASS_H
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

class Model
{
    public:
        Model(char *path, bool gamma = false)
            : gammaCorrection(gamma)
        {
            loadModel(path);
        }

        void Draw(Shader &shader);

    private:
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;
        bool gammaCorrection;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};