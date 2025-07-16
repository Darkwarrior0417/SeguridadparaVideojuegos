#include "FileEncryptor.h"  // Manejo de cifrado y descifrado de archivos
#include "XOREncoder.h"      // Cifrado XOR
#include "Vignere.h"         // Cifrado Vigenère
#include <iostream>          // Entrada y salida estándar
#include <string>            // Manejo de cadenas
#include <filesystem>        // Para verificar la existencia de archivos
#include <direct.h>
#include <limits>
#include <fstream>           // Para lectura y escritura de archivos

namespace fs = std::filesystem;

int main() {
    std::string inputFile, outputFile, key;
    int choice;
    bool encrypting;
    int shift;  // Clave para el cifrado César

    // Cambiar el directorio de trabajo a "raw"
    _chdir("C:\\Users\\DarkW\\OneDrive\\Escritorio\\Github\\VanguardiaGuerrero\\SeguridadparaVideojuegos\\Seguridad para Videojuegos\\raw");

    // Menú para elegir cifrado o descifrado
    std::cout << "=== Menu de Cifrado ===" << std::endl;
    std::cout << "1) Cifrar" << std::endl;
    std::cout << "2) Descifrar" << std::endl;
    std::cout << "Seleccione una opcion: ";
    std::cin >> choice;
    encrypting = (choice == 1);

    // Menú para elegir el tipo de cifrado
    std::cout << "Selecciona el algoritmo de cifrado: " << std::endl;
    std::cout << "1) Cesar" << std::endl;
    std::cout << "2) XOR" << std::endl;
    std::cout << "3) Vigenere" << std::endl;
    std::cout << "4) DES" << std::endl;
    std::cout << "Selecciona una opción: ";
    std::cin >> choice;

    // Solicitar nombre de archivo (sin la ruta completa)
    std::cout << "Ingresa el nombre del archivo (con extension .txt): ";
    std::cin >> inputFile;

    // Verificar si el archivo existe
    std::string fullInputPath = "C:\\Users\\DarkW\\OneDrive\\Escritorio\\Github\\VanguardiaGuerrero\\SeguridadparaVideojuegos\\Seguridad para Videojuegos\\raw\\" + inputFile;
    if (!fs::exists(fullInputPath)) {
        std::cerr << "[ERROR] El archivo " << inputFile << " no se pudo abrir. Verifique la ruta." << std::endl;
        return 1;  // Salir si el archivo no existe
    }

    // Definir automáticamente la carpeta de salida
    std::string outputDir = "C:\\Users\\DarkW\\OneDrive\\Escritorio\\Github\\VanguardiaGuerrero\\SeguridadparaVideojuegos\\Seguridad para Videojuegos\\cif\\";
    outputFile = outputDir + inputFile;  // Usar el mismo nombre de archivo para salida

    // Asegurarse de que la carpeta "cif" exista
    if (!fs::exists(outputDir)) {
        std::cout << "[INFO] Carpeta 'cif' no encontrada, creando..." << std::endl;
        fs::create_directory(outputDir);  // Crear la carpeta "cif"
    }

    // Solicitar la clave según el cifrado seleccionado
    std::cout << "Ingresa la clave: ";
    if (choice == 1) {  // Para César, debe ser un número
        while (true) {
            if (std::cin >> shift) {
                break;
            }
            else {
                std::cout << "[ERROR] La clave para César debe ser un numero entero." << std::endl;
                std::cout << "Ingresa la clave: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    else {
        std::cin >> key;
    }

    // Instanciar el objeto de XOR
    XOREncoder xorEncoder;

    // Instanciar el objeto de Vigenère
    Vignere vigenere(key);

    // Abrir el archivo de entrada
    std::ifstream inputFileStream(fullInputPath);
    std::stringstream buffer;
    buffer << inputFileStream.rdbuf();  // Leer todo el contenido del archivo
    std::string fileContent = buffer.str();

    // Procesar el archivo según el tipo de cifrado seleccionado
    switch (choice) {
    case 1:  // Cifrado César
    {
        FileEncryptor encryptor;
        encryptor.processFile(fullInputPath, outputFile, std::to_string(shift), FileEncryptor::CipherType::CAESAR, encrypting);
    }
    break;
    case 2:  // Cifrado XOR
    {
        std::string result = xorEncoder.encode(fileContent, key);  // Usar la función encode para cifrar/descifrar

        // Guardar el resultado en un archivo de salida
        std::ofstream outputFileStream(outputFile);
        outputFileStream << result;
        outputFileStream.close();
    }
    break;
    case 3:  // Cifrado Vigenère
    {
        if (encrypting) {
            std::string result = vigenere.encode(fileContent); // Cifrar el texto
            std::ofstream outputFileStream(outputFile);
            outputFileStream << result;
            outputFileStream.close();
        }
        else {
            std::string result = vigenere.decode(fileContent); // Descifrar el texto
            std::ofstream outputFileStream(outputFile);
            outputFileStream << result;
            outputFileStream.close();
        }
    }
    break;
    case 4:  // Cifrado DES
    {
        FileEncryptor encryptor;
        encryptor.processFile(fullInputPath, outputFile, key, FileEncryptor::CipherType::DES, encrypting);
    }
    break;
    default:
        std::cerr << "[ERROR] Opción no válida." << std::endl;
        return 1;
    }

    std::cout << "Archivo procesado correctamente y guardado en: " << outputFile << std::endl;

    return 0;
}
