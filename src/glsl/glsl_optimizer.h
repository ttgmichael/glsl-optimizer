#pragma once
#ifndef GLSL_OPTIMIZER_H
#define GLSL_OPTIMIZER_H

/*
 Main GLSL optimizer interface.
 See ../../README.md for more instructions.

 General usage:

 ctx = glslopt_initialize();
 for (lots of shaders) {
   shader = glslopt_optimize (ctx, shaderType, shaderSource, options);
   if (glslopt_get_status (shader)) {
     newSource = glslopt_get_output (shader);
   } else {
     errorLog = glslopt_get_log (shader);
   }
   glslopt_shader_delete (shader);
 }
 glslopt_cleanup (ctx);
*/

struct glslopt_shader;
struct glslopt_ctx;

enum glslopt_shader_type {
	kGlslOptShaderVertex = 0,
	kGlslOptShaderFragment,
};

// Options flags for glsl_optimize
enum glslopt_options {
	kGlslOptionSkipPreprocessor = (1<<0), // Skip preprocessing shader source. Saves some time if you know you don't need it.
	kGlslOptionNotFullShader = (1<<1), // Passed shader is not the full shader source. This makes some optimizations weaker.
};

// Optimizer target language
enum glslopt_target {
	kGlslTargetOpenGL = 0,
	kGlslTargetOpenGLES20 = 1,
	kGlslTargetOpenGLES30 = 2,
	kGlslTargetMetal = 3,
};

// Type info
enum glslopt_basic_type {
	kGlslTypeFloat = 0,
	kGlslTypeInt,
	kGlslTypeBool,
	kGlslTypeTex2D,
	kGlslTypeTex3D,
	kGlslTypeTexCube,
	kGlslTypeTex2DShadow,
	kGlslTypeTex2DArray,
	kGlslTypeOther,
	kGlslTypeCount
};
enum glslopt_precision {
	kGlslPrecHigh = 0,
	kGlslPrecMedium,
	kGlslPrecLow,
	kGlslPrecCount
};

glslopt_ctx* glslopt_initialize (enum glslopt_target target);
void glslopt_cleanup (struct glslopt_ctx* ctx);

void glslopt_set_max_unroll_iterations (struct glslopt_ctx* ctx, unsigned iterations);

glslopt_shader* glslopt_optimize (struct glslopt_ctx* ctx, enum glslopt_shader_type type, const char* shaderSource, unsigned options);
bool glslopt_get_status (struct glslopt_shader* shader);
const char* glslopt_get_output (struct glslopt_shader* shader);
const char* glslopt_get_raw_output (struct glslopt_shader* shader);
const char* glslopt_get_log (struct glslopt_shader* shader);
void glslopt_shader_delete (struct glslopt_shader* shader);

int glslopt_shader_get_input_count (struct glslopt_shader* shader);
void glslopt_shader_get_input_desc (struct glslopt_shader* shader, int index, const char** outName, enum glslopt_basic_type* outType, enum glslopt_precision* outPrec, int* outVecSize, int* outMatSize, int* outArraySize, int* outLocation);
int glslopt_shader_get_uniform_count (struct glslopt_shader* shader);
int glslopt_shader_get_uniform_total_size (struct glslopt_shader* shader);
void glslopt_shader_get_uniform_desc (struct glslopt_shader* shader, int index, const char** outName, enum glslopt_basic_type* outType, enum glslopt_precision* outPrec, int* outVecSize, int* outMatSize, int* outArraySize, int* outLocation);
int glslopt_shader_get_texture_count (struct glslopt_shader* shader);
void glslopt_shader_get_texture_desc (struct glslopt_shader* shader, int index, const char** outName, enum glslopt_basic_type* outType, enum glslopt_precision* outPrec, int* outVecSize, int* outMatSize, int* outArraySize, int* outLocation);

// Get *very* approximate shader stats:
// Number of math, texture and flow control instructions.
void glslopt_shader_get_stats (struct glslopt_shader* shader, int* approxMath, int* approxTex, int* approxFlow);


#endif /* GLSL_OPTIMIZER_H */
