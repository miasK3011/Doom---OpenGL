#include "enemy.h"

Enemy::Enemy(float x, float z){
    posx = x;
    posz = z;
}

void Enemy::render(){
    glPushMatrix();
    glTranslatef(posx, 0, posz);

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
    
    glPopMatrix();
}

float Enemy::getPosx(){
	return posx;
}

float Enemy::getPosz(){
	return posz;
}

float Enemy::getPosy(){
	return 0;
}

void Enemy::setPosx(float x){
	posx = x;
}


void Enemy::setPosz(float z){
	posz = z;
}

float Enemy::getRadius(){
	return radius;
}
