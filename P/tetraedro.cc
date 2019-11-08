#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

  // inicializar la tabla de vértices

  v.resize(4);

  v[0]={-50,-50,-50};
  v[1]={0,-50,50};
  v[2]={50,-50,-50};
  v[3]={0,50,0};

  // inicializar la tabla de caras o triángulos:
  // (es importante en cada cara ordenar los vértices en sentido contrario
  //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

  f.resize(4);

  f[0]={0,1,3};
  f[1]={1,2,3};
  f[2]={2,0,3};
  f[3]={0,2,1};

  c.resize(4);

}