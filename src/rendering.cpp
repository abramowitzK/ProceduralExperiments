/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/
#include <rendering.hpp>
#include <mesh.hpp>
#include <mesh_renderer.hpp>
#include <game_object.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ResourceManager.h>


namespace CBlocks {
	Renderer::Renderer(int width, int height) {
		GLenum res = glewInit();
		if(res != GLEW_OK) {
			//TODO: Do something better here
			assert(false);
		}
		apply_render_state(DefaultRenderState);
		SDL_GL_SetSwapInterval(0);
		sb = new SpriteBatch();
		sb->init();
		sprite = {&tex , {0,0}, {50,50}, RED, 0 };
		mWidth = width;
		mHeight = height;
		mChunk = new Chunk();
		if (FT_Init_FreeType(&mFt)) {
			fprintf(stderr, "Could not init freetype library\n");
			exit(1);
		}
		if (FT_New_Face(mFt, "C:\\Windows\\fonts\\arial.ttf", 0, &mDefaultFont)) {
			fprintf(stderr, "Could not open font\n");
			exit(1);
		}
		FT_Set_Pixel_Sizes(mDefaultFont, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(mDefaultFont, c, FT_LOAD_RENDER)) {
				fprintf(stderr, "Could not load character 'X'\n");
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				mDefaultFont->glyph->bitmap.width,
				mDefaultFont->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				mDefaultFont->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(mDefaultFont->glyph->bitmap.width, mDefaultFont->glyph->bitmap.rows),
				glm::ivec2(mDefaultFont->glyph->bitmap_left, mDefaultFont->glyph->bitmap_top),
				(GLuint)mDefaultFont->glyph->advance.x
			};
			mChars.insert(std::pair<GLchar, Character>(c, character));
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		FT_Done_Face(mDefaultFont);
		FT_Done_FreeType(mFt);

		glGenVertexArrays(1, &mTtfVao);
		glBindVertexArray(mTtfVao);
		glGenBuffers(1, &mTtfVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mTtfVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		auto manager = ResourceManager::instance();
		mDefaultShader = manager->get_shader("basic");
		mDefaultTtfShader = manager->get_shader("ttf");
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
		//render_chunk();
		RenderTTF("Hello, World!", 50, 50, 2.0f, { 1,0,0,1 });
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
		mCamera = make_shared<Camera>(manager, mWidth, mHeight);
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
	void Renderer::render_mesh(MeshRenderer* mesh) {
		RenderState oldState = current_render_state;
		current_render_state = mesh->required_state;
		apply_render_state(current_render_state, &oldState);
		mCamera->render();
		auto vp = mCamera->projection*mCamera->view*(mesh->owner->transform.GetTransform());
		mesh->material->shader->bind();
		
		glUniformMatrix4fv(glGetUniformLocation(mesh->material->shader->get_program(), "mvp"), 1, GL_FALSE, glm::value_ptr(vp));

		mesh->mesh->render();
		current_render_state = oldState;
		apply_render_state(current_render_state);
		auto err = glGetError();
	}
	void Renderer::RenderTTF(const std::string & text, float x, float y, float scale, glm::vec4 color) {
		RenderState oldState = current_render_state;
		mDefaultTtfShader->bind();
		current_render_state = DefaultTTFState;
		apply_render_state(current_render_state, &oldState);
		glm::mat4 projection = glm::ortho(0.0f, (float)mWidth, 0.0f, (float)mHeight);
		glUniform3f(glGetUniformLocation(mDefaultTtfShader->get_program(), "textColor"), color.x, color.y, color.z);
		auto loc = glGetUniformLocation(mDefaultTtfShader->get_program(), "projection");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(mTtfVao);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			Character ch = mChars[*c];

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, mTtfVbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		apply_render_state(oldState, &current_render_state);
		current_render_state = oldState;
	}


}
