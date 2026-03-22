#include <iostream>
#include <funciones.h>
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

void imprimir_frame(int ancho, int alto, unsigned char** tablero,
                    unsigned char pieza[4], int p_ancho, int p_alto,
                    int pieza_x, int pieza_y) {

    int bytes_por_fila = ancho / 8;

    for(int x = 0; x < (ancho * 2) + 2; x++) {
        cout << "_";
    }
    cout <<endl;

    for(int y = 0; y < alto; y++) {
        cout << "|";
        int x_actual = 0;

        for(int b = 0; b < bytes_por_fila; b++) {
            for(int bit = 7; bit >= 0; bit--) {

                bool bit_tablero = (tablero[y][b] >> bit) & 1;
                bool bit_pieza = false;

                bool en_rango_vertical = (y >= pieza_y) && (y < pieza_y + p_alto);
                bool en_rango_horizontal = (x_actual >= pieza_x) && (x_actual < pieza_x + p_ancho);

                if (en_rango_vertical && en_rango_horizontal){
                    int alto_verdadero = y - pieza_y;
                    int ancho_verdadero = x_actual - pieza_x;
                    int bit_leer = (p_ancho - 1) - ancho_verdadero;
                    bit_pieza = (pieza[alto_verdadero] >> bit_leer) & 1;
                }

                if (bit_tablero || bit_pieza){
                    cout << "[]";
                }
                else{
                    cout << " .";
                }

                x_actual++;
            }
        }
        cout <<"|"<<endl;
    }

    for(int x = 0; x < (ancho * 2) + 2; x++) {
        cout << "-";
    }
    cout <<endl;
}



bool verificar_colision(int ancho, int alto, unsigned char** tablero,
                        unsigned char pieza[4], int p_ancho, int p_alto,
                        int futuro_x, int futuro_y) {

    // recorrer area de la pieza
    for (int fila_pieza = 0; fila_pieza < p_alto; fila_pieza++) {
        for (int col_pieza = 0; col_pieza < p_ancho; col_pieza++) {

            // verificar si el bit de la pieza es # o .
            int bit_leer = (p_ancho - 1) - col_pieza;
            bool bloque_solido_pieza = (pieza[fila_pieza] >> bit_leer) & 1;

            if (!bloque_solido_pieza){
                continue;
            }

            //si el bit es #, verificamos su futura pocision (x,y) en el tablero
            int y_tablero = futuro_y + fila_pieza;
            int x_tablero = futuro_x + col_pieza;

            // colision con bordes
            if (x_tablero < 0 || x_tablero >= ancho || y_tablero >= alto) {
                return true;
            }

            if (y_tablero < 0){
                continue;
            }

            //cf --> coordenada futura
            // calcula a qué byte y bit del tablero base corresponde esta coordenada
            int byte_cf = x_tablero / 8;
            int bit_cf = 7 - (x_tablero % 8);

            // ya hay un bloque que ocupa ese espacio?
            bool bloque_ocupado_tablero = (tablero[y_tablero][byte_cf] >> bit_cf) & 1;

            if (bloque_ocupado_tablero) {
                return true;
            }
        }
    }

    return false;
}


void eliminar_filas(int ancho, int alto, unsigned char** tablero) {
    int bytes_por_fila = ancho / 8;


    for(int i = alto - 1; i >= 0; i--) {
        //se asume que la fila esta llena
        bool fila_llena = true;

        for(int j = 0; j < ancho; j++) {

            // Hallar el bit exacto
            int byte_i = j / 8;
            int bit_i = 7 - (j % 8);

            // Leemos si hay bloque (1) o vacío (0)
            bool bloque_ocupado = (tablero[i][byte_i] >> bit_i) & 1;

            if (!bloque_ocupado) {
                fila_llena = false;
                break;
            }
        }


        if (fila_llena) {

            // Tomamos la fila actual (i) y todas las que están por encima de ella,
            // y hacemos que copien la información de la fila que tienen arriba.
            for (int y = i; y > 0; y--) {
                for (int b = 0; b < bytes_por_fila; b++) {
                    tablero[y][b] = tablero[y - 1][b];
                }
            }

            // Como todo bajó un espacio, la fila más alta del tablero (la 0)
            // se queda duplicada, así que la vaciamos llenándola de ceros (0).
            for (int b = 0; b < bytes_por_fila; b++) {
                tablero[0][b] = 0;
            }

            //Como la fila i cayo se debe reavaluar su estado, x lo tanto sumamos en i
            //para revertir el i-- del for y reevaluar
            i++;
        }
    }
}


