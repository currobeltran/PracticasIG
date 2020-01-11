#include "brazo.h"

Brazo::Brazo(){
    parteSuperior=new Cilindro(30,1.5,1,true,true);
    parteInferior=new Cilindro(30,1.5,0.9,true,true);
    mano=new Esfera(30,30,0.9,true,true);
    codo=new Esfera(30,30,1,true,true);
    rotacionCodo=0.0;
    rotacionBrazo=0.0;
}

void Brazo::draw(int modo, bool p, bool l, bool s,bool a,bool i, Tupla3f color){
    glPushMatrix();
        glRotatef(rotacionBrazo,1,0,0);
        parteSuperior->draw(modo,p,l,s,a,i,nullptr,color);
        glTranslatef(0,-1.5,0);
        codo->draw(modo,p,l,s,a,i,nullptr,color);
        glRotatef(rotacionCodo,1,0,0);
        glTranslatef(0,-1,0);
        parteInferior->draw(modo,p,l,s,a,i,nullptr,color);
        glTranslatef(0,-1.5,0);
        mano->draw(modo,p,l,s,a,i,nullptr,color);
    glPopMatrix();
}

void Brazo::modificarCodo(float inc){
    if(rotacionCodo+inc>=-90 && rotacionCodo+inc<0){
        rotacionCodo+=inc;
    }
}

void Brazo::modificarBrazo(float inc){
    if(rotacionBrazo+inc>=-45 && rotacionBrazo+inc<=0){
        rotacionBrazo+=inc;
    }
}

void Brazo::setMaterial(Material mat){
    mano->setMaterial(mat);
    parteInferior->setMaterial(mat);
    parteSuperior->setMaterial(mat);
    codo->setMaterial(mat);
}