#pragma once

/**
 * @file ogl_constants.h
 * @brief Most of used OpenGL constants (type related constants are in ogl_types.h)
 */


#include "ogl_types.h"

#ifdef __cplusplus

const GLenum GL_FALSE = 0;
const GLenum GL_TRUE = 1;


const GLenum GL_DEPTH_BUFFER_BIT = 0x00000100;
const GLenum GL_STENCIL_BUFFER_BIT = 0x00000400;
const GLenum GL_COLOR_BUFFER_BIT = 0x00004000;


/* Stencil */
const GLenum GL_STENCIL_BITS = 0x0D57;
const GLenum GL_STENCIL_TEST = 0x0B90;
const GLenum GL_STENCIL_CLEAR_VALUE = 0x0B91;
const GLenum GL_STENCIL_FUNC = 0x0B92;
const GLenum GL_STENCIL_VALUE_MASK = 0x0B93;
const GLenum GL_STENCIL_FAIL = 0x0B94;
const GLenum GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
const GLenum GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
const GLenum GL_STENCIL_REF = 0x0B97;
const GLenum GL_STENCIL_WRITEMASK = 0x0B98;
const GLenum GL_STENCIL_INDEX = 0x1901;
const GLenum GL_KEEP = 0x1E00;
const GLenum GL_REPLACE = 0x1E01;
const GLenum GL_INCR = 0x1E02;
const GLenum GL_DECR = 0x1E03;

/* Pixel Mode / Transfer */
const GLenum GL_MAP_COLOR =  0x0D10;
const GLenum GL_MAP_STENCIL =  0x0D11;
const GLenum GL_INDEX_SHIFT =  0x0D12;
const GLenum GL_INDEX_OFFSET =  0x0D13;
const GLenum GL_RED_SCALE =  0x0D14;
const GLenum GL_RED_BIAS =  0x0D15;
const GLenum GL_GREEN_SCALE =  0x0D18;
const GLenum GL_GREEN_BIAS =  0x0D19;
const GLenum GL_BLUE_SCALE =  0x0D1A;
const GLenum GL_BLUE_BIAS =  0x0D1B;
const GLenum GL_ALPHA_SCALE =  0x0D1C;
const GLenum GL_ALPHA_BIAS =  0x0D1D;
const GLenum GL_DEPTH_SCALE =  0x0D1E;
const GLenum GL_DEPTH_BIAS =  0x0D1F;
const GLenum GL_PIXEL_MAP_S_TO_S_SIZE =  0x0CB1;
const GLenum GL_PIXEL_MAP_I_TO_I_SIZE =  0x0CB0;
const GLenum GL_PIXEL_MAP_I_TO_R_SIZE =  0x0CB2;
const GLenum GL_PIXEL_MAP_I_TO_G_SIZE =  0x0CB3;
const GLenum GL_PIXEL_MAP_I_TO_B_SIZE =  0x0CB4;
const GLenum GL_PIXEL_MAP_I_TO_A_SIZE =  0x0CB5;
const GLenum GL_PIXEL_MAP_R_TO_R_SIZE =  0x0CB6;
const GLenum GL_PIXEL_MAP_G_TO_G_SIZE =  0x0CB7;
const GLenum GL_PIXEL_MAP_B_TO_B_SIZE =  0x0CB8;
const GLenum GL_PIXEL_MAP_A_TO_A_SIZE =  0x0CB9;
const GLenum GL_PIXEL_MAP_S_TO_S =  0x0C71;
const GLenum GL_PIXEL_MAP_I_TO_I =  0x0C70;
const GLenum GL_PIXEL_MAP_I_TO_R =  0x0C72;
const GLenum GL_PIXEL_MAP_I_TO_G =  0x0C73;
const GLenum GL_PIXEL_MAP_I_TO_B =  0x0C74;
const GLenum GL_PIXEL_MAP_I_TO_A =  0x0C75;
const GLenum GL_PIXEL_MAP_R_TO_R =  0x0C76;
const GLenum GL_PIXEL_MAP_G_TO_G =  0x0C77;
const GLenum GL_PIXEL_MAP_B_TO_B =  0x0C78;
const GLenum GL_PIXEL_MAP_A_TO_A =  0x0C79;
const GLenum GL_PACK_ALIGNMENT =  0x0D05;
const GLenum GL_PACK_LSB_FIRST =  0x0D01;
const GLenum GL_PACK_ROW_LENGTH =  0x0D02;
const GLenum GL_PACK_SKIP_PIXELS =  0x0D04;
const GLenum GL_PACK_SKIP_ROWS =  0x0D03;
const GLenum GL_PACK_SWAP_BYTES =  0x0D00;
const GLenum GL_UNPACK_ALIGNMENT =  0x0CF5;
const GLenum GL_UNPACK_LSB_FIRST =  0x0CF1;
const GLenum GL_UNPACK_ROW_LENGTH =  0x0CF2;
const GLenum GL_UNPACK_SKIP_PIXELS =  0x0CF4;
const GLenum GL_UNPACK_SKIP_ROWS =  0x0CF3;
const GLenum GL_UNPACK_SWAP_BYTES =  0x0CF0;
const GLenum GL_ZOOM_X =  0x0D16;
const GLenum GL_ZOOM_Y =  0x0D17;

