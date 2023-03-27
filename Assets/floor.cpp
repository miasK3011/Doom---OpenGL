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


Floor::Floor(float x, float y, float z, float tam){
    m_x = x;
    m_y = y;
    m_z = z;
    m_tam = tam;
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

	floorNormals[0][0] = -hs;
	floorNormals[0][1] = 0;
	floorNormals[0][2] = -hs;

	floorNormals[1][0] = -hs;
	floorNormals[1][1] = 0;
	floorNormals[1][2] = hs;
	
	floorNormals[2][0] = hs;
	floorNormals[2][1] = 0;
	floorNormals[2][2] = hs;

	floorNormals[3][0] = hs;
	floorNormals[3][1] = 0;
	floorNormals[3][2] = -hs;

	normalize(floorNormals, 4);

	glPushMatrix();
	glTranslatef(m_x, m_y, m_z);
	glColor3f(0, 0.6, 0);
	glBegin(GL_QUADS);
		glNormal3f(floorNormals[0][0], floorNormals[0][1] , floorNormals[0][2]);
		glVertex3f(-hs, 0, -hs);
		glNormal3f(floorNormals[1][0], floorNormals[1][1] , floorNormals[1][2]);
		glVertex3f(-hs, 0,  hs);
		glNormal3f(floorNormals[2][0], floorNormals[2][1] , floorNormals[2][2]);
		glVertex3f( hs, 0,  hs);
		glNormal3f(floorNormals[3][0], floorNormals[3][1] , floorNormals[3][2]);
		glVertex3f( hs, 0, -hs);
	glEnd();
	glPopMatrix();

}