#include <iostream>

using namespace std;


void matriz_impresa(int ancho,int largo){
    int **matriz,i,e;
    matriz= new int*[largo];
    for(i=0;i<largo;i++){
        matriz[i]=new int[ancho];
    }

    for(i=0;i<largo;i++){
        for(e=0;e<ancho;e++){
            matriz[i][e]=0;
        }
    }//.

    for(i=0;i<largo;i++){
        for(e=0;e<ancho;e++){
            cout<<matriz[i][e]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    matriz_impresa( 4, 4);
    return 0;
}
