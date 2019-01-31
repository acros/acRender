#ifndef AcUTIL_H
#define AcUTIL_H

#include <stdlib.h>
#include <cassert>
#include "utils.h"

#define ACROS_USE_IMGUI	1


void logMessage(const char *formatStr, ...);

int  esGenSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals,GLfloat** colors,
	GLfloat **texCoords, GLuint **indices);

int  esGenCube(float scale, GLfloat **vertices, GLfloat **normals,
	GLfloat **texCoords, GLuint **indices);

int  esGenSquareGrid(int size, GLfloat **vertices, GLuint **indices);

int esGenMitureBufferTriangle(GLfloat **vertices, GLfloat** colors, GLuint **indices);


#define SAFE_DELETE(N) {if((N)!=nullptr) {delete (N); (N) = nullptr;}}
#define SAFE_FREE(N) {if((N)!=nullptr) {free(N); (N) = nullptr;}}


#define ACROS_GL_CHECK_ERROR(N)\
	{GLenum sx = glGetError();\
	if(sx != GL_NO_ERROR)\
		logMessage("GL Check %s : %d \n",(N),sx);\
	}


/*
#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define   __cdecl
#define ESCALLBACK  __cdecl
#else
#define 
#define ESCALLBACK
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


GLEWContext* glewGetContext();   // This needs to be defined for GLEW MX to work, along with the GLEW_MX define in the perprocessor!

#ifdef __cplusplus
}
#endif
*/
#endif // AcUTIL_H
