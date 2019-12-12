#ifndef __PERSONA_H_
#define __PERSONA_H_

#include "aux.h"
#include "pierna.h"
#include "tronco.h"
#include "brazo.h"
#include "cabeza.h"
#include "material.h"

class Persona{
    private:
        Pierna * piernaDerecha, * piernaIzquierda;
        Tronco * cuerpo;
        Brazo * brazoDerecho, * brazoIzquierdo;
        Cabeza * cabeza;
        Material * mat;

    public:
        Persona();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i);
        void modificarRodillas(bool piernaD, bool inc);
        void rotarPiernas(bool piernaD, bool inc);
        void modificarCodo(bool brazoD, bool inc);
        void modificarBrazo(bool brazoD, bool inc);
        void setMaterial(Material mat);
};

#endif