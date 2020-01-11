#ifndef CONO_H
#define CONO_H

#include "aux.h"
#include "objrevolucion.h"

class Cono : public ObjRevolucion{
    public:
        Cono(const int num_instancias_perf,const float altura,const float radio,bool tapaSup, 
        bool tapaInf);
};

#endif 