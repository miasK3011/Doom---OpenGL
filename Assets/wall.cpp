#include <cstdio>
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

#include "wall.h"

Wall::Wall(float x, float z, float size, GLuint texture) {
    m_x = x;
    m_z = z;
    m_size = size;
    m_texture = texture;
}

void Wall::render(void) {
    glPushMatrix();
    glTranslatef(m_x, m_size/2, m_z);
    // metade do tamanho
    float hs = m_size * 0.5f;

    // habilita texturas
    glEnable(GL_TEXTURE_2D);

    // define as texturas para cada face do cubo
	glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs, -hs,  hs);
    glTexCoord2f(1.0, 0.0); glVertex3f( hs, -hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f(-hs,  hs,  hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f( hs, -hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs, -hs, -hs);
    glTexCoord2f(1.0, 1.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-hs, -hs, -hs);
	glTexCoord2f(1.0, 0.0); glVertex3f(-hs, -hs,  hs);
	glTexCoord2f(1.0, 1.0); glVertex3f(-hs,  hs,  hs);
	glTexCoord2f(0.0, 1.0); glVertex3f(-hs,  hs, -hs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f( hs, -hs,  hs);
	glTexCoord2f(1.0, 0.0); glVertex3f( hs, -hs, -hs);
	glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs, -hs);
	glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs,  hs);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs,  hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs,  hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

float Wall::getSize(){
    return m_size;
}

float Wall::getX(){
    return m_x;
}

float Wall::getZ(){
    return m_z;
}
