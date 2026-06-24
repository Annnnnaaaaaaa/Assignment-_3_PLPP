#include "pch.h"
#include "cipher.h"

CaesarCipher::CaesarCipher(int key) : key_(key) {}

std::string CaesarCipher::encrypt(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        if (std::isupper(c)) {
            c = c + key_;
            while (c > 'Z') 
                c -= 26;
        }
        else if (std::islower(c)) {
            c = c + key_;
            while (c > 'z') 
                c -= 26;
        }
    }
    return result;
}

std::string CaesarCipher::decrypt(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        if (std::isupper(c)) {
            c = c - key_;
            while (c < 'A') 
                c += 26;
        }
        else if (std::islower(c)) {
            c = c - key_;
            while (c < 'a') 
                c += 26;
        }
    }
    return result;
}




VigenereCipher::VigenereCipher(const std::string& key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string& text) {
    std::string result = text;
    int keyIndex = 0;
    for (int i = 0; i < (int)result.size(); i++) { // для кожного символу c в рядку result
                             // & означає посилання на саму літеру з рядка, а не її копію. Тому коли ми змінюємо c, змінюється і сам рядок result
        unsigned char c = result[i];
        if (std::isalpha(c)) {
            int shift = std::toupper(key_[keyIndex]) - 'A';
            // std - стандартна бібліотека C++, живуть всі вбудовані інструменти
            // :: — оператор доступу

            if (std::isupper(c)) {
                c = c + shift;
                while (c > 'Z') c -= 26;
            }
            else {
                c = c + shift;
                while (c > 'z') c -= 26;
            }
            result[i] = c;
            keyIndex++;
            if (keyIndex == key_.size()) 
                keyIndex = 0;
        }
    }
    return result;
}

std::string VigenereCipher::decrypt(const std::string& text) {
    std::string result = text;
    int keyIndex = 0;
    for (int i = 0; i < (int)result.size(); i++) {
        unsigned char c = result[i];
        if (std::isalpha(c)) {
            int shift = std::toupper(key_[keyIndex]) - 'A';

            if (std::isupper(c)) {
                c = c - shift;
                while (c < 'A') c += 26;
            }
            else {
                c = c - shift;
                while (c < 'a') c += 26;
            }
            result[i] = c;
            keyIndex++;
            if (keyIndex == key_.size())
                keyIndex = 0;
        }
    }
    return result;
}