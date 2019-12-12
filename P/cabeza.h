#ifndef __CABEZA_H_
#define __CABEZA_H_

#include "aux.h"
#include "esfera.h"

class Cabeza : public Malla3D {
    private:
        Esfera * cabeza;
    
    public:
        Cabeza();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i);
        void setMaterial(Material mat);
};

#endif