/* Hints */
const GLenum GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50;
const GLenum GL_POINT_SMOOTH_HINT = 0x0C51;
const GLenum GL_LINE_SMOOTH_HINT = 0x0C52;
const GLenum GL_POLYGON_SMOOTH_HINT = 0x0C53;
const GLenum GL_FOG_HINT = 0x0C54;
const GLenum GL_DONT_CARE = 0x1100;
const GLenum GL_FASTEST = 0x1101;
const GLenum GL_NICEST = 0x1102;

/* Gets */
const GLenum GL_ATTRIB_STACK_DEPTH = 0x0BB0;
const GLenum GL_CLIENT_ATTRIB_STACK_DEPTH = 0x0BB1;
const GLenum GL_COLOR_CLEAR_VALUE = 0x0C22;
const GLenum GL_COLOR_WRITEMASK = 0x0C23;
const GLenum GL_CURRENT_INDEX = 0x0B01;
const GLenum GL_CURRENT_COLOR = 0x0B00;
const GLenum GL_CURRENT_NORMAL = 0x0B02;
const GLenum GL_CURRENT_RASTER_COLOR = 0x0B04;
const GLenum GL_CURRENT_RASTER_DISTANCE = 0x0B09;
const GLenum GL_CURRENT_RASTER_INDEX = 0x0B05;
const GLenum GL_CURRENT_RASTER_POSITION = 0x0B07;
const GLenum GL_CURRENT_RASTER_TEXTURE_COORDS = 0x0B06;
const GLenum GL_CURRENT_RASTER_POSITION_VALID = 0x0B08;
const GLenum GL_CURRENT_TEXTURE_COORDS = 0x0B03;
const GLenum GL_INDEX_CLEAR_VALUE = 0x0C20;
const GLenum GL_INDEX_MODE = 0x0C30;
const GLenum GL_INDEX_WRITEMASK = 0x0C21;
const GLenum GL_MODELVIEW_MATRIX = 0x0BA6;
const GLenum GL_MODELVIEW_STACK_DEPTH = 0x0BA3;
const GLenum GL_NAME_STACK_DEPTH = 0x0D70;
const GLenum GL_PROJECTION_MATRIX = 0x0BA7;
const GLenum GL_PROJECTION_STACK_DEPTH = 0x0BA4;
const GLenum GL_RENDER_MODE = 0x0C40;
const GLenum GL_RGBA_MODE = 0x0C31;
const GLenum GL_TEXTURE_MATRIX = 0x0BA8;
const GLenum GL_TEXTURE_STACK_DEPTH = 0x0BA5;
const GLenum GL_VIEWPORT = 0x0BA2;

/* Polygons */
const GLenum GL_POINT = 0x1B00;
const GLenum GL_LINE = 0x1B01;
const GLenum GL_FILL = 0x1B02;
const GLenum GL_CW = 0x0900;
const GLenum GL_CCW = 0x0901;
const GLenum GL_FRONT = 0x0404;
const GLenum GL_BACK = 0x0405;
const GLenum GL_POLYGON_MODE = 0x0B40;
const GLenum GL_POLYGON_SMOOTH = 0x0B41;
const GLenum GL_POLYGON_STIPPLE = 0x0B42;
const GLenum GL_EDGE_FLAG = 0x0B43;
const GLenum GL_CULL_FACE = 0x0B44;
const GLenum GL_CULL_FACE_MODE = 0x0B45;
const GLenum GL_FRONT_FACE = 0x0B46;
const GLenum GL_POLYGON_OFFSET_FACTOR = 0x8038;
const GLenum GL_POLYGON_OFFSET_UNITS = 0x2A00;
const GLenum GL_POLYGON_OFFSET_POINT = 0x2A01;
const GLenum GL_POLYGON_OFFSET_LINE = 0x2A02;
const GLenum GL_POLYGON_OFFSET_FILL = 0x8037;

