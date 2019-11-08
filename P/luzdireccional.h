#ifndef _LUZDIRECCIONAL_H
#define _LUZDIRECCIONAL_H

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz{
    
    protected:
        float alpha;
        float beta;
    
    public:
    //  inicializar la fuente de luz
        LuzDireccional(const Tupla3f& orientacion, const GLenum idLuz, Tupla4f ambiente, 
        Tupla4f especular, Tupla4f difuso);
        
    //  Cambiar ángulo:
    
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
    
};

#endif