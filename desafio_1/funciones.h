#ifndef FUNCIONES_H
#define FUNCIONES_H

unsigned char** crear_tablero(int ancho, int alto);

void destruir_tablero(unsigned char** tablero, int alto);

void iniciar_aleatoriedad();

int indice_aleatorio();


void cargar_pieza(int tipo, unsigned char filas_destino[4], unsigned char& ancho, unsigned char& alto);


void generar_pieza_aleatoria(
    unsigned char filas_destino[4],
    unsigned char& ancho_destino,
    unsigned char& alto_destino,
    int& tipo_destino
    );


void imprimir_frame(int ancho, int alto, unsigned char** tablero,
                    unsigned char pieza[4], int p_ancho, int p_alto,
                    int pieza_x, int pieza_y);


bool verificar_colision(int ancho_tablero, int alto_tablero, unsigned char** tablero,
                        unsigned char pieza[4], int p_ancho, int p_alto,
                        int pos_x, int pos_y);

void rotar_pieza_horario(unsigned char pieza[4], int p_ancho, int p_alto);


bool intentar_rotar(unsigned char pieza_actual[4],
                    int &p_ancho, int &p_alto,
                    int pos_x, int pos_y,
                    int ancho_tablero, int alto_tablero, unsigned char** tablero);

void fijar_pieza(unsigned char** tablero, unsigned char pieza[4], int p_ancho, int p_alto, int pos_x, int pos_y, int ancho_tablero, int alto_tablero);


void eliminar_filas(int ancho, int alto, unsigned char** tablero);


bool comprobar_game_over(int ancho_tablero, int alto_tablero, unsigned char** tablero,
                         unsigned char pieza[4], int p_ancho, int p_alto,
                         int pos_x_inicial, int pos_y_inicial);

#endif 
