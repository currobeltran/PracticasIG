#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   v.resize(8);

   float trans=lado*50.0;

   v[0]={-lado,-lado,lado};
   v[1]={lado,-lado,lado};
   v[2]={lado,lado,lado};
   v[3]={-lado,lado,lado};
   v[4]={-lado,-lado,-lado};
   v[5]={lado,-lado,-lado};
   v[6]={lado,lado,-lado};
   v[7]={-lado,lado,-lado};

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f.resize(12);

   f[0]={3,0,1}; 
   f[1]={3,1,2}; 
   f[2]={2,1,5}; 
   f[3]={5,6,2}; 
   f[4]={6,5,4}; 
   f[5]={4,7,6}; 
   f[6]={7,4,0}; 
   f[7]={0,3,7}; 
   f[8]={7,3,2}; 
   f[9]={2,6,7}; 
   f[10]={0,4,5};
   f[11]={5,1,0};

   c.resize(8);
}

