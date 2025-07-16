# SeguridadparaVideojuegos
Clases de la Universidad para Criptoanalisis
En este primer parcial se exploraron diversos métodos de cifrado clásico y moderno, implementados en C++ de forma modular y estructurada. Se desarrollaron sistemas de encriptación/desencriptación, conversión de datos, y técnicas de análisis criptográfico, destacando los siguientes aprendizajes:

🔐 1. Cifrado César
Se implementó el algoritmo César para cifrar mensajes desplazando letras, dígitos y símbolos. Se complementó con:

Descifrado inverso.

Ataque por fuerza bruta, evaluando todas las claves posibles.

Deducción automática de clave probable, usando frecuencias de letras y conteo de vocales, mejorando la precisión sin depender de diccionarios.

⚙️ 2. Cifrado XOR
El cifrado XOR se aplicó como método simétrico simple:

Se implementó la codificación bit a bit entre el mensaje y una clave repetida.

Se añadió la conversión de cadenas hexadecimales a bytes.

Se incluyeron técnicas de fuerza bruta de 1 y 2 bytes, así como un ataque por diccionario usando palabras como "clave", "admin", "friki", "goofyahh", entre otras.

🔒 3. Cifrado DES
Se trabajó con bloques fijos de 64 bits:

Se construyó un cifrado DES básico, con expansión, sustitución (S-Boxes), y rondas Feistel.

Se añadió padding automático para asegurar que el texto sea múltiplo de 8 bytes.

El resultado cifrado se mostró en hexadecimal, y el texto descifrado se comparó con el original.

🧠 4. Representación binaria y hexadecimal
Se codificaron funciones para convertir texto ASCII a binario y viceversa.

Se imprimieron salidas cifradas en hexadecimal legible.

Estas herramientas permitieron visualizar internamente cómo cambia un mensaje tras ser cifrado.

Seguridad para Videojuegos - Segundo Parcial 🔐🎮
En este segundo parcial, nos enfocamos en la creación de herramientas criptográficas avanzadas para asegurar datos sensibles en videojuegos y otras aplicaciones. A través de la clase CryptoGenerator, implementamos una serie de funcionalidades que permiten generar contraseñas, claves, vectores de inicialización (IVs), salts y realizar codificación y decodificación en Base64. Además, proporcionamos métodos para validar contraseñas y calcular su fortaleza en términos de entropía.

🚀 Funcionalidades Implementadas
Generación de Contraseñas Seguras: Permite crear contraseñas aleatorias con caracteres mayúsculas, minúsculas, números y símbolos, asegurando que cumplan con políticas de seguridad.

Generación de Claves y IVs: Funciones para generar claves simétricas criptográficamente seguras y vectores de inicialización (IVs) para cifrado simétrico.

Generación de Salt Criptográfico: Crea un valor aleatorio único que se combina con contraseñas para derivar claves y evitar ataques de tabla arcoíris.

Codificación y Decodificación Base64: Funciones para convertir datos binarios a Base64 y viceversa, facilitando el almacenamiento y la transmisión segura de datos.

Generación de Bytes Aleatorios: Permite la creación de buffers de bytes aleatorios para su uso en cifrado y otras operaciones criptográficas.

Limpieza Segura de Datos: Métodos para sobrescribir de manera segura datos sensibles en memoria, evitando que queden accesibles.

Validación y Estimación de Contraseñas: Funciones para validar contraseñas según políticas mínimas y estimar su entropía (fortaleza).

📥 Instrucciones para Usar el Ejecutable
1. Descarga del Proyecto
Asegúrate de tener el proyecto compilado en tu máquina. Puedes descargar el proyecto desde el repositorio o clonar el código fuente.

2. Compilación (si es necesario)
Si aún no tienes el ejecutable, asegúrate de tener un compilador C++ compatible con C++17 o superior.

Abre una terminal y navega al directorio del proyecto.

Ejecuta el comando de compilación dependiendo de tu compilador:

GCC: g++ -std=c++17 -o crypto_tool main.cpp CryptoGenerator.cpp -lstdc++

MSVC: Usa Visual Studio para compilar el proyecto, seleccionando C++17 como estándar.

3. Uso del Ejecutable
Una vez compilado el proyecto, puedes usar el ejecutable generado para realizar las tareas criptográficas. Sigue las siguientes instrucciones para interactuar con el programa:

Generación de Contraseñas:
Ejecuta el programa con los parámetros adecuados para generar una contraseña segura. El programa solicitará los parámetros de longitud de la contraseña y si se deben incluir caracteres mayúsculas, minúsculas, números o símbolos.

Generación de Claves y IVs:
Puedes generar claves y IVs para usarlas en cifrados. El programa te permitirá especificar el tamaño de la clave o IV que deseas generar.

Codificación/Decodificación Base64:
Usa el ejecutable para codificar datos binarios a Base64 o decodificar cadenas Base64 a su representación binaria.

Validación de Contraseñas:
El programa te permitirá ingresar una contraseña y determinar si cumple con los requisitos mínimos de seguridad y te mostrará su fortaleza.
5. Limpieza de Memoria
El programa también permite limpiar de forma segura cualquier dato sensible, como contraseñas o claves, utilizando el método secureWipe.
⚙️ Funciones de la Clase CryptoGenerator
1. Generación de Contraseñas:
La función generatePassword() permite generar contraseñas seguras con un tamaño y conjunto de caracteres específicos.

2. Generación de Claves y IVs:
Las funciones generateKey() y generateIV() permiten generar claves y vectores de inicialización para su uso en cifrado simétrico.

3. Codificación y Decodificación Base64:
Utiliza toBase64() para convertir bytes a Base64 y fromBase64() para decodificar cadenas Base64.

4. Limpieza de Datos Sensibles:
Usa secureWipe() para sobrescribir datos en memoria y asegurar que no se filtren.

5. Validación y Estimación de Contraseñas:
Con validatePassword() puedes validar si una contraseña cumple con los requisitos, y con estimateEntropy() se calcula la entropía de la contraseña, indicando su fortaleza.

📝 Conclusión
Este segundo parcial nos permitió profundizar en la generación de datos seguros para aplicaciones criptográficas, tales como la creación de contraseñas, claves y vectores de inicialización, así como la codificación y decodificación en Base64. Estas herramientas son fundamentales para asegurar la integridad y confidencialidad de los datos en juegos y aplicaciones sensibles.

Si tienes alguna duda o sugerencia, no dudes en contactarme. ¡Que disfrutes asegurando tus aplicaciones! 💻🔐
