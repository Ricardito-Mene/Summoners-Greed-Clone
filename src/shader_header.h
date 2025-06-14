#if !defined(ENGINE) && defined(__cplusplus)
#define ENGINE
#endif

#ifdef ENGINE // Inside Game / Engine
#pragma once

#include "main_lib.h"
#define vec2 Vec2
#define ivec2 IVec2
#define vec4 Vec4

extern int RENDERING_OPTION_FLIP_X;
extern int RENDERING_OPTION_FLIP_Y;
extern int RENDERING_OPTION_FONT;
// Inside Shader
#else 
const int RENDERING_OPTION_FLIP_X = 1 << 0;
const int RENDERING_OPTION_FLIP_Y = 1 << 1;
const int RENDERING_OPTION_FONT = 1 << 2;
#define BIT(i) 1 << i

// Inside Both
#endif 

// #############################################################################
//                           Rendering Constants
// #############################################################################


// #############################################################################
//                           Rendering Structs
// #############################################################################
struct Transform
{
  vec2 pos; // This is currently the Top Left!!
  vec2 size;
  ivec2 atlasOffset;
  ivec2 spriteSize;
  int renderOptions;
  int materialIdx;
  float layer;
  int padding;
};

struct Material
{
	// Operator inside the Engine to compare materials
#ifdef ENGINE 
  vec4 color = COLOR_WHITE;
	bool operator==(Material other)
	{
		return color == other.color;
	}
#else
  vec4 color;
#endif
};