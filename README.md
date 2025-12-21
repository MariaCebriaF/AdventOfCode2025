# Advent of Code 2025 · PRA · GIIROB
### Equipo: ```cout<< "HO HO HO";``` 

``` 
Adriana Baghdasaryan Hovnatanyan
Javier Baena Martín
María Fátima Cebriá Fernández
```
---
## Días a entregar
- [Día 5: Árbol](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia5/dia5arbol.cpp) -> [Explicación del día 5](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia5/READMEdía5.md#diseño-y-técnica-utilizada)
- [Día 7 : Hash Table](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia7/dia7hashtable.cpp) -> [Explicación del día 7](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia7/README7.md)
- [Día 8 : Grafos (+ Divide y Vencerás)](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia8/dia8a.cpp) -> [Explicación del día 8](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia8/REAMEdía8.md)
- [Día 11 : Programacion Dinamica](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia11/dia11programaciondinamica.cpp) -> [Explicación del día 11](https://github.com/MariaCebriaF/AdventOfCode2025/blob/master/dia11/READMEdia11.md)


## Criterios de elección de los problemas
Los problemas seleccionados cumplen al menos uno de los siguientes objetivos formativos:

- Son problemas donde la estructura de datos es necesaria para alcanzar una solución eficiente.
- Obligan a adaptar o combinar técnicas vistas en clase con el planteamiento del problema.
- Permiten analizar alternativas y justificar por qué una solución es preferible frente a otras.De este modo, cada día actúa como un ejemplo representativo de una técnica distinta.

### Relación problema – estructura de datos
#### Día 5 – Árboles
El problema presenta una jerarquía natural que se modela directamente como un árbol. El uso de esta estructura permite recorrer y procesar la información de forma estructurada, evitando soluciones lineales poco expresivas.

#### Día 7 – Hash Tables
El estado del sistema es disperso y dinámico. El uso de una hash table permite almacenar únicamente los elementos activos en cada iteración, evitando recorrer estructuras completas innecesarias.
Además, se implementa una hash table propia para demostrar comprensión del funcionamiento interno (hash, colisiones, rehash), más allá del uso de la STL.
#### Día 8 – Grafos (+ Divide y Vencerás)
Aunque el problema se descompone en subestructuras más pequeñas, la técnica principal utilizada no es divide y vencerás en sentido estricto, sino el modelado mediante grafos y el análisis de sus componentes. La descomposición sirve para facilitar el procesamiento del grafo, pero no existe una fase explícita de combinación de soluciones parciales.

El problema se modela de forma natural como un grafo, donde nodos y aristas representan relaciones entre elementos. El uso de estructuras de grafos permite aplicar recorridos y técnicas estándar que no serían posibles con estructuras lineales simples. 

#### Día 11 – Programación Dinámica
El problema presenta subproblemas solapados. El uso de memoización evita recomputaciones innecesarias y reduce el coste computacional de forma significativa, convirtiendo una solución potencialmente exponencial en una solución eficiente.


### Justificación técnica (rúbrica · memoria)
En todos los casos:
> Se justifica por qué la estructura elegida es adecuada para el problema.
Se explica cómo se aplica dentro del algoritmo.
Se analizan las mejoras de eficiencia obtenidas frente a enfoques más simples.
Se detallan las limitaciones de cada enfoque cuando existen.
Cada carpeta contiene un README específico donde se desarrolla la explicación técnica completa del día correspondiente.

### Alternativas consideradas (generales)
Durante la resolución de los problemas se han considerado alternativas como:
- Uso de vectores o matrices completas en lugar de hash tables.
- Resoluciones por fuerza bruta antes de aplicar optimizaciones.
- Implementaciones directas frente a versiones optimizadas con memoización.

Estas alternativas se han descartado cuando:
No escalaban correctamente con el tamaño del input.
Introducían complejidad innecesaria.
No reflejaban correctamente el modelo conceptual del problema.

### Inconvenientes durante la resolución
Este año el Advent of Code ha sido más corto, por lo tanto esto ha supuesto limitaciones a la hora de encontrar problemas especificos en los que utilizar estructuras de datos o metodologias de resolución especificas. Sabemos que el objetivo de la tarea era resolver un minimo de 5 problemas con estas estructuras/metodologías: 
- Hash tables (conseguido)
- Arboles (conseguido)
- Grafos (conseguido)
- Programación dinámica (conseguido)
- Divide y Vencerás (justificado)

Aun así en este repositorio encontrarás todo el advent of code resuelto con C++ excepto el día 10, cuya solución fue sacada mediante un excel puesto que con C++ era prácticamente imposible sin librerias externas que no hemos aprendido a utilizar. 

### Aprendizajes
Durante la resolución día tras día del advent hemos conseguido mejorar nuestras habilidades de programación, orientas tanto a la eficiencia como a la competición, puesto que de una historia y algun ejemplo del input y output hemos logrado identificar estructuras básicas a la hora de resolver cientos de problemas. 

Por otro lado estamos muy contentos pues nos ha supuesto un reto muy entretenido y del que hemos sacado una experiencia muy educativa. 

Además hemos llegado a "discutir" sobre las diferentes formas de resolver un mismo problema y tras probarlas decidir cuál era la optima debido a los costes temporales, lo que nos ha permitido ser más conscientes de la importacia de optimizar el código.
