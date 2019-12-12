#include "tronco.h"

Tronco::Tronco(){
    tronco=new Cilindro(30,3,3.5,true,true);
}

void Tronco::draw(int modo, bool p, bool l, bool s,bool a,bool i){
    glPushMatrix();
        glTranslatef(0,3,0);
        tronco->draw(modo,p,l,s,a,i);
    glPopMatrix();
}

void Tronco::setMaterial(Material mat){
    tronco->setMaterial(mat);
}