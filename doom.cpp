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
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <forward_list>

#include "Assets/wall.h"
#include "Assets/floor.h"
#include "Assets/config.h"
#include "Assets/player.h"
#include "Assets/glut_text.h"
#include "Assets/Texturas/scenario/wallGrime.h"
#include "Assets/Texturas/scenario/grass.h"
#include "Assets/Texturas/skybox/tex_skybox.h"
#include "Assets/skybox.h"

//Declaração do objeto jogador
Player p(PLAYER_X, PLAYER_Z, PLAYER_LX, PLAYER_LZ, PLAYER_ANGLE);

//Lista de paredes
std::forward_list<Wall> walls;
std::forward_list<Floor> floors;

int count_rate = -1;
int frames_playing = 0;
int fps = 0;
int lock_fps = FPS/2;

//Matriz de id das texturas
unsigned int id_textures[QUANT_TEX];

//Prototipagem das funções
void drawSnowMan();
int main(int argc, char **argv);
void changeSize(int w, int h);
void display(void);
void keyboardSpecialKeys(int key, int xx, int yy);
void keyboardNormalKeys(unsigned char key, int x, int y);
void drawMap();
void renderWalls(void);
void renderFloors(void);
bool checkCollision();
void textureFilters();
void framerate();
void timer(int value);

void timer(int value){
	glutTimerFunc(1000/lock_fps, timer, 0);
	glutPostRedisplay();
}

void framerate(){
	static GLuint frames = 0;
	static GLuint clock;
	static GLuint next_clock = 0;

	count_rate++;
	frames_playing++;
	frames++;

	clock = glutGet(GLUT_ELAPSED_TIME);

	if (clock < next_clock) {
		return;
	}
	fps = frames;
	if (next_clock != 0) {
		frames = 0;
		next_clock = clock + 1000;
	}
}

void textureFilters(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

//Utiliza a matriz map para desenhar o mapa.
void drawMap(){
	float size = 6;
	float width = size, depth = size;

	for (int row = 0; row <= TAM_MAP; row++) {
		for (int column = 0; column <= TAM_MAP; column++) {
			int x = width * row;
			int z = depth * column;

			if (map[row][column] == 0){
				Floor f(x, 0, z, size, id_textures[1]);
				floors.push_front(f);
			}
			if (map[row][column] == 1) {					
				Wall w(x, z, size, id_textures[0]);
				walls.push_front(w);
			}

		}
	}
}

void renderWalls(){
	for (std::forward_list<Wall>::iterator it = walls.begin(); it != walls.end(); it++) {
		it->render();
	}
}

void renderFloors(){
	for (std::forward_list<Floor>::iterator it = floors.begin(); it != floors.end(); it++) {
		it->render();
	}
}

//Checa colisão e evita que o jogador fique preso dentro da parede.
bool checkCollision(){
	float player_radius = 2.0f;
	float min_distance = 0.1f; // valor mínimo de distância entre o jogador e a parede
	
	for (std::forward_list<Wall>::iterator it = walls.begin(); it != walls.end(); it++) {
		float wall_radius = it->getSize() / 2.0f;
		float dist = sqrt(pow(p.posx() - it->getX(), 2) + pow(p.posz() - it->getZ(), 2));
		
		if (dist <= player_radius + wall_radius - min_distance) {
			float dx = p.posx() - it->getX();
			float dz = p.posz() - it->getZ();
			float len = sqrt(dx * dx + dz * dz);
			
			dx /= len;
			dz /= len;
			
			float separation = player_radius + wall_radius - dist + min_distance;
			
			dx *= separation;
			dz *= separation;

			p.setx(p.posx() + dx);
			p.setz(p.posz() + dz);
			return true;
		}
	}
	return false;
}


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

void display(void) {
	framerate();

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0.5, 1);
	
	glColor3f(1.0f, 1.0f, 1.0f);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	p.posx()		  , 1.0f, p.posz(),
				p.posx()+p.poslx(), 1.0f, p.posz()+p.poslz(),
				0.0f			  ,	1.0f, 0.0f);
	
	renderWalls();
	renderFloors();
	skybox(0, 0, 200, id_textures);

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}
	
	glutSwapBuffers();
}

void keyboardSpecialKeys(int key, int xx, int yy) {
	enum {up, down, left, right};
	switch (key) {
		case GLUT_KEY_LEFT:
			p.movement(left);
			break;
		case GLUT_KEY_RIGHT :
			p.movement(right);
			break;
		case GLUT_KEY_UP:
			if (!checkCollision()) {
				p.movement(up);
			}
			p.printPos();
			break;
		case GLUT_KEY_DOWN :
			if (!checkCollision()){
				p.movement(down);
			}
			p.printPos();			
			break;				
	}
	
}

void keyboardNormalKeys(unsigned char key, int x, int y) {
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

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboardNormalKeys);
	glutSpecialFunc(keyboardSpecialKeys);
	glutTimerFunc(1000/lock_fps, timer, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
   	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

	glGenTextures(QUANT_TEX, id_textures);
	
	glBindTexture(GL_TEXTURE_2D, id_textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, wallGrime);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	textureFilters();
	
	glBindTexture(GL_TEXTURE_2D, id_textures[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxTop);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxBottom);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxFront);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxBack);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxRight);
	textureFilters();

	glBindTexture(GL_TEXTURE_2D, id_textures[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, boxLeft);
	textureFilters();


	
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
	

	drawMap();
	glutMainLoop();

	return EXIT_SUCCESS;
}