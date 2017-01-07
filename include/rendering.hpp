/*
* Created by Kyle on 12/10/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#ifndef CBLOCKS_RENDERING_HPP
#define CBLOCKS_RENDERING_HPP

#include <GL/glew.h>
#include <vector>
#include <cassert>
#include "render_state.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "sprite_batch.hpp"
#include "events.hpp"
#include "camera.hpp"
#include "chunk.h"
#include <mesh_renderer.hpp>
#include <map>
#include <memory>
#include <ft2build.h>
#include <mesh.hpp>
#include FT_FREETYPE_H

namespace CBlocks {
	struct Character {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	};
	struct Renderer {
	public:
		Renderer(int width, int height);
		void update(double dt) { mCamera->update(dt); }
		void render();
		void clear_screen(bool depth, bool color);
		void handle_resize(int width, int height);
		void create_camera(EventManager& manager);
		void render_chunk();
		void render_mesh(MeshRenderer* mesh);
		void RenderTTF(const std::string& text, float x, float y, float scale, glm::vec4 color);
		RenderState current_render_state = DefaultRenderState;
	private:
		RenderState mDefault = DefaultRenderState;
		Shader* mDefaultShader;
		Shader* mDefaultTtfShader;
		Texture tex;
		SpriteBatch* sb;
		Sprite sprite;
		shared_ptr<Camera> mCamera;
		int mWidth;
		int mHeight;
		Chunk* mChunk;
		std::map<GLchar, Character> mChars;
		FT_Library mFt;
		FT_Face mDefaultFont;
		GLuint mTtfVao;
		GLuint mTtfVbo;
		RenderState mTtf;
	};
}

#endif //CBLOCKS_RENDERING_HPP