/* Scissor box */
const GLenum GL_SCISSOR_BOX = 0x0C10;
const GLenum GL_SCISSOR_TEST = 0x0C11;

/* Points */
const GLenum GL_POINT_SMOOTH = 0x0B10;
const GLenum GL_POINT_SIZE = 0x0B11;
const GLenum GL_POINT_SIZE_GRANULARITY = 0x0B13;
const GLenum GL_POINT_SIZE_RANGE = 0x0B12;

/* Depth buffer */
const GLenum GL_NEVER = 0x0200;
const GLenum GL_LESS = 0x0201;
const GLenum GL_EQUAL = 0x0202;
const GLenum GL_LEQUAL = 0x0203;
const GLenum GL_GREATER = 0x0204;
const GLenum GL_NOTEQUAL = 0x0205;
const GLenum GL_GEQUAL = 0x0206;
const GLenum GL_ALWAYS = 0x0207;
const GLenum GL_DEPTH_TEST = 0x0B71;
const GLenum GL_DEPTH_BITS = 0x0D56;
const GLenum GL_DEPTH_CLEAR_VALUE = 0x0B73;
const GLenum GL_DEPTH_FUNC = 0x0B74;
const GLenum GL_DEPTH_RANGE = 0x0B70;
const GLenum GL_DEPTH_WRITEMASK = 0x0B72;
const GLenum GL_DEPTH_COMPONENT = 0x1902;

/* Logic Ops */
const GLenum GL_LOGIC_OP = 0x0BF1;
const GLenum GL_INDEX_LOGIC_OP = 0x0BF1;
const GLenum GL_COLOR_LOGIC_OP = 0x0BF2;
const GLenum GL_LOGIC_OP_MODE = 0x0BF0;
const GLenum GL_CLEAR = 0x1500;
const GLenum GL_SET = 0x150F;
const GLenum GL_COPY = 0x1503;
const GLenum GL_COPY_INVERTED = 0x150C;
const GLenum GL_NOOP = 0x1505;
const GLenum GL_INVERT = 0x150A;
const GLenum GL_AND = 0x1501;
const GLenum GL_NAND = 0x150E;
const GLenum GL_OR = 0x1507;
const GLenum GL_NOR = 0x1508;
const GLenum GL_XOR = 0x1506;
const GLenum GL_EQUIV = 0x1509;
const GLenum GL_AND_REVERSE = 0x1502;
const GLenum GL_AND_INVERTED = 0x1504;
const GLenum GL_OR_REVERSE = 0x150B;
const GLenum GL_OR_INVERTED = 0x150D;

/** Draw Modes */

const GLenum GL_POINTS = 0x0;
const GLenum GL_LINE_STRIP = 0x3;
const GLenum GL_LINE_LOOP = 0x2;
const GLenum GL_LINES = 0x1;
const GLenum GL_TRIANGLE_STRIP = 0x5;
const GLenum GL_TRIANGLE_FAN = 0x6;
const GLenum GL_TRIANGLES = 0x4;
const GLenum GL_QUAD_STRIP = 0x8;
const GLenum GL_QUADS = 0x7;

/** Framebuffers */




/** Textures */

const GLenum GL_RGB = 0x1907;
const GLenum GL_RGBA = 0x1908;
const GLenum GL_RGB4 = 0x804F;
const GLenum GL_RGB5 = 0x8050;
const GLenum GL_RGB8 = 0x8051;
const GLenum GL_RGB10 = 0x8052;
const GLenum GL_RGB12 = 0x8053;
const GLenum GL_RGB16 = 0x8054;
const GLenum GL_RGBA2 = 0x8055;
const GLenum GL_RGBA4 = 0x8056;
const GLenum GL_RGB5_A1 = 0x8057;
const GLenum GL_RGBA8 = 0x8058;
const GLenum GL_RGB10_A2 = 0x8059;
const GLenum GL_RGBA12 = 0x805A;
const GLenum GL_RGBA16 = 0x805B;
const GLenum GL_R3_G3_B2 = 0x2A10;

