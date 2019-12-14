#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "jpg_imagen.hpp"

class Textura{
    private:
        GLuint textura_id = 0;
        unsigned char * data;
        int width,height;
        jpg::Imagen * pimg=NULL;
    
    public:
        Textura(std::string archivo);
        void activar();
};

#endif