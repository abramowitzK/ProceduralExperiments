#include "ResourceManager.h"
#include <Texture.h>

ResourceManager::ResourceManager() {}


ResourceManager::~ResourceManager() {}

void ResourceManager::LoadScene(const std::string & name) {
	using namespace tinyxml2;
	XMLDocument doc;
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
}

void ResourceManager::LoadTexture(std::string name) {
	Texture t = Create2DTexture(TexturePath + name);
	m_textures.insert({ name, t });
}

void ResourceManager::LoadModel(const char * path) {}
