#ifndef CILINDRO_H
#define CILINDRO_H

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion{
    public:
        Cilindro(const int num_instancias_perf,
        const float altura,const float radio,bool tapaSup, bool tapaInf);
};
#endif 