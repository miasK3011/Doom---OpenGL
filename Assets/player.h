#include "config.h"
#include <cmath>
#include <cstdio>
#include <vector>

#ifndef player_h
#define player_h

class Player{
    public:
        float x, z;
        float lx, lz;
        float angulo;

        Player() : x(20.0f), z(10.0f), lx(0.0f), lz(-1.0f), angulo(0.0f) {}
        
        // Função de movimentação do personagem
        void movement(int direction){
            switch (direction) {
                case 0:
			        x += lx * VEL_MOV;
			        z += lz * VEL_MOV;
                    break;
                case 1:
                    x -= lx * VEL_MOV;
			        z -= lz * VEL_MOV;
                    break;
                case 2:
                    angulo -= SENSE_CAM;
                    lx = sin(angulo);
                    lz = -cos(angulo);
                    break;
                case 3:
                    angulo += SENSE_CAM;
			        lx = sin(angulo);
			        lz = -cos(angulo);
                    break;
            }
        }

        void printPos(){
            printf("x = %2f, z = %2f\n", x, z);
        }
};

#endif