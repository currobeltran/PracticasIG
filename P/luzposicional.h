#ifndef _LUZPOSICIONAL_H
#define _LUZPOSICIONAL_H

#include "aux.h"
#include "luz.h"


class LuzPosicional : public Luz{
    
    public:
        LuzPosicional(const Tupla3f& orientacion, const GLenum idLuz, Tupla4f ambiente, 
        Tupla4f especular, Tupla4f difuso);

        void variarPosicion(int variacion);
};

#endif