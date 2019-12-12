#include "pierna.h"

Pierna::Pierna(){
    parteSuperior=new Cilindro(30,2,1,true,true);
    parteInferior=new Cilindro(30,2,0.9,true,true);
    rodilla=new Esfera(30,30,1,true,true);
    rotarRodilla=0.0;
    rotarPierna=0.0;
}

void Pierna::draw(int modo, bool p, bool l, bool s,bool a,bool i){
    glPushMatrix();
        glTranslatef(0,1,0);
        glRotatef(rotarPierna,1,0,0);
        parteSuperior->draw(modo,p,l,s,a,i);
        glTranslatef(0,-2,0);
        rodilla->draw(modo,p,l,s,a,i);
        glRotatef(rotarRodilla,1,0,0);
        glTranslatef(0,-2,0);
        parteInferior->draw(modo,p,l,s,a,i);
    glPopMatrix();
}

void Pierna::rotacionRodilla(bool incremento){
    if(incremento && rotarRodilla<45){
        rotarRodilla+=1.0;
    }
    else if(!incremento && rotarRodilla>-1){
        rotarRodilla-=1.0;
    }
}

void Pierna::rotacionPierna(bool incremento){
    if(incremento && rotarPierna<45){
        rotarPierna+=1.0;
    }
    else if(!incremento && rotarPierna>-45){
        rotarPierna-=1.0;
    }
}

void Pierna::setMaterial(Material mat){
    parteInferior->setMaterial(mat);
    rodilla->setMaterial(mat);
    parteSuperior->setMaterial(mat);
}