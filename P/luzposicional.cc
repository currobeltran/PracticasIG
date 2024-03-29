#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f& orientacion, const GLenum idLuz, Tupla4f ambiente, 
    Tupla4f especular, Tupla4f difuso){

    id=idLuz;
    colorAmbiente=ambiente;
    colorEspecular=especular;
    colorDifuso=difuso;

    posicion[0]=orientacion[0];
    posicion[1]=orientacion[1];
    posicion[2]=orientacion[2];
    posicion[3]=1;

    inicial=posicion;
    
}

void LuzPosicional::variarPosicion(int variacion){
    posicion[0]=sin(variacion*(M_PI/180))*inicial[0];
    posicion[2]=cos(variacion*(M_PI/180))*inicial[2];
}