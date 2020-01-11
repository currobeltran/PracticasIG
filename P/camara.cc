#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float top, 
float right, float near, float far){
    this->eye=eye;
    this->at=at;
    this->up=up;
    up.normalized();

    this->tipo=tipo;

    this->right=right;
    this->left=-right;
    this->top=top;
    this->bottom=-top;
    this->near=near;
    this->far=far;

    aspect=(right*2)/(top*2);
    // fovy=atan(right/near)*(180/M_PI)*2;

    fovy=10;

    // El orden en los 3 calculos siguientes afecta
    n=(at-eye);

    u=(up.cross(n));
    u=u.normalized();

    v=(u.cross(n));
    v=v.normalized();

    setProyeccion();
    setObserver();
}

void Camara::rotarXExaminar(float angle){
    angle*=(M_PI/180);
    rotarExaminar(angle,true);
}

void Camara::rotarYExaminar(float angle){
    angle*=(M_PI/180);
    rotarExaminar(angle,false);
}

void Camara::rotarXFirstPerson(float angle){
    angle*=(M_PI/180);
    rotarFP(angle,true);
}

void Camara::rotarYFirstPerson(float angle){
    angle*=(M_PI/180);
    rotarFP(angle,false);
}

void Camara::girar(int x, int y){
    rotarXExaminar(x);
    rotarYExaminar(y);
}

void Camara::zoom(float factor){
    if(fovy+factor<=100 && fovy+factor>=0)
        fovy+=factor;

    // left = tan((fovy/2)*(M_PI/180))*near;
    // top = left*aspect;
}

void Camara::mover(float x, float y, float z){
    eye={x,y,z};
}

void Camara::setProyeccion(){
    if(tipo==0){
        gluPerspective(fovy,aspect,near,far);
    }
    else{
        glOrtho(left,right,bottom,top,near,far);
    }
}

Tupla3f Camara::Euler(Tupla3f eje, Tupla3f vector, float angle){
    Tupla3f resultado;

    resultado[0] =  (cos(angle)+eje[0]*eje[0]*(1-cos(angle)))*vector[0]+
                    (eje[0]*eje[1]*(1-cos(angle))-eje[2]*sin(angle))*vector[1]+ 
                    (eje[0]*eje[2]*(1-cos(angle))+eje[1]*sin(angle))*vector[2];   
    
    resultado[1] =  (eje[1]*eje[0]*(1-cos(angle))+eje[2]*sin(angle))*vector[0]+
                    (cos(angle)+eje[1]*eje[1]*(1-cos(angle)))*vector[1]+ 
                    (eje[1]*eje[2]*(1-cos(angle))-eje[0]*sin(angle))*vector[2];



    resultado[2] =  (eje[2]*eje[0]*(1-cos(angle))-eje[1]*sin(angle))*vector[0]+
                    (eje[2]*eje[1]*(1-cos(angle))+eje[0]*sin(angle))*vector[1]+ 
                    (cos(angle)+eje[2]*eje[2]*(1-cos(angle)))*vector[2];

    return resultado;
}

void Camara::rotarExaminar(float angle, bool x){
    Tupla3f n2,up2;

    n2=at-eye;

    if(x){
        n2=Euler(v,n2,angle);
        up2=Euler(v,up,angle);
        u=Euler(v,u,angle);
    }
    else{
        n2=Euler(u,n2,angle);
        up2=Euler(u,up,angle);
        v=Euler(u,v,angle);
    }

    eye=at+n2;

    u=u.normalized();
    v=v.normalized();

    up=up2;
    up=up.normalized();
}

void Camara::rotarFP(float angle, bool x){
    Tupla3f at2,up2;

    n=at-eye;

    if(x){
        at2=Euler(v,n,angle);
        up2=Euler(v,up,angle);
        u=Euler(v,u,angle);
    }
    else{
        at2=Euler(u,n,angle);
        up2=Euler(u,up,angle);
        v=Euler(u,v,angle);
    }

    at=at2+eye;

    u=u.normalized();
    v=v.normalized();

    up=up2;
    up=up.normalized();
}

void Camara::setPuntoRotacion(Tupla3f newAt){
    this->at=newAt;
}