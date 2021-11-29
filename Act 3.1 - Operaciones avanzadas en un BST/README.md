# Analisis de Complejidad

#visit

1. Preorder 

2. Inorder

3. Postorder

Estas primeras tres pasan por cada uno de los nodos, por lo que es O(n)

4. Level by level

Puede recuperar todos los valores en tiempo O(n).

Posteriormente se usa un ciclo de complejidad O(h) donde n>h lo que se podría tomar como otro O(n).

Es decir, la catalogamos como 2(n)

La complejidad de visit queda como O(5n) o O(kn)

#height

Obtiene la altura del BST

Necesita explorar todo por lo que es O(n)


#ancestors

Obtiene los ancestros de un dato


Ancestors tiene una validación con el find, de complejidad O(logn) luego el peor de los casos de ancestors tambien es log(n)

Por lo tanto es 2(log n).

#whatlevelamI

Obtiene un entero que indica el nivel en que se encuentra un dato, o -1 en caso de que no se encuentre en el BST

Analogo que el caso anterior es O(2 log n) o O(2n) si está como linked list.
