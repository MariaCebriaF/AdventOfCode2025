# Advent of Code - Día 5
### El inventario de los elfos en un Árbol Binario
## Resumen del problema
Los Elfos tienen una base de datos con rangos numéricos que indican ingredientes frescos y una lista de IDs de ingredientes disponibles.
Un ID es fresco si pertenece a cualquier rango.

- El objetivo es contar cuántos IDs son frescos en el input completo.

## Justificación de la elección del problema
Este ejercicio es un caso perfécto para aplicar la estructura del arbol ya que:

- Los rangos pueden solaparse 
- Necesitamos hacer muchas consultas sobre los IDs
- Se podría resolver con fuerza bruta, pero no sería una solución eficiente debido al tamaño del input

## Diseño y técnica utilizada
### Pasos a seguir para resolverlo 
1. Ordenamos y fusionamos los intervalos
2. Construimos el árbol con los intervalos: cada nodo contiene un inicio, un fin y un puntero a los hijos
3. Consulta cada ID y si aparece dentro de un intervalo lo consideramos fresco 

#### Posibles artenativas 
Podríamos aplicar fuerza bruta comparando cada ID con cada rango, pero esto aumentaría la complejidad del problema. 

En cambio optamos por un árbol para aportar una estructura clara del código, además de la eficiencia.

## Conclusión
- Hemos practicado el manejo de intervalos
- Hemos aprendido a aplicar un Árbol Binario de Búsqueda para facilitar las consultas
- Hemos mejorado la claridad y eficiencia del código
