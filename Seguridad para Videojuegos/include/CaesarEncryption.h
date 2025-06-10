#pragma once
#include "Prerequisites.h"
#include <string>
#include <iostream>
#include <cctype>

/**
 * @class CaesarEncryption
 * @brief Implementación del cifrado César con funciones de cifrado, descifrado y análisis.
 */
class 
CaesarEncryption {
public:
    CaesarEncryption() = default;
    ~CaesarEncryption() = default;

    /**
   * @brief Cifra un texto utilizando el cifrado César.
   * @param texto Texto a cifrar.
   * @param desplazamiento Valor de desplazamiento en el alfabeto.
   * @return Texto cifrado.
   */
    std::string EncryptionCaesar(const std::string& texto, int desplazamiento) {
        std::string result = "";

        for (char c : texto) {
            if (c >= 'A' && c <= 'Z') {
                result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
            }
            else if (c >= 'a' && c <= 'z') {
                result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
            }
            else if (c >= '0' && c <= '9') {
                result += (char)(((c - '0' + desplazamiento) % 10) + '0');
            }
            else {
                result += c;
            }
        }
        return result;
    }


    /**
     * @brief Descifra un texto cifrado con el cifrado César.
     * @param texto Texto cifrado.
     * @param desplazamiento Valor de desplazamiento usado en el cifrado original.
     * @return Texto descifrado.
     */
    std::string DecodeCaesar(const std::string& texto, int desplazamiento) {
        return EncryptionCaesar(texto, 26 - (desplazamiento % 26));
    }

    /**
     * @brief Realiza un ataque de fuerza bruta al cifrado César probando las 26 claves posibles.
     * @param texto Texto cifrado sobre el que se aplicará la fuerza bruta.
     */
    void 
    bruteForce(const std::string& texto) {
        for (int i = 0; i < 26; i++) {
            std::string attempt = EncryptionCaesar(texto, 26 - i);
            std::cout << "Intento: " << i << ": " << attempt << std::endl;
        }
    }

    /**
    * @brief Evalúa la clave más probable basada en frecuencia de letras y cantidad de vocales.
    * @param texto Texto cifrado que se desea analizar.
    * @return Valor de desplazamiento más probable.
    */
    int 
    evaluatePossibleKey(const std::string& texto) {
        int frecuencias[26] = { 0 };

        for (char c : texto) {
            if (c >= 'a' && c <= 'z') {
                frecuencias[c - 'a']++;
            }
            else if (c >= 'A' && c <= 'Z') {
                frecuencias[c - 'A']++;
            }
        }

        const char letrasReferencia[] = { 'e', 'a', 'o', 's', 'r' };
        int indiceMax = 0;
        for (int i = 1; i < 26; ++i) {
            if (frecuencias[i] > frecuencias[indiceMax]) {
                indiceMax = i;
            }
        }

        int mejorClave = 0;
        int maxVocales = -1;

        for (char letraRef : letrasReferencia) {
            int clave = (indiceMax - (letraRef - 'a') + 26) % 26;
            std::string descifrado = EncryptionCaesar(texto, 26 - clave);

            int vocales = 0;
            for (char c : descifrado) {
                char lower = std::tolower(c);
                if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
                    vocales++;
                }
            }

            if (vocales > maxVocales) {
                maxVocales = vocales;
                mejorClave = clave;
            }
        }

        return mejorClave;
    }

private:
};
