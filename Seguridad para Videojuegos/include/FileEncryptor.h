#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <filesystem>

#include "CaesarEncryption.h"
#include "Vignere.h"
#include "DES.h"
#include "XOREncoder.h"

namespace fs = std::filesystem;

class FileEncryptor {
public:
    /**
     * @brief Enumeración de tipos de cifrado disponibles.
     */
    enum class CipherType { CAESAR, XORC, VIGENERE, DES };

    /**
     * @brief Cifra un texto utilizando el algoritmo especificado.
     * @param input Texto a cifrar.
     * @param type Tipo de cifrado (Caesar, XOR, Vigenere, DES).
     * @param key Clave para el cifrado.
     * @return Texto cifrado.
     */
    std::string encrypt(const std::string& input, CipherType type, const std::string& key);

    /**
     * @brief Descifra un texto utilizando el algoritmo especificado.
     * @param input Texto a descifrar.
     * @param type Tipo de descifrado (Caesar, XOR, Vigenere, DES).
     * @param key Clave para el descifrado.
     * @return Texto descifrado.
     */
    std::string decrypt(const std::string& input, CipherType type, const std::string& key);

    /**
     * @brief Procesa un archivo: lee su contenido, lo cifra/descifra y escribe el resultado en otro archivo.
     * @param inputPath Ruta del archivo de entrada.
     * @param outputPath Ruta del archivo de salida.
     * @param key Clave para el cifrado/descifrado.
     * @param type Tipo de cifrado/descifrado.
     * @param encrypting Bandera que indica si se está cifrando (true) o descifrando (false).
     */
    void processFile(const std::string& inputPath, const std::string& outputPath,
        const std::string& key, CipherType type, bool encrypting);

private:
    /**
     * @brief Lee el contenido de un archivo.
     * @param filename Ruta del archivo a leer.
     * @return Contenido del archivo como una cadena de texto.
     * @throws std::runtime_error Si no se puede abrir el archivo.
     */
    std::string readFile(const std::string& filename);

    /**
     * @brief Escribe el contenido en un archivo.
     * @param filename Ruta del archivo donde se escribirá el contenido.
     * @param content Contenido a escribir en el archivo.
     * @throws std::runtime_error Si no se puede escribir en el archivo.
     */
    void writeFile(const std::string& filename, const std::string& content);
};
