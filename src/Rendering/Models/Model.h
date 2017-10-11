#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "../IGameObject.h"
#include "../Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>

namespace Rendering {
    namespace Models
    {
        class Model : public IGameObject
        {
        public:
            Model();
			Model(std::string& path);
            ~Model();
            
            virtual void Draw() override;
            virtual void Draw(const glm::mat4& projectionMatrix,
                              const glm::mat4& viewMatrix) override;
            virtual void Update() override;
            virtual void SetProgram(GLuint program) override;
            virtual void Destroy() override;
            
            GLuint GetVao() const override;
            const std::vector<GLuint>& GetVbos() const override;
            
        protected:
            GLuint vao;
            GLuint program;
            std::vector<GLuint> vbos;
			std::vector<Mesh> meshes;
			std::string directory;

		private:
			void LoadModel(std::string& path);
			void ProcessNode(aiNode* node, const aiScene* scene);
			Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
			std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
			GLint TextureFromFile(const char* path, std::string directory);
        };
    }
}

#endif
