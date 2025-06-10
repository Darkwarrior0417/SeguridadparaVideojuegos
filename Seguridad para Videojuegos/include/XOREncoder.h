#pragma once
#include "Prerequisites.h"

/**
 * @class XOREncoder
 * @brief Implementa cifrado XOR, impresión hexadecimal y ataques de fuerza bruta.
 */
class 
XOREncoder {
public:
    XOREncoder() = default;
    ~XOREncoder() = default;

    /**
     * @brief Cifra un texto usando XOR con una clave.
     * @param input Texto de entrada.
     * @param key Clave para el cifrado.
     * @return Texto cifrado.
     */
    std::string encode(const std::string& input, const std::string& key) {
        std::string output = input;
        for (int i = 0; i < input.size(); i++) {
            output[i] = input[i] ^ key[i % key.size()];
        }
        return output;
    }

    /**
     * @brief Convierte una cadena hexadecimal a un vector de bytes.
     * @param input Cadena hexadecimal.
     * @return Vector de bytes.
     */
    std::vector<unsigned char> HexToBytes(const std::string& input) {
        std::vector<unsigned char> bytes;
        std::istringstream iss(input);
        std::string hexValue;

        while (iss >> hexValue) {
            if (hexValue.size() == 1) {
                hexValue = "0" + hexValue;
            }
            unsigned int byte;
            std::stringstream ss;
            ss << std::hex << hexValue;
            ss >> byte;
            bytes.push_back(static_cast<unsigned char>(byte));
        }
        return bytes;
    }
    /**
     * @brief Imprime una cadena como valores hexadecimales.
     * @param input Texto a imprimir en formato hexadecimal.
     */
    void 
    printHex(const std::string& input) {
        for (unsigned char c : input) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
        }
        std::cout << std::dec << std::endl;
    }
    /**
     * @brief Verifica si un texto es imprimible o legible.
     * @param data Texto a verificar.
     * @return true si es legible, false si no lo es.
     */
    bool 
    isValidText(const std::string& data) {
        return std::all_of(data.begin(), data.end(), [](unsigned char c) {
            return std::isprint(c) || std::isspace(c) || c == '\n';
            });
    }

    /**
     * @brief Fuerza bruta usando una sola clave XOR de 1 byte.
     * @param cifrado Texto cifrado en formato de bytes.
     */
    void bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
        for (int clave = 0; clave < 256; ++clave) {
            std::string result;

            for (unsigned char c : cifrado) {
                result += static_cast<unsigned char>(c ^ clave);
            }

            if (isValidText(result)) {
                std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
                std::cout << "Clave 1   : '" << static_cast<char>(clave)
                    << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
                std::cout << "Texto posible : " << result << "\n";
            }
        }
    }

    /**
    * @brief Fuerza bruta usando claves XOR de 2 bytes.
    * @param cifrado Texto cifrado en formato de bytes.
    */
    void 
    bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
        for (int b1 = 0; b1 < 256; ++b1) {
            for (int b2 = 0; b2 < 256; ++b2) {
                std::string result;
                unsigned char key[2] = {
                    static_cast<unsigned char>(b1),
                    static_cast<unsigned char>(b2)
                };

                for (int i = 0; i < cifrado.size(); i++) {
                    result += cifrado[i] ^ key[i % 2];
                }

                if (isValidText(result)) {
                    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
                    std::cout << "Clave 2  : '" << static_cast<char>(b1) << static_cast<char>(b2)
                        << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
                        << " 0x" << std::setw(2) << std::setfill('0') << b2 << ")\n";
                    std::cout << "Texto posible : " << result << "\n";
                }
            }
        }
    }
    /**
    * @brief Fuerza bruta con un diccionario de claves comunes.
    * @param cifrado Texto cifrado en formato de bytes.
    */
    void 
    bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
        std::vector<std::string> clavesComunes = {
            "clave", "admin", "1234", "root", "test", "abc", "hola", "user",
            "pass", "12345", "0000", "password", "default", "friki", "goofyahh"
        };

        for (const auto& clave : clavesComunes) {
            std::string result;
            for (int i = 0; i < cifrado.size(); i++) {
                result += static_cast<unsigned char>(cifrado[i] ^ clave[i % clave.size()]);
            }

            if (isValidText(result)) {
                std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
                std::cout << "Clave de diccionario: '" << clave << "'\n";
                std::cout << "Texto posible : " << result << "\n";
            }
        }
    }

private:

};