void rotar_pieza_horario(unsigned char pieza[4], int p_ancho, int p_alto) {
    unsigned char temporal[4] = {0, 0, 0, 0};

    for (int fila = 0; fila < p_alto; fila++) {
        for (int col = 0; col < p_ancho; col++) {

            // Leer el bit de la pieza original
            int bit_leer = (p_ancho - 1) - col;
            bool bit_encendido = (pieza[fila] >> bit_leer) & 1;

            if (bit_encendido) {
                int nueva_fila = col;
                int nueva_col = (p_alto - 1) - fila;

                int nuevo_ancho = p_alto;
                int bit_escribir = (nuevo_ancho - 1) - nueva_col;

                // Guardamos el bit en la nueva posición
                temporal[nueva_fila] |= (1 << bit_escribir);
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        pieza[i] = temporal[i];
    }
}


bool intentar_rotar(unsigned char pieza_actual[4],
                    int &p_ancho, int &p_alto,
                    int pos_x, int pos_y,
                    int ancho_tablero, int alto_tablero, unsigned char** tablero) {

    
    unsigned char pieza_clon[4];
    for(int i = 0; i < 4; i++) pieza_clon[i] = pieza_actual[i];

    rotar_pieza_horario(pieza_clon, p_ancho, p_alto);


    int nuevo_ancho = p_alto;
    int nuevo_alto = p_ancho;

  
    bool choca = verificar_colision(ancho_tablero, alto_tablero, tablero,
                                    pieza_clon, nuevo_ancho, nuevo_alto,
                                    pos_x, pos_y);

    if (choca) {
        return false;
    } else {
        for(int i = 0; i < 4; i++) pieza_actual[i] = pieza_clon[i];
        p_ancho = nuevo_ancho;
        p_alto = nuevo_alto;
        return true;
    }
}



void fijar_pieza(unsigned char** tablero, unsigned char pieza[4], int p_ancho, int p_alto, int pos_x, int pos_y, int ancho_tablero, int alto_tablero) {

    // recorrer el area activa de la pieza
    for (int fila = 0; fila < p_alto; fila++) {
        for (int col = 0; col < p_ancho; col++) {

            // extraer bit actual
            int bit_leer = (p_ancho - 1) - col;
            bool bit_encendido = (pieza[fila] >> bit_leer) & 1;

            if (bit_encendido) {
                // calcular las coordenadas reales del bit en el tablero
                int tablero_y = pos_y + fila;
                int tablero_x = pos_x + col;

                // Solo escribimos si las coordenadas están estrictamente dentro del tablero
                if (tablero_y >= 0 && tablero_y < alto_tablero && tablero_x >= 0 && tablero_x < ancho_tablero) {

                    // obtener indice exacto del bit dentro del tablero
                    int byte_idx = tablero_x / 8;
                    int bit_idx = 7 - (tablero_x % 8);

                    // (Bitwise OR) ---> agregar en el mismo byte un nuevo bit (pieza)
                    tablero[tablero_y][byte_idx] |= (1 << bit_idx);
                }
            }
        }
    }
}





bool comprobar_game_over(int ancho_tablero, int alto_tablero, unsigned char** tablero,
                         unsigned char pieza[4], int p_ancho, int p_alto,
                         int pos_x_inicial, int pos_y_inicial) {


    return verificar_colision(ancho_tablero, alto_tablero, tablero,
                              pieza, p_ancho, p_alto,
                              pos_x_inicial, pos_y_inicial);
}
