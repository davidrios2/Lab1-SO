# wunzip

Programa simple en C que descomprime archivos generados por `wzip`.
Lee pares binarios en este formato: cantidad (`int`) + byte (`char`).

Archivo principal: `wunzip.c`

## Comportamiento esperado

1. Recibe uno o mas archivos comprimidos.
2. Lee cada archivo en orden y descomprime a salida estandar.
3. Por cada par leido (`int` + `char`), imprime el `char` tantas veces como indique el `int`.
4. Si no recibe archivos, imprime `wunzip: file1 [file2 ...]` y termina con error.
5. Si un archivo no se puede abrir, imprime `wunzip: cannot open file` y termina con error.
6. Si el archivo comprimido esta truncado o invalido, imprime `wunzip: invalid compressed file` y termina con error.
7. En casos validos, termina con estado 0.

## Compilacion (WSL)

Desde esta carpeta (`programas/wunzip`):

```bash
gcc -Wall -Wextra -Werror -std=c11 -O2 wunzip.c -o wunzip
```

## Ejecucion

Descomprimir un archivo:

```bash
./wunzip archivo.z > archivo.txt
```

Descomprimir varios archivos comprimidos:

```bash
./wunzip parte1.z parte2.z > salida.txt
```

## Lista minima de pruebas

1. Caso ida y vuelta con `wzip`.
   - Entrada: `texto.txt` -> `./wzip texto.txt > texto.z` -> `./wunzip texto.z > salida.txt`
   - Esperado: `salida.txt` igual a `texto.txt`.

2. Sin argumentos.
   - Entrada: `./wunzip`
   - Esperado: `wunzip: file1 [file2 ...]` por `stderr` y exit status 1.

3. Archivo inexistente.
   - Entrada: `./wunzip no_existe.z`
   - Esperado: `wunzip: cannot open file` por `stderr` y exit status 1.

4. Archivo comprimido invalido/truncado.
   - Entrada: archivo con bytes incompletos de un run.
   - Esperado: `wunzip: invalid compressed file` por `stderr` y exit status 1.

## Problemas y Soluciones (version mal vs version bien del codigo)

1. aceptar archivos truncados sin detectarlos

Version mal:

```c
while (fread(&count, sizeof(int), 1, file) == 1) {
    fread(&byte, sizeof(unsigned char), 1, file);
    ...
}
```

Version bien (codigo actual):

```c
while (fread(&count, sizeof(int), 1, file) == 1) {
    if (fread(&byte, sizeof(unsigned char), 1, file) != 1) {
        return 1;
    }
    ...
}
```

Por que lo soluciona: si falta el byte del par, se marca archivo invalido y se aborta.

2. descomprimir mal una corrida

Version mal:

```c
fputc(byte, stdout);
```

Version bien (codigo actual):

```c
while (count > 0) {
    fputc(byte, stdout);
    count--;
}
```

Por que lo soluciona: escribe el byte exactamente `count` veces.

3. ignorar archivos despues del primero

Version mal:

```c
FILE *file = fopen(argv[1], "rb");
expand_stream(file);
```

Version bien (codigo actual):

```c
for (i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");
    ...
}
```

Por que lo soluciona: recorre todos los archivos comprimidos en orden.
