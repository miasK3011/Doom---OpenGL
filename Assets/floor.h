#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


#ifndef floor_h
#define floor_h

class Floor {
    public:
        Floor(float x, float y, float z, float tam);
        void render();
        void normalize(GLfloat (*vertices)[3], int num_vertices);
    private:
        float m_x, m_y, m_z, m_tam;
};

#endif