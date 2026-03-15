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


void destruir_tablero(unsigned char** tablero, int alto) {
    for(int i = 0; i < alto; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
}


void impresion_matriz(int ancho, int alto, unsigned char** tablero) {
    int bytes_por_fila = ancho / 8;

    for(int i = 0; i < alto; i++) {
        for(int b = 0; b < bytes_por_fila; b++) {

            for(int bit = 7; bit >= 0; bit--) {
                if(tablero[i][b] & (1 << bit)) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}

int main(){
    int alto,ancho;
    while (true){
        cout<<"Ingrese el alto del tablero (minimo 8): ";
        cin>>alto;
        if (alto>=8 && alto<=30){
            break;
        }
        else {
            if(alto>30){
                cout<<"Esta altura sobrepasa los limites visibles del tablero. Ingrese otro numero"<<endl;
            }
            else{
                cout<<"Incorrecto, Ingrese otro numero"<<endl;
            }
        }

    }
    while (true){
        cout<<"Ingrese el ancho del tablero (minimo 8 y multiplo de 8): ";
        cin>>ancho;
        if(ancho>=8 && ancho%8==0){
            break;
        }
        else{
            cout<<"Incorrecto, Ingrese otro numero"<<endl;
        }
    }


    unsigned char** miMatriz = crear_tablero(ancho, alto);

    impresion_matriz(ancho, alto, miMatriz);

}
