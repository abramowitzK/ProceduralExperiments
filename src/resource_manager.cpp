#include <camera_component.hpp>
#include <component.hpp>
#include <fstream>
#include <material.hpp>
#include <physics.hpp>
#include <platform.hpp>
#include <resource_manager.hpp>
#include <scene.hpp>
#include <streambuf>
namespace Aurora {
ResourceManager* ResourceManager::sInstance;
ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
    for (const auto& mesh : mMeshes) {
        delete mesh.second;
    }
    for (const auto& m : mMaterials) {
        delete m.second;
    }
    for (const auto& s : mShaders) {
        delete s.second;
    }
}

void ResourceManager::load_defaults() {
    load_shader("basic");
    load_shader("ttf");
    load_shader("spriteBatch");
    load_shader("texturedGouraud");
    load_texture("default.png");
    load_material("default", mShaders["texturedGouraud"],
                  {mTextures["default"]});
}

Scene* ResourceManager::load_scene(const std::string& name) {
    using namespace tinyxml2;
    tinyxml2::XMLDocument doc;
    auto                  path = ScenePath + name;
    doc.LoadFile(path.c_str());
    auto sceneNode    = doc.FirstChildElement();
    auto resourceList = sceneNode->FirstChildElement("ResourceList");
    auto modelList    = resourceList->FirstChildElement("Models");
    auto matList      = resourceList->FirstChildElement("Materials");
    auto texList      = resourceList->FirstChildElement("Textures");
    auto shaderList   = resourceList->FirstChildElement("Shaders");
    for (auto e = texList->FirstChildElement(); e != nullptr;
         e      = e->NextSiblingElement()) {
        load_texture(e->GetText());
    }
    for (auto e = modelList->FirstChildElement(); e != nullptr;
         e      = e->NextSiblingElement()) {
        auto inv = e->BoolAttribute("invert");
        load_model(e->GetText(), inv);
    }
    for (auto e = shaderList->FirstChildElement(); e != nullptr;
         e      = e->NextSiblingElement()) {
        load_shader(std::string(e->Attribute("name")));
    }
    for (auto e = matList->FirstChildElement(); e != nullptr;
         e      = e->NextSiblingElement()) {
        auto                 s = e->FirstChildElement("Shader");
        std::vector<Texture> texs;
        for (auto t = e->FirstChildElement("Texture"); t != nullptr;
             t      = t->NextSiblingElement("Texture")) {
            auto texName = std::string(t->Attribute("name"));
            texs.push_back(mTextures[texName]);
        }

        load_material(std::string(e->Attribute("name")),
                      mShaders[std::string(s->Attribute("name"))], texs);
    }
    Scene* s              = new Scene();
    auto   gameObjectList = sceneNode->FirstChildElement("SceneGraph");
    for (auto e = gameObjectList->FirstChildElement(); e != nullptr;
         e      = e->NextSiblingElement()) {
        parse_game_object(&s->root, e, s);
    }
    auto obj    = s->create_object();
    obj->parent = &s->root;
    obj->parent->mChildren.push_back(obj);
    obj->transform         = Transform();
    obj->transform.mParent = &s->root.transform;
    obj->transform.set_translation({0, 0, 0});
    obj->transform.set_scale(1);
    return s;
}

Component* ResourceManager::parse_component(XMLElement& comp,
                                            GameObject* parent, Scene* scene) {
    if (strcmp("Camera", comp.Value()) == 0) {
        return new CameraComponent(EventManager::mResizeX,
                                   EventManager::mResizeY);
    }
    if (strcmp("CharacterController", comp.Value()) == 0) {
    }
    if (strcmp("Model", comp.Value()) == 0) {
        auto m   = comp.FirstChildElement("Material");
        auto mat = mMaterials[std::string(m->Attribute("name"))];
        return new MeshRenderer(mMeshes[comp.Attribute("name")], mat);
    }
    return nullptr;
}

