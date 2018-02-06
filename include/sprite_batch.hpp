#pragma once
#include <GL/glew.h>
#include <vector>

#include "vector_math.hpp"
#include "sprite.hpp"
#include "render_state.hpp"
#include "structures.hpp"
#include "shader.hpp"
namespace Aurora {
	struct Renderer;
	using namespace std;
	struct Texture;

	struct RenderBatch {
		RenderBatch(GLuint offset, GLuint numVertices, Texture *tex) : offset(offset), numVerts(numVertices), texture(tex) {};
		GLuint offset;
		GLuint numVerts;
		Texture *texture;
	};

	struct Glyph {
		Glyph() {}

		Glyph(const Vector4 &destRect, const Vector4 &uvRect, float depth, Texture *Texture, const Color &color) {
			texture = Texture;
			depth = depth;

			topLeft.color = color;
			topLeft.position = {destRect.x, destRect.y + destRect.w};
			topLeft.uvs = {uvRect.x, uvRect.y + uvRect.w};

			bottomLeft.color = color;
			bottomLeft.position = {destRect.x, destRect.y};
			bottomLeft.uvs = {uvRect.x, uvRect.y};

			bottomRight.color = color;
			bottomRight.position = {destRect.x + destRect.z, destRect.y};
			bottomRight.uvs = {uvRect.x + uvRect.z, uvRect.y};

			topRight.color = color;
			topRight.position = {destRect.x + destRect.z, destRect.y + destRect.w};
			topRight.uvs = {uvRect.x + uvRect.z, uvRect.y + uvRect.w};
		}

		Texture *texture;
		float depth;
		Vertex2D topLeft;
		Vertex2D bottomLeft;
		Vertex2D topRight;
		Vertex2D bottomRight;
	};

	struct SpriteBatch {
		SpriteBatch();

		~SpriteBatch();

		void init();

		void begin(GlyphSortType type = GlyphSortType::Texture);

		void end();

		void draw(const Vector4 &destRect, const Vector4 &uvRect, float depth, Texture *texture, const Color &color);

		void draw(Sprite s);

		void render_batches(Renderer *renderer);

		Shader* default_shader = nullptr;

	private:

		void create_render_batches();

		void sort_glyphs();

		bool mIsInitialized = false;
		bool mIsBegun = false;
		GLuint mVbo = 0;
		GLuint mVao = 0;
		vector<Glyph> mGlyphData;
		vector<Glyph *> mGlyphs;
		vector<RenderBatch> mBatches;
		GlyphSortType mType;
		const RenderState sSpriteBatchState{
				CullState::On,
				BlendState::Off,
				DepthState::Off,

				BlendFunc::SourceAlpha,
				BlendFunc::OneMinusSourceAlpha,
				DepthFunc::Less,

				{0.0, 0.0, 0.0, 1.0},
				FrontFace::Ccw,
				CullFace::Back,
				PolygonMode::Fill
		};

	};
}
