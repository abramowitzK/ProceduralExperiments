#include "ResourceManager.h"
#include <fstream>
#include <streambuf>
#include <component.hpp>
#include <physics.hpp>
namespace CBlocks {
	ResourceManager* ResourceManager::s_instance;
	void ResourceManager::reload_scripts() {}
	ResourceManager::ResourceManager() {}


	ResourceManager::~ResourceManager() {}

	void ResourceManager::load_defaults() {
		load_shader("basic");
		load_shader("ttf");
		load_shader("spriteBatch");
		load_shader("texturedGouraud");
		load_material("default", mShaders["texturedGouraud"]);
	}

	Scene* ResourceManager::LoadScene(const std::string & name) {
		using namespace tinyxml2;
		tinyxml2::XMLDocument doc;
		auto path = ScenePath + name;
		doc.LoadFile(path.c_str());
		auto sceneNode = doc.FirstChildElement();
		auto resourceList = sceneNode->FirstChildElement("ResourceList");
		auto modelList = resourceList->FirstChildElement("Models");
		auto matList = resourceList->FirstChildElement("Materials");
		auto texList = resourceList->FirstChildElement("Textures");
		auto shaderList = resourceList->FirstChildElement("Shaders");
		auto scriptList = resourceList->FirstChildElement("Scripts");
		for (auto e = texList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			load_texture(e->GetText());
		}
		for (auto e = modelList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			load_model(e->GetText());
		}
		for (auto e = shaderList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			load_shader(std::string(e->Attribute("name")));
		}
		for (auto e = matList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			auto s = e->FirstChildElement("Shader");
			load_material(std::string(e->Attribute("name")), mShaders[std::string(s->Attribute("name"))]);
		}
		for (auto e = scriptList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			load_script(std::string(e->Attribute("name")));
		}
		Scene* s = new Scene();
		auto gameObjectList = sceneNode->FirstChildElement("SceneGraph");
		for (auto e = gameObjectList->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			GameObject* o = s->create_object();
			o->parent = &(s->root);
			s->root.mChildren.push_back(o);
			auto tf = e->FirstChildElement("Transform");
			o->transform.set_translation(parse_vector3(tf->FirstChildElement("Pos")->GetText()));
			o->transform.set_rotation(parse_vector3(tf->FirstChildElement("Rot")->GetText()));
			o->transform.set_scale(parse_vector3(tf->FirstChildElement("Scale")->GetText()));
			auto componentList = e->FirstChildElement("Components");
			for (auto c = componentList->FirstChildElement(); c != nullptr; c = c->NextSiblingElement()) {
				auto comp = parse_component(*c);
				comp->owner = o;
				o->add_component(comp);
				if (strcmp(e->Attribute("name"), "plane") == 0) {
					auto rb = Physics::instance()->plane;
					auto rbc = new RigidBody(rb);
					rbc->owner = o;
					o->add_component(rbc);
				}
			}
		}
		return s;
	}

	Component* ResourceManager::parse_component(XMLElement & comp) {
		if (strcmp("Model", comp.Value()) == 0) {
			auto m = comp.FirstChildElement("Material");
			auto mat = mMaterials[std::string(m->Attribute("name"))];
			return new MeshRenderer(mMeshes[comp.Attribute("name")], mat);
		}
		if (strcmp("Script", comp.Value()) == 0) {
			auto name = comp.Attribute("name");
			return new Script(name,mScripts[name]);
		}
		return nullptr;
	}

	void ResourceManager::load_texture(const std::string& name){
		Texture t = create_2d_texture(TexturePath + name);
		mTextures.insert({ name, t });
	}

	void ResourceManager::load_model(const std::string& name) {
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
	void ResourceManager::load_shader(const std::string & name) {
		auto s = new Shader(name + ".vert", name + ".frag", ShaderPath);
		mShaders.insert({ name, s });
	}
	void ResourceManager::load_material(const std::string & name, Shader* shader) {
		auto m = new Material(shader);
		mMaterials.insert({ name, m });
	}
	void ResourceManager::load_script(const std::string & name) {
		std::ifstream t(ScriptPath + name + ".lua");
		std::string str;

		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		mScripts.insert({ name, std::move(str) });
	}
}