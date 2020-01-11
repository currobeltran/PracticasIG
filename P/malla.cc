#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::setColor(Tupla3f color, std::vector<Tupla3f> &vectorc){
   for(int i=0; i<vectorc.size(); i++){
      vectorc[i]=color;
   }
}

void Malla3D::setMaterial(Material mat){
   m=new Material(mat);
}

void Malla3D::modoDibujado(GLenum modo, bool inmediato){
   glPolygonMode(GL_FRONT_AND_BACK, modo); 

   if(inmediato)
      glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,f.data());
   else{
      glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT, 0 );
   }
}

void Malla3D::setNuevoColor(Tupla3f color){
   setColor(color,cs);
}

void Malla3D::seleccionColorDiferido(std::vector<Tupla3f> color, GLuint &VBO){

   if(VBO==0){
      VBO=CrearVBO(GL_ARRAY_BUFFER, color.size() * sizeof(float) * 3, color.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER,VBO);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER,0);

}


void Malla3D::draw_ModoInmediato(bool p, bool l, bool s)
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer( 3,GL_FLOAT, 0, v.data() ) ;

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());

   //Seleccion de modos entre punto, linea y solido

   glEnableClientState(GL_COLOR_ARRAY);

   if(p){
      glColorPointer(3, GL_FLOAT, 0, cpun.data());
      modoDibujado(GL_POINT, true);
   }
   if(l){
      glColorPointer(3, GL_FLOAT, 0, cl.data());
      modoDibujado(GL_LINE, true);
   }
   if(s){
      glColorPointer(3, GL_FLOAT, 0, cs.data());
      modoDibujado(GL_FILL, true);
   }
   
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool p, bool l, bool s,Tupla3f color)
{
   //Si no se han creado los vbo, se crean y se guardan sus identificadores
   if(id_vbo_ver==0 && id_vbo_tri==0){
      id_vbo_ver=CrearVBO(GL_ARRAY_BUFFER, v.size() * sizeof(float) * 3, v.data());
      id_vbo_tri=CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(int) * 3, f.data());
   }

   if(id_vbo_nor==0){
      id_vbo_nor=CrearVBO(GL_ARRAY_BUFFER, nv.size() * sizeof(float) * 3, nv.data());
   }

   //Inicio array vertices
   glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ver);
   glVertexPointer( 3,GL_FLOAT, 0, 0 );
   glBindBuffer(GL_ARRAY_BUFFER, 0 );
   glEnableClientState(GL_VERTEX_ARRAY);
   
   //Inicio array triangulos 
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_tri);

   //Inicio array normales
   glBindBuffer(GL_ARRAY_BUFFER,id_vbo_nor);
   glNormalPointer( GL_FLOAT, 0, 0 );
   glBindBuffer(GL_ARRAY_BUFFER, 0 );
   glEnableClientState(GL_NORMAL_ARRAY);

   //Inicio array colores y dibujo
   glEnableClientState(GL_COLOR_ARRAY);

   if(p){
      seleccionColorDiferido(cpun, id_vbo_col_punto);
      modoDibujado(GL_POINT, false);
   }
   if(l){
      seleccionColorDiferido(cl, id_vbo_col_linea);
      modoDibujado(GL_LINE, false);
   }
   if(s){
      seleccionColorDiferido(cs, id_vbo_col_solido);
      modoDibujado(GL_FILL, false);
   }

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); 

   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato, a draw_ModoDiferido o draw_ModoInmediatoAjedrez

