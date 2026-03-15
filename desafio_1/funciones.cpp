#include <iostream>

using namespace std;


bool **creacion_matriz(int ancho,int alto){
    int i,e;
    bool **matriz;
    matriz= new bool*[alto];
    for(i=0;i<alto;i++){
        matriz[i]=new bool[ancho];
    }

    for(i=0;i<alto;i++){
        for(e=0;e<ancho;e++){
            matriz[i][e]=true;
        }
    }
    return matriz;
}

void impresion_matriz(int ancho,int alto,bool **matriz){
    int i,e;
    for(i=0;i<alto;i++){
        cout<<"|";
        for(e=0;e<ancho;e++){
            if (matriz[i][e]){
                cout<<"."<<" ";
            }
            else{
                cout<<"[]"<<" ";
            }
        }
        cout<<"|"<<endl;
    }

}

void eliminar(int ancho,int alto,bool **matriz){
    for(int i=0;i<alto;i++){
        delete [] matriz[i];
    }
    delete [] matriz;
}
