#include <cmath>
#include <cstdio>

#ifndef player_h
#define player_h

class Player{
    public:
        Player(float x, float z, float lx, float lz, float angulo);
        void movement(int direction);
        void printPos();
        float posx();
        float posz();
        float posy();
        float poslx();
        float poslz();
        void setx(float x);
        void setz(float z);
        void modelView();
    private:
        float m_x, m_z, m_y, m_lx, m_lz, m_angle;
};

#endif