#include "aux.h"
#include "malla.h"
#include "piramide.h"

Piramide::Piramide(float lado){
    v.resize(5);

    v[0]={-lado,0,lado};
    v[1]={lado,0,lado};
    v[2]={lado,0,-lado};
    v[3]={-lado,0,-lado};
    v[4]={0,lado*1.5,0};

    f.resize(6);
    f[0]={3,1,0};
    f[1]={3,2,1};
    f[2]={1,4,0};
    f[3]={2,4,1};
    f[4]={3,4,2};
    f[5]={0,4,3};

    c.resize(5);

}