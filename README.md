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
