    #include "XOREncoder.h"  // Clase para la codificación XOR

    /**
     * @brief Realiza el cifrado XOR de una cadena con una clave.
     * @param input Texto a cifrar.
     * @param key Clave con la que se realiza el cifrado.
     * @return Cadena de texto cifrada.
     */
    std::string XOREncoder::encode(const std::string& input, const std::string& key) {
        std::string output = input;
        for (size_t i = 0; i < input.size(); i++) {
            output[i] = input[i] ^ key[i % key.size()];  // Aplica el cifrado XOR byte a byte
        }
        return output;
    }

    /**
     * @brief Convierte una cadena hexadecimal en un vector de bytes.
     * @param input Cadena de texto en formato hexadecimal.
     * @return Vector de bytes resultante.
     */
    std::vector<unsigned char> XOREncoder::HexToBytes(const std::string& input) {
        std::vector<unsigned char> bytes;
        std::istringstream iss(input);
        std::string hexValue;

        while (iss >> hexValue) {
            if (hexValue.size() == 1) hexValue = "0" + hexValue;  // Asegura que el valor hexadecimal tenga 2 dígitos
            unsigned int byte;
            std::stringstream ss;
            ss << std::hex << hexValue;
            ss >> byte;
            bytes.push_back(static_cast<unsigned char>(byte));  // Agrega el byte al vector
        }
        return bytes;
    }

    /**
     * @brief Imprime una cadena en formato hexadecimal.
     * @param input Cadena de texto a imprimir en formato hexadecimal.
     */
    void XOREncoder::printHex(const std::string& input) {
        for (unsigned char c : input) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";  // Imprime cada byte en hexadecimal
        }
        std::cout << std::dec << std::endl;  // Vuelve a la notación decimal
    }

    /**
     * @brief Verifica si una cadena de texto contiene solo caracteres imprimibles o espacios.
     * @param data Cadena de texto a verificar.
     * @return true si la cadena solo contiene caracteres imprimibles o espacios, false en caso contrario.
     */
    bool XOREncoder::isValidText(const std::string& data) {
        return std::all_of(data.begin(), data.end(), [](unsigned char c) {
            return std::isprint(c) || std::isspace(c) || c == '\n';  // Verifica si el carácter es imprimible o espacio
            });
    }

    /**
     * @brief Realiza un ataque de fuerza bruta para descifrar una cadena cifrada con XOR usando una clave de 1 byte.
     * @param cifrado Vector de bytes cifrados.
     */
    void XOREncoder::bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
        for (int clave = 0; clave < 256; ++clave) {  // Prueba todas las posibles claves de 1 byte (0-255)
            std::string result;
            for (unsigned char c : cifrado) {
                result += static_cast<unsigned char>(c ^ clave);  // Aplica el XOR con la clave
            }
            if (isValidText(result)) {  // Si el resultado es texto válido, lo imprime
                std::cout << "Clave 1 byte: " << clave << " Texto: " << result << "\n";
            }
        }
    }

    /**
     * @brief Realiza un ataque de fuerza bruta para descifrar una cadena cifrada con XOR usando una clave de 2 bytes.
     * @param cifrado Vector de bytes cifrados.
     */
    void XOREncoder::bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
        for (int b1 = 0; b1 < 256; ++b1) {  // Prueba las claves de 1 byte para el primer byte
            for (int b2 = 0; b2 < 256; ++b2) {  // Prueba las claves de 1 byte para el segundo byte
                std::string result;
                unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };  // Clave de 2 bytes
                for (size_t i = 0; i < cifrado.size(); i++) {
                    result += cifrado[i] ^ key[i % 2];  // Aplica el XOR con la clave de 2 bytes
                }
                if (isValidText(result)) {  // Si el resultado es texto válido, lo imprime
                    std::cout << "Clave 2 bytes: " << b1 << " " << b2 << " Texto: " << result << "\n";
                }
            }
        }
    }

    /**
     * @brief Realiza un ataque de fuerza bruta usando un diccionario de posibles claves para descifrar la cadena.
     * @param cifrado Vector de bytes cifrados.
     */
    void XOREncoder::bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
        std::vector<std::string> claves = { "clave", "admin", "1234", "root" };  // Diccionario de claves comunes
        for (const auto& clave : claves) {
            std::string result;
            for (size_t i = 0; i < cifrado.size(); i++) {
                result += static_cast<unsigned char>(cifrado[i] ^ clave[i % clave.size()]);  // Aplica el XOR con la clave del diccionario
            }
            if (isValidText(result)) {  // Si el resultado es texto válido, lo imprime
                std::cout << "Clave diccionario: " << clave << " Texto: " << result << "\n";
            }
        }
    }
