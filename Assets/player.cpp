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

#include "player.h"
#include "config.h"

Player::Player(float x, float z, float lx, float lz, float angle){
    m_x = x;
    m_z = z;
    m_lx = lx;
    m_lz = lz;
    m_angle = angle;
}

// Função de movimentação do personagem
void Player::movement(int direction){
    switch (direction) {
        case 0:
            m_x += m_lx * VEL_MOV;
            m_z += m_lz * VEL_MOV;
            break;
        case 1:
            m_x -= m_lx * VEL_MOV;
            m_z -= m_lz * VEL_MOV;
            break;
        case 2:
            m_angle -= SENSE_CAM;
            m_lx = sin(m_angle);
            m_lz = -cos(m_angle);
            break;
        case 3:
            m_angle += SENSE_CAM;
            m_lx = sin(m_angle);
            m_lz = -cos(m_angle);
            break;
    }
}

float Player::posx(){
    return m_x;
}

float Player::posz(){
    return m_z;
}

float Player::poslx(){
    return m_lx;
}

float Player::poslz(){
    return m_lz;
}

void Player::setx(float x){
    m_x = x;
}

void Player::setz(float z){
    m_z = z;
}

void Player::printPos(){
    printf("x = %2f, z = %2f\n", m_x, m_z);
}

void Player::shoot(){
    shooting = true;
};

void Player::resetShoot(){
    shooting = false;
}