#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){

    pimg=new jpg::Imagen(archivo);

    width=pimg->tamX();
    height=pimg->tamY();

    data=pimg->leerPixels();
    
    glGenTextures(1, &textura_id);
    
}

void Textura::activar(){
    glBindTexture(GL_TEXTURE_2D, textura_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
}