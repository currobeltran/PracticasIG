#include "cilindro.h"

Cilindro::Cilindro(const int num_instancias_perf,
const float altura,const float radio,bool tapaSup, bool tapaInf){
    
    std::vector<Tupla3f> perfil;

    perfil.resize(4);

    perfil[0]={0,altura,0};
    perfil[1]={radio,altura,0};
    
    perfil[2]={radio,-altura,0};
    perfil[3]={0,-altura,0};

    crearMalla(perfil, num_instancias_perf, tapaSup, tapaInf);
}