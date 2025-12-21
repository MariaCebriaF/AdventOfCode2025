# Advent of Code - Día 8
### Conectando cajas "electricas" en 3D usando grafos y UF (Union Find)
## Resumen del problema
El reto consiste en conectar una serie de cajas de conexiones (nodos) situadas en un espacio 3D. Cada línea del input contiene coordenadas X,Y,Z. Queremos conectar las parejas más cercanas para asegurar que la electricidad pueda fluir entre ellas usando la menor cantidad posible de cable.

Para poder conseguirlo hemos seguido estos pasos: 
1. Calcular todas las distancias entre pares de cajas
2. Ordenarlas por distancia ascendente
3. Unir las 1000 parejas más cortas
4. Hallar los componentes conectados resultantes
5. Calcular el producto de los tamaños de los 3 componentes más grandes

## Justificación de la elección del problema
Este ejercicio es un caso claro de teoría de grafos, apoyado en la estructura Union-Find (DSU) y precedido por una estrategia de divide y vencerás a nivel conceptual.

El problema se aborda dividiéndolo en varias fases bien diferenciadas:
- Descomposición del problema (divide): El conjunto global de cajas se divide en subproblemas locales, considerando inicialmente todas las posibles conexiones entre pares de cajas mediante el cálculo de distancias.

- Resolución de subproblemas:
Cada posible conexión se analiza de forma independiente, evaluando su coste (distancia) y su impacto en la conectividad del sistema.

- Combinación estructurada (vencerás):
Las soluciones parciales se integran progresivamente utilizando Union-Find, que permite unir componentes conexas y construir la estructura global sin redundancias.

>Aunque no se trata de un algoritmo de divide y vencerás clásico basado en recursión y combinación directa de resultados, el planteamiento comparte la idea fundamental de descomponer un problema complejo en partes manejables antes de construir la solución final.

## Diseño y técnica utilizada
#### Representación del grafo
Nodo -> Índice de cada punto del vector
Arista -> Distancia^2 + indices de nodos

#### Cálculo de las distancias (usando Euclídes)
```
dist^2=(x1​−x2​)^2+(y1​−y2​)^2+(z1​−z2​)^2
```

#### Unir los nodos
Con Union Find averiguamos si dos nodos ya estaban conectados con `find(x)` o los unimos con `union (x, y)`

#### Cálculo del resultado 
1. Obtenemos los tamaños de los nodos unidos
2. Seleccionamos los 3 más grandes
3. Multiplicamos el tamaño de los tres 

## Conclusión
El Día 8 combina de forma coherente:
- Divide y vencerás, como estrategia de descomposición conceptual del problema.
- Grafos, para modelar las relaciones entre cajas.
- Union-Find, para combinar eficientemente las soluciones parciales.

Esta combinación permite resolver el problema de forma clara, eficiente y escalable, evitando enfoques de fuerza bruta y reforzando la comprensión de técnicas algorítmicas complementarias.



## Alternativas consideradas
Durante el planteamiento y resolución del problema se consideraron distintas alternativas, que finalmente fueron descartadas por motivos de eficiencia, claridad o adecuación al modelo del problema.

#### Uso de fuerza bruta sin estructura de datos

Una primera alternativa consistía en conectar las cajas sin ningún tipo de estructura adicional, recalculando manualmente las conexiones y comprobando la conectividad tras cada unión.

Esta opción se descartó porque:
- Requería comprobaciones repetidas de conectividad.
- Introducía un coste computacional elevado.
- No escalaba correctamente con el número de cajas.

#### Uso de recorridos de grafos (DFS/BFS) tras cada conexión
Otra alternativa era realizar un recorrido DFS o BFS cada vez que se añadía una conexión para determinar las componentes conexas resultantes.

Aunque conceptualmente correcta, esta solución se descartó porque:

- Repetir recorridos completos del grafo tras cada unión es innecesario.
- El coste acumulado resulta muy superior al uso de Union-Find.
- La lógica del código se vuelve más compleja y menos clara.

#### Construccion de un árbol 
También se valoró la posibilidad de construir un árbol generador mínimo completo mediante algoritmos clásicos como Kruskal o Prim.

Esta alternativa se descartó porque:
- El problema no requiere conectar todas las cajas en una única componente.
- Solo interesa analizar la estructura resultante tras un número limitado de conexiones.
- Construir el MST completo supondría trabajo adicional sin aportar beneficios directos al objetivo final.

#### Uso exclusivo de estructuras geométricas
Se consideró aprovechar estructuras geométricas avanzadas (como particiones espaciales) para reducir el número de distancias calculadas.

Sin embargo, esta opción se descartó porque:
- Aumentaba significativamente la complejidad del código.
- No era necesaria para el tamaño del input del problema.
- Desviaba el foco del ejercicio hacia geometría computacional avanzada en lugar de grafos y estructuras de datos.

### Conclusión sobre las alternativas
Las alternativas analizadas permiten comprobar que la solución elegida:
- Es más eficiente que los enfoques por fuerza bruta.
- Mantiene un equilibrio adecuado entre claridad y rendimiento.
- Aplica de forma justificada Union-Find como estructura central.
El análisis de alternativas refuerza la elección final y demuestra una toma de decisiones algorítmica consciente y razonada.
