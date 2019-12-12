#ifndef __BRAZO_H_
#define __BRAZO_H_

#include"aux.h"
#include"cilindro.h"
#include"esfera.h"

class Brazo : public Malla3D{
    private:
        Cilindro * parteSuperior;
        Cilindro * parteInferior;
        Esfera * mano;
        Esfera * codo;
        float rotacionCodo;
        float rotacionBrazo;

    public:
        Brazo();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i);
        void modificarCodo(bool inc);
        void modificarBrazo(bool inc);
        void setMaterial(Material mat);
};

#endif