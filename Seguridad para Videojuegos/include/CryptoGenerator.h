#pragma once

#include "Prerequisites.h"
#include <random>

/**
 * @class CryptoGenerator
 * @brief Genera contraseñas, claves, IVs y salts criptográficamente seguras,
 *        y provee utilidades de codificación (hex/Base64) y limpieza de memoria.
 */
class CryptoGenerator {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa el motor Mersenne Twister con semilla extraída de
     * std::random_device para garantizar entropía criptográfica.
     */
    CryptoGenerator() {
        std::random_device rd;  // Dispositivo de generación de números aleatorios con alta entropía.
        m_engine.seed(rd());    // Semilla el motor Mersenne Twister con la entropía del dispositivo.
    }

    ~CryptoGenerator() = default;

    /**
     * @brief Genera una contraseña aleatoria.
     *
     * @param length Longitud de la contraseña a generar.
     * @param useUpper Incluir letras mayúsculas [A-Z].
     * @param useLower Incluir letras minúsculas [a-z].
     * @param useDigits Incluir dígitos [0-9].
     * @param useSymbols Incluir símbolos especiales.
     * @return std::string Contraseña generada.
     * @throws std::runtime_error Si no está habilitado ningún tipo de carácter.
     */
    std::string generatePassword(unsigned int length,
        bool useUpper = true,
        bool useLower = true,
        bool useDigits = true,
        bool useSymbols = false);

    /**
     * @brief Genera un buffer de bytes aleatorios.
     *
     * @param numBytes Cantidad de bytes a generar.
     * @return std::vector<uint8_t> Vector con valores en [0x00–0xFF].
     */
    std::vector<uint8_t> generateBytes(unsigned int numBytes);

    /**
     * @brief Convierte bytes a cadena hexadecimal.
     *
     * @param data Vector de bytes de entrada.
     * @return std::string Representación hexadecimal.
     */
    std::string toHex(const std::vector<uint8_t>& data);

    /**
     * @brief Decodifica una cadena hexadecimal a bytes.
     *
     * @param hex Cadena hexadecimal.
     * @return std::vector<uint8_t> Bytes decodificados.
     * @throws std::runtime_error Si la cadena no es hexadecimal válida.
     */
    std::vector<uint8_t> fromHex(const std::string& hex);

    /**
     * @brief Genera una clave simétrica de tamaño dado en bits.
     *
     * @param bits Tamaño de la clave en bits (debe ser múltiplo de 8).
     * @return std::vector<uint8_t> Clave generada.
     * @throws std::runtime_error Si bits no es múltiplo de 8.
     */
    std::vector<uint8_t> generateKey(unsigned int bits);

    /**
     * @brief Genera un vector de inicialización (IV) de tamaño dado en bytes.
     *
     * @param blockSize Tamaño del IV en bytes.
     * @return std::vector<uint8_t> IV generado.
     */
    std::vector<uint8_t> generateIV(unsigned int blockSize);

    /**
     * @brief Genera una salt criptográfica de longitud dada.
     *
     * @param length Longitud de la salt en bytes.
     * @return std::vector<uint8_t> Salt generada.
     */
    std::vector<uint8_t> generateSalt(unsigned int length);

    /**
     * @brief Convierte un vector de bytes a una cadena Base64.
     *
     * @param data Vector de bytes de entrada.
     * @return std::string Representación Base64.
     */
    std::string toBase64(const std::vector<uint8_t>& data);

    /**
     * @brief Decodifica una cadena Base64 estándar en bytes.
     *
     * @param b64 Cadena Base64.
     * @return std::vector<uint8_t> Bytes decodificados.
     * @throws std::runtime_error Si la cadena no es Base64 válida.
     */
    std::vector<uint8_t> fromBase64(const std::string& b64);

    /**
     * @brief Limpia de forma segura los datos sensibles en un vector.
     *
     * Sobrescribe cada byte con cero para evitar filtraciones en memoria.
     *
     * @param data Vector cuyos elementos serán limpiados.
     */
    void secureWipe(std::vector<uint8_t>& data);

    /**
     * @brief Valida si una contraseña cumple con políticas mínimas.
     *
     * Requiere al menos una mayúscula, una minúscula, un dígito y longitud mínima de 8.
     *
     * @param password Contraseña a validar.
     * @return true si cumple la política; false en caso contrario.
     */
    bool validatePassword(const std::string& password);

    /**
     * @brief Estima la entropía aproximada (en bits) de una contraseña.
     *
     * @param password Contraseña a evaluar.
     * @return Bits de entropía estimados.
     */
    double estimateEntropy(const std::string& password);

    /**
     * @brief Devuelve una calificación cualitativa de la fortaleza de la contraseña.
     *
     * @param password Contraseña a calificar.
     * @return Una cadena con la calificación: "Muy débil", "Débil", "Moderada", "Fuerte" o "Muy fuerte".
     */
    std::string passwordStrength(const std::string& password);

private:
    std::mt19937 m_engine;  ///< Motor de generación de números aleatorios Mersenne Twister.
    std::mutex _mtx;        ///< Mutex para uso thread-safe.
    std::array<uint8_t, 256> _decTable;  ///< Tabla de decodificación Base64.
};
