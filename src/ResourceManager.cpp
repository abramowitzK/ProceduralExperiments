#include "ResourceManager.h"
namespace CBlocks {
	ResourceManager::ResourceManager() {}


	ResourceManager::~ResourceManager() {}

	Scene* ResourceManager::LoadScene(const std::string & name) {
		using namespace tinyxml2;
		tinyxml2::XMLDocument doc;
		auto path = ScenePath + name;
		doc.LoadFile(path.c_str());
		auto sceneNode = doc.FirstChildElement();
		auto resourceList = sceneNode->FirstChildElement("ResourceList");
		auto modelList = resourceList->FirstChildElement("Models");
		auto texList = resourceList->FirstChildElement("Textures");
		for (auto e = texList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			LoadTexture(e->GetText());
		}
		for (auto e = modelList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			LoadModel(e->GetText());
		}

		Scene* s = new Scene();
		auto gameObjectList = sceneNode->FirstChildElement("SceneGraph");
		for (auto e = gameObjectList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			auto o = s->create_object();
			o->parent = &s->root;
			auto tf = e->FirstChildElement("Transform");
			o->transform.set_translation(parse_vector3(tf->FirstChildElement("Pos")->GetText()));
			o->transform.set_rotation(parse_vector3(tf->FirstChildElement("Rot")->GetText()));
			o->transform.set_scale(parse_vector3(tf->FirstChildElement("Scale")->GetText()));
			auto componentList = e->FirstChildElement("Components");
			for (auto c = componentList->FirstChildElement(); c != nullptr; c = c->NextSiblingElement()) {
				o->add_component(*(parse_component(*c)));
			}
		}
		return s;

	}

	Component* ResourceManager::parse_component(XMLElement & comp) {
		if (strcmp("Model", comp.Value()) == 0) {
			return mMeshes[comp.GetText()];
		}
		return nullptr;
	}

	void ResourceManager::LoadTexture(const std::string& name){
		Texture t = create_2d_texture(TexturePath + name);
		mTextures.insert({ name, t });
	}

	void ResourceManager::LoadModel(const std::string& name) {
		Assimp::Importer importer;
		auto scene = importer.ReadFile(ModelPath + name, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		if (!scene) {
			//Todo error log
		}
		//TODO handle case of multiple meshes
		auto model = scene->mMeshes[0];
		MeshData data;
		data.indices.reserve(model->mNumFaces * 3);
		data.vertices.resize(model->mNumVertices);
		for (unsigned i = 0; i < model->mNumVertices; i++) {
			const auto& vert = model->mVertices[i];
			const auto& normal = model->mNormals[i];
			const auto& uv = model->mTextureCoords[0][i];
			data.vertices[i] = { 
				{vert.x, vert.y, vert.z},
				{normal.x, normal.y, normal.z},
				{uv.x, uv.y}
			};
		}
		for (unsigned i = 0; i < model->mNumFaces; i++) {
			const auto& face = model->mFaces[i];
			data.indices.push_back(face.mIndices[0]);
			data.indices.push_back(face.mIndices[1]);
			data.indices.push_back(face.mIndices[2]);
		}
		mMeshes.insert({ name, new Mesh(data)});
	}
}