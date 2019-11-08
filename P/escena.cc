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
   
   unPly=new ObjPLY("./plys/beethoven.ply");
   unObjRev=new ObjRevolucion("./plys/peon.ply",30);
   unCono=new Cono(40,1,1,true,true);

   unaLuz=new LuzPosicional({500,500,500},GL_LIGHT1,{0.0, 0.0, 0.0, 1.0},
   {1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   unaLuz2=new LuzDireccional({1,1,5},GL_LIGHT1,{0.0, 0.0, 0.0, 1.0},
   {1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   mat=Material({1.0,1.0,1.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},128.0);
   luces={false};
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

   change_projection( float(UI_window_width)/float(UI_window_height) );
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
   ejes.draw();

   if(modoIluminacion){
      if(!glIsEnabled(GL_LIGHTING))
         glEnable(GL_LIGHTING); // se habilitan las luces
      unObjRev->setMaterial(mat);
      // unCono->setMaterial(mat); 
   }
   else{
      if(glIsEnabled(GL_LIGHTING))
         glDisable(GL_LIGHTING);
   }

   glEnable(GL_CULL_FACE);

   glPushMatrix();
      glScalef(20,20,20);
      glTranslatef(5,2,2);
      //unCono->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
      glTranslatef(-5,-2,-2);
      unObjRev->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
      //tetraedro->draw(modoDibujo, modoPunto, modoLinea, modoSolido, modoAjedrez, modoIluminacion);
      unaLuz2->activar();
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
         if(modoMenu==SELVISUALIZACION){
            cout << "Visualizando el objeto en modo ajedrez" <<endl;
            modoAjedrez=!modoAjedrez;
         }
      break;

      case '0':
         if(modoIluminacion){
            luces[0]=!luces[0];
         }
      break;

      case '1':
         //SELECCION DEL MODO INMEDIATO
         if(modoMenu==SELDIBUJADO){
            cout << "Visualizando el objeto en modo inmediato" <<endl;
            modoDibujo=1;
         }
         else if(modoIluminacion){
            luces[1]=!luces[1];
         }
      break;

      case '2':
         //SELECCION DEL MODO DIFERIDO
         if(modoMenu==SELDIBUJADO){
            cout << "Visualizando el objeto en modo diferido" <<endl;
            modoDibujo=2;
         }
         else if(modoIluminacion){
            luces[2]=!luces[2];
         }
      break;

      case '3':
         if(modoIluminacion){
            luces[3]=!luces[3];
         }
      break;

      case '4':
         if(modoIluminacion){
            luces[4]=!luces[4];
         }
      break;

      case '5':
         if(modoIluminacion){
            luces[5]=!luces[5];
         }
      break;

      case '6':
         if(modoIluminacion){
            luces[6]=!luces[6];
         }
      break;

      case '7':
         if(modoIluminacion){
            luces[7]=!luces[7];
         }
      break;

      case 'T':
         //SELECCION DE TAPAS
         unObjRev->cambiarTapas(tapas);
         //unCono->cambiarTapas(tapasant);
      break;

      case 'I':
         //MODO DE ILUMINACION
         if(modoMenu==SELVISUALIZACION){
            modoIluminacion=!modoIluminacion;
            cout << "Seleccion del modo de iluminacion" <<endl;
         }
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
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
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

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
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
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
