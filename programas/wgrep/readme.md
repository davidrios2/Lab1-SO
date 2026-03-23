# wgrep

Programa simple en C que busca un termino dentro de lineas de texto.
Si una linea contiene el termino, se imprime. Si no, no se imprime.

Archivo principal: `wgrep.c`

## Comportamiento esperado

1. Siempre recibe un termino de busqueda y cero o mas archivos.
2. Si hay archivos, busca en cada archivo linea por linea.
3. El matching es case-sensitive (`foo` y `Foo` son distintos).
4. Si no hay archivos, lee desde entrada estandar (`stdin`).
5. Si no hay argumentos, imprime `wgrep: searchterm [file ...]` y termina con error.
6. Si un archivo no se puede abrir, imprime `wgrep: cannot open file` y termina con error.
7. En otros casos, termina con estado 0.
8. Si el termino de busqueda es vacio "", se imprimen todas las lineas.

## Compilacion (WSL)

Desde esta carpeta (`programas/wgrep`):

```bash
gcc -Wall -Wextra -Werror -std=c11 -O2 -D_POSIX_C_SOURCE=200809L wgrep.c -o wgrep
```

## Ejecucion

Ejemplo con un archivo:

```bash
./wgrep foo bar.txt
```

Ejemplo con varios archivos:

```bash
./wgrep foo a.txt b.txt
```

Ejemplo leyendo desde stdin:

```bash
printf "uno\nfoo\ndos\n" | ./wgrep foo
```

## Lista minima de pruebas

1. Caso normal con un archivo.
   - Entrada: `./wgrep foo bar.txt`
   - Esperado: imprime solo las lineas que contienen `foo`.

2. Caso normal con varios archivos.
   - Entrada: `./wgrep foo a.txt b.txt`
   - Esperado: imprime lineas coincidentes de `a.txt` y luego de `b.txt`.

3. Sin argumentos.
   - Entrada: `./wgrep`
   - Esperado: `wgrep: searchterm [file ...]` por `stderr` y exit status 1.

4. Archivo inexistente.
   - Entrada: `./wgrep foo no_existe.txt`
   - Esperado: `wgrep: cannot open file` por `stderr` y exit status 1.

5. Lectura desde stdin.
   - Entrada: `printf "x\nfoo\ny\n" | ./wgrep foo`
   - Esperado: imprime solo `foo`.

6. Case-sensitive.
   - Entrada: archivo con `foo` y `Foo`, correr `./wgrep foo archivo.txt`.
   - Esperado: imprime solo lineas con `foo` exacto.

7. Busqueda vacia.
   - Entrada: `./wgrep "" archivo.txt`
   - Esperado: imprime todas las lineas.

8. Validacion para `./wgrep a.txt`.
   - Entrada: ejecutar con un solo argumento que es archivo existente.
   - Esperado: `wgrep: searchterm [file ...]` por `stderr` y exit status 1.


## Problemas y Soluciones

1. No funciona en pipeline por olvidar `stdin`

Version mal:

```c
for (i = 2; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    search_in_stream(file, search_term);
}
```

Version bien (codigo actual):

```c
if (argc == 2) {
    search_in_stream(stdin, search_term);
    return 0;
}
```

Por que lo soluciona: cuando no hay archivos, el programa lee desde entrada estandar.

4. perder memoria con `getline`

Version mal:

```c
char *line = NULL;
while (getline(&line, &line_capacity, stream) != -1) {
    ...
}
// sin free(line)
```

Version bien (codigo actual):

```c
char *line = NULL;
while ((line_length = getline(&line, &line_capacity, stream)) != -1) {
    ...
}
free(line);
```

Por que lo soluciona: libera el buffer dinamico al terminar la busqueda.
