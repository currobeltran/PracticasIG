// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        void cambiarTapas(bool &tapas);
    protected:
        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapaSup, bool conTapaInf);
        void crearTapas(int num_instancias, int perfil_size, Tupla3f tapa, bool TapaSup);
        void eliminarTapas(int num_instancias); 
    private:
        int numeroPerfiles;
        int verticesPorPerfil;
        Tupla3f tapaSup;
        Tupla3f tapaInf;
} ;




#endif
