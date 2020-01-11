#ifndef CAMARA_H_
#define CAMARA_H_

#include "aux.h"

class Camara{
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;
        int tipo;// ORTOGONAL o Perspectiva
        float left, right, near, far, top, bottom;
        float fovy, aspect;
        Tupla3f n, v, u; 
        Tupla3f direccion;
        
    public:
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float top, 
        float right, float near, float far);
        
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);

        void girar(int x, int y);
        
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        
        void mover(float x,float y,float z);
        void zoom(float factor);
        void setProyeccion();
        void setObserver(){gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);};

        Tupla3f Euler(Tupla3f eje, Tupla3f vector, float angle);
        void rotarExaminar(float angle, bool x);
        void rotarFP(float angle, bool x);

        void setPuntoRotacion(Tupla3f newAt);
};

#endif