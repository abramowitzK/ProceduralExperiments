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
namespace CBlocks {
	struct Renderer {
	public:
		Renderer(int width, int height);
		void update(float dt) { mCamera->update(dt); }
		void render();
		void clear_screen(bool depth, bool color);
		void handle_resize(int width, int height);
		void create_camera(EventManager& manager);
		void render_chunk();
		RenderState current_render_state = DefaultRenderState;
	private:
		RenderState mDefault = DefaultRenderState;
		Shader* mDefaultShader;
		Texture tex;
		SpriteBatch* sb;
		Sprite sprite;
		Camera* mCamera;
		int mWidth;
		int mHeight;
		Chunk* mChunk;
	};
}

#endif //CBLOCKS_RENDERING_HPP
