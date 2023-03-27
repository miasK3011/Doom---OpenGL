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

#include <cmath>
#include "floor.h"
#include "config.h"


Floor::Floor(float x, float y, float z, float tam, GLint texture){
    m_x = x;
    m_y = y;
    m_z = z;
    m_tam = tam;
	m_tex = texture;
}

void Floor::normalize(GLfloat (*vertices)[3], int num_vertices) {
    float length = 0.0f;

    // Calcula o comprimento do vetor
    for (int i = 0; i < num_vertices; i += 3) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float z = vertices[i][2];

        length += x*x + y*y + z*z;
    }

    length = sqrt(length);

    // Divide as coordenadas pelo comprimento do vetor
    for (int i = 0; i < num_vertices; i += 3) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float z = vertices[i][2];

        vertices[i][0] = x / length;
        vertices[i][1] = y / length;
        vertices[i][2] = z / length;
    }
}

void Floor::render(){
    float hs = m_tam/2;

	glPushMatrix();
	glTranslatef(m_x, m_y, m_z);
	glColor3f(0.0f, 0.5f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0.0, 0.0);glVertex3f(-hs, 0, -hs);		
		glTexCoord2f(1.0, 0.0);glVertex3f(-hs, 0,  hs);
		glTexCoord2f(1.0, 1.0);glVertex3f(hs, 0,  hs);
		glTexCoord2f(0.0, 1.0);glVertex3f(hs, 0,  -hs);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}