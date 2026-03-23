# wzip

Programa simple en C que comprime archivos usando RLE (Run-Length Encoding).
Cuenta repeticiones consecutivas de cada byte y escribe pares: cantidad (int) + byte.

Archivo principal: `wzip.c`

## Comportamiento esperado

1. Recibe uno o mas archivos de entrada.
2. Lee todos los archivos en orden, como si fueran un solo flujo continuo.
3. Agrupa bytes consecutivos iguales y escribe en salida estandar:
   - `int` con la cantidad de repeticiones.
   - `char` con el byte repetido.
4. Si no recibe archivos, imprime `wzip: file1 [file2 ...]` y termina con error.
5. Si un archivo no se puede abrir, imprime `wzip: cannot open file` y termina con error.
6. En casos validos, termina con estado 0.

## Compilacion (WSL)

Desde esta carpeta (`programas/wzip`):

```bash
gcc -Wall -Wextra -Werror -std=c11 -O2 wzip.c -o wzip
```

## Ejecucion

Comprimir un archivo:

```bash
./wzip archivo.txt > archivo.z
```

Comprimir varios archivos:

```bash
./wzip a.txt b.txt > salida.z
```

## Lista minima de pruebas

1. Caso normal con repeticiones.
   - Entrada: archivo con `aaabb`.
   - Esperado: salida binaria con runs `(3,'a')` y `(2,'b')`.

2. Varios archivos y continuidad entre archivos.
   - Entrada: `a.txt` termina en `a` y `b.txt` empieza con `a`.
   - Esperado: se juntan en la misma corrida (run) porque el flujo es continuo.

3. Sin argumentos.
   - Entrada: `./wzip`
   - Esperado: `wzip: file1 [file2 ...]` por `stderr` y exit status 1.

4. Archivo inexistente.
   - Entrada: `./wzip no_existe.txt`
   - Esperado: `wzip: cannot open file` por `stderr` y exit status 1.

5. Archivo vacio.
   - Entrada: archivo de tamano 0.
   - Esperado: no escribe datos en stdout y no falla.


## Problemas y Soluciones

1. romper continuidad de corridas entre archivos

Version mal:

```c
for (i = 1; i < argc; i++) {
    count = 0;
    previous_byte = 0;
    FILE *file = fopen(argv[i], "rb");
}
```

Version bien (codigo actual):

```c
previous_byte = 0;
count = 0;
int has_data = 0;

for (i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");
    ...
}
```

Por que lo soluciona: mantiene estado global de corrida para todos los archivos.

2. perder la ultima corrida

Version mal:

```c
while ((current_byte = fgetc(file)) != EOF) {
    ...
}
// falta escribir corrida final
```

Version bien (codigo actual):

```c
if (has_data) {
    write_run(count, previous_byte);
}
```

Por que lo soluciona: guarda el ultimo bloque que no dispara cambio de byte al final.

3. contar mal repeticiones por inicializacion incorrecta

Version mal:

```c
if (!has_data) {
    count = 0;
}
```

Version bien (codigo actual):

```c
if (!has_data) {
    previous_byte = current_byte;
    count = 1;
    has_data = 1;
} else if (current_byte == previous_byte) {
    count++;
} else {
    write_run(count, previous_byte);
    previous_byte = current_byte;
    count = 1;
}
```

Por que lo soluciona: cada nueva corrida empieza en 1 y las repeticiones se acumulan correctamente.