#ifndef __TRONCO_H_
#define __TRONCO_H_

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"

class Tronco : public Malla3D{
    private:
        Cilindro * tronco;
    
    public: 
        Tronco();
        void draw(int modo, bool p, bool l, bool s,bool a,bool i);
        void setMaterial(Material mat);
};

#endif
