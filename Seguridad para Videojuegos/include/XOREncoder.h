#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

class XOREncoder {
public:
    /**
     * @brief Constructor por defecto.
     */
    XOREncoder() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~XOREncoder() = default;

    /**
     * @brief Cifra o descifra un texto usando el algoritmo XOR con la clave proporcionada.
     * @param input Texto a cifrar o descifrar.
     * @param key Clave que se usará para el cifrado/descifrado.
     * @return Cadena de texto cifrada o descifrada.
     */
    std::string encode(const std::string& input, const std::string& key);

    /**
     * @brief Convierte una cadena hexadecimal en un vector de bytes.
     * @param input Cadena en formato hexadecimal.
     * @return Vector de bytes.
     */
    std::vector<unsigned char> HexToBytes(const std::string& input);

    /**
     * @brief Imprime una cadena de texto en formato hexadecimal.
     * @param input Texto a imprimir en formato hexadecimal.
     */
    void printHex(const std::string& input);

    /**
     * @brief Verifica si una cadena contiene solo caracteres imprimibles o espacios.
     * @param data Cadena de texto a verificar.
     * @return true si la cadena solo contiene caracteres imprimibles o espacios, false en caso contrario.
     */
    bool isValidText(const std::string& data);

    /**
     * @brief Realiza un ataque de fuerza bruta probando todas las posibles claves de 1 byte.
     * @param cifrado Vector de bytes cifrados.
     */
    void bruteForce_1Byte(const std::vector<unsigned char>& cifrado);

    /**
     * @brief Realiza un ataque de fuerza bruta probando todas las posibles claves de 2 bytes.
     * @param cifrado Vector de bytes cifrados.
     */
    void bruteForce_2Byte(const std::vector<unsigned char>& cifrado);

    /**
     * @brief Realiza un ataque de fuerza bruta usando un diccionario de claves comunes.
     * @param cifrado Vector de bytes cifrados.
     */
    void bruteForceByDictionary(const std::vector<unsigned char>& cifrado);
};
