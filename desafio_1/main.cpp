#include <iostream>
#include "funciones.h"

using namespace std;


int main() {
    bool jugando = true;
    char tecla;

    int alto_tablero, ancho_tablero;

    while (true){
        cout<<"Ingrese el alto del tablero (minimo 8):";
        cin>>alto_tablero;
        if (alto_tablero>=8) break;
        cout<<"Incorrecto, Ingrese otro numero\n";
    }

    while (true){
        cout<<"Ingrese el ancho del tablero (minimo 8 y multiplo de 8):";
        cin>>ancho_tablero;
        if(ancho_tablero>=8 && ancho_tablero%8==0) break;
        cout<<"Incorrecto, Ingrese otro numero\n";
    }


    iniciar_aleatoriedad();
    unsigned char** tablero = crear_tablero(ancho_tablero, alto_tablero);

    //u_ancho y u_alto ---> variables temporales
    unsigned char pieza_activa[4];
    unsigned char u_ancho, u_alto;
    int tipo_pieza;


    generar_pieza_aleatoria(pieza_activa, u_ancho, u_alto, tipo_pieza);

    int p_ancho = u_ancho;
    int p_alto = u_alto;


    int pos_x = (ancho_tablero / 2) - 1;
    int pos_y = -p_alto + 1;


    while (jugando) {


        imprimir_frame(ancho_tablero, alto_tablero, tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y);


        cout << "Movimiento (a=izq, d=der, s=bajar, w=rotar, q=salir): ";
        cin >> tecla;

        switch (tecla) {

        case 'a': case 'A':
            pos_x--;
            if (verificar_colision(ancho_tablero, alto_tablero, tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y)) {
                pos_x++;
            }
            break;

        case 'd': case 'D':
            pos_x++;
            if (verificar_colision(ancho_tablero, alto_tablero, tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y)) {
                pos_x--;
            }
            break;

        case 'w': case 'W':
            intentar_rotar(pieza_activa, p_ancho, p_alto, pos_x, pos_y, ancho_tablero, alto_tablero, tablero);
            break;

        case 's': case 'S':
            pos_y++;

            if (verificar_colision(ancho_tablero, alto_tablero, tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y)) {

                pos_y--;


                fijar_pieza(tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y, ancho_tablero, alto_tablero);

                eliminar_filas(ancho_tablero, alto_tablero, tablero);


                generar_pieza_aleatoria(pieza_activa, u_ancho, u_alto, tipo_pieza);
                p_ancho = u_ancho;
                p_alto = u_alto;

                pos_x = (ancho_tablero / 2) - 1;
                pos_y = -p_alto + 1;

                if (comprobar_game_over(ancho_tablero, alto_tablero, tablero, pieza_activa, p_ancho, p_alto, pos_x, pos_y)) {
                    jugando = false;
                }
            }
            break;

        case 'q': case 'Q':
            jugando = false;
            break;

        default:
            break;
        }
    }

    cout <<endl<<"GAME OVER. Has perdido malooooo."<<endl;


    destruir_tablero(tablero, alto_tablero);
    return 0;
}