void Malla3D::draw(int modo, bool p, bool l, bool s, bool a, bool i,Textura * t, Tupla3f color)
{

   if(i){
      glEnable(GL_NORMALIZE);
      glEnable(GL_SMOOTH);
      m->aplicar();

      if(nv.empty()){
         calcular_normales();
      }
   }
   
   else{
      glEnable(GL_FLAT);
   }

   if(!ct.empty()){
      glTexCoordPointer( 2,GL_FLOAT, 0, ct[0]);

      tex=t;

      tex->activar();
   }

   if(tex!=nullptr)
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   if(cpun.empty()){
      cpun.resize(c.size());
      setColor({1.0,0,0},cpun);
   }
   if(cl.empty()){
      cl.resize(c.size());
      setColor({0,1.0,0},cl);
   }
   if(cs.empty()){
      cs.resize(c.size());
      if(ct.empty())
         setColor({0,0,1.0},cs);
      else
         setColor({1.0,1.0,1.0},cs);
   }

   if(modo==2)
      draw_ModoDiferido(p,l,s,color);
   
   else if(modo==1 && !a)
      draw_ModoInmediato(p,l,s);
   
   else if(modo==1 && a)
      draw_ModoInmediatoAjedrez();
   
}
// -----------------------------------------------------------------------------
// Funcion para crear un VBO, que nos servira para dibujar figuras en modo diferido

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid*puntero_ram){
   GLuint id_vbo;
   
   glGenBuffers( 1, &id_vbo);
   glBindBuffer(tipo_vbo,id_vbo);
   
   glBufferData(tipo_vbo,tamanio_bytes,puntero_ram,GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0 );

   return id_vbo;
}
// -----------------------------------------------------------------------------
// Modo de visualizacion en el cual se ven unas caras de un color y otras en otro
// usando un dibujado inmediato.

void Malla3D::draw_ModoInmediatoAjedrez(){
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer( 3,GL_FLOAT, 0, v.data() ) ;

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
   glEnableClientState(GL_COLOR_ARRAY);

   Tupla3f a={1,0,0}, b={0,0,1};
   std::vector<Tupla3f> cp, ci;
   std::vector<Tupla3i> p, im;

   setFiguraAjedrez(a,b,cp,ci,f,p,im,c);
   
   glColorPointer(3, GL_FLOAT, 0, cp.data());
   glDrawElements(GL_TRIANGLES,p.size()*3,GL_UNSIGNED_INT,p.data());
 
   glColorPointer(3, GL_FLOAT, 0, ci.data());
   glDrawElements(GL_TRIANGLES,im.size()*3,GL_UNSIGNED_INT,im.data());

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

// -----------------------------------------------------------------------------
// Configuracion de la figura en modo ajedrez

void Malla3D::setFiguraAjedrez(Tupla3f colorA, Tupla3f colorB, std::vector<Tupla3f> &colorPar, std::vector<Tupla3f> &colorImpar, 
const std::vector<Tupla3i> &caras, std::vector<Tupla3i> &carasPares, std::vector<Tupla3i> &carasImpares, 
const std::vector<Tupla3f> &colores){

   colorImpar.resize(colores.size());
   colorPar.resize(colores.size());

   setColor(colorA,colorImpar);
   setColor(colorB,colorPar);

   carasPares.resize(caras.size()/2);
   carasImpares.resize(caras.size()/2);

   for(int i=0, j=0; i<f.size(); i+=2, j++){
      carasPares[j]=caras[i];
      carasImpares[j]=caras[i+1];
   }

}

void Malla3D::calcular_normales(){
   //Calcular normales de las caras
   std::vector<Tupla3f> normalesCaras;
   Tupla3f a, b, perpendicular, normal;
   int x, y, z;

   for(int i=0; i<f.size(); i++){
      //Vertices, que deben de estar en todos los casos en el mismo sentido, 
      //ya sea horario o antihorario.
      x=f[i][0];
      y=f[i][1];
      z=f[i][2];
      
      //Aristas
      a=v[y]-v[x];
      b=v[z]-v[x];

      perpendicular=a.cross(b); 
      normal=perpendicular.normalized(); //Normal de la perpendicular de la cara

      normalesCaras.push_back(normal);
   }

   //Normales de los vertices
   nv=std::vector<Tupla3f>(v.size(),{0,0,0});

   for(int i=0; i<f.size(); i++){
      x=f[i][0];
      y=f[i][1];
      z=f[i][2];

      nv[x]=(nv[x]+normalesCaras[i]);
      nv[y]=(nv[y]+normalesCaras[i]);
      nv[z]=(nv[z]+normalesCaras[i]);
   }

   for(int i=0; i<nv.size(); i++){
      Tupla3f normalizado;
      normalizado=nv[i].normalized();
      nv[i]=normalizado;
   }
   
}