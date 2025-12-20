# Advent of Code — Día 17
### Laboratorios · Hash Table 

## Resumen del problema
El diagrama del laboratorio se representa como una cuadrícula por la que desciende un haz de taquiones desde la celda S.

El haz se desplaza siempre hacia abajo y puede dividirse al encontrar un splitter (^), generando dos nuevos haces hacia abajo a la izquierda y a la derecha.

Cuando varios haces alcanzan la misma celda, se consideran un único haz.
El objetivo de la Parte 1 es contar cuántas divisiones (^) se producen durante todo el recorrido.

## Justificación de la técnica elegida
- Este problema es un caso típico de:
- Simulación discreta paso a paso
- Manejo de estados activos en estructuras dispersas
- Uso de hash tables para representar conjuntos dinámicos

La idea clave es que, en cada fila del mapa, solo unas pocas columnas contienen haces activos.

Recorrer todas las columnas en cada fila sería innecesario e ineficiente.
Por eso, se utiliza una hash table para almacenar únicamente las columnas activas, permitiendo:
- Inserciones rápidas
- Eliminación automática de duplicados
- Fusión natural de haces que llegan a la misma celda

## Diseño y técnica utilizada

1. Representación del estado

El estado del sistema en cada iteración se representa como un conjunto de columnas activas:

Cada entero representa una columna por la que desciende al menos un haz.
No se distingue entre varios haces en la misma columna, ya que se fusionan.
En lugar de usar unordered_set, se implementa una hash table propia llamada ConjuntoHash.

2. Implementación de la Hash Table

La estructura ConjuntoHash está diseñada específicamente para almacenar enteros (int) y presenta las siguientes características:


- Capacidad siempre potencia de 2
- Control explícito del factor de carga
- Rehash automático cuando la ocupación supera aproximadamente el 70 %

Internamente utiliza:
- Un vector claves para almacenar los valores
- Un vector estado para marcar posiciones ocupadas o libres

Esto permite controlar completamente el comportamiento de la estructura sin depender librerias. 

3. Lectura del input

El input se lee como un vector de strings que representa el mapa del laboratorio.

Después:

        1. Se buscan las coordenadas de la celda inicial S
        2. Se inicializa el conjunto actual con la columna de inicio

4. Simulación fila a fila

La simulación avanza desde la fila de S hasta el final del mapa.

**En cada fila:** Se recorre la hash table actual

**Para cada columna activa:** Si la celda es ^, se incrementa el contador de divisiones y se activan las columnas c-1 y c+1 en la fila siguiente
En caso contrario, el haz continúa recto hacia abajo
Las columnas resultantes se insertan en siguiente
Se intercambian actual y siguiente
El proceso termina cuando no quedan columnas activas.

5. Conteo de divisiones

Cada vez que un haz alcanza un splitter (^), se incrementa el contador de divisiones.

**Gracias a la hash table:**
Un splitter se cuenta una sola vez por columna activa
Los haces fusionados no generan conteos duplicados


## Complejidad
- F el número de filas del mapa
- K el número medio de columnas activas por fila

Por tanto la complejidad seria O(F * K)


## Algunos aspectos a comentar
- Fusión de haces: Si varios haces llegan a la misma celda, se representan como una única entrada en la hash table, sin lógica adicional.
- Hash table propia: La implementación evita depender de unordered_set y permite entender y controlar: colisiones, rehash y distribución de claves
- Overflow: El contador de divisiones se almacena en long long, suficiente para la Parte 1 del problema.

## Conclusión
Este ejercicio es un buen ejemplo de uso justificado de hash tables en simulaciones:
- El estado del sistema es disperso
- La hash table modela el problema de forma natural
- La implementación propia refuerza la comprensión real de la estructura de datos
- La solución es clara, eficiente y fácilmente reutilizable en otros problemas del Advent of Code.

