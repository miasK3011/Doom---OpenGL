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

#ifndef wall_h
#define wall_h

class Wall  {
    public:
        Wall(float x, float z, float size, GLuint texture);
        void render(void);
        float getSize();
        float getPosx();
        float getPosz();
    private:
        float m_x, m_z;
        float m_size;
        GLuint m_texture;
};

#endif





