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

#include <cstdio>

#include "Assets/config.h"
#include "Assets/player.h"

//Prototipagem das funções
void drawSnowMan();
int main(int argc, char **argv);
void processSpecialKeys(int key, int xx, int yy);
void renderScene(void);
void processNormalKeys(unsigned char key, int x, int y);
void changeSize(int w, int h);
void drawParede(float posx, float posz, float w, float h);

//Declaração do objeto jogador
Player p;

void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);
// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);
// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

// Posx, Posz = Posição da parede.
// w, h = altura e largura da parede.
void drawParede(float posx, float posz, float w, float h){
	glBegin(GL_QUADS);
		glVertex3f(posx, h, posz);
		glVertex3f(posx+w, h, posz);
		glVertex3f(posx+w, 0, posz);
		glVertex3f(posx, 0, posz);
	glEnd();	
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(6.0, 6.0, 6.0, 1.0);

	GLfloat light_pos[] = {-2.0, 2.0, 2.0, 0.0};
	GLfloat light_Ka[] = {0.4, 0.4, 0.4, 0.0};
	GLfloat light_Kd[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_Ks[] = {1.0, 1.0, 1.0, 0.0};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	p.x, 1.0f, p.z,
			p.x+p.lx, 1.0f,  p.z+p.lz,
			0.0f, 1.0f,  0.0f);

        // Draw ground
	
	
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	drawParede(-20.0f, -15.0f, 5.0f, 5.0f);

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
	enum {up, down, left, right};

	switch (key) {
		case GLUT_KEY_LEFT:
			p.movement(left);
			break;
		case GLUT_KEY_RIGHT :
			p.movement(right);
			break;
		case GLUT_KEY_UP :
			p.movement(up);
			break;
		case GLUT_KEY_DOWN :
			p.movement(down);			
			break;
	}
	p.printPos();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void changeSize(int w, int h) {

	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition((1336-JANELA_X)/2,(736-JANELA_Y)/2);
	glutInitWindowSize(JANELA_X, JANELA_Y);
	glutCreateWindow("Doom");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);

	glutMainLoop();

	return 1;
}