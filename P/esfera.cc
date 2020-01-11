#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil,const int num_instancias_perf,const float radio
,bool tapaSup, bool tapaInf){
    std::vector<Tupla3f> perfil;
    perfil.resize(num_vert_perfil);

    perfil[0]={0,radio,0};

    for(int i=1; i<num_vert_perfil-1; i++){
        float angulo=(i*M_PI)/num_vert_perfil;
        perfil[i]={radio*(sin(angulo)),cos(angulo)*radio,0};
    }

    perfil[num_vert_perfil-1]={0,-radio,0};

    crearMalla(perfil, num_instancias_perf, tapaSup, tapaInf);
}