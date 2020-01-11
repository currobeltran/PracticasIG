#include "persona.h"

Persona::Persona(){
    piernaDerecha=new Pierna();
    piernaIzquierda=new Pierna();
    brazoDerecho=new Brazo();
    brazoIzquierdo=new Brazo();
    cuerpo=new Tronco();
    cabeza=new Cabeza();
    posicion=0;
}

void Persona::draw(int modo, bool p, bool l, bool s,bool a,bool i, Tupla3f color){
    glTranslatef(0,0,posicion/45);

    glPushMatrix();
        cabeza->draw(modo,p,l,s,a,i,color);
        cuerpo->draw(modo,p,l,s,a,i,color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.5,4,0);
        brazoIzquierdo->draw(modo,p,l,s,a,i,color);
        glTranslatef(-9,0,0);
        brazoDerecho->draw(modo,p,l,s,a,i,color);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2,0,0);
        piernaIzquierda->draw(modo,p,l,s,a,i,color);
        glTranslatef(-4,0,0);
        piernaDerecha->draw(modo,p,l,s,a,i,color);
    glPopMatrix();
}

void Persona::modificarRodillas(bool piernaD, float inc){
    if(piernaD)
        piernaDerecha->rotacionRodilla(inc);
    else
        piernaIzquierda->rotacionRodilla(inc);
}

void Persona::rotarPiernas(bool piernaD, float inc){
    if(piernaD)
        piernaDerecha->rotacionPierna(inc);
    else
        piernaIzquierda->rotacionPierna(inc);
}

void Persona::modificarCodo(bool brazoD, float inc){
    if(brazoD){
        brazoDerecho->modificarCodo(inc);
    }
    else{
        brazoIzquierdo->modificarCodo(inc);
    }
}

void Persona::modificarBrazo(bool brazoD, float inc){
    if(brazoD){
        brazoDerecho->modificarBrazo(inc);
    }
    else{
        brazoIzquierdo->modificarBrazo(inc);
    }
}

void Persona::mover(){
    posicion++;
}

void Persona::setMaterial(Material mat){
    cabeza->setMaterial(mat);
    piernaDerecha->setMaterial(mat);
    piernaIzquierda->setMaterial(mat);
    brazoDerecho->setMaterial(mat);
    brazoIzquierdo->setMaterial(mat);
    cuerpo->setMaterial(mat);
}