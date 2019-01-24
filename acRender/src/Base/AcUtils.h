#ifndef AcUTIL_H
#define AcUTIL_H

#include <stdlib.h>
#include <cassert>


void logMessage(const char *formatStr, ...);

int  esGenSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
	GLfloat **texCoords, GLuint **indices);

int  esGenCube(float scale, GLfloat **vertices, GLfloat **normals,
	GLfloat **texCoords, GLuint **indices);

int  esGenSquareGrid(int size, GLfloat **vertices, GLuint **indices);


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