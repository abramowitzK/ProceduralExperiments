#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <unordered_map>
#include <texture.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <mesh.hpp>
using namespace tinyxml2;
namespace Aurora {
	using namespace std;
	const std::string ResourcePath = "../../Data/";
	const std::string TexturePath = ResourcePath + "Textures/";
	const std::string ModelPath = ResourcePath + "Models/";
	const std::string FontPath = ResourcePath + "Fonts/";
	const std::string AudioPath = ResourcePath + "Sounds/";
	const std::string ScenePath = ResourcePath + "Scenes/";
	const std::string ShaderPath = ResourcePath + "Shaders/";
	const std::string ScriptPath = ResourcePath + "Scripts/";
	struct Scene;
	class ResourceManager {
	public:
		static void expose_to_script(ScriptManager* m);
		~ResourceManager();
		void load_defaults();
		Scene* load_scene(const std::string& name);
		inline Texture* get_texture(const std::string& name) {
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
		
		static ResourceManager* instance() {
			if (!sInstance)
				sInstance = new ResourceManager();
			return sInstance;
		}
		void reload_scripts();
		ResourceManager();
		void load_texture(const std::string& name);
		void load_model(const std::string& name);
		void load_shader(const std::string& name);
		void load_material(const std::string& name, Shader* shader, std::vector<Texture> tex);
		void load_script(const std::string& name);
	private:
		static ResourceManager* sInstance;
		Component* parse_component(XMLElement& comp, GameObject* parent);
		GameObject* parse_game_object(GameObject* parent, XMLElement* o, Scene* s);
		unordered_map<string, Mesh*> mMeshes;
		unordered_map<string, Texture> mTextures;
		unordered_map<string, Shader*> mShaders;
		unordered_map<string, Material*> mMaterials;
		unordered_map<string, std::string> mScripts;

	};

}