const GLenum GL_TEXTURE_ENV = 0x2300;
const GLenum GL_TEXTURE_ENV_MODE = 0x2200;
const GLenum GL_TEXTURE_1D = 0x0DE0;
const GLenum GL_TEXTURE_2D = 0x0DE1;
const GLenum GL_TEXTURE_WRAP_S = 0x2802;
const GLenum GL_TEXTURE_WRAP_T = 0x2803;
const GLenum GL_TEXTURE_PRIORITY = 0x8066;
const GLenum GL_TEXTURE_MAG_FILTER = 0x2800;
const GLenum GL_TEXTURE_MIN_FILTER = 0x2801;
const GLenum GL_TEXTURE_ENV_COLOR = 0x2201;
const GLenum GL_TEXTURE_GEN_S = 0x0C60;
const GLenum GL_TEXTURE_GEN_T = 0x0C61;
const GLenum GL_TEXTURE_GEN_R = 0x0C62;
const GLenum GL_TEXTURE_GEN_Q = 0x0C63;
const GLenum GL_TEXTURE_GEN_MODE = 0x2500;
const GLenum GL_TEXTURE_BORDER_COLOR = 0x1004;
const GLenum GL_TEXTURE_WIDTH = 0x1000;
const GLenum GL_TEXTURE_HEIGHT = 0x1001;
const GLenum GL_TEXTURE_BORDER = 0x1005;
const GLenum GL_TEXTURE_COMPONENTS = 0x1003;
const GLenum GL_TEXTURE_RED_SIZE = 0x805C;
const GLenum GL_TEXTURE_GREEN_SIZE = 0x805D;
const GLenum GL_TEXTURE_BLUE_SIZE = 0x805E;
const GLenum GL_TEXTURE_ALPHA_SIZE = 0x805F;
const GLenum GL_TEXTURE_LUMINANCE_SIZE = 0x8060;
const GLenum GL_TEXTURE_INTENSITY_SIZE = 0x8061;
const GLenum GL_NEAREST_MIPMAP_NEAREST = 0x2700;
const GLenum GL_NEAREST_MIPMAP_LINEAR = 0x2702;
const GLenum GL_LINEAR_MIPMAP_NEAREST = 0x2701;
const GLenum GL_LINEAR_MIPMAP_LINEAR = 0x2703;
const GLenum GL_OBJECT_LINEAR = 0x2401;
const GLenum GL_OBJECT_PLANE = 0x2501;
const GLenum GL_EYE_LINEAR = 0x2400;
const GLenum GL_EYE_PLANE = 0x2502;
const GLenum GL_SPHERE_MAP = 0x2402;
const GLenum GL_DECAL = 0x2101;
const GLenum GL_MODULATE = 0x2100;
const GLenum GL_NEAREST = 0x2600;
const GLenum GL_REPEAT = 0x2901;
const GLenum GL_CLAMP = 0x2900;
const GLenum GL_S = 0x2000;
const GLenum GL_T = 0x2001;
const GLenum GL_R = 0x2002;
const GLenum GL_Q = 0x2003;
const GLenum GL_COLOR_INDEX = 0x1900;

const GLenum GL_LINEAR = 0x2601;

/** String Requests */

const GLenum GL_VENDOR = 0x1F00;
const GLenum GL_RENDERER = 0x1F01;
const GLenum GL_VERSION = 0x1F02;
const GLenum GL_EXTENSIONS = 0x1F03;

/* Vertex Arrays */
const GLenum GL_VERTEX_ARRAY =  0x8074;
const GLenum GL_NORMAL_ARRAY =  0x8075;
const GLenum GL_COLOR_ARRAY =  0x8076;
const GLenum GL_INDEX_ARRAY =  0x8077;
const GLenum GL_TEXTURE_COORD_ARRAY =  0x8078;
const GLenum GL_EDGE_FLAG_ARRAY =  0x8079;
const GLenum GL_VERTEX_ARRAY_SIZE =  0x807A;
const GLenum GL_VERTEX_ARRAY_TYPE =  0x807B;
const GLenum GL_VERTEX_ARRAY_STRIDE =  0x807C;
const GLenum GL_NORMAL_ARRAY_TYPE =  0x807E;
const GLenum GL_NORMAL_ARRAY_STRIDE =  0x807F;
const GLenum GL_COLOR_ARRAY_SIZE =  0x8081;
const GLenum GL_COLOR_ARRAY_TYPE =  0x8082;
const GLenum GL_COLOR_ARRAY_STRIDE =  0x8083;
const GLenum GL_INDEX_ARRAY_TYPE =  0x8085;
const GLenum GL_INDEX_ARRAY_STRIDE =  0x8086;
const GLenum GL_TEXTURE_COORD_ARRAY_SIZE =  0x8088;
const GLenum GL_TEXTURE_COORD_ARRAY_TYPE =  0x8089;
const GLenum GL_TEXTURE_COORD_ARRAY_STRIDE =  0x808A;
const GLenum GL_EDGE_FLAG_ARRAY_STRIDE =  0x808C;
const GLenum GL_VERTEX_ARRAY_POINTER =  0x808E;
const GLenum GL_NORMAL_ARRAY_POINTER =  0x808F;
const GLenum GL_COLOR_ARRAY_POINTER =  0x8090;
const GLenum GL_INDEX_ARRAY_POINTER =  0x8091;
const GLenum GL_TEXTURE_COORD_ARRAY_POINTER =  0x8092;
const GLenum GL_EDGE_FLAG_ARRAY_POINTER =  0x8093;

