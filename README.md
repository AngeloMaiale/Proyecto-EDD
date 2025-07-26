Este proyecto se desarrolló en varias fases, siguiendo un enfoque progresivo y modular. Primero, se definió la estructura básica de Mago, 
que incluye todos los atributos relevantes para representar a un mago: nombre, edad, género, tipo de hechizo, estado (vivo o muerto), 
propietario del hechizo e ID del padre para construir la genealogía.

A continuación, se creó la clase MagicTree, que implementa el árbol binario con relaciones de herencia. Se añadieron funciones clave como 
insertMago, findByID, deleteMago, updateMago, displayTree y autoAssignOwner, cada una diseñada para desempeñar una función específica en la 
lógica del sistema mágico.

Una vez listas las estructuras principales, se diseñó el archivo main.cpp con un menú interactivo. Cada opción del menú corresponde a una f
unción del árbol y permite al usuario ver, editar o ampliar la estructura genealógica. El sistema también lee datos de un archivo CSV, 
construye el árbol al inicio y permite guardar los cambios antes de salir.

En general, el código busca ser claro, portátil y funcional, con una separación entre lógica, interfaz y almacenamiento. El resultado es un 
sistema de magia controlado por consola, donde cada mago puede ser consultado, modificado o eliminado según reglas bien definidas. Todo el flujo 
de trabajo se ha probado exhaustivamente para garantizar su estabilidad y flexibilidad, especialmente en secuencias automáticas y validación de entrada.
