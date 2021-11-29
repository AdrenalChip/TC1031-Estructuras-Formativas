# Analisis de Complejidad
#Hash

#put

full: Tiempo constante O(1) pues solo compara count con size

indexOf:Complejidad O(n) ejecuta el salto cuadrática n veces. Sabemos que a diferencia de lo implementación lineal de colisiones d
este método no garantiza recorrer todo el hash completo.

Además la función por si misma tiene un ciclo de complejidad O(n) que busca encontrar un espacio vacío en la tabla

La complejidad de la función put es de O(2n)

#get

get usa indexOf desde una interfaz llamada constains luego usa indexOf

Por lo tanto tiene una complediad de O(2n) 
