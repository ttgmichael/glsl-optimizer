//
//  glslopt.h
//  glsl-optimizer
//
//  Created by Michael Tang on 1/26/25.
//

#include <stdbool.h>
#include "glsl/glsl_optimizer.h"

struct glslopt_ctx* glslopt_initialize (enum glslopt_target target);
void glslopt_cleanup (struct glslopt_ctx* ctx);

void glslopt_set_max_unroll_iterations (struct glslopt_ctx* ctx, unsigned iterations);

struct glslopt_shader* glslopt_optimize (struct glslopt_ctx* ctx, enum glslopt_shader_type type, const char* shaderSource, unsigned options);
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
