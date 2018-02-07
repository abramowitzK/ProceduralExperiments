#pragma once
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <sstream>
#include <string>
#include <vector>
namespace Aurora {
typedef glm::vec2   Vector2;
typedef glm::vec3   Vector3;
typedef glm::vec4   Vector4;
typedef glm::mat4x4 Matrix4;
typedef glm::quat   Quaternion;

// TODO move to string library
static void split(const std::string& s, char delim, std::vector<std::string>& elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

static Vector3 parse_vector3(const std::string& string) {
    auto    sp = split(string, ',');
    Vector3 ret;
    int     i = 0;
    for (const auto& ch : sp) {
        ret[i] = (float)atof(ch.c_str());
        i++;
    }
    return ret;
}

} // namespace Aurora
