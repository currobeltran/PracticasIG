#include "cabeza.h"

Cabeza::Cabeza(){
    cabeza=new Esfera(30,30,2,true,true);
}

void Cabeza::draw(int modo, bool p, bool l, bool s,bool a,bool i){
    glPushMatrix();
        glTranslatef(0,8,0);
        cabeza->draw(modo,p,l,s,a,i);
    glPopMatrix();
}

void Cabeza::setMaterial(Material mat){
    cabeza->setMaterial(mat);
}