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
#include <resource_manager.hpp>
#include <camera_component.hpp>
#include <material.hpp>

namespace Aurora {
	Renderer::Renderer(int width, int height) {
		GLenum res = glewInit();
		if (res != GLEW_OK) {
			//TODO: Do something better here
			assert(false);
		}
		apply_render_state(DefaultRenderState);

		mWidth = width;
		mHeight = height;
		if (FT_Init_FreeType(&mFt)) {
			fprintf(stderr, "Could not init freetype library\n");
			exit(1);
		}
		//Todo move to resource manager/replace/find better way to render text.
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

	}

	void Renderer::init_default_resources() {
		auto manager = ResourceManager::instance();
		sb = new SpriteBatch();
		sb->init();
		sb->default_shader = manager->get_shader("spriteBatch");
		sprite = {&tex , {0,0}, {50,50}, RED, 0};
		mDefaultShader = manager->get_shader("basic");
		mDefaultTtfShader = manager->get_shader("ttf");
	}

	void Renderer::render(CameraComponent* cam) {
		cam->render(this);
		view = cam->view;
		proj = cam->proj;
	}

	void Renderer::clear_screen(bool depth, bool color) {
		if (depth) {
			if (color) {
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

	void Renderer::create_camera() {
		EventManager::subscribe_to_resize_event([=](int a, int b) {this->handle_resize(a, b); });
		mCamera = make_shared<Camera>(mWidth, mHeight);
	}

	void Renderer::render_mesh(MeshRenderer* mesh) {
		RenderState oldState = current_render_state;
		current_render_state = mesh->required_state;
		apply_render_state(current_render_state, &oldState);
		Matrix4 vp, m, v, p;
		if (debug) {
			mCamera->render();
			view = mCamera->view;
			proj = mCamera->projection;
		}
		vp = proj * view*mesh->mTransform->get_transform();//mCamera->projection*mCamera->view*(mesh->mOwner->transform.get_transform());
		m = mesh->mOwner->transform.get_transform();
		v = view;
		p = proj;
		auto first = GL_TEXTURE0;
		auto second = GL_TEXTURE1;
		mesh->material->shader->bind();
		int i = 0;
		for (const auto& t : mesh->material->tex) {
			glUniform1i(glGetUniformLocation(mesh->material->shader->get_program(), (std::string("tex") + std::to_string(i)).c_str()), i);
			glActiveTexture(first++);
			glBindTexture(GL_TEXTURE_2D, t.Tex);
			i++;
		}
		first = GL_TEXTURE0;
		glUniformMatrix4fv(glGetUniformLocation(mesh->material->shader->get_program(), "mvp"), 1, GL_FALSE, glm::value_ptr(vp));
		glUniformMatrix4fv(glGetUniformLocation(mesh->material->shader->get_program(), "m"), 1, GL_FALSE, glm::value_ptr(m));
		glUniformMatrix4fv(glGetUniformLocation(mesh->material->shader->get_program(), "v"), 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(glGetUniformLocation(mesh->material->shader->get_program(), "p"), 1, GL_FALSE, glm::value_ptr(p));

		mesh->mesh->render();
		for (const auto& t : mesh->material->tex) {
			glBindSampler(i, 0);
			glActiveTexture(first++);
			glBindTexture(GL_TEXTURE_2D, 0);
			i++;
		}
		current_render_state = oldState;
		apply_render_state(current_render_state);
	}

	void Renderer::render_ttf(const std::string & text, float x, float y, float scale, glm::vec4 color) {
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
