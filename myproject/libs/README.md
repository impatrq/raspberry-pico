# libs directory

Este directorio es para agregar cualquier `.c` necesario para el proyecto. Algunos pasos son necesarios para que pueda ser compilado apropiadamente:

1- Crear un archivo con extension `.c` (lib.c por ejemplo)

2- Agregar al `CMakeLists.txt` el archivo dentro de la directiva `add_library` como:

```cmake
${LIBS}/lib.c
```

3- Si esta biblioteca tiene dependencias con otras, agregarla dentro de la directiva `target_link_libraries`