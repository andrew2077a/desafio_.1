#include <iostream>

using namespace std;

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
    return 0;


}