/* Blending */
const GLenum GL_BLEND = 0x0BE2;
const GLenum GL_BLEND_SRC = 0x0BE1;
const GLenum GL_BLEND_DST = 0x0BE0;
const GLenum GL_ZERO = 0;
const GLenum GL_ONE = 1;
const GLenum GL_SRC_COLOR = 0x0300;
const GLenum GL_ONE_MINUS_SRC_COLOR = 0x0301;
const GLenum GL_SRC_ALPHA = 0x0302;
const GLenum GL_ONE_MINUS_SRC_ALPHA = 0x0303;
const GLenum GL_DST_ALPHA = 0x0304;
const GLenum GL_ONE_MINUS_DST_ALPHA = 0x0305;
const GLenum GL_DST_COLOR = 0x0306;
const GLenum GL_ONE_MINUS_DST_COLOR = 0x0307;
const GLenum GL_SRC_ALPHA_SATURATE = 0x0308;

/* Lighting */
const GLenum GL_LIGHTING = 0x0B50;
const GLenum GL_LIGHT0 = 0x4000;
const GLenum GL_LIGHT1 = 0x4001;
const GLenum GL_LIGHT2 = 0x4002;
const GLenum GL_LIGHT3 = 0x4003;
const GLenum GL_LIGHT4 = 0x4004;
const GLenum GL_LIGHT5 = 0x4005;
const GLenum GL_LIGHT6 = 0x4006;
const GLenum GL_LIGHT7 = 0x4007;
const GLenum GL_SPOT_EXPONENT = 0x1205;
const GLenum GL_SPOT_CUTOFF = 0x1206;
const GLenum GL_CONSTANT_ATTENUATION = 0x1207;
const GLenum GL_LINEAR_ATTENUATION = 0x1208;
const GLenum GL_QUADRATIC_ATTENUATION = 0x1209;
const GLenum GL_AMBIENT = 0x1200;
const GLenum GL_DIFFUSE = 0x1201;
const GLenum GL_SPECULAR = 0x1202;
const GLenum GL_SHININESS = 0x1601;
const GLenum GL_EMISSION = 0x1600;
const GLenum GL_POSITION = 0x1203;
const GLenum GL_SPOT_DIRECTION = 0x1204;
const GLenum GL_AMBIENT_AND_DIFFUSE = 0x1602;
const GLenum GL_COLOR_INDEXES = 0x1603;
const GLenum GL_LIGHT_MODEL_TWO_SIDE = 0x0B52;
const GLenum GL_LIGHT_MODEL_LOCAL_VIEWER = 0x0B51;
const GLenum GL_LIGHT_MODEL_AMBIENT = 0x0B53;
const GLenum GL_FRONT_AND_BACK = 0x0408;
const GLenum GL_SHADE_MODEL = 0x0B54;
const GLenum GL_FLAT = 0x1D00;
const GLenum GL_SMOOTH = 0x1D01;
const GLenum GL_COLOR_MATERIAL = 0x0B57;
const GLenum GL_COLOR_MATERIAL_FACE = 0x0B55;
const GLenum GL_COLOR_MATERIAL_PARAMETER = 0x0B56;
const GLenum GL_NORMALIZE = 0x0BA1;

/* Alpha testing */
const GLenum GL_ALPHA_TEST = 0x0BC0;
const GLenum GL_ALPHA_TEST_REF = 0x0BC2;
const GLenum GL_ALPHA_TEST_FUNC = 0x0BC1;

/* Matrix Mode */
const GLenum GL_MATRIX_MODE = 0x0BA0;
const GLenum GL_MODELVIEW = 0x1700;
const GLenum GL_PROJECTION = 0x1701;
const GLenum GL_TEXTURE = 0x1702;


#else

#define GL_FALSE 0
#define GL_TRUE 1


