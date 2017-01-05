#ifndef CBLOCKS_SHADER_H
#define CBLOCKS_SHADER_H
#include <GL\glew.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
namespace CBlocks {
	struct Shader {
	public:
		Shader();

		Shader(const char *vShaderFileName, const char *fShaderFileName);
		Shader(const char *vShaderFileName, const char *fShaderFileName, const std::string& shaderPath);
		~Shader();

		void load_vertex_shader(std::string shaderFileName);

		void load_fragment_shader(std::string shaderFileName);

		void bind();

		GLuint get_program() const {
			return mProgram;
		}

	private:
		void add_vertex_shader(const GLchar *text);

		void add_fragment_shader(const GLchar *text);

		void add_program(const GLchar *text, GLuint type);

		void compile_shader();

		std::vector<GLint> mShaders;
		static std::string SHADER_DIR;
		GLuint mProgram;
	};
}
#endif

