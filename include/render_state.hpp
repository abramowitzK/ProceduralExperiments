#pragma once
#include <GL/glew.h>
#include "vector_math.hpp"

namespace Aurora {
	enum class BlendState : bool {
		On = true,
		Off = false
	};
	enum class BlendFunc : GLenum {
		Zero = GL_ZERO,
		One = GL_ONE,
		SourceColor = GL_SRC_COLOR,
		OneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
		DestinationColor = GL_DST_COLOR,
		OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
		SourceAlpha = GL_SRC_ALPHA,
		OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
		DestinationAlpha = GL_DST_ALPHA,
		OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
		ConstantColor = GL_CONSTANT_COLOR,
		OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
		ConstantAlpha = GL_CONSTANT_ALPHA,
		OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
		SourceAlphaSaturate = GL_SRC_ALPHA_SATURATE,
		Source1Color = GL_SRC1_COLOR,
		OneMinusSource1Color = GL_ONE_MINUS_SRC1_COLOR,
		Source1Alpha = GL_SRC1_ALPHA,
		OneMinusSource1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
	};
	enum class CullState {
		On = true,
		Off = false
	};
	enum class DepthState {
		On = true,
		Off = false
	};
	enum class DepthFunc : GLenum {
		Never = GL_NEVER,
		Equal = GL_EQUAL,
		NotEqual = GL_NOTEQUAL,
		Always = GL_ALWAYS,
		Greater = GL_GREATER,
		GreaterEqual = GL_GEQUAL,
		Less = GL_LESS,
		LessEqual = GL_LEQUAL,
	};
	enum class FrontFace : GLenum {
		Ccw = GL_CCW,
		Cw = GL_CW
	};

	enum class CullFace : GLenum {
		Front = GL_FRONT,
		Back = GL_BACK,
		FrontAndBack = GL_FRONT_AND_BACK,
	};

	enum class PolygonMode : GLenum {
		Line = GL_LINE,
		Fill = GL_FILL,
	};
	struct RenderState {
		CullState CullState;
		BlendState BlendState;
		DepthState DepthState;

		BlendFunc BlendFuncSource;
		BlendFunc BlendFuncDest;
		DepthFunc DepthFunc;

		Vector4 ClearColor;
		FrontFace FrontFace;
		CullFace CullFace;
		PolygonMode PolyMode;
	};
	static const RenderState DefaultRenderState = {
			CullState::On,
			BlendState::Off,
			DepthState::On,

			BlendFunc::Zero,
			BlendFunc::Zero,
			DepthFunc::Less,

			{1.0, 1.0, 1.0, 1.0},
			FrontFace::Ccw,
			CullFace::Back,
			PolygonMode::Fill
	};
	static const RenderState DefaultTTFState = {
			CullState::Off,
			BlendState::On,
			DepthState::Off,

			BlendFunc::SourceAlpha,
			BlendFunc::OneMinusSourceAlpha,
			DepthFunc::Less,

			{0.0, 0.0, 0.0, 1.0},
			FrontFace::Ccw,
			CullFace::Back,
			PolygonMode::Fill
	};

//TODO how to make this more efficient? This is efficient for the OpenGL but probably not friendly
//to the branch prediction hw?
	static void apply_render_state(const RenderState &state, const RenderState *oldState = nullptr) {

		if(oldState) {
			if(state.CullState != oldState->CullState)
				state.CullState == CullState::On ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
			if(state.DepthState != oldState->DepthState)
				state.DepthState == DepthState::On ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
			if(state.BlendState != oldState->BlendState)
				state.BlendState == BlendState::On ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
			if(state.FrontFace != oldState->FrontFace)
				glFrontFace((GLenum) state.FrontFace);
			if(state.ClearColor != oldState->ClearColor)
				glClearColor(state.ClearColor.x, state.ClearColor.y, state.ClearColor.z, state.ClearColor.z);
			if(state.BlendFuncDest != oldState->BlendFuncDest || state.BlendFuncSource != oldState->BlendFuncSource)
				glBlendFunc((GLenum) state.BlendFuncSource, (GLenum) state.BlendFuncDest);
			if(state.DepthFunc != oldState->DepthFunc)
				glDepthFunc((GLenum) state.DepthFunc);
			if(state.CullFace != oldState->CullFace)
				glCullFace((GLenum) state.CullFace);
			if(state.PolyMode != oldState->PolyMode)
				glPolygonMode(GL_FRONT_AND_BACK, (GLenum) state.PolyMode);
		} else {
			state.CullState == CullState::On ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
			state.DepthState == DepthState::On ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
			state.BlendState == BlendState::On ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
			glFrontFace((GLenum) state.FrontFace);
			glClearColor(state.ClearColor.x, state.ClearColor.y, state.ClearColor.z, state.ClearColor.z);
			glBlendFunc((GLenum) state.BlendFuncSource, (GLenum) state.BlendFuncDest);
			glDepthFunc((GLenum) state.DepthFunc);
			glCullFace((GLenum) state.CullFace);
			glPolygonMode(GL_FRONT_AND_BACK, (GLenum) state.PolyMode);
		}
	}
}
