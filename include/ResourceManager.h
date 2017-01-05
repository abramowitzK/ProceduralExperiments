#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <unordered_map>
#include <texture.hpp>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <mesh.hpp>
#include <scene.hpp>
using namespace tinyxml2;
namespace CBlocks {
	using namespace std;
	class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		Scene* LoadScene(const std::string& name);
		inline Texture* GetTexture(const std::string& name) {
			return &mTextures[name];
		}
		inline Mesh* get_mesh(const std::string& name) {
			return mMeshes[name];
		}
		Component* parse_component(XMLElement& comp);
	private:
		void LoadTexture(const std::string& name);
		void LoadModel(const std::string& name);
		const std::string ResourcePath = "..\\..\\Data\\";
		const std::string TexturePath = ResourcePath + "Textures\\";
		const std::string ModelPath = ResourcePath + "Models\\";
		const std::string FontPath = ResourcePath + "Fonts\\";
		const std::string AudioPath = ResourcePath + "Sounds\\";
		const std::string ScenePath = ResourcePath + "Scenes\\";

		unordered_map<string, Mesh*> mMeshes;
		unordered_map<string, Texture> mTextures;
	};

}