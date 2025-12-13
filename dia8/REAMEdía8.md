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
Este ejercicio es un caso claro de teoría de grafos con estrcutura DSU/Union Find

- Los nodos son cajas electricas 
- Las aristas son conexiones posibles en las que el peso es igual a la distancia euclídea al cuadrado 
- Union Find se usa para gestionar dinámicamente las componentes conexas 


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
- Hemos repasado la teoría de grafos aplicandola a un problema en parte geométrico 
- Hemos aprendido a utilizar Union Find que simplifica el manejo y la creación de los grafos
