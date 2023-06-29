#pragma once

/**
 * @file ogl_types.h
 * @brief Declaration of OpenGL types and related constants
 */


#ifdef __cplusplus
#include <cstdint>

using OGLContext = void*;

using GLboolean = bool;// 	1+	A boolean value, either GL_TRUE or GL_FALSE
using GLbyte = char;// 	8	Signed, 2's complement binary integer	GL_BYTE
using GLubyte = unsigned char;// 	8	Unsigned binary integer	GL_UNSIGNED_BYTE
using GLshort = int16_t;// 	16	Signed, 2's complement binary integer	GL_SHORT
using GLushort = uint16_t;// 	16	Unsigned binary integer	GL_UNSIGNED_SHORT
using GLint = int32_t;// 	32	Signed, 2's complement binary integer	GL_INT
using GLuint = uint32_t;// 	32	Unsigned binary integer	GL_UNSIGNED_INT
using GLfixed = int32_t;// 	32	Signed, 2's complement 16.16 integer	GL_FIXED
using GLint64 = int64_t;// 	64	Signed, 2's complement binary integer
using GLuint64 = uint64_t;// 	64	Unsigned binary integer
using GLsizei = uint32_t;// 	32	A non-negative binary integer, for sizes.
using GLenum = uint32_t;// 	32	An OpenGL enumerator value
using GLbitfield = uint32_t;// 	32	A bitfield value
using GLfloat = float;// 	32	An IEEE-754 floating-point value	GL_FLOAT
using GLclampf = float;// 	32	An IEEE-754 floating-point value, clamped to the range [0,1]
using GLdouble = double;// 	64	An IEEE-754 floating-point value	GL_DOUBLE
using GLclampd = double;// 	64	An IEEE-754 floating-point value, clamped to the range [0,1]
using GLvoid = void;

using GLintptr = GLint*;
using GLsizeiptr = GLsizei*;
using GLsync = void*;

constexpr GLenum GL_BYTE = 0x1400;
constexpr GLenum GL_UNSIGNED_BYTE = 0x1401;
constexpr GLenum GL_SHORT = 0x1402;
constexpr GLenum GL_UNSIGNED_SHORT = 0x1403;
constexpr GLenum GL_INT = 0x1404;
constexpr GLenum GL_UNSIGNED_INT = 0x1405;
constexpr GLenum GL_FLOAT = 0x1406;
constexpr GLenum GL_2_BYTES = 0x1407;
constexpr GLenum GL_3_BYTES = 0x1408;
constexpr GLenum GL_4_BYTES = 0x1409;
constexpr GLenum GL_DOUBLE = 0x140A;

#else

#include <stdint.h>

typedef  char GLboolean; // 	1+	A boolean value, either GL_TRUE or GL_FALSE
typedef  char GLbyte; //; 	8	Signed, 2's complement binary integer	GL_BYTE
typedef  unsigned char GLubyte; // 	8	Unsigned binary integer	GL_UNSIGNED_BYTE
typedef  int16_t GLshort; // 	16	Signed, 2's complement binary integer	GL_SHORT
typedef  uint16_t GLushort; // 	16	Unsigned binary integer	GL_UNSIGNED_SHORT
typedef  int32_t GLint; // 	32	Signed, 2's complement binary integer	GL_INT
typedef  uint32_t GLuint; // 	32	Unsigned binary integer	GL_UNSIGNED_INT
typedef  int32_t GLfixed; // 	32	Signed, 2's complement 16.16 integer	GL_FIXED
typedef  int64_t GLint64; // 	64	Signed, 2's complement binary integer
typedef  uint64_t GLuint64; // 	64	Unsigned binary integer
typedef  uint32_t GLsizei; // 	32	A non-negative binary integer, for sizes.
typedef  uint32_t GLenum; // 	32	An OpenGL enumerator value
typedef  uint32_t GLbitfield; // 	32	A bitfield value
typedef  float GLfloat; // 	32	An IEEE-754 floating-point value	GL_FLOAT
typedef  float GLclampf; // 	32	An IEEE-754 floating-point value, clamped to the range [0,1]
typedef  double GLdouble; // 	64	An IEEE-754 floating-point value	GL_DOUBLE
typedef  double GLclampd; // 	64	An IEEE-754 floating-point value, clamped to the range [0,1]
typedef  void GLvoid;

typedef  GLint* GLintptr ;
typedef  GLsizei* GLsizeiptr ;
typedef  void* GLsync ;

#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_2_BYTES 0x1407
#define GL_3_BYTES 0x1408
#define GL_4_BYTES 0x1409
#define GL_DOUBLE 0x140A

#endif