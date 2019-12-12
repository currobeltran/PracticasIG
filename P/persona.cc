#include "persona.h"

Persona::Persona(){
    piernaDerecha=new Pierna();
    piernaIzquierda=new Pierna();
    brazoDerecho=new Brazo();
    brazoIzquierdo=new Brazo();
    cuerpo=new Tronco();
    cabeza=new Cabeza();
}

void Persona::draw(int modo, bool p, bool l, bool s,bool a,bool i){
    glPushMatrix();
        cabeza->draw(modo,p,l,s,a,i);
        cuerpo->draw(modo,p,l,s,a,i);
        glTranslatef(4.5,3.5,0);
        brazoIzquierdo->draw(modo,p,l,s,a,i);
        glTranslatef(-9,0,0);
        brazoDerecho->draw(modo,p,l,s,a,i);
        glTranslatef(6.5,-5,0);
        piernaIzquierda->draw(modo,p,l,s,a,i);
        glTranslatef(-4,0,0);
        piernaDerecha->draw(modo,p,l,s,a,i);
    glPopMatrix();
}

void Persona::modificarRodillas(bool piernaD, bool inc){
    if(piernaD)
        piernaDerecha->rotacionRodilla(inc);
    else
        piernaIzquierda->rotacionRodilla(inc);
}

void Persona::rotarPiernas(bool piernaD, bool inc){
    if(piernaD)
        piernaDerecha->rotacionPierna(inc);
    else
        piernaIzquierda->rotacionPierna(inc);
}

void Persona::modificarCodo(bool brazoD, bool inc){
    if(brazoD){
        brazoDerecho->modificarCodo(inc);
    }
    else{
        brazoIzquierdo->modificarCodo(inc);
    }
}

void Persona::modificarBrazo(bool brazoD, bool inc){
    if(brazoD){
        brazoDerecho->modificarBrazo(inc);
    }
    else{
        brazoIzquierdo->modificarBrazo(inc);
    }
}

void Persona::setMaterial(Material mat){
    cabeza->setMaterial(mat);
    piernaDerecha->setMaterial(mat);
    piernaIzquierda->setMaterial(mat);
    brazoDerecho->setMaterial(mat);
    brazoIzquierdo->setMaterial(mat);
    cuerpo->setMaterial(mat);
}