#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000


/* Stencil */
#define GL_STENCIL_BITS 0x0D57
#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_STENCIL_INDEX 0x1901
#define GL_KEEP 0x1E00
#define GL_REPLACE 0x1E01
#define GL_INCR 0x1E02
#define GL_DECR 0x1E03

/* Pixel Mode / Transfer */
#define GL_MAP_COLOR  0x0D10
#define GL_MAP_STENCIL  0x0D11
#define GL_INDEX_SHIFT  0x0D12
#define GL_INDEX_OFFSET  0x0D13
#define GL_RED_SCALE  0x0D14
#define GL_RED_BIAS  0x0D15
#define GL_GREEN_SCALE  0x0D18
#define GL_GREEN_BIAS  0x0D19
#define GL_BLUE_SCALE  0x0D1A
#define GL_BLUE_BIAS  0x0D1B
#define GL_ALPHA_SCALE  0x0D1C
#define GL_ALPHA_BIAS  0x0D1D
#define GL_DEPTH_SCALE  0x0D1E
#define GL_DEPTH_BIAS  0x0D1F
#define GL_PIXEL_MAP_S_TO_S_SIZE  0x0CB1
#define GL_PIXEL_MAP_I_TO_I_SIZE  0x0CB0
#define GL_PIXEL_MAP_I_TO_R_SIZE  0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE  0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE  0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE  0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE  0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE  0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE  0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE  0x0CB9
#define GL_PIXEL_MAP_S_TO_S  0x0C71
#define GL_PIXEL_MAP_I_TO_I  0x0C70
#define GL_PIXEL_MAP_I_TO_R  0x0C72
#define GL_PIXEL_MAP_I_TO_G  0x0C73
#define GL_PIXEL_MAP_I_TO_B  0x0C74
#define GL_PIXEL_MAP_I_TO_A  0x0C75
#define GL_PIXEL_MAP_R_TO_R  0x0C76
#define GL_PIXEL_MAP_G_TO_G  0x0C77
#define GL_PIXEL_MAP_B_TO_B  0x0C78
#define GL_PIXEL_MAP_A_TO_A  0x0C79
#define GL_PACK_ALIGNMENT  0x0D05
#define GL_PACK_LSB_FIRST  0x0D01
#define GL_PACK_ROW_LENGTH  0x0D02
#define GL_PACK_SKIP_PIXELS  0x0D04
#define GL_PACK_SKIP_ROWS  0x0D03
#define GL_PACK_SWAP_BYTES  0x0D00
#define GL_UNPACK_ALIGNMENT  0x0CF5
#define GL_UNPACK_LSB_FIRST  0x0CF1
#define GL_UNPACK_ROW_LENGTH  0x0CF2
#define GL_UNPACK_SKIP_PIXELS  0x0CF4
#define GL_UNPACK_SKIP_ROWS  0x0CF3
#define GL_UNPACK_SWAP_BYTES  0x0CF0
#define GL_ZOOM_X  0x0D16
#define GL_ZOOM_Y  0x0D17

/* Hints */
#define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#define GL_POINT_SMOOTH_HINT 0x0C51
#define GL_LINE_SMOOTH_HINT 0x0C52
#define GL_POLYGON_SMOOTH_HINT 0x0C53
#define GL_FOG_HINT 0x0C54
#define GL_DONT_CARE 0x1100
#define GL_FASTEST 0x1101
#define GL_NICEST 0x1102

/* Gets */
#define GL_ATTRIB_STACK_DEPTH 0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH 0x0BB1
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_CURRENT_INDEX 0x0B01
#define GL_CURRENT_COLOR 0x0B00
#define GL_CURRENT_NORMAL 0x0B02
#define GL_CURRENT_RASTER_COLOR 0x0B04
#define GL_CURRENT_RASTER_DISTANCE 0x0B09
#define GL_CURRENT_RASTER_INDEX 0x0B05
#define GL_CURRENT_RASTER_POSITION 0x0B07
#define GL_CURRENT_RASTER_TEXTURE_COORDS 0x0B06
#define GL_CURRENT_RASTER_POSITION_VALID 0x0B08
#define GL_CURRENT_TEXTURE_COORDS 0x0B03
#define GL_INDEX_CLEAR_VALUE 0x0C20
#define GL_INDEX_MODE 0x0C30
#define GL_INDEX_WRITEMASK 0x0C21
#define GL_MODELVIEW_MATRIX 0x0BA6
#define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#define GL_NAME_STACK_DEPTH 0x0D70
#define GL_PROJECTION_MATRIX 0x0BA7
#define GL_PROJECTION_STACK_DEPTH 0x0BA4
#define GL_RENDER_MODE 0x0C40
#define GL_RGBA_MODE 0x0C31
#define GL_TEXTURE_MATRIX 0x0BA8
#define GL_TEXTURE_STACK_DEPTH 0x0BA5
#define GL_VIEWPORT 0x0BA2

