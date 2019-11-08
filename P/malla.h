// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool p, bool l, bool s);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool p, bool l, bool s);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo, bool p, bool l, bool s, bool a, bool i) ;

   // funcion para establecer el color de una figura
   void setColor(Tupla3f color, std::vector<Tupla3f> &vectorc);

   //Diferentes modos de visualizacion
   void modoDibujado(GLenum modo, bool inmediato);

   //Seleccion del color modoInmediato
   void seleccionColorInmediato(Tupla3f color);

   //Seleccion del color modoDiferido
   void seleccionColorDiferido(Tupla3f color, GLuint VBO);

   //Funcion para modo ajedrez
   void draw_ModoInmediatoAjedrez();

   //Funcion para establecer el material del que se hace la malla
   void setMaterial(Material mat);
   
   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   
   // Funcion que crea los VBO necesarios para el modo diferido
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid* puntero_ram);

   // Funcion para configurar la figura a dibujar en modo ajedrez
   void setFiguraAjedrez(Tupla3f colorA, Tupla3f colorB, std::vector<Tupla3f> &colorPar, std::vector<Tupla3f> &colorImpar,
   const std::vector<Tupla3i> &caras, std::vector<Tupla3i> &carasPares, std::vector<Tupla3i> &carasImpares, const std::vector<Tupla3f> &colores);

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3f> v2; // tabla de coordenadas de vértices con tapas

   std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f2; // tabla de caras con tapas

   std::vector<Tupla3f> c; // terna de 3 floats para cada vertice
   
   std::vector<Tupla3f> nv; // vector de normales a los vertices
   std::vector<Tupla3f> nv2; // vector de normales con tapas
   Material * m; 

   GLuint id_vbo_ver=0;
   GLuint id_vbo_tri=0;
   GLuint id_vbo_col_linea=0;
   GLuint id_vbo_col_punto=0;
   GLuint id_vbo_col_solido=0;
   GLuint id_vbo_nor=0;


   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
