# Práctica 2 Extra – Control de parpadeo con Timer e Interrupciones

## Descripción

Esta práctica utiliza un **ESP32** para controlar el parpadeo de un LED mediante un **timer hardware** y dos botones.

El programa hace que el LED conectado al **GPIO 2** parpadee a una frecuencia configurable.  
La frecuencia se puede aumentar o disminuir usando dos pulsadores:

- **GPIO 18**: aumenta la frecuencia de parpadeo.
- **GPIO 19**: disminuye la frecuencia de parpadeo.

## Funcionamiento

El programa usa una interrupción por temporizador que se ejecuta cada **1 ms**.

Dentro de esa interrupción se realizan dos tareas principales:

1. **Controlar el LED**
   - El LED cambia de estado periódicamente.
   - La velocidad de parpadeo depende de la variable `blinkFrequency`.
   - La frecuencia inicial es de **2 Hz**.

2. **Leer los botones**
   - El botón de subida aumenta la frecuencia.
   - El botón de bajada disminuye la frecuencia.
   - Se aplica un pequeño sistema de antirrebote mediante contadores.
   - La frecuencia queda limitada entre **1 Hz y 10 Hz**.

## Pines utilizados

| Elemento | Pin ESP32 |
|---|---:|
| LED | GPIO 2 |
| Botón subir frecuencia | GPIO 18 |
| Botón bajar frecuencia | GPIO 19 |

## Configuración PlatformIO

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

Resumen del programa

El ESP32 configura un timer con prescaler 80, de forma que cada tick equivale a 1 microsegundo.

Después, se programa una alarma cada 1000 microsegundos, es decir, cada 1 ms

Cada vez que salta la interrupción, se actualiza el contador del LED y se comprueba el estado de los botones.

El loop() está vacío porque todo el funcionamiento del programa se realiza desde la interrupción del timer.

# Conclusión

Esta práctica demuestra cómo usar un temporizador hardware del ESP32 para controlar tareas periódicas sin usar delay().

El programa permite modificar en tiempo real la frecuencia de parpadeo de un LED usando dos botones, manteniendo el procesador libre en el loop().
