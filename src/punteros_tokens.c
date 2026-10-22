/* Matricula: 10240041
   Nombre: DIEGO DECIDERIO GARCIA
   Actividad 2 - Apuntadores y tokens */

#include <stddef.h>
#include <stdio.h>

int avanzar_linea(int *linea) {
    if (linea == NULL) {
        return 0;
    }

    (*linea)++;
    return 1;
}

size_t longitud_lexema(const char *texto) {
    const char *cursor;
    size_t longitud = 0;

    if (texto == NULL) return 0;
    cursor = texto;

    while (*cursor != '\0') {
        cursor++;
        longitud++;
    }
    return longitud;
}

int main(void) {
    int linea_actual = 1;
    int *p_linea = &linea_actual;

    printf("directo=%d | por_puntero=%d | misma_direccion=%s\n",
           linea_actual, *p_linea,
           p_linea == &linea_actual ? "si" : "no");

    printf("avance_valido=%d\n", avanzar_linea(p_linea));
    printf("avance_nulo=%d\n", avanzar_linea(NULL));
    printf("despues=%d\n", linea_actual);

    const char *lexema = "total";

    printf("lexema=%s | longitud=%zu\n",
           lexema, longitud_lexema(lexema));
    printf("vacio=%zu | nulo=%zu\n",
           longitud_lexema(""), longitud_lexema(NULL));
    return 0;
}