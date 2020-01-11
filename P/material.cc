#include "material.h"

Material::Material(){};

Material::Material(const Tupla4f mdifuso, const Tupla4f mespecular, const Tupla4f mambiente, 
const float bri){
    difuso=mdifuso;
    especular=mespecular;
    ambiente=mambiente;
    brillo=bri;
}

void Material::aplicar(){

    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    const float* bri=new float(brillo);
    glMaterialfv(GL_FRONT, GL_SHININESS, bri);

}