GameObject* ResourceManager::parse_game_object(GameObject* parent,
                                               XMLElement* o, Scene* s) {
    GameObject* object        = s->create_object();
    object->parent            = parent;
    object->transform.mParent = &parent->transform;
    parent->mChildren.push_back(object);
    for (auto e = o->FirstChildElement("GameObject"); e != nullptr;
         e      = e->NextSiblingElement()) {
        parse_game_object(object, e, s);
    }
    auto tf = o->FirstChildElement("Transform");
    object->transform.set_translation(
        parse_vector3(tf->FirstChildElement("Pos")->GetText()));
    object->transform.set_rotation(
        parse_vector3(tf->FirstChildElement("Rot")->GetText()));
    object->transform.set_scale(
        parse_vector3(tf->FirstChildElement("Scale")->GetText()));
    auto componentList = o->FirstChildElement("Components");
    for (auto c = componentList->FirstChildElement(); c != nullptr;
         c      = c->NextSiblingElement()) {
        auto comp = parse_component(*c, object, s);
        if (comp == nullptr)
            continue;
        comp->mOwner     = object;
        comp->mTransform = new Transform();

        auto tf = c->FirstChildElement("Transform");
        if (tf) {
            comp->mTransform->set_translation(
                parse_vector3(tf->FirstChildElement("Pos")->GetText()));
            comp->mTransform->set_rotation(
                parse_vector3(tf->FirstChildElement("Rot")->GetText()));
            comp->mTransform->set_scale(
                parse_vector3(tf->FirstChildElement("Scale")->GetText()));
        }
        comp->mTransform->mParent = &object->transform;
        object->add_component(comp);
    }
    return object;
}

void ResourceManager::load_texture(const std::string& name) {
    Texture t = create_2d_texture(TexturePath + name);
    t.name    = name;
    mTextures.insert({name, t});
}

void ResourceManager::load_model(const std::string& name, bool invert) {
    Assimp::Importer importer;
    auto             scene = importer.ReadFile(
        ModelPath + name, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                              aiProcess_FlipUVs | aiProcess_GenUVCoords);
    if (!scene) {
        // Todo error log
        assert(false);
    }
    // TODO handle case of multiple meshes
    auto     model = scene->mMeshes[0];
    MeshData data;
    data.indices.reserve(model->mNumFaces * 3);
    data.vertices.resize(model->mNumVertices);
    for (unsigned i = 0; i < model->mNumVertices; i++) {
        const auto& vert   = model->mVertices[i];
        const auto& normal = model->mNormals[i];
        if (model->HasTextureCoords(0)) {
            const auto& uv   = model->mTextureCoords[0][i];
            data.vertices[i] = {{vert.x, vert.y, vert.z},
                                {normal.x, normal.y, normal.z},
                                {uv.x, uv.y}};
        } else {
            data.vertices[i] = {{vert.x, vert.y, vert.z},
                                {normal.x, normal.y, normal.z}};
        }
    }
    for (unsigned i = 0; i < model->mNumFaces; i++) {
        const auto& face = model->mFaces[i];
        data.indices.push_back(face.mIndices[0]);
        data.indices.push_back(face.mIndices[1]);
        data.indices.push_back(face.mIndices[2]);
    }
    mMeshes.insert({name, new Mesh(data)});
}
void ResourceManager::load_shader(const std::string& name) {
    auto s = new Shader(name + ".vert", name + ".frag", ShaderPath);
    mShaders.insert({name, s});
}
void ResourceManager::load_material(const std::string& name, Shader* shader,
                                    std::vector<Texture> tex) {
    auto m = new Material(shader, tex[0]);
    if (tex.size() > 1) {
        for (int i = 1; i < tex.size(); i++) {
            m->tex.push_back(tex[i]);
        }
    }
    mMaterials.insert({name, m});
}
} // namespace Aurora
