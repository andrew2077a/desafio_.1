#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int NUM_PIEZAS = 7;
int MAX_FILAS_PIEZA = 4;

unsigned char MASCARA_PIEZAS[7][4] = {
    {0b0001, 0b0001, 0b0001, 0b0001}, // I
    {0b0011, 0b0011, 0, 0},           // O
    {0b0010, 0b0111, 0, 0},           // T
    {0b0011, 0b0110, 0, 0},           // S
    {0b0110, 0b0011, 0, 0},           // Z
    {0b0100, 0b0111, 0, 0},           // J
    {0b0001, 0b0111, 0, 0}            // L
};

unsigned char ANCHO_PIEZAS[7] = {1, 2, 3, 3, 3, 3, 3};
unsigned char ALTO_PIEZAS[7]  = {4, 2, 2, 2, 2, 2, 2};


void iniciar_aleatoriedad() {
    srand(time(nullptr));
}


int indice_aleatorio() {
    return rand() % NUM_PIEZAS;
}


void cargar_pieza(
    int tipo,
    unsigned char filas_destino[4],
    unsigned char& ancho_destino,
    unsigned char& alto_destino
    ) {

    for (int i = 0; i < MAX_FILAS_PIEZA; i++) {
        filas_destino[i] = MASCARA_PIEZAS[tipo][i];
    }

    ancho_destino = ANCHO_PIEZAS[tipo];
    alto_destino = ALTO_PIEZAS[tipo];
}


void generar_pieza_aleatoria(
    unsigned char filas_destino[4],
    unsigned char& ancho_destino,
    unsigned char& alto_destino,
    int& tipo_destino
    ) {
    tipo_destino = indice_aleatorio();
    cargar_pieza(tipo_destino, filas_destino, ancho_destino, alto_destino);
}


void imprimir_pieza(
    const unsigned char filas[4],
    unsigned char ancho,
    unsigned char alto,
    const char* nombre
    ) {
    cout << "Pieza " << nombre << " (" << (int)ancho << "x" << (int)alto << "):\n";

    for (int i = 0; i < alto; i++) {
        cout << "  ";
        for (int b = ancho - 1; b >= 0; b--) {
            cout << ((filas[i] >> b) & 1 ? "#" : ".");
        }
        cout << "\n";
    }
}

int main() {
    iniciar_aleatoriedad();

    unsigned char pieza_actual[4];
    unsigned char ancho_actual, alto_actual;
    int tipo_actual;

    for (int i = 0; i < 5; i++) {
        generar_pieza_aleatoria(pieza_actual, ancho_actual, alto_actual, tipo_actual);

        cout << "\n--- Pieza #" << i+1 << " (tipo " << tipo_actual << ") ---\n";
        imprimir_pieza(pieza_actual, ancho_actual, alto_actual,
                       (tipo_actual == 0 ? "I" :
                            tipo_actual == 1 ? "O" :
                            tipo_actual == 2 ? "T" :
                            tipo_actual == 3 ? "S" :
                            tipo_actual == 4 ? "Z" :
                            tipo_actual == 5 ? "J" :
                                                 "L"));
    }

    return 0;
}

