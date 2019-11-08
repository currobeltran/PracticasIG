#include "cono.h"

Cono::Cono(const int num_instancias_perf,const float altura,const float radio,bool tapaSup, 
bool tapaInf){
    
    std::vector<Tupla3f> perfil;
    perfil.resize(3);

    perfil[0]={0,altura,0};
    perfil[perfil.size()-2]={radio,-altura,0};
    perfil[perfil.size()-1]={0,-altura,0};

    crearMalla(perfil, num_instancias_perf, tapaSup, tapaInf);

}