
# Advent of Code — Día 11
### Conteo de caminos en un grafo dirigido usando DFS + Programación Dinámica

## Resumen del problema
El input describe un grafo dirigido mediante una lista de adyacencia textual.
Cada línea contiene un nodo origen seguido de los nodos destino a los que se puede llegar desde él.

El objetivo es calcular cuántos caminos distintos existen desde el nodo "you" hasta el nodo "out" siguiendo las direcciones del grafo. El enfoque asume que el grafo es acíclico o sea que no existen ciclos que permitan caminos infinitos.

## Justificación de la técnica elegida
Este problema es un caso típico de:
- Teoría de grafos dirigidos
- Conteo de caminos
- Programación dinámica sobre grafos

La idea clave es que el número de caminos desde un nodo se puede expresar como la suma de los caminos desde todos sus nodos vecinos.
Por eso la memoización evita recalcular subproblemas repetidos, reduciendo mucho el coste computacional.

## Diseño y técnica utilizada
1. Representación del grafo
Los nodos del input vienen identificados por strings. Para trabajar de forma eficiente:
Se asigna a cada nodo un ID entero usando `unordered_map<string, int>`
El grafo se almacena como una lista de adyacencia:
`vector<vector<int>> ady;`

    Donde: Cada índice representa un nodo ady[u] tiene los nodos alcanzables desde u

2. Convertimos los nodos (string → int)
Se utiliza una lambda ID(nombre) que:
Devuelve el ID si el nodo ya existe
Crea un nuevo ID y una lista de adyacencia vacía si no existe
Esto permite convertir el grafo de una string a un grafo numérico.

3. Lectura del input y construcción del grafo
Cada línea del input se procesa con stringstream:
El primer "token" es el origen (se elimina : si existe)
El resto de "tokens" son destinos
Se añade una arista dirigida origen → destino

4. Conteo de caminos ***DFS + memoización***
La función principal es:
```long long caminos(int u, int objetivo,
                  const vector<vector<int>> &ady,
                  vector<long long> &memo)
```
Casos base
Si u == objetivo → existe exactamente 1 camino
Si memo[u] != -1 → el valor ya fue calculado y se reutiliza
Recurrencia
El número de caminos desde u es la suma de los caminos desde todos sus vecinos.

5. Nodo origen y destino
El programa fija: 
- Origen: "you"
- Destino: "out"

Y calcula:
`long long resultado = caminos(origen, objetivo, ady, memo)`

El resultado se imprime con `cout<< resultado`.

## Complejidad
Gracias a la memoización:
- Cada nodo se calcula una sola vez
- Cada arista se recorre una vez

Por lo tanto la complejidad temporal es: O(N+M)

Donde:
- N es el número de nodos
- M es el número de aristas

## Algunos aspectos a comentar
- Ciclos: el código no detecta ciclos. Si el grafo contiene ciclos alcanzables desde "you", el número de caminos podría ser infinito. Por suerte en nuestro input no hay ciclos infinitos
- Overflow: se usa long long, pero en grafos muy grandes el número de caminos podría ser necesaria alguna variable del tipo int128 porque es posible pasarse.

## Conclusión
Este ejercicio es un buen ejemplo de programación dinámica aplicada a grafos dirigidos:
El problema se puede descomponer en subproblemas simples

La memorización evita recomputaciones innecesaria lo que hace mucho más optima la solución

