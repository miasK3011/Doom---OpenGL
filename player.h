#include "config.h"
#include <cmath>

#ifndef player_h
#define player_h

class Player{
    public:
        float x = 0.0f, z = 5.0f;
	    float lx = 0.0f, lz = -1.0f;
	    float angulo = 0.0f;

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

        float pos(int coordenada){
            if (coordenada == 1) {
                return x;
            }
            return 0;
        }
};

#endif