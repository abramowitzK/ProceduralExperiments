/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/
#include "rendering.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace CBlocks {
	Renderer::Renderer(int width, int height) {
		GLenum res = glewInit();
		if(res != GLEW_OK) {
			//TODO: Do something better here
			assert(false);
		}
		apply_render_state(DefaultRenderState);
		SDL_GL_SetSwapInterval(0);
		mDefaultShader = new Shader();
		std::string path = "C:\\Users\\Kyle\\Downloads\\grass.png";
		tex = create_2d_texture(path);
		sb = new SpriteBatch();
		sb->init();
		sprite = {&tex , {0,0}, {50,50}, RED, 0 };
		mWidth = width;
		mHeight = height;
		mChunk = new Chunk();
		

	}

	void Renderer::render() {
		//glm::mat4 projection = glm::ortho(0.0f, (float)mWidth, 0.0f, (float)mHeight);
		//sb->default_shader->bind();
		//auto loc = glGetUniformLocation(sb->default_shader->get_program(), "projection");
		//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
		//sb->begin();
		//sb->draw(sprite);
		//sb->end();
		//sb->render_batches(this);
		render_chunk();
	}

	void Renderer::clear_screen(bool depth, bool color) {
		if(depth) {
			if(color) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			} else {
				glClear(GL_DEPTH_BUFFER_BIT);
			}
		} else {
			glClear(GL_COLOR_BUFFER_BIT);
		}

	}

	void Renderer::handle_resize(int width, int height) {
		mWidth = width;
		mHeight = height;
		glViewport(0, 0, mWidth, mHeight);
	}

	void Renderer::create_camera(EventManager& manager){
		mCamera = new Camera(manager, mWidth, mHeight);
	}
	void Renderer::render_chunk(){
		apply_render_state(DefaultRenderState);
		mCamera->render();
		auto vp = mCamera->projection*mCamera->view*glm::mat4(1.0f);
		mDefaultShader->bind();
		glUniformMatrix4fv(glGetUniformLocation(mDefaultShader->get_program(),"mvp"),1, GL_FALSE, glm::value_ptr(vp));
		mChunk->Render();
		auto err = glGetError();
		apply_render_state(current_render_state);
	}
}
