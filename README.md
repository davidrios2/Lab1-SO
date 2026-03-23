# Laboratorio 1 - Sistemas Operativos

## Estudiante
David Rios Vélez
1036963759
david.rios2@udea.edu.co


Este repositorio contiene la implementacion de cuatro programas en C inspirados en utilidades clasicas de Unix: `wcat`, `wgrep`, `wzip` y `wunzip`. Cada uno de ellos contiene la explicion de la impelmentación en un `readme.md`.

## Estructura de carpetas

```text
S0-Lab1-20261/
├── 01-LengC.pdf
├── Laboratorio 1.mp4
├── README.md
└── programas/
	 ├── wcat/
	 │   ├── readme.md
	 │   ├── test1.txt
	 │   ├── test2.txt
	 │   ├── test3.txt
	 │   ├── wcat
	 │   └── wcat.c
	 ├── wgrep/
	 │   ├── a.txt
	 │   ├── b.txt
	 │   ├── bar.txt
	 │   ├── readme.md
	 │   ├── wgrep
	 │   └── wgrep.c
	 ├── wzip/
	 │   ├── a.txt
	 │   ├── b.txt
	 │   ├── readme.md
	 │   ├── t1.txt
	 │   ├── t1.z
	 │   ├── wzip
	 │   └── wzip.c
	 └── wunzip/
		  ├── bad.z
		  ├── original.txt
		  ├── original.z
		  ├── readme.md
		  ├── recovered.txt
		  ├── t1.txt
		  ├── t1.z
		  ├── t2.txt
		  ├── t2.z
		  ├── wunzip
		  └── wunzip.c
```

## Manifiesto de transparencia

Durante el laboratorio se uso IA como apoyo tecnico y de redaccion en los siguientes puntos:

1. Preguntar por librerias
	- Se consulto que headers y funciones estandar eran adecuados para cada programa en C (por ejemplo, manejo de archivos, lectura de lineas y operaciones de cadenas).

2. Clarificar decisiones de diseno
	- Se uso IA para validar decisiones como manejo de errores, codigos de salida, lectura secuencial de multiples archivos y formato de entrada/salida esperado por cada utilidad.

3. Crear plan de pruebas en los readme de cada programa
	- Se elaboraron listas de pruebas minimas por programa en los `readme.md` respectivos para cubrir casos normales, casos borde y manejo de errores.

4. Expandir los `readme.md`, dándoles estrucctura.

5. Pulir implementaciones
	- Se utilizo IA para revisar claridad del codigo, consistencia de mensajes de error y pequenos ajustes de robustez sin alejarse de una implementacion simple de nivel principiante.

6. Parafrasear comentarios explicativos
	- Se reformularon comentarios para que fueran mas claros y directos, manteniendo el sentido tecnico y el estilo del proyecto.

### Enlace al Video
https://drive.google.com/file/d/1ohk-RzpFtjt7e-BPQd6fdJ8w9BxE46nz/view?usp=sharing