/* Polygons */
#define GL_POINT 0x1B00
#define GL_LINE 0x1B01
#define GL_FILL 0x1B02
#define GL_CW 0x0900
#define GL_CCW 0x0901
#define GL_FRONT 0x0404
#define GL_BACK 0x0405
#define GL_POLYGON_MODE 0x0B40
#define GL_POLYGON_SMOOTH 0x0B41
#define GL_POLYGON_STIPPLE 0x0B42
#define GL_EDGE_FLAG 0x0B43
#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_FRONT_FACE 0x0B46
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_POLYGON_OFFSET_POINT 0x2A01
#define GL_POLYGON_OFFSET_LINE 0x2A02
#define GL_POLYGON_OFFSET_FILL 0x8037

/* Scissor box */
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11

/* Points */
#define GL_POINT_SMOOTH 0x0B10
#define GL_POINT_SIZE 0x0B11
#define GL_POINT_SIZE_GRANULARITY 0x0B13
#define GL_POINT_SIZE_RANGE 0x0B12

/* Depth buffer */
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_BITS 0x0D56
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_FUNC 0x0B74
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_DEPTH_COMPONENT 0x1902

/* Logic Ops */
#define GL_LOGIC_OP 0x0BF1
#define GL_INDEX_LOGIC_OP 0x0BF1
#define GL_COLOR_LOGIC_OP 0x0BF2
#define GL_LOGIC_OP_MODE 0x0BF0
#define GL_CLEAR 0x1500
#define GL_SET 0x150F
#define GL_COPY 0x1503
#define GL_COPY_INVERTED 0x150C
#define GL_NOOP 0x1505
#define GL_INVERT 0x150A
#define GL_AND 0x1501
#define GL_NAND 0x150E
#define GL_OR 0x1507
#define GL_NOR 0x1508
#define GL_XOR 0x1506
#define GL_EQUIV 0x1509
#define GL_AND_REVERSE 0x1502
#define GL_AND_INVERTED 0x1504
#define GL_OR_REVERSE 0x150B
#define GL_OR_INVERTED 0x150D

/** Draw Modes */

#define GL_POINTS 0x0
#define GL_LINE_STRIP 0x3
#define GL_LINE_LOOP 0x2
#define GL_LINES 0x1
#define GL_TRIANGLE_STRIP 0x5
#define GL_TRIANGLE_FAN 0x6
#define GL_TRIANGLES 0x4
#define GL_QUAD_STRIP 0x8
#define GL_QUADS 0x7

/** Framebuffers */




/** Textures */

#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_RGB4  0x804F
#define GL_RGB5  0x8050
#define GL_RGB8  0x8051
#define GL_RGB10  0x8052
#define GL_RGB12  0x8053
#define GL_RGB16  0x8054
#define GL_RGBA2  0x8055
#define GL_RGBA4  0x8056
#define GL_RGB5_A1  0x8057
#define GL_RGBA8  0x8058
#define GL_RGB10_A2  0x8059
#define GL_RGBA12  0x805A
#define GL_RGBA16  0x805B
#define GL_R3_G3_B2  0x2A10

#define GL_TEXTURE_ENV 0x2300
#define GL_TEXTURE_ENV_MODE 0x2200
#define GL_TEXTURE_1D 0x0DE0
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TEXTURE_PRIORITY 0x8066
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_ENV_COLOR 0x2201
#define GL_TEXTURE_GEN_S 0x0C60
#define GL_TEXTURE_GEN_T 0x0C61
#define GL_TEXTURE_GEN_R 0x0C62
#define GL_TEXTURE_GEN_Q 0x0C63
#define GL_TEXTURE_GEN_MODE 0x2500
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_TEXTURE_WIDTH 0x1000
#define GL_TEXTURE_HEIGHT 0x1001
#define GL_TEXTURE_BORDER 0x1005
#define GL_TEXTURE_COMPONENTS 0x1003
#define GL_TEXTURE_RED_SIZE 0x805C
#define GL_TEXTURE_GREEN_SIZE 0x805D
#define GL_TEXTURE_BLUE_SIZE 0x805E
#define GL_TEXTURE_ALPHA_SIZE 0x805F
#define GL_TEXTURE_LUMINANCE_SIZE 0x8060
#define GL_TEXTURE_INTENSITY_SIZE 0x8061
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_OBJECT_LINEAR 0x2401
#define GL_OBJECT_PLANE 0x2501
#define GL_EYE_LINEAR 0x2400
#define GL_EYE_PLANE 0x2502
#define GL_SPHERE_MAP 0x2402
#define GL_DECAL 0x2101
#define GL_MODULATE 0x2100
#define GL_NEAREST 0x2600
#define GL_REPEAT 0x2901
#define GL_CLAMP 0x2900
#define GL_S 0x2000
#define GL_T 0x2001
#define GL_R 0x2002
#define GL_Q 0x2003
#define GL_COLOR_INDEX 0x1900

