# wcat

Programa simple en C que muestra en pantalla el contenido de uno o mas archivos de texto, en el orden en que se pasan por argumento. Fue realizado siguiendo las instrucciones de la practica, con las funciones explicadas.

Archivo principal: `wcat.c`

## Comportamiento esperado

1. Si recibe uno o mas archivos:
	- Abre cada archivo.
	- Lee linea por linea con `fgets`.
	- Imprime cada linea con `printf`.
2. Si no recibe archivos:
	- Muestra mensaje de uso por `stderr`.
	- Termina con codigo de error.
3. Si un archivo no se puede abrir:
	- Muestra error por `stderr`.
	- Termina con codigo de error.

## Compilacion (WSL)

Desde esta carpeta (`programas/wcat`):

```bash
gcc -Wall -Wextra -Werror -std=c11 -O2 wcat.c -o wcat
```

## Ejecucion

Ejemplo con un archivo:

```bash
./wcat test1.txt
```

Ejemplo con varios archivos:

```bash
./wcat test1.txt test2.txt
```

## Lista minima de pruebas

1. Caso normal con un archivo.
	- Entrada: un archivo con 2 o 3 lineas.
	- Esperado: imprime exactamente esas lineas.

2. Caso normal con varios archivos.
	- Entrada: dos archivos con contenido distinto.
	- Esperado: imprime primero todo el archivo 1 y luego todo el archivo 2.

3. Sin argumentos.
	- Entrada: ejecutar sin parametros.
	- Esperado: mensaje de uso en `stderr` y salida con error.

4. Archivo inexistente.
	- Entrada: nombre de archivo que no existe.
	- Esperado: mensaje de error en `stderr` y salida con error.

5. Archivo vacio.
	- Entrada: archivo de tamano 0.
	- Esperado: no imprime contenido, pero no falla.

test1.txt: archivo con varias lineas
test2.txt: archivo con una linea
test3.txt: archivo vacío


## Problemas y Soluciones

1. leer un archivo que no se pudo abrir

Version mal:

```c
FILE *file = fopen(argv[i], "r");
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
}
```

Version bien (codigo actual):

```c
FILE *file = fopen(argv[i], "r");
if (file == NULL) {
    fprintf(stderr, "wcat: cannot open file\n");
    return 1;
}
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
}
fclose(file);
```

Por que lo soluciona: evita usar un puntero invalido y termina con mensaje claro.


2. dejar archivos abiertos

Version mal:

```c
// se abre el archivo, pero nunca se cierra
```

Version bien (codigo actual):

```c
fclose(file);
```

Por que lo soluciona: libera recursos correctamente en cada iteracion.
