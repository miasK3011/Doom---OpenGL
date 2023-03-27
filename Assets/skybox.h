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

#ifndef skybox_h
#define skybox_h

inline void skybox(float m_x, float m_z, float m_size, GLuint m_texture[8]){
    glPushMatrix();
    glTranslatef(m_x, m_size/2, m_z);
    // metade do tamanho
    float hs = m_size * 0.5f;

    // habilita texturas
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.3, 0.3, 1);
    
    // define as texturas para cada face do cubo
	glBindTexture(GL_TEXTURE_2D, m_texture[4]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs, -hs,  hs);
    glTexCoord2f(1.0, 0.0); glVertex3f( hs, -hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f(-hs,  hs,  hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[5]);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f( hs, -hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs, -hs, -hs);
    glTexCoord2f(1.0, 1.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[7]);
	glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-hs, -hs, -hs);
	glTexCoord2f(1.0, 0.0); glVertex3f(-hs, -hs,  hs);
	glTexCoord2f(1.0, 1.0); glVertex3f(-hs,  hs,  hs);
	glTexCoord2f(0.0, 1.0); glVertex3f(-hs,  hs, -hs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[6]);
	glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f( hs, -hs,  hs);
	glTexCoord2f(1.0, 0.0); glVertex3f( hs, -hs, -hs);
	glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs, -hs);
	glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs,  hs);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs,  hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[3]);
	glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-hs,  hs, -hs);
    glTexCoord2f(1.0, 0.0); glVertex3f(-hs,  hs,  hs);
    glTexCoord2f(1.0, 1.0); glVertex3f( hs,  hs,  hs);
    glTexCoord2f(0.0, 1.0); glVertex3f( hs,  hs, -hs);
    glEnd();

	glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

#endif