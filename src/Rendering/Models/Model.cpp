#include "Model.h"
#include <vector>

using namespace std;
using namespace Rendering;
using namespace Models;
Model::Model()
:mScale(glm::vec3(1.0, 1.0, 1.0))
,mTransform(glm::vec3(0.0, 0.0, 0.0))

{
    
}

Model::Model(const std::string& path)
{
	Model();
	LoadModel(path);
}

Model::~Model()
{
    Destroy();
}

void Model::Update()
{
    
}

void Model::SetProgram(GLuint program)
{
    this->program = program;
}

void Model::Draw()
{
    
}

void Model::Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix, const glm::mat4& modelMatrix)
{
	glm::mat4 model;
	model = glm::scale(modelMatrix, mScale);
	model = glm::translate(model, mTransform);
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].Draw(program, projectionMatrix, viewMatrix, model);
}

void Model::Destroy()
{
    glDeleteVertexArrays(1, &vao);
	if (vbos.size() > 0)
		glDeleteBuffers(vbos.size(), &vbos[0]);
    vbos.clear();
}

GLuint Model::GetVao() const
{
    return vao;
}

const std::vector<GLuint>& Model::GetVbos() const 
{
    return vbos;
}

void Model::LoadModel(const std::string& path)
{
	// Read file via ASSIMP 
	Assimp::Importer importer; 
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->ProcessNode(scene->mRootNode, scene);
}

// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->ProcessMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		if (mesh->HasPositions())
			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->HasNormals())
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<Texture> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		//std::cout << str.C_Str() << std::endl;
		for (int i = 0; i < loadedTextures.size(); ++i)
		{
			if (std::strcmp(loadedTextures[i].path.C_Str(), str.C_Str()) == 0)
			{
				skip = true;
				textures.push_back(loadedTextures[i]);
				break;
			}
		}
		Texture texture;
		std::string path(str.C_Str());
		if (path.find("materials") != string::npos)
			path = path.substr(path.find("materials"), path.length());
		texture.id = TextureFromFile(path.c_str(), this->directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
		loadedTextures.push_back(texture);
	}
	return textures;
}


GLint Model::TextureFromFile(const char* path, string directory)
{
	//Generate texture ID and load texture data 
	string filename = string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	int comp;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, &comp, SOIL_LOAD_RGB);
	
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}