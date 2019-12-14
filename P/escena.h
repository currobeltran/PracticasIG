#ifndef _ESCENA_H
#define _ESCENA_H

#include "aux.h"
#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"
#include "persona.h"
#include "cuadro.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELTAPAS} menu;

class Escena{

    private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
    
    // variables que definen la posicion de la camara en coordenadas polares
        GLfloat Observer_distance;
        GLfloat Observer_angle_x;
        GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
        GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
        void change_projection( const float ratio_xy );
        void change_observer();

        void clear_window();

        menu modoMenu=NADA;
    
    // Objetos de la escena
        Ejes ejes;
        Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
        Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
        ObjPLY * unPly=nullptr;
        ObjRevolucion * unObjRev=nullptr;
        Cilindro * unCil=nullptr;
        Cono * unCono=nullptr;
        Esfera * unaEsfera=nullptr;
        LuzPosicional * unaLuz=nullptr;
        LuzDireccional * unaLuz2=nullptr;
        Material mat, mat2, mat3;
        Persona * modelo;
        Cuadro * cuadro=nullptr, * cuadro2=nullptr;
        Textura * textura1, * textura2;
   
    // Variable que contiene el modo de dibujado, si inmediato o diferido
        int modoDibujo;

    // Variables que contiene el modo de visualizacion, si linea, punto, solido o ajedrez
        bool modoPunto=false;
        bool modoLinea=false;
        bool modoSolido=false;
        bool modoAjedrez=false;
        bool modoIluminacion=false;
        bool animacion=false;
        bool animacionLuz=false;
        bool alfa=false;
        std::vector<bool> luces=std::vector<bool>(8);

    //Booleano que decide si hay que poner o no tapas
        bool tapas=true;
        bool tapasant=true;

    // Variables modelo jerarquico
        float velocidad=1.0;
        int pasos=0;
        int parte=0;
        int gradoLibertad=0;
        bool cambiarModeloManual=false;
        int variacionLuzPuntual=0;

    public:
        
        Escena();
        void inicializar( int UI_window_width, int UI_window_height );
        void redimensionar( int newWidth, int newHeight ) ;

    // Dibujar
        void dibujar() ;

    // Interacción con la escena
        bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
        void teclaEspecial( int Tecla1, int x, int y );

    // Animacion del modelo jerarquico
        void animarModeloJerarquico();
        bool animacionActivada();
        void darPaso(bool piernaD);
        void darPaso2(bool piernaD);
        void moverBrazo(bool brazoD);
        void moverBrazo2(bool brazoD);

    // Animacion luz puntual
        void animarLuz();
        bool animacionLuzActivada();

};
#endif
