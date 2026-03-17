#include <iostream>

using namespace std;


unsigned char** crear_tablero(int ancho, int alto) {

    int bytes_por_fila = ancho / 8;

    unsigned char** tablero = new unsigned char*[alto];

    for(int i = 0; i < alto; i++) {
        tablero[i] = new unsigned char[bytes_por_fila];

        for(int j = 0; j < bytes_por_fila; j++) {
            tablero[i][j] = 0;
        }
    }

    return tablero;
}

void impresion_matriz(int ancho, int alto, unsigned char** tablero) {
    int bytes_por_fila = ancho / 8;

    for(int i = 0; i < alto; i++) {
        cout<<"|";
        for(int b = 0; b < bytes_por_fila; b++) {

            for(int bit = 7; bit >= 0; bit--) {
                if(tablero[i][b] & (1 << bit)) {
                    cout << "[]";
                } else {
                    cout << "."<<" ";
                }
            }
        }
        cout<<"|"<<endl;
    }
}

void primera_pieza(unsigned char** matriz, int ancho) {
    int a = ancho / 2;

    int byte_pos = a / 8;
    int bit_pos = 7 - (a % 8);

    matriz[0][byte_pos] |= (1 << bit_pos);
}




void cambio_abajo(int ancho, int alto, unsigned char** tablero){

    int bytes_por_fila = ancho / 8;
    alto-=1;

    for(int i = 0; i < alto; i++) {
        for(int b = 0; b < bytes_por_fila; b++) {

            for(int bit = 7; bit >= 0; bit--) {
                if(tablero[i][b] & (1 << bit)) {
                    tablero[i+1][b]|=(1 << bit);
                    tablero[i][b] &= ~(1 << bit);
                    return ;
                }
            }
        }
    }
}

void cambio_derecha(int ancho, int alto, unsigned char** tablero){

    int bytes_por_fila = ancho / 8;

    for(int i = 0; i < alto; i++) {
        for(int b = 0; b < bytes_por_fila; b++) {

            for(int bit = 7; bit >= 0; bit--) {
                if(tablero[i][b] & (1 << bit)) {
                    if(bit > 0) {
                        tablero[i][b] |= (1 << (bit - 1));
                        tablero[i][b] &= ~(1 << bit);
                        return;
                    }

                }
            }
        }
    }
}

void cambio_izquierda(int ancho, int alto, unsigned char** tablero){

    int bytes_por_fila = ancho / 8;

    for(int i = 0; i < alto; i++) {
        for(int b = 0; b < bytes_por_fila; b++) {

            for(int bit = 7; bit >= 0; bit--) {
                if(tablero[i][b] & (1 << bit)) {
                    if(bit < 7) {
                        tablero[i][b] |= (1 << (bit + 1));
                        tablero[i][b] &= ~(1 << bit);
                        return;
                    }
                }
            }
        }
    }
}

void coliciones(){

}

