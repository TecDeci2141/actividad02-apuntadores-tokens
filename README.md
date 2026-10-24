# Actividad 2: apuntadores aplicados al recorrido de tokens en C

## Identificación
- Matrícula: 10240041
- Nombre completo: DIEGO DECIDERIO GARCÍA
- Grupo: 10SC251
- Asignatura: Programación de Sistemas
- Actividad: 2
- Unidad: 4. Análisis sintáctico

## Objetivo
Construir un programa en C que manipula un flujo de tokens ya
construido mediante apuntadores, estructuras y cursores. Se practican
los operadores &, * y ->, el uso de const y NULL, el recorrido seguro
de arreglos y el doble apuntador (Token **), sin desarrollar un
analizador léxico ni sintáctico.

## Declaración
Los tokens fueron escritos manualmente; el programa no realiza
análisis léxico ni sintáctico.

## Estructura del proyecto
actividad02-apuntadores-tokens/
├── src/
│   └── punteros_tokens.c
├── evidencias/
│   ├── salida-final.txt
│   └── sanitizadores.txt
├── .gitignore
└── README.md

## Compilación
gcc -std=c11 -Wall -Wextra -Wpedantic src/punteros_tokens.c -o punteros_tokens

## Ejecución
./punteros_tokens

## Compilación con sanitizadores
gcc -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g src/punteros_tokens.c -o punteros_tokens_san
./punteros_tokens_san

## Resultados de las cinco pruebas obligatorias

### Prueba 1 – Compilación estricta
GCC con -std=c11 -Wall -Wextra -Wpedantic terminó sin errores ni advertencias.

### Prueba 2 – Ejecución normal
- lineas_corregidas=5
- cantidad=12
- identificadores=3
- puntos_y_coma=3
- avance_en_fin=0
- primero_print=print linea=2
- desconocido=no encontrado
- intervalo_vacio=0
- estado de salida: 0

### Prueba 3 – Casos frontera
- avance_nulo=0
- vacio=0 | nulo=0
- avance_en_fin=0
- intervalo_vacio=0

### Prueba 4 – Sanitizadores
AddressSanitizer y UndefinedBehaviorSanitizer no reportaron problemas.
estado_sanitizadores=0.

### Prueba 5 – Regresión
Tras recompilar y volver a ejecutar, se conservan los doce tokens,
los conteos, las búsquedas, los casos frontera y ambos estados en 0.

## Explicación de conceptos clave

- **&** : obtiene la dirección de una variable. Ejemplo: &linea_actual
- ***** : desreferencia; accede al valor situado en esa dirección. Ejemplo: *p_linea
- **->** : accede a un campo a través de un apuntador a estructura. Ejemplo: p_token->linea
- **const** : solo lectura a través de ese apuntador; no permite modificar el objeto
- **NULL** : indica que el apuntador no señala un objeto válido; siempre se comprueba antes de * o ->
- **Token **** : doble apuntador; permite que una función modifique el cursor del llamador

## Respuestas de razonamiento

### 1. Checkpoints 1 y 2: diferencia entre p_linea, *p_linea y &linea_actual
linea_actual es la variable (el valor entero). &linea_actual obtiene
su dirección en memoria. p_linea es un apuntador (int *) que guarda
esa dirección. *p_linea lee o modifica el entero situado allí.
p_linea = 2 sería incorrecto porque asignaría el número 2 como si
fuera una dirección, no un valor. avanzar_linea puede modificar la
variable original porque recibe la dirección (int *) y usa (*linea)++.

### 2. Checkpoint 2: por qué comprobar NULL antes de *linea
Desreferenciar un apuntador nulo provoca un fallo de segmentación.
Si linea == NULL, la función devuelve 0 sin tocar memoria. La evidencia
es avance_nulo=0: el programa no se cae y comunica que la operación
no pudo realizarse.

### 3. Checkpoint 3: función de \0, const char * y literales de cadena
\0 marca el final de la cadena; el cursor avanza mientras
*cursor != '\0'. const char * expresa solo lectura: la función observa
los caracteres sin modificarlos. Un literal de cadena ("total") no debe
modificarse porque reside en memoria de solo lectura; intentar escribirlo
provoca comportamiento indefinido.

### 4. Checkpoint 4: punto, flecha y const Token *
Se utiliza punto (.) con una estructura (muestra.linea) y flecha (->)
con un apuntador a estructura (p_token->linea). const Token * en
mostrar_token impide modificar los campos del token a través de ese
apuntador; solo permite observar.

### 5. Checkpoint 5: sizeof y por qué fin no se desreferencia
sizeof flujo / sizeof flujo[0] divide los bytes totales del arreglo
entre los bytes de un elemento y obtiene la cantidad. fin = flujo + cantidad
apunta al espacio inmediatamente posterior al último elemento. Se puede
comparar (cursor < fin) pero no desreferenciar, porque allí no existe
un token válido.

### 6. Checkpoint 6: por qué contar_tipo usa copia y avanzar_cursor usa Token **
contar_tipo recibe const Token *inicio: mueve una copia del apuntador
y no altera el del llamador. avanzar_cursor necesita const Token **
porque debe modificar el cursor original. &cursor entrega la dirección
de la variable cursor; *cursor es el cursor actual; (*cursor)++ lo avanza.
(void) indica que se descarta intencionalmente el valor de retorno.

### 7. Checkpoints 7 y 8: comprobación de buscar_primero y Token * mutable
Antes de usar el resultado de buscar_primero se debe comprobar
primero != NULL. Si es nulo, no existe el token buscado y desreferenciar
provocaría un fallo. corregir_lineas recibe Token * (sin const) porque
modifica el campo linea; con const Token * el compilador no permitiría
la escritura.

### 8. Cierre: relación del cursor con un analizador sintáctico
El cursor representa la posición de lectura sobre una secuencia de
tokens, de forma análoga a como un analizador sintáctico consume tokens
uno a uno. Esta práctica no construye un analizador léxico ni sintáctico:
los tokens se escribieron manualmente y el programa solo inspecciona
y desplaza apuntadores sobre esos registros en memoria.

## URL del repositorio
https://github.com/TecDeci2141/actividad02-apuntadores-tokens.git