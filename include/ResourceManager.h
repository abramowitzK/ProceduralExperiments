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
	const std::string ResourcePath = "..\\..\\Data\\";
	const std::string TexturePath = ResourcePath + "Textures\\";
	const std::string ModelPath = ResourcePath + "Models\\";
	const std::string FontPath = ResourcePath + "Fonts\\";
	const std::string AudioPath = ResourcePath + "Sounds\\";
	const std::string ScenePath = ResourcePath + "Scenes\\";
	const std::string ShaderPath = ResourcePath + "Shaders\\";
	const std::string ScriptPath = ResourcePath + "Scripts\\";
	class ResourceManager {
	public:
		
		~ResourceManager();
		void load_defaults();
		Scene* LoadScene(const std::string& name);
		inline Texture* GetTexture(const std::string& name) {
			return &mTextures[name];
		}
		inline Mesh* get_mesh(const std::string& name) {
			return mMeshes[name];
		}
		inline Shader* get_shader(const std::string& name) {
			return mShaders[name];
		}
		inline Material* get_material(const std::string& name) {
			return mMaterials[name];
		}
		inline const std::string& get_script(const std::string& name) {
			return mScripts[name];
		}
		Component* parse_component (XMLElement& comp);
		static ResourceManager* instance() {
			if (!s_instance)
				s_instance = new ResourceManager();
			return s_instance;
		}
		void reload_scripts();
	private:

		static ResourceManager* s_instance;
		ResourceManager();
		void load_texture(const std::string& name);
		void load_model(const std::string& name);
		void load_shader(const std::string& name);
		void load_material(const std::string& name, Shader* shader);
		void load_script(const std::string& name);

		unordered_map<string, Mesh*> mMeshes;
		unordered_map<string, Texture> mTextures;
		unordered_map<string, Shader*> mShaders;
		unordered_map<string, Material*> mMaterials;
		unordered_map<string, std::string> mScripts;

	};

}