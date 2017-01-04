#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <unordered_map>
#include <texture.hpp>
namespace CBlocks {
	using namespace std;
	class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		void LoadScene(const std::string& name);
		Texture* GetTexture(string name) {
			return &m_textures[name];
		}

	private:
		void LoadTexture(string name);
		void LoadModel(const char* name);
		const std::string ResourcePath = "..\\..\\Data\\";
		const std::string TexturePath = ResourcePath + "Textures\\";
		const std::string ModelPath = ResourcePath + "Models\\";
		const std::string FontPath = ResourcePath + "Fonts\\";
		const std::string AudioPath = ResourcePath + "Sounds\\";
		const std::string ScenePath = ResourcePath + "Scenes\\";

		unordered_map<string, Texture> m_textures;
	};

}