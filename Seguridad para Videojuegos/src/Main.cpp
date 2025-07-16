#include "FileEncryptor.h"  // Manejo de cifrado y descifrado de archivos
#include "XOREncoder.h"      // Cifrado XOR
#include <iostream>          // Entrada y salida estándar
#include <string>            // Manejo de cadenas

int main() {
    std::string inputFile, outputFile, key;  ///< Variables de archivos y clave
    int choice;  ///< Opción del menú
    bool encrypting;  ///< Bandera de cifrado/descifrado

    /**
     * @brief Menú para seleccionar operación de cifrado o descifrado
     * @param choice Opción seleccionada por el usuario (1 para cifrar, 2 para descifrar)
     */
    std::cout << "=== Menú de Cifrado ===" << std::endl;
    std::cout << "1) Cifrar" << std::endl;
    std::cout << "2) Descifrar" << std::endl;
    std::cout << "Selecciona una opción: ";
    std::cin >> choice;
    encrypting = (choice == 1);  ///< Determina si es cifrado o descifrado

    /**
     * @brief Solicita el archivo de entrada, salida y la clave
     * @param inputFile Nombre del archivo de entrada
     * @param outputFile Nombre del archivo de salida
     * @param key Clave de cifrado
     */
    std::cout << "Ingresa el nombre del archivo (con extensión .txt): ";
    std::cin >> inputFile;
    std::cout << "Ingresa el nombre del archivo de salida (sin extensión): ";
    std::cin >> outputFile;
    std::cout << "Ingresa la clave: ";
    std::cin >> key;

    /**
     * @brief Menú para seleccionar el algoritmo de cifrado
     * @param choice Opción seleccionada para el algoritmo de cifrado (1: César, 2: XOR, 3: Vigenère, 4: DES)
     */
    std::cout << "Selecciona el algoritmo de cifrado: " << std::endl;
    std::cout << "1) César" << std::endl;
    std::cout << "2) XOR" << std::endl;
    std::cout << "3) Vigenère" << std::endl;
    std::cout << "4) DES" << std::endl;
    std::cout << "Selecciona una opción: ";
    std::cin >> choice;

    /**
     * @brief Instanciación de FileEncryptor para manejar el proceso de cifrado/descifrado
     */
    FileEncryptor encryptor;

    /**
     * @brief Procesa el archivo con el algoritmo seleccionado
     * @param inputFile Nombre del archivo de entrada
     * @param outputFile Nombre del archivo de salida
     * @param key Clave para el cifrado/descifrado
     * @param encrypting Bandera para indicar cifrado (true) o descifrado (false)
     */

     // Se modifica para que el archivo de salida se guarde en la carpeta "cif"
    outputFile = "cif\\" + outputFile;  // Agrega la carpeta "cif" al nombre del archivo de salida

    switch (choice) {
    case 1:  ///< Cifrado César
        encryptor.processFile(inputFile, outputFile, key, FileEncryptor::CipherType::CAESAR, encrypting);
        break;
    case 2:  ///< Cifrado XOR
        encryptor.processFile(inputFile, outputFile, key, FileEncryptor::CipherType::XORC, encrypting);
        break;
    case 3:  ///< Cifrado Vigenère
        encryptor.processFile(inputFile, outputFile, key, FileEncryptor::CipherType::VIGENERE, encrypting);
        break;
    case 4:  ///< Cifrado DES
        encryptor.processFile(inputFile, outputFile, key, FileEncryptor::CipherType::DES, encrypting);
        break;
    default:
        std::cerr << "Opción no válida." << std::endl;  ///< Mensaje de error si la opción no es válida
        return 1;
    }

    std::cout << "Archivo procesado correctamente y guardado en: " << outputFile << std::endl; // Confirmación

    return 0;  ///< Finaliza el programa correctamente
}
