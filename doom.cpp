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
#include <math.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

using namespace std;

#include "Assets/wall.h"
#include "Assets/floor.h"
#include "Assets/config.h"
#include "Assets/player.h"
#include "Assets/enemy.h"
#include "Assets/glut_text.h"
#include "Assets/Texturas/scenario/wallGrime.h"
#include "Assets/Texturas/scenario/grass.h"
#include "Assets/Texturas/skybox/tex_skybox.h"
#include "Assets/skybox.h"

ALuint a_pistol;

void load_audio(const char* filename, ALuint *source) {
	ALCdevice* device = alcOpenDevice(nullptr);
    ALCcontext* context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    // Load the audio file
    ALuint buffer;
    alGenBuffers(1, &buffer);
    FILE* file = fopen(filename, "rb");
    if (file) {
        // Get the file size
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        // Allocate a buffer for the file data
        char* data = new char[size];
        fread(data, 1, size, file);
        fclose(file);

        // Load the file data into the buffer
        alBufferData(buffer, AL_FORMAT_MONO16, data, size, 44100);
        delete[] data;
    }else{
		printf("Erro\n");
	}

    // Create a source for the audio

    
    alGenSources(1, source);
    alSourcei(*source, AL_BUFFER, buffer);
}
//Declaração do objeto jogador
Player p(PLAYER_X, PLAYER_Z, PLAYER_LX, PLAYER_LZ, PLAYER_ANGLE);

int j_width, j_height;


//Lista de Game Objects
std::forward_list<Wall> walls;
std::forward_list<Floor> floors;
std::forward_list<Enemy> enemys;

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
void resetEnemys();

void drawHUD() {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, j_width, 0, j_height, -1, 1); // define as dimensões da tela

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a cor do crosshair como vermelho
    glColor3f(0.0f, 1.0f, 0.0f);
    
    // Define a largura da linha do crosshair
    glLineWidth(2.0f);
    
    // Desenha uma linha vertical
	glPushMatrix();
	glTranslatef(j_width/2, j_height/2, 0);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
    
    // Desenha uma linha horizontal
    glBegin(GL_LINES);
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    glEnd();
	glPopMatrix();
	float ratio = 1.0* j_width / j_height;

	draw_text_stroke(0, 5, "Kills: " + to_string(kills), 0.3);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, j_width, j_height);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
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

void renderEnemys(){
	for (std::forward_list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++) {
		it->render();
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
			if(map[row][column] == 2){
				Enemy e(x, z);
				qntEnemy++;
				Floor f(x, 0, z, size, id_textures[1]);
				floors.push_front(f);
				enemys.push_front(e);
			}
		}
	}
}

void resetEnemys(){
	for (std::forward_list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++) {
		it->reset();
	}
	killCount = 0;
}

bool checkHit(){
	for (std::forward_list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++) {
		float enemy_radius = it->getRadius()+1;

		float projection = ((it->getPosx() - p.posx()) * p.poslx()) + ((it->getPosz() - p.posz()) * p.poslz());
		float directionLength = sqrt(p.poslx() * p.poslx() + p.poslz() * p.poslz());
		float normalDirX = p.poslx() / directionLength;
		float normalDirZ = p.poslz() / directionLength;

		float rayX = p.posx() + projection * normalDirX;
		float rayY = p.posy();
		float rayZ = p.posz() + projection * normalDirZ;

		float distance = sqrt((rayX - it->getPosx()) * (rayX - it->getPosx()) + (rayY - it->getPosy()) * (rayY - it->getPosy()) + (rayZ - it->getPosz()) * (rayZ - it->getPosz()));

		if (distance < enemy_radius) {
			
			it->countHit();
			
			if (it->isDead()) {
				killCount++;
				kills++;
				it->setPosx(-100);
				printf("Inimigo eliminado\n");	
			}

			return true;
		}
	}
	return false;
}

//Checa colisão com inimigos e evita que o jogador fique preso dentro da parede.
bool checkCollision(){
	float player_radius = 2.0f;
	float min_distance = 0.1f; // valor mínimo de distância entre o jogador e a parede
	
	for (std::forward_list<Wall>::iterator it = walls.begin(); it != walls.end(); it++) {
		float wall_radius = it->getSize() / 2.0f;
		float dist = sqrt(pow(p.posx() - it->getPosx(), 2) + pow(p.posz() - it->getPosz(), 2));
		
		if (dist <= player_radius + wall_radius - min_distance) {
			float dx = p.posx() - it->getPosx();
			float dz = p.posz() - it->getPosz();
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

	for (std::forward_list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++) {
		float enemy_radius = it->getRadius();
		float dist = sqrt(pow(p.posx() - it->getPosx(), 2) + pow(p.posz() - it->getPosz(), 2));
		if (dist <= player_radius + enemy_radius - min_distance) {
			float dx = p.posx() - it->getPosx();
			float dz = p.posz() - it->getPosz();
			float len = sqrt(dx * dx + dz * dz);
			
			dx /= len;
			dz /= len;
			
			float separation = player_radius + enemy_radius - dist + min_distance;
			
			dx *= separation;
			dz *= separation;

			p.setx(p.posx() + dx);
			p.setz(p.posz() + dz);
			return true;
		}
	}

	return false;
}

void display(void) {

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
	// Manda renderizar o jogo
	renderWalls();
	renderFloors();
	renderEnemys();
	drawHUD();
	p.modelView();

	if (killCount == qntEnemy) {
		resetEnemys();
	}

	skybox(0, 0, 200, id_textures);

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
	if (key == 27) {
		exit(0);
	}
	if (key == ' ') {
		alSourcePlay(a_pistol);
		if(checkHit()){
			printf("Acerto!!\n");
		}
	} 
}

void changeSize(int w, int h) {

	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	j_width = w;
	j_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	printf("%s\n", argv[0]);
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

	load_audio("/home/mias/Documentos/Github/Doom---OpenGL/Assets/SFX/pistol.wav", &a_pistol);

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

	//Cria os gameobjects e salva numa lista
	drawMap();
	
	glutMainLoop();

	return EXIT_SUCCESS;
}