#pragma once

#ifdef _WIN32 
    #define EXPORT __declspec(dllexport)
#else // для Linux/macOS
    #define EXPORT __attribute__((visibility("default")))
#endif

typedef void* cipher_type; // вказівник на об'єкт шифру 
                           // (екземпляр класу CaesarCipher або VigenereCipher який створюється в пам'яті)
                           // cipher_t — те саме що void*, для читабельності

extern "C" {
    EXPORT cipher_type* cipher_create_caesar(int key);
    EXPORT cipher_type* cipher_create_vigenere(const char* key);

    EXPORT char* cipher_encrypt(cipher_type* cipher, const char* text);
    EXPORT char* cipher_decrypt(cipher_type* cipher, const char* text);

    EXPORT void cipher_destroy(cipher_type* cipher);
    EXPORT void cipher_free(char* str);
}
