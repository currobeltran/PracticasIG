#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado){
    v.resize(4);

    v[0]={0,0,0};
    v[1]={lado,0,0};
    v[2]={lado,lado,0};
    v[3]={0,lado,0};

    f.resize(2);

    f[0]={3,0,1}; 
    f[1]={3,1,2};

    c.resize(4);

    ct.resize(4);

    ct[0]={0,0};
    ct[1]={1,0};
    ct[2]={1,1};
    ct[3]={0,1};
}