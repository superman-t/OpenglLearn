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

namespace Rendering {
    namespace Models
    {
        class Model : public IGameObject
        {
        public:
            Model();
			Model(const std::string& path);
            ~Model();
            
            virtual void Draw() override;
            virtual void Draw(const glm::mat4& projectionMatrix,
                              const glm::mat4& viewMatrix,
							  const glm::mat4& modelMatrix) override;
            virtual void Update() override;
            virtual void SetProgram(GLuint program) override;
            virtual void Destroy() override;
            
            GLuint GetVao() const override;
            const std::vector<GLuint>& GetVbos() const override;

			void SetTransform(const glm::vec3& transform);
			void SetScale(const glm::vec3& scale);
            
        protected:
            GLuint vao;
            GLuint program;
            std::vector<GLuint> vbos;
			std::vector<Mesh> meshes;
			std::string directory;
			glm::vec3 mScale;
			glm::vec3 mTransform;

		private:
			std::vector<Texture> loadedTextures;
			void LoadModel(const std::string& path);
			void ProcessNode(aiNode* node, const aiScene* scene);
			Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
			std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
			GLint TextureFromFile(const char* path, std::string directory);
        };

		inline void Model::SetScale(const glm::vec3& scale)
		{
			mScale = scale;
		}

		inline void Model::SetTransform(const glm::vec3& transform)
		{
			mTransform = transform;
		}
    }
}

#endif
