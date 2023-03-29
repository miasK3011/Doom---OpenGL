#include "enemy.h"
#include <GL/gl.h>
#include <random>

Enemy::Enemy(float x, float z){
    posx = x;
    posz = z;
	radius = 0.75f;
	hit = 0;
	resetx = posx;
	resetz = posz;
}

void Enemy::render() {
  glPushMatrix();
  glTranslatef(posx, 0, posz);

  glColor3f(0.5f, 0.0f, 0.0f);
  // Draw Body
  glTranslatef(0.0f, 1.25f, 0.0f);
  glPushMatrix();
  glScalef(0.75f, 1.0f, 0.15f);
  glutSolidCube(1);
  glPopMatrix();
  // Draw Head
  glPushMatrix();
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, -0.1f, 0.1f);
  glScalef(0.5f, 0.80f, 0.1f);
  glutSolidCube(1);
  glPopMatrix();

  // Draw Eyes
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 0.0f);
  glTranslatef(0.155f, 0.10f, 0.15f);
  glScalef(1.75f, 0.8f, 0.5f);
  glutSolidSphere(0.05f, 10, 10);
  glTranslatef(-0.2f, 0.0f, 0.0f);
  glutSolidSphere(0.05f, 10, 10);
  glPopMatrix();

  // Draw Nose
  glPushMatrix();
  glColor3f(0.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, -0.2f, 0.15f);
  glScalef(1.0f, 1.25f, 0.1f);
  glutSolidCube(0.3);
  glPopMatrix();

  // Legs
  glPushMatrix();
  glColor3f(0.8f, 0.0f, 0.0f);
  glTranslatef(-0.3f, -0.9f, 0.0f);
  glScalef(0.3f, 1.0f, 0.2f);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.8f, 0.0f, 0.0f);
  glTranslatef(0.3f, -0.9f, 0.0f);
  glScalef(0.3f, 1.0f, 0.2f);
  glutSolidCube(1);
  glPopMatrix();

  // Left Shoulder
  glPushMatrix();
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(0.5f, 0.45f, 0.0f);
  glScalef(1.5f, 1.0f, 1.0f);
  glutSolidSphere(0.16f, 20, 10);
  // Left Arm
  glColor3f(0.8f, 0.0f, 0.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glRotatef(15, 0.0, 1.0, 0.0);
  glScalef(0.2f, 1.0f, 0.2f);
  glutSolidCube(1);
  glPopMatrix();

  // Right Shoulder
  glPushMatrix();
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(-0.5f, 0.45f, 0.0f);
  glScalef(1.5f, 1.0f, 1.0f);
  glutSolidSphere(0.16f, 20, 10);

  glColor3f(0.8f, 0.0f, 0.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glRotatef(-15, 0.0, 1.0, 0.0);
  glScalef(0.2f, 1.0f, 0.2f);
  glutSolidCube(1);
  glPopMatrix();

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

void Enemy::countHit(){
	hit++;
}

bool Enemy::isDead(){
	if (hit >= 3){
		hit = 0;
		return dead = true;
	}
	return false;
}

void Enemy::reset(){
	dead = false;
	hit = 0;
	posx = resetx;
	posz = resetz;
}

/* void Enemy::randMov(){
	if (!isDead()) {
		std::random_device r;
		std::mt19937 gen(r());
		std::uniform_int_distribution<> dis(0, 0.02f);



		posx *= ;
	}
} */

float Enemy::getRadius(){
	return radius;
}
