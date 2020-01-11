#ifndef __PIERNA_H_
#define __PIERNA_H_

#include"aux.h"
#include"cilindro.h"
#include"esfera.h"

class Pierna : public Malla3D{
    private:
        Cilindro * parteSuperior;
        Cilindro * parteInferior;
        Esfera * rodilla;
        float rotarRodilla;
        float rotarPierna;

    public:
        Pierna();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i, Tupla3f color={-1,-1,-1});
        void rotacionRodilla(float incremento);
        void rotacionPierna(float incremento);
        void setMaterial(Material mat);
};

#endif