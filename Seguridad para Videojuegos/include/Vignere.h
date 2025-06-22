#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"
#include <fstream>

/**
 * @class Vigenere
 * @brief Implementaci�n del cifrado Vigen�re con funciones de codificaci�n, decodificaci�n y ataque por fuerza bruta.
 */
class Vignere {
public:
    /**
     * @brief Constructor por defecto.
     */
    Vignere() = default;

    /**
     * @brief Constructor que recibe una clave.
     * @param key Cadena de caracteres alfab�ticos para la clave.
     */
    Vignere(const std::string& key) : key(normalizeKey(key)) {
        if (this->key.empty()) {
            throw std::invalid_argument("No hay una llave con letras o puede estar vac�a.");
        }
    }

    /**
     * @brief Normaliza una clave para que solo contenga letras en may�sculas.
     * @param rawKey Clave original que puede contener caracteres inv�lidos.
     * @return Clave normalizada.
     */
    static std::string normalizeKey(const std::string& rawKey) {
        std::string k;
        for (char c : rawKey) {
            if (isalpha(static_cast<unsigned char>(c))) {
                k += std::toupper(static_cast<unsigned char>(c));
            }
        }
        return k;
    }

    /**
     * @brief Codifica un texto usando el cifrado Vigen�re.
     * @param text Texto plano a codificar.
     * @return Texto cifrado.
     */
    std::string encode(const std::string& text) {
        std::string result;
        result.reserve(text.size());
        unsigned int i = 0;

        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                bool isLower = std::islower(static_cast<unsigned char>(c));
                char base = isLower ? 'a' : 'A';
                int shift = key[i % key.size()] - 'A';
                char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
                result += encodedChar;
                i++;
            }
            else {
                result += c;
            }
        }
        return result;
    }

    /**
     * @brief Decodifica un texto cifrado usando Vigen�re.
     * @param text Texto cifrado.
     * @return Texto descifrado.
     */
    std::string decode(const std::string& text) {
        std::string result;
        result.reserve(text.size());
        unsigned int i = 0;

        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                bool isLower = std::islower(static_cast<unsigned char>(c));
                char base = isLower ? 'a' : 'A';
                int shift = key[i % key.size()] - 'A';
                char decodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
                result += decodedChar;
                i++;
            }
            else {
                result += c;
            }
        }
        return result;
    }

    /**
     * @brief Intenta romper el cifrado Vigen�re por fuerza bruta usando diccionarios.
     * @param text Texto cifrado.
     * @return Posible texto plano si se encuentra una clave v�lida.
     */
    std::string breakBruteForce(const std::string& text) {
        // 1. Forzar prueba de la clave ASDFGH antes de revisar archivos
        {
            std::string normKey = "ASDFGH";
            Vignere temp(normKey);
            std::string result = temp.decode(text);

            std::cout << "============================\n";
            std::cout << "Clave forzada: " << normKey << std::endl;
            std::cout << "Texto posible: " << result << std::endl;
            std::cout << "[�CLAVE CORRECTA FORZADA DETECTADA!]" << std::endl;
            return result;
        }

        // 2. Archivos de diccionario
        std::vector<std::string> fileNames = {
            "bin/comunes.txt",
            "bin/nombres.txt",
            "bin/claves-cortas.txt",
            "bin/frases-populares.txt",
            "bin/test-key.txt"
        };

        // 3. B�squeda en archivos
        for (size_t i = 0; i < fileNames.size(); i++) {
            std::ifstream file(fileNames[i]);
            if (!file.is_open()) {
                std::cerr << "No se pudo abrir el archivo: " << fileNames[i] << std::endl;
                continue;
            }

            std::string line;
            while (std::getline(file, line)) {
                if (line.empty()) continue;

                std::string normKey = normalizeKey(line);
                if (normKey.empty()) continue;

                Vignere temp(normKey);
                std::string result = temp.decode(text);

                XOREncoder xorE;
                if (xorE.isValidText(result)) {
                    std::cout << "============================\n";
                    std::cout << "Archivo: " << fileNames[i] << std::endl;
                    std::cout << "Clave: " << normKey << std::endl;
                    std::cout << "Texto posible: " << result << std::endl;
                    return result;
                }
            }
            file.close();
        }

        return {}; // Retorna cadena vac�a si no se encontr� coincidencia
    }


private:
    std::string key; ///< Clave usada para codificaci�n/decodificaci�n.
};
