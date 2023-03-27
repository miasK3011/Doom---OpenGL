/*
    Biblioteca com configurações e constantes do jogo:
    VEL_MOV = Velocidade de movimento do jogador
    SENSE_CAM = Sensibilidade da camera
    TAM_MAP = Tamanho do mapa
*/

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

#ifndef config_h
#define config_h

#define JANELA_X 640
#define JANELA_Y 480
#define FPS 24
#define VEL_MOV 0.5
#define SENSE_CAM 0.08
#define TAM_MAP 10
#define QUANT_TEX 8

#define PLAYER_X 9.74f
#define PLAYER_Z 24.65f
#define PLAYER_LX 0.0f
#define PLAYER_LZ -1.0f
#define PLAYER_ANGLE 0.0f

static GLfloat light_pos[] = {-2.0, 2.0, 2.0, 0.0};
static GLfloat light_Ka[] = {0.4, 0.4, 0.4, 0.0};
static GLfloat light_Kd[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat light_Ks[] = {1.0, 1.0, 1.0, 0.0};

static GLfloat material_Ka[] = {0.33, 0.22, 0.03, 1.00};
static GLfloat material_Kd[] = {0.78, 0.57, 0.11, 1.00};
static GLfloat material_Ks[] = {0.99, 0.94, 0.81, 1.00};
static GLfloat material_Ke[] = {0.00, 0.00, 0.00, 0.00};
static GLfloat material_Se = 28;

static int map[TAM_MAP][TAM_MAP] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, 
                                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
                                    };


#endif