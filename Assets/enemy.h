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

#include <random>

#ifndef enemy_h
#define enemy_h

class Enemy {
    public:
        Enemy(float x, float z);
        void render();
        void randMov();
        float getPosx();
        float getPosz();
        float getPosy();
        void setPosx(float x);
        void setPosz(float z);
        float getRadius();
        void countHit();
        bool isDead();
        void reset();

    private:
        float posx, posz, hit, resetx, resetz;
        float radius;
        bool dead;
};

#endif