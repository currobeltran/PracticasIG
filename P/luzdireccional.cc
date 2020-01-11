#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla3f &orientacion, const GLenum idLuz, Tupla4f ambiente, 
    Tupla4f especular, Tupla4f difuso){

    alpha=0;
    beta=0;

    id=idLuz;
    colorAmbiente=ambiente;
    colorEspecular=especular;
    colorDifuso=difuso;

    posicion[0]=orientacion[0];
    posicion[1]=orientacion[1];
    posicion[2]=orientacion[2];
    posicion[3]=0;

}

void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha+=incremento;
    variarPosicionAngulos();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta+=incremento; 
    variarPosicionAngulos();   
}

void LuzDireccional::variarPosicionAngulos(){
    posicion[0]=sin(alpha*(M_PI/180));
    posicion[1]=sin(beta*(M_PI/180));
    posicion[2]=cos(alpha*(M_PI/180))*cos(beta*(M_PI/180));
}