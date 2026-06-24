#include "pch.h"
#include "cipher_api.h"
#include "cipher.h"
#include <string>
#include <cstring>

extern "C" {
    EXPORT cipher_type* cipher_create_caesar(int key) {
        CaesarCipher* obj = new CaesarCipher(key);
        return reinterpret_cast<cipher_type*>(obj);
    }

    EXPORT cipher_type* cipher_create_vigenere(const char* key) {
        VigenereCipher* obj = new VigenereCipher(std::string(key));
        return reinterpret_cast<cipher_type*>(obj);
    }

    EXPORT char* cipher_encrypt(cipher_type* cipher, const char* text) {
        Cipher* c = reinterpret_cast<Cipher*>(cipher);
        std::string result = c->encrypt(std::string(text));
        char* out = new char[result.size() + 1];
        strcpy_s(out, result.size() + 1, result.c_str());
        return out;
    }

    EXPORT char* cipher_decrypt(cipher_type* cipher, const char* text) {
        Cipher* c = reinterpret_cast<Cipher*>(cipher);
        std::string result = c->decrypt(std::string(text));
        char* out = new char[result.size() + 1];
        strcpy_s(out, result.size() + 1, result.c_str());
        return out;
    }

    EXPORT void cipher_destroy(cipher_type* cipher) {
        delete reinterpret_cast<Cipher*>(cipher);
    }

    EXPORT void cipher_free(char* str) {
        delete[] str;
    }
}