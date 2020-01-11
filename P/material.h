#ifndef MATERIAL_H
#define MATERIAL_H

#include <aux.h>

class Material{
    
    private:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    
    public:
        Material();

        Material(const Tupla4f mdifuso,const Tupla4f mespecular,const Tupla4f mambiente,
        const float bri);
        
        void aplicar();
    
};

#endif