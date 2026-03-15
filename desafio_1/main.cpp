#include <iostream>

using namespace std;

unsigned char** crear_tablero(int ancho, int alto);
void impresion_matriz(int ancho, int alto, unsigned char** tablero);
void destruir_tablero(unsigned char** tablero, int alto);
void primera_pieza(unsigned char** matriz, int ancho);
void cambio_abajo(int ancho, int alto, unsigned char** tablero);

int main(){
    int alto,ancho;//..
    while (true){
        cout<<"Ingrese el alto del tablero (minimo 8):";
        cin>>alto;
        if (alto>=8){
            break;
        }
        else {
            cout<<"Incorrecto, Ingrese otro numero"<<endl;
        }

    }
    while (true){
        cout<<"Ingrese el ancho del tablero (minimo 8 y multiplo de 8):";
        cin>>ancho;
        if(ancho>=8 && ancho%8==0){
            break;
        }
        else{
            cout<<"Incorrecto, Ingrese otro numero"<<endl;
        }
    }
    unsigned char** tablero = crear_tablero(ancho, alto);
    primera_pieza(tablero, ancho);
    impresion_matriz( ancho,  alto, tablero);


    while(true){
        char a;
        cout<<endl;
        cout<<"Accion:"<<" [A]Izq "<<"[D]Der "<<"[S]Bajar "<<"[W]Rotar "<<"[Q]Salir ";
        cin>>a;
        switch(a){
        case ('A'):
            cambio_abajo( ancho, alto, tablero);
            impresion_matriz( ancho,  alto, tablero);
            break;
        case('D'):
            break;
        case('S'):
            break;
        case('W'):
            break;
        case('Q'):
            break;
        default:
            cout<<"Ingreso ua letra invalida";


        }
    return 0;
    }

}

