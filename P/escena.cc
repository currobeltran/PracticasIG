#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   tetraedro=new Tetraedro();
   cubo=new Cubo();
   cuadro=new Cuadro(2);
   cuadro2=new Cuadro(200);
   unaPiramide=new Piramide();
   
   unPly=new ObjPLY("./plys/big_dodge.ply");
   unObjRev=new ObjRevolucion("./plys/peon.ply",40);
   unCono=new Cono(40,2,2,true,true);
   unCil=new Cilindro(30,1,1,true,true);

   unaLuz=new LuzPosicional({40,40,40},GL_LIGHT1,{0.0, 0.0, 0.0, 1.0},
   {1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   unaLuz2=new LuzDireccional({1,1,1},GL_LIGHT2,{0.0, 0.0, 0.0, 1.0},
   {1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});

   //Material blanco
   mat=Material({1.0,1.0,1.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},128.0);

   //Material rojo techo
   mat2=Material({0.2295,0.08825,0.0275,1.0},{0.5508,0.2118,0.066,1.0},{0.580594,0.223257,0.0695701,1.0},128.0);
   
   //Material verde
   mat3=Material({0.135,0.2225,0.1575,0.95},{0.54,0.89,0.63,0.95},{0.316228,0.316228,0.316228,0.95},128.0);

   textura1=new Textura("./img/grass.jpg");
   textura2=new Textura("./img/bricks.jpg");

   modelo=new Persona();
   
   luces={false};

   camaras[0]=new Camara({200,200,200},{0,0,0},{0,1,0},0,10,10,50,1000);
   camaras[1]=new Camara({0,50,200},{0,0,0},{0,1,0},1,10,10,50,1000);
   camaras[2]=new Camara({0,0,-200},{0,0,0},{0,1,0},0,1000,1000,0.1,1000);

   seleccionado=false;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
   
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );
 
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar(){

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   change_observer();
   
   if(glIsEnabled(GL_LIGHTING))
      glDisable(GL_LIGHTING);
   
   ejes.draw();

   if(modoIluminacion){
      if(!glIsEnabled(GL_LIGHTING))
         glEnable(GL_LIGHTING);

      unObjRev->setMaterial(mat3); 
      cubo->setMaterial(mat);
      unCono->setMaterial(mat);
      unPly->setMaterial(mat);
      unCil->setMaterial(mat);
      modelo->setMaterial(mat);
      cuadro->setMaterial(mat);
      cuadro2->setMaterial(mat);
      unaPiramide->setMaterial(mat2);
      tetraedro->setMaterial(mat);

      if(luces[1])
         unaLuz->activar();
      else{
         glDisable(GL_LIGHT1);
      }

      if(luces[2])
         unaLuz2->activar();
      else{
         glDisable(GL_LIGHT2);
      }

   }

   else{
      if(glIsEnabled(GL_LIGHTING))
         glDisable(GL_LIGHTING);
   }

   glEnable(GL_CULL_FACE);

   glEnable(GL_TEXTURE_2D);
      glPushMatrix();
         cuadro2->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion, textura1);
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   glPushMatrix();
      glTranslatef(-20,0,-20);
      glRotatef(90,0,1,0);
      glScalef(0.1,0.1,0.1);
      modelo->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(10,0,0);
      unCono->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-10,0,-20);
      glRotatef(-90,0,1,0);
      glScalef(0.3,0.3,0.3);
      unPly->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

   glPushMatrix();
      unObjRev->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-25,2,20);
      glScalef(3,3,3);
      tetraedro->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-25,2,-20);
      glScalef(3,3,3);
      cubo->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
      glTranslatef(0,1,0);
      unaPiramide->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
   glPopMatrix();

}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
      break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Modo visualizacion objeto" <<endl;
      break ;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Modo dibujado objeto" <<endl;
      break ;

      case 'P':
         //SELECCION DEL MODO PUNTO
         if(modoMenu==SELVISUALIZACION){
            cout << "Visualizando el objeto en modo punto" <<endl;
            modoPunto=!modoPunto;
         }
      break;

      case 'L':
         //SELECCION DEL MODO LINEA
         if(modoMenu==SELVISUALIZACION){
            cout << "Visualizando el objeto en modo linea" <<endl;
            modoLinea=!modoLinea;
         }
      break;

      case 'S':
         //SELECCION DEL MODO SOLIDO
         if(modoMenu==SELVISUALIZACION){
            cout << "Visualizando el objeto en modo solido" <<endl;
            modoSolido=!modoSolido;
         }
      break;

      case 'A':
         //SELECCION DEL MODO AJEDREZ
         if(modoMenu==SELVISUALIZACION && !modoIluminacion){
            cout << "Visualizando el objeto en modo ajedrez" <<endl;
            modoAjedrez=!modoAjedrez;
         }
         if(modoIluminacion){
            cout << "Modo de variación del ángulo alpha" <<endl;
            alfa=true;
         }
      break;

      case '0':
         if(modoIluminacion && modoMenu==SELVISUALIZACION){
            luces[0]=!luces[0];
            cout << "Cambiando estado de luz 0" <<endl;
         }
         if(cambiarModeloManual && modoMenu==SELVISUALIZACION){
            gradoLibertad=0;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
         if(menuCamara && modoMenu==SELVISUALIZACION){
            camaraActiva=0;
         }
      break;

      case '1':
         //SELECCION DEL MODO INMEDIATO
         if(modoMenu==SELDIBUJADO){
            cout << "Visualizando el objeto en modo inmediato" <<endl;
            modoDibujo=1;
         }
         else if(modoIluminacion && modoMenu==SELVISUALIZACION){
            luces[1]=!luces[1];
            cout << "Cambiando estado de luz 1" <<endl;
         }
         if(cambiarModeloManual && modoMenu==SELVISUALIZACION){
            gradoLibertad=1;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
         if(menuCamara && modoMenu==SELVISUALIZACION){
            camaraActiva=1;
         }
      break;

      case '2':
         //SELECCION DEL MODO DIFERIDO
         if(modoMenu==SELDIBUJADO){
            cout << "Visualizando el objeto en modo diferido" <<endl;
            modoDibujo=2;
         }
         else if(modoIluminacion && modoMenu==SELVISUALIZACION){
            luces[2]=!luces[2];
            cout << "Cambiando estado de luz 2" <<endl;
         }
         if(cambiarModeloManual && modoMenu==SELVISUALIZACION){
            gradoLibertad=2;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
         if(menuCamara && modoMenu==SELVISUALIZACION){
            camaraActiva=2;
         }
      break;

      case '3':
         if(modoIluminacion){
            luces[3]=!luces[3];
            cout << "Cambiando estado de luz 3" <<endl;
         }
         if(cambiarModeloManual){
            gradoLibertad=3;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
      break;

      case '4':
         if(modoIluminacion){
            luces[4]=!luces[4];
            cout << "Cambiando estado de luz 4" <<endl;
         }
         if(cambiarModeloManual){
            gradoLibertad=4;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
      break;

      case '5':
         if(modoIluminacion){
            luces[5]=!luces[5];
            cout << "Cambiando estado de luz 5" <<endl;
         }
         if(cambiarModeloManual){
            gradoLibertad=5;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
      break;

      case '6':
         if(modoIluminacion){
            luces[6]=!luces[6];
            cout << "Cambiando estado de luz 6" <<endl;
         }
         if(cambiarModeloManual){
            gradoLibertad=6;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
      break;

      case '7':
         if(modoIluminacion){
            luces[7]=!luces[7];
            cout << "Cambiando estado de luz 7" <<endl;
         }
         if(cambiarModeloManual){
            gradoLibertad=7;
            cout << "Seleccionado grado libertad " << gradoLibertad <<endl;
         }
      break;

      case 'T':
         //SELECCION DE TAPAS
         unObjRev->cambiarTapas(tapas);
         unCono->cambiarTapas(tapas);
         unCil->cambiarTapas(tapas);
         cout << "Cambiando el estado de las tapas de los objetos de revolución" <<endl;
      break;

      case 'I':
         //MODO DE ILUMINACION
         if(modoMenu==SELVISUALIZACION){
            modoIluminacion=!modoIluminacion;
            cout << "Seleccion del modo de iluminacion" <<endl;
         }
      break;

      case 'B':
         if(modoIluminacion){
            cout << "Modo de variación del ángulo beta" <<endl;
            alfa=false;
         }
      break;

      case '>':
         if(alfa && modoMenu==SELVISUALIZACION){
            unaLuz2->variarAnguloAlpha(1.0);
         }
         else if(!alfa && modoMenu==SELVISUALIZACION){
            unaLuz2->variarAnguloBeta(1.0);
         }
      break;

      case '<':
         if(alfa && modoMenu==SELVISUALIZACION){
            unaLuz2->variarAnguloAlpha(-1.0);
         }
         else if(!alfa && modoMenu==SELVISUALIZACION){
            unaLuz2->variarAnguloBeta(-1.0);
         }
      break;

      case 'G':
         if(modoMenu==SELVISUALIZACION){
            cambiarModeloManual=!cambiarModeloManual;
            cout << "Seleccione grado de libertad a cambiar" <<endl;
         }
      break;

      case '+':
         if(cambiarModeloManual){
            switch(gradoLibertad){
               case 0:
                  modelo->modificarRodillas(true,1.0);
               break;

               case 1:
                  modelo->modificarRodillas(false,1.0);
               break;

               case 2:
                  modelo->rotarPiernas(true,1.0);
               break;

               case 3:
                  modelo->rotarPiernas(false,1.0);
               break;

               case 4:
                  modelo->modificarCodo(true,1.0);
               break;

               case 5:
                  modelo->modificarCodo(false,1.0);
               break;

               case 6:
                  modelo->modificarBrazo(true,1.0);
               break;

               case 7:
                  modelo->modificarBrazo(false,1.0);
               break;
            }
         }
      break;

      case '-':
         if(cambiarModeloManual){
            switch(gradoLibertad){
               case 0:
                  modelo->modificarRodillas(true,-1.0);
               break;

               case 1:
                  modelo->modificarRodillas(false,-1.0);
               break;

               case 2:
                  modelo->rotarPiernas(true,-1.0);
               break;

               case 3:
                  modelo->rotarPiernas(false,-1.0);
               break;

               case 4:
                  modelo->modificarCodo(true,-1.0);
               break;

               case 5:
                  modelo->modificarCodo(false,-1.0);
               break;

               case 6:
                  modelo->modificarBrazo(true,-1.0);
               break;

               case 7:
                  modelo->modificarBrazo(false,-1.0);
               break;
            }
         }
      break;

      case 'J':
         if(modoMenu==SELVISUALIZACION){
            animacion=!animacion;
            cout << "Animacion persona activada" <<endl;
         }
      break;

      case 'X':
         if(modoMenu==SELVISUALIZACION && modoIluminacion){
            animacionLuz=!animacionLuz;
            cout << "Animacion de luz activada" <<endl;
         }
      break;

      case 'C':
         menuCamara=!menuCamara;
         cout << "Seleccione la camara que desea usar";
      break;

   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva]->zoom(1);
         change_projection();
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva]->zoom(-1);
         change_projection();
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camaras[camaraActiva]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva]->setObserver();
}

void Escena::animarModeloJerarquico(){
   switch(parte){
      case 0:
         darPaso(true);
         darPaso2(false);
         moverBrazo(false);
         moverBrazo2(true);
         modelo->mover();
         if(pasos%45==0 && pasos!=0){
            parte=1;
         }
      break;

      case 1:
         darPaso2(true);
         darPaso(false);
         moverBrazo(true);
         moverBrazo2(false);
         modelo->mover();
         if(pasos%45==0){
            parte=2;
         }
      break;

      case 2:
         darPaso(false);
         darPaso2(true);
         moverBrazo(false);
         moverBrazo2(true);
         modelo->mover();
         if(pasos%45==0){
            parte=3;
         }
      break;

      case 3:
         darPaso2(false);
         darPaso(true);
         moverBrazo(true);
         moverBrazo2(false);
         modelo->mover();
         if(pasos%45==0){
            parte=0;
         }
      break;
   }

   pasos++;
}

bool Escena::animacionActivada(){
   return animacion;
}

bool Escena::animacionLuzActivada(){
   return animacionLuz;
}

void Escena::darPaso(bool piernaD){
   modelo->rotarPiernas(piernaD,-velocidad);
   modelo->modificarRodillas(piernaD,velocidad);
}

void Escena::darPaso2(bool piernaD){
   modelo->rotarPiernas(piernaD,velocidad);
   modelo->modificarRodillas(piernaD,-velocidad);
}

void Escena::moverBrazo(bool brazoD){
   modelo->modificarBrazo(brazoD,-velocidad);
   modelo->modificarCodo(brazoD,-velocidad);
}

void Escena::moverBrazo2(bool brazoD){
   modelo->modificarBrazo(brazoD,velocidad);
   modelo->modificarCodo(brazoD,velocidad);
}

void Escena::animarLuz(){
   variacionLuzPuntual++;
   unaLuz->variarPosicion(variacionLuzPuntual);
}

void Escena::ratonMovido( int x, int y ){
   if(estadoRaton==1){
      if(seleccionado)
         camaras[camaraActiva]->girar(x-xant,y-yant);

      else{
         camaras[camaraActiva]->rotarXFirstPerson((x-xant)*0.01);
         camaras[camaraActiva]->rotarYFirstPerson((y-yant)*0.01);
      }
      xant=x;
      yant=y;
   }
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   if(boton==GLUT_RIGHT_BUTTON){
      if(estado==GLUT_DOWN){
         estadoRaton=1;
         xant=x;
         yant=y;
      }
   }
   
   else if(boton==GLUT_LEFT_BUTTON){
      if(estado==GLUT_DOWN){
         xsel=x;
         ysel=y;
         dibujaSeleccion();
      }
   }

   else{
      estadoRaton=0;
   }

}

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);
   bool i=false;

   if(glIsEnabled(GL_LIGHTING)){
      i=true;
      modoIluminacion=false;
      glDisable(GL_LIGHTING);
   }
   Tupla3f colorNuevo={1.0,0,0};
   Tupla3f resultado;
   seleccionado=true;

   unCono->setNuevoColor(colorNuevo);

   dibujar();

   glReadPixels(xsel,ysel,1,1,GL_RGB,GL_FLOAT,(void *)resultado);

   if(resultado[0]==1.0 && resultado[1]==0 && resultado[2]==0){
      camaras[camaraActiva]->setPuntoRotacion({10,0,0});
   }
   else{
      camaras[camaraActiva]->setPuntoRotacion({0,0,0});
      seleccionado=false;
   }

   unCono->setNuevoColor({0,0,1.0});

   if(i){
      modoIluminacion=true;
      glEnable(GL_LIGHTING);
   }
   glEnable(GL_DITHER);
}