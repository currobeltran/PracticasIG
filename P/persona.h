#ifndef __PERSONA_H_
#define __PERSONA_H_

#include "aux.h"
#include "pierna.h"
#include "tronco.h"
#include "brazo.h"
#include "cabeza.h"
#include "material.h"

class Persona : public Malla3D{
    private:
        Pierna * piernaDerecha, * piernaIzquierda;
        Tronco * cuerpo;
        Brazo * brazoDerecho, * brazoIzquierdo;
        Cabeza * cabeza;
        Material * mat;
        int posicion;

    public:
        Persona();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i, Tupla3f color={-1,-1,-1});
        void modificarRodillas(bool piernaD, float inc);
        void rotarPiernas(bool piernaD, float inc);
        void modificarCodo(bool brazoD, float inc);
        void modificarBrazo(bool brazoD, float inc);
        void mover();
        void setMaterial(Material mat);
};

#endif