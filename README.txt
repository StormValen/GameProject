La frequéncia de actualización del GameScene varía según el pc en el que se ejecute el juego,
por lo que las velocidades predefinidas con las que se deberían mover los objetos
cambian según el equipo. Para ello hemos establecido una serie de variables que controlan
esto (hacen que la funcion que actualiza el movimiento de los objetos se ejecute cada ciertos 
frames), para cada pc se han de configurar manualmente:

U - //Disminuir velocidad de rotacion de la nave
H - //Augmentar velocidad de rotacion de la nave
I - //Augmentar frecuancia de aparicion asteroides
J - //Disminuir frecuancia de aparicion asteroides
O - //Disminuir velocidad de movimiento de asteroides y disparos
K - //Augmentar velocidad de movimiento de asteroides y disparos
P - //Disminuir velocidad de movimiento de la nave
L - //Augmentar velocidad de movimiento de la nave

Las valor predefinido de las variables es:
0 -> 3000 -> Aparición de asteroides
1 -> 25	-> Movimiento asteroides y disparos
2 -> 50 -> Movimiento de la nave
3 -> 10 -> Rotacion de la nave