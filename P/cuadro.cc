#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado){
    v.resize(4);

    v[0]={-lado,-1,lado};
    v[1]={lado,-1,lado};
    v[2]={lado,-1,-lado};
    v[3]={-lado,-1,-lado};

    f.resize(2);

    f[0]={3,0,1}; 
    f[1]={3,1,2};

    c.resize(4);

    ct.resize(4);

    ct[0]={0,0};
    ct[1]={50,0};
    ct[2]={50,50};
    ct[3]={0,50};
}