#define GL_LINEAR 0x2601

/** String Requests */

#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03

/* Vertex Arrays */
#define GL_VERTEX_ARRAY  0x8074
#define GL_NORMAL_ARRAY  0x8075
#define GL_COLOR_ARRAY  0x8076
#define GL_INDEX_ARRAY  0x8077
#define GL_TEXTURE_COORD_ARRAY  0x8078
#define GL_EDGE_FLAG_ARRAY  0x8079
#define GL_VERTEX_ARRAY_SIZE  0x807A
#define GL_VERTEX_ARRAY_TYPE  0x807B
#define GL_VERTEX_ARRAY_STRIDE  0x807C
#define GL_NORMAL_ARRAY_TYPE  0x807E
#define GL_NORMAL_ARRAY_STRIDE  0x807F
#define GL_COLOR_ARRAY_SIZE  0x8081
#define GL_COLOR_ARRAY_TYPE  0x8082
#define GL_COLOR_ARRAY_STRIDE  0x8083
#define GL_INDEX_ARRAY_TYPE  0x8085
#define GL_INDEX_ARRAY_STRIDE  0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE  0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE  0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE  0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE  0x808C
#define GL_VERTEX_ARRAY_POINTER  0x808E
#define GL_NORMAL_ARRAY_POINTER  0x808F
#define GL_COLOR_ARRAY_POINTER  0x8090
#define GL_INDEX_ARRAY_POINTER  0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER  0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER  0x8093

/* Blending */
#define GL_BLEND 0x0BE2
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND_DST 0x0BE0
#define GL_ZERO 0
#define GL_ONE 1
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308

/* Lighting */
#define GL_LIGHTING 0x0B50
#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001
#define GL_LIGHT2 0x4002
#define GL_LIGHT3 0x4003
#define GL_LIGHT4 0x4004
#define GL_LIGHT5 0x4005
#define GL_LIGHT6 0x4006
#define GL_LIGHT7 0x4007
#define GL_SPOT_EXPONENT 0x1205
#define GL_SPOT_CUTOFF 0x1206
#define GL_CONSTANT_ATTENUATION 0x1207
#define GL_LINEAR_ATTENUATION 0x1208
#define GL_QUADRATIC_ATTENUATION 0x1209
#define GL_AMBIENT 0x1200
#define GL_DIFFUSE 0x1201
#define GL_SPECULAR 0x1202
#define GL_SHININESS 0x1601
#define GL_EMISSION 0x1600
#define GL_POSITION 0x1203
#define GL_SPOT_DIRECTION 0x1204
#define GL_AMBIENT_AND_DIFFUSE 0x1602
#define GL_COLOR_INDEXES 0x1603
#define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#define GL_LIGHT_MODEL_LOCAL_VIEWER 0x0B51
#define GL_LIGHT_MODEL_AMBIENT 0x0B53
#define GL_FRONT_AND_BACK 0x0408
#define GL_SHADE_MODEL 0x0B54
#define GL_FLAT 0x1D00
#define GL_SMOOTH 0x1D01
#define GL_COLOR_MATERIAL 0x0B57
#define GL_COLOR_MATERIAL_FACE 0x0B55
#define GL_COLOR_MATERIAL_PARAMETER 0x0B56
#define GL_NORMALIZE 0x0BA1

/* Alpha testing */
#define GL_ALPHA_TEST 0x0BC0
#define GL_ALPHA_TEST_REF 0x0BC2
#define GL_ALPHA_TEST_FUNC 0x0BC1

/* Matrix Mode */
#define GL_MATRIX_MODE 0x0BA0
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define GL_TEXTURE 0x1702

#endif