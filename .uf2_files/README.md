# .uf2 files

## Contenido

Este directorio contiene dos archivos `.uf2` para la Raspberry Pico: 

- `flash_nuke.uf2`: sirve para poder limpiar la flash de la Raspberry Pico.
- `rp2-pico-20220117-v1.18.uf2`: firmware de MicroPython para la Raspberry Pico (v1.18).

Para poder usarlos, se conecta la Raspberry Pico a la PC manteniendo presionado el BOOTSEL. Esto va a hacer entrar a la Pico en modo bootloader y va a aparecer en la PC como un dispositivo de almacenamiento masivo. Para flashearla con uno de estos archivos, simplemente se copia el que se desee y se pega en la unidad que se asigno a la Pico.