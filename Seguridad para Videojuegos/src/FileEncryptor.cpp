#include "FileEncryptor.h"
#include "CaesarEncryption.h"
#include "Vignere.h"
#include "DES.h"
#include "XOREncoder.h"

#include <bitset>
#include <iostream>
#include <fstream>
#include <stdexcept>

/**
 * @brief Convierte una cadena de texto a su representación binaria de 64 bits (para DES).
 * @param s Cadena de texto a convertir.
 * @return Cadena de 64 bits representando el texto en binario.
 */
static std::string stringToBinary64(const std::string& s) {
    std::string binary;
    for (unsigned char c : s) {
        for (int i = 7; i >= 0; --i) {
            binary += ((c >> i) & 1) ? '1' : '0';  // Convierte cada carácter en su representación binaria
        }
    }
    if (binary.size() > 64) binary = binary.substr(0, 64);  // Trunca si excede 64 bits
    else if (binary.size() < 64) binary.append(64 - binary.size(), '0');  // Rellena con ceros si es menor a 64 bits
    return binary;
}

/**
 * @brief Cifra un texto utilizando el algoritmo especificado.
 * @param input Texto a cifrar.
 * @param type Tipo de cifrado (Caesar, XOR, Vigenere, DES).
 * @param key Clave para el cifrado.
 * @return Texto cifrado.
 */
std::string FileEncryptor::encrypt(const std::string& input, CipherType type, const std::string& key) {
    switch (type) {
    case CipherType::CAESAR: {
        CaesarEncryption c;
        int shift = 0;
        try {
            shift = std::stoi(key);  // Convierte la clave a un número entero
        }
        catch (...) {
            std::cerr << "[ERROR] La clave para Caesar debe ser un número entero." << std::endl;
            return {};  // Devuelve vacío en caso de error
        }
        return c.EncryptionCaesar(input, shift);  // Cifra con el algoritmo César
    }
    case CipherType::XORC: {
        XOREncoder x;
        return x.encode(input, key);  // Cifra con el algoritmo XOR
    }
    case CipherType::VIGENERE: {
        Vignere v(key);
        return v.encode(input);  // Cifra con el algoritmo Vigenère
    }
    case CipherType::DES: {
        std::string bitKeyString = stringToBinary64(key);  // Convierte la clave a binario
        std::bitset<64> bitKey(bitKeyString);

        DES des(bitKey);
        std::string out;

        for (size_t i = 0; i < input.size(); i += 8) {
            std::string block = input.substr(i, 8);  // Toma bloques de 8 caracteres
            if (block.size() < 8) block.append(8 - block.size(), '\0');  // Rellena con '\0' si es menor a 8

            std::bitset<64> blockBits = des.stringToBitset64(block);
            std::bitset<64> encryptedBlock = des.encode(blockBits);  // Aplica cifrado DES

            out += encryptedBlock.to_string();  // Agrega el bloque cifrado al resultado
        }
        return out;
    }
    default:
        std::cerr << "[ERROR] Tipo de cifrado no soportado." << std::endl;
        return {};  // Devuelve vacío si el tipo de cifrado no es válido
    }
}

/**
 * @brief Descifra un texto utilizando el algoritmo especificado.
 * @param input Texto a descifrar.
 * @param type Tipo de descifrado (Caesar, XOR, Vigenere, DES).
 * @param key Clave para el descifrado.
 * @return Texto descifrado.
 */
std::string FileEncryptor::decrypt(const std::string& input, CipherType type, const std::string& key) {
    switch (type) {
    case CipherType::CAESAR: {
        CaesarEncryption c;
        int shift = 0;
        try {
            shift = std::stoi(key);  // Convierte la clave a un número entero
        }
        catch (...) {
            std::cerr << "[ERROR] La clave para Caesar debe ser un número entero." << std::endl;
            return {};  // Devuelve vacío en caso de error
        }
        return c.DecodeCaesar(input, shift);  // Descifra con el algoritmo César
    }
    case CipherType::XORC: {
        XOREncoder x;
        return x.encode(input, key);  // XOR es simétrico, por lo que se usa el mismo método para descifrar
    }
    case CipherType::VIGENERE: {
        Vignere v(key);
        return v.decode(input);  // Descifra con el algoritmo Vigenère
    }
    case CipherType::DES: {
        std::string bitKeyString = stringToBinary64(key);  // Convierte la clave a binario
        std::bitset<64> bitKey(bitKeyString);

        DES des(bitKey);
        std::string out;

        if (input.size() % 64 != 0) {  // Verifica que el tamaño del texto cifrado sea múltiplo de 64
            std::cerr << "[ERROR] El texto cifrado DES debe tener longitud múltiplo de 64 bits." << std::endl;
            return {};  // Devuelve vacío si el tamaño no es correcto
        }

        for (size_t i = 0; i < input.size(); i += 64) {
            std::string block = input.substr(i, 64);  // Toma bloques de 64 bits
            std::bitset<64> blockBits(block);
            std::bitset<64> decryptedBlock = des.decode(blockBits);  // Aplica descifrado DES

            out += des.bitset64ToString(decryptedBlock);  // Convierte el bloque descifrado a cadena
        }

        // Elimina padding '\0' al final del texto descifrado
        while (!out.empty() && out.back() == '\0') {
            out.pop_back();
        }
        return out;
    }
    default:
        std::cerr << "[ERROR] Tipo de descifrado no soportado." << std::endl;
        return {};  // Devuelve vacío si el tipo de descifrado no es válido
    }
}

/**
 * @brief Procesa un archivo, cifrando o descifrando su contenido y guardando el resultado en otro archivo.
 * @param inputPath Ruta del archivo de entrada.
 * @param outputPath Ruta del archivo de salida.
 * @param key Clave para el cifrado/descifrado.
 * @param type Tipo de cifrado/descifrado.
 * @param encrypting Bandera que indica si se está cifrando o descifrando.
 */
void FileEncryptor::processFile(const std::string& inputPath, const std::string& outputPath,
    const std::string& key, CipherType type, bool encrypting) {

    std::string content;
    try {
        content = readFile(inputPath);  // Lee el archivo de entrada
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return;
    }

    if (content.empty()) {
        std::cerr << "[ERROR] El archivo de entrada está vacío." << std::endl;
        return;
    }

    std::string result = encrypting ? encrypt(content, type, key) : decrypt(content, type, key);  // Cifra o descifra

    if (result.empty()) {
        std::cerr << "[ERROR] No se pudo procesar el archivo (resultado vacío)." << std::endl;
        return;
    }

    try {
        writeFile(outputPath, result);  // Guarda el resultado en el archivo de salida
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return;
    }

    std::cout << (encrypting ? "Archivo cifrado" : "Archivo descifrado")
        << " guardado en: " << outputPath << std::endl;
}

/**
 * @brief Lee el contenido de un archivo.
 * @param filename Ruta del archivo a leer.
 * @return Contenido del archivo como cadena de texto.
 * @throws std::runtime_error Si no se puede abrir el archivo.
 */
std::string FileEncryptor::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

/**
 * @brief Escribe contenido en un archivo.
 * @param filename Ruta del archivo donde se escribirá el contenido.
 * @param content Contenido a escribir en el archivo.
 * @throws std::runtime_error Si no se puede escribir en el archivo.
 */
void FileEncryptor::writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se pudo escribir el archivo: " + filename);
    }
    file.write(content.c_str(), content.size());
}
