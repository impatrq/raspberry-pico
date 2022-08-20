# MyProject

## Contenido

Este directorio contiene lo minimo e indispensable para poder generar un nuevo proyecto con la Raspberry Pico. En el se encuentran:

- `main.c`: programa principal con una inicializacion del stdio y el bucle infinito.
- `CMakeLists.txt`: descripcion y directivas de los archivos fuente (.c) y bibliotecas del proyecto.
- `libs`: es un directorio para contener bibliotecas adicionales. Dentro, tiene un directorio `inc` para almacenar los headers necesarios para estas bibliotecas.

## Como modificar

Luego de clonar el repositorio, puede usarse este directorio para crear cualquier nuevo proyecto. Es necesario, pero no indispensable:

- Cambiar le nombre del directorio.
- Si se hizo el cambio de nombre, se debe cambiar el nombre en la linea 8 de `CMakeLists.txt`.
- Si se agregaron bibliotecas adicionales al `main.c` del SDK de la Raspberry Pico, deben agregarse dentro de `target_link_libraries`.
- Si se agregaron bibliotecas dentro del directorio `libs`, se deben seguir las instrucciones en ese directorio para poder agregarlas y linkearlas al resto de los archivos.

## Como compilar y flashear

En Windows, una vez que el proyecto este listo para compilar, se abre una terminal en el raiz del proyecto y se escribe:

```bash
mkdir build
cd build
cmake -G "MinGW MakeFiles" ..
make
```

Si el sistema operativo es Linux, se corren los comandos:

```bash
mkdir build
cd build
cmake ..
make -j4
```

Si los comandos no arrojaron ningun error, entonces puede procederse a conectar la Raspberry Pico por USB a la PC presionando el BOOTSEL para que entre en modo bootloader. Luego, aparecera en la PC como un dispositivo de almacenamiento masivo. Se debe buscar entonces dentro de build el archivo `project_name.uf2` (donde project_name coincidira con el nombre del proyecto que se haya escogido) y copiarse dentro de la unidad que haya sido asignada a la Raspberry. 

Como alternativa, se puede correr en la terminal:

```bash
cp project_name.uf2 e:
```

Suponiendo que la unidad asignada a la Raspberry Pico fuese la E.

### Volver a compilar

Si se han hecho cambios dentro del `main.c`, solo es necesario volver a correr en la consola `make`. En cambio, si se hicieron cambios dentro del `CMakeLists.txt`, deben correrse ambos comandos.
