#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){
    glGenTextures(1, &textura_id);

    pimg=new jpg::Imagen(archivo);

    width=pimg->tamX();
    height=pimg->tamY();

    data=pimg->leerPixels();
}

void Textura::activar(){
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textura_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, width,height,GL_RGB,GL_UNSIGNED_BYTE,data);

}