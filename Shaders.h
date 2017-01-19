

static const char* concursionPoint_frg =
"#version 150\n"
"\n"
"in vec4 final_color;\n"
"out vec4 frag_color;\n"
"\n"
"void main() \n"
"{\n"
"	frag_color = final_color;\n"
"}\n"
;


static const char* concursionPoint_vrt =
"#version 150\n"
"\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"\n"
"uniform vec4 color;\n"
"\n"
"in vec3 pos;\n"
"\n"
"out vec4 final_color;\n"
"\n"
"void main()\n"
"{\n"
"	vec4 mv_Pos = viewMatrix*modelMatrix*vec4(0.0,0.0,0.0,1.0);\n"
"	mv_Pos += vec4(pos,0.0);\n"
"	gl_Position = projectionMatrix*mv_Pos;\n"
"	final_color = color;\n"
"}\n"
"\n"
;


static const char* glowSphere_frg =
"#version 150\n"
"\n"
"in vec2 orig_pos;\n"
"in vec4 final_color;\n"
"\n"
"out vec4 frag_color;\n"
"\n"
"void main() \n"
"{\n"
"    float radius = abs(length(orig_pos)) * 1.414;\n"
"	if (radius < 1) {\n"
"		frag_color = final_color * (1.0 - radius*radius);\n"
"	} else {\n"
"		frag_color = vec4(0,0,0,1);\n"
"	}\n"
"}\n"
;


static const char* glowSphere_vrt =
"#version 150\n"
"\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"\n"
"uniform vec4 color;\n"
"\n"
"in vec3 pos;\n"
"\n"
"out vec2 orig_pos;\n"
"out vec4 final_color;\n"
"\n"
"void main()\n"
"{\n"
"	orig_pos = normalize(vec2(pos));\n"
"	vec4 mv_pos = viewMatrix*modelMatrix*vec4(0.0,0.0,0.0,1.0);\n"
"	mv_pos += vec4(pos,0.0);\n"
"	gl_Position = projectionMatrix*mv_pos;\n"
"	\n"
"	// Pass along the color\n"
"	final_color = color;\n"
"}\n"
"\n"
;


static const char* scanLine_frg =
"#version 150\n"
"in vec2 pass_texcoord;\n"
"\n"
"uniform sampler2D texFramebuffer;\n"
"uniform int scan_lines;\n"
"\n"
"out vec4 frag_color;\n"
"\n"
"void main() {\n"
"	vec4 pixel = texture(texFramebuffer, pass_texcoord);\n"
"	pixel = floor(pixel*16)/16;\n"
"	float mag;\n"
"	int mod_coord = int(mod(gl_FragCoord.y,scan_lines));\n"
"	int adj_coord = abs(mod_coord - scan_lines/2);\n"
"//	if (mod_coord == 0) {\n"
"//	    frag_color = vec4(0.0,1.0,0.0,1.0);\n"
"//	} else if (mod_coord == scan_lines -1) {\n"
"//	    frag_color = vec4(1.0,0.0,0.0,1.0);\n"
"//	} else if (adj_coord == 0) {\n"
"//	    frag_color = vec4(0.0,0.0,1.0,1.0);	\n"
"	mag = 1 - float(adj_coord)/float(scan_lines);\n"
"	frag_color = pixel*mag;\n"
"	\n"
"}\n"
;


static const char* scanLine_vrt =
"#version 150\n"
"in vec2 pos;\n"
"in vec2 tex;\n"
"\n"
"out vec2 pass_texcoord;\n"
"\n"
"void main() {\n"
"    gl_Position = vec4(pos, 0.0, 1.0);\n"
"    pass_texcoord = tex;\n"
"}\n"
;


static const char* simpleIndexedColor_frg =
"#version 150\n"
"\n"
"in vec4 final_color;\n"
"out vec4 frag_color;\n"
"\n"
"void main() \n"
"{\n"
"	frag_color = final_color;\n"
"}\n"
;


static const char* simpleIndexedColor_vrt =
"#version 150\n"
"\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"\n"
"in vec3 pos;\n"
"in vec4 color;\n"
"\n"
"out vec4 final_color;\n"
"\n"
"void main()\n"
"{    \n"
"	gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(pos,1.0);\n"
"	\n"
"	final_color = color;\n"
"}\n"
"\n"
;

static const int shaderCount = 8;

static const char* const programNames[] = {
    "concursionPoint",
    "concursionPoint",
    "glowSphere",
    "glowSphere",
    "scanLine",
    "scanLine",
    "simpleIndexedColor",
    "simpleIndexedColor",
};


static const char* const shaderNames[] = {
    "concursionPoint_frg",
    "concursionPoint_vrt",
    "glowSphere_frg",
    "glowSphere_vrt",
    "scanLine_frg",
    "scanLine_vrt",
    "simpleIndexedColor_frg",
    "simpleIndexedColor_vrt",
};


static const char* const shaderText[] = {
    concursionPoint_frg,
    concursionPoint_vrt,
    glowSphere_frg,
    glowSphere_vrt,
    scanLine_frg,
    scanLine_vrt,
    simpleIndexedColor_frg,
    simpleIndexedColor_vrt,
};

enum ShaderTypeEnum {
    FRAGMENT = 0,
    VERTEX = 1
};

static const ShaderTypeEnum shaderType[] = {
    FRAGMENT,
    VERTEX,
    FRAGMENT,
    VERTEX,
    FRAGMENT,
    VERTEX,
    FRAGMENT,
    VERTEX,
};

