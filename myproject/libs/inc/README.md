# inc directory

Este es un directorio para almacenar cualquier `.h` que sea necesario. Solo es necesario crear el archivo y es incluido en la compilacion.

Para incluir un header desde el `main.c` se puede hacer con:

```c
#include "lib.h"
```

Reemplazando `lib` por el nombre correspondiente del header.

Abajo se propone un template para un header:

```c
#ifndef _LIB_H_
#define _LIB_H_

/* Otros include */

/* Macros y definiciones */

/* Typedefs y definiciones de estructuras */

/* Prototipos de funciones */

#endif /* _LIB_H_ */
```