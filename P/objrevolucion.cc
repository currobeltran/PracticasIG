#include "aux.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo, perfil);

   numeroPerfiles=num_instancias;
   verticesPorPerfil=perfil.size();
   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   numeroPerfiles=num_instancias;
   verticesPorPerfil=archivo.size();
   crearMalla(archivo, num_instancias, tapa_sup, tapa_inf);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapaSup, bool conTapaInf) {
   bool hayTapaSup=true, hayTapaInf=true;

   //Si estan los vertices de abajo a arriba, ponerlos de arriba a abajo
   if(perfil_original[0][1]<perfil_original[perfil_original.size()-1][1]){
      std::vector<Tupla3f> reverse;
      reverse.resize(perfil_original.size());
      for(int i=0; i<perfil_original.size(); i++){
         reverse[i]=perfil_original[perfil_original.size()-1-i];
      }
      for(int i=0; i<perfil_original.size(); i++){
         perfil_original[i]=reverse[i];
      }
   }

   int tam=perfil_original.size();
   //Detectar tapa superior e inferior
   for(int i=0; i<perfil_original.size(); i++){
      if(perfil_original[0][0]>perfil_original[i][0] || perfil_original[0][0]!=0){
         hayTapaSup=false;
      }
      if(perfil_original[tam-1][0]>perfil_original[i][0] || perfil_original[tam-1][0]!=0){
         hayTapaInf=false;
      }
   }
   
   //Recoger tapa superior
   if(hayTapaSup){   
      tapaSup=perfil_original[0];
      
      std::vector<Tupla3f> sinTapa;
      sinTapa.resize(perfil_original.size()-1);
      for(int i=0; i<sinTapa.size(); i++){
         sinTapa[i]=perfil_original[i+1];
      }

      perfil_original.resize(sinTapa.size());
      for(int i=0; i<perfil_original.size(); i++){
         perfil_original[i]=sinTapa[i];
      }

   }

   //Recoger tapa inferior
   if(hayTapaInf){   
      tapaInf=perfil_original[perfil_original.size()-1];
      perfil_original.pop_back();
   }

   //Generar vertices laterales
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<perfil_original.size(); j++){
         Tupla3f aux=perfil_original[j];
         aux[2]=sin((2*M_PI*i)/num_instancias)*aux[0];
         aux[0]=cos((2*M_PI*i)/num_instancias)*aux[0];
         v.push_back(aux);
      }
   }

   //Generar caras laterales
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<perfil_original.size()-1; j++){
         int a=perfil_original.size()*i+j;
         int a1=perfil_original.size()*i+j+1;

         int b=perfil_original.size()*((i+1)%num_instancias)+j;
         int b1=perfil_original.size()*((i+1)%num_instancias)+j+1;
      
         f.push_back({a,b,b1});
         f.push_back({a,b1,a1});
      }
   }

   v2=v;
   f2=f;

   //Añadir tapas en el otro vector
   if(hayTapaSup){
      crearTapas(num_instancias, perfil_original.size(), tapaSup, true);
   }
   else{
      tapaSup={0,perfil_original[0][1],0};
      crearTapas(num_instancias, perfil_original.size(), tapaSup, true);
   }

   if(hayTapaInf){
      crearTapas(num_instancias, perfil_original.size(), tapaInf, false);
   }
   else{
      tapaInf={0,perfil_original[perfil_original.size()-1][1],0};
      crearTapas(num_instancias, perfil_original.size(), tapaInf, false);
   }

   c.resize(v2.size());
}

void ObjRevolucion::crearTapas(int num_instancias, int perfil_size, Tupla3f tapa, bool tapaSup){
   v2=v2;
   f2=f2;
   v2.push_back(tapa);
   int tap, a, b;
   tap=v2.size()-1;
   
   if(tapaSup){
      for(int i=0; i<num_instancias; i++){
         
         a=perfil_size*i;
         b=perfil_size*((i+1)%num_instancias);
         f2.push_back({a,tap,b});
      
      }
   }
   else{
      for(int i=1; i<num_instancias-1; i++){
         a=perfil_size*i-1;
         b=perfil_size*((i+1)%num_instancias)-1;
         f2.push_back({b,tap,a});
      }

      a=perfil_size*num_instancias-(perfil_size+1);
      b=perfil_size*num_instancias-1;
      f2.push_back({b,tap,a});

      a=perfil_size*num_instancias-1;
      b=perfil_size-1;
      f2.push_back({b,tap,a});
   }
}

void ObjRevolucion::cambiarTapas(bool &tapas){
   
   std::vector<Tupla3f> aux=v;
   v=v2;
   v2=aux;

   std::vector<Tupla3i> aux2=f;
   f=f2;
   f2=aux2;

   tapas=!tapas;

}