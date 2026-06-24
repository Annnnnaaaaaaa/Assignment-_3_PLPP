#include <iostream>
#include <string>
#include <windows.h>
#include "cipher_api.h"

typedef cipher_type* (*CreateCaesar)(int);
typedef cipher_type* (*CreateVigenere)(const char*);
typedef char* (*CipherEncrypt)(cipher_type*, const char*);
typedef char* (*CipherDecrypt)(cipher_type*, const char*);
typedef void (*CipherDestroy)(cipher_type*);
typedef void (*CipherFree)(char*);

int main()
{
    HMODULE dll = LoadLibraryA("some_Dll.dll"); // завантажуємо DLL в пам'ять
    if (!dll) {
        std::cout << "Error: could not load DLL\n";
        return 1;
    }

    // отримуємо вказівники на функції
    auto create_caesar = (CreateCaesar)GetProcAddress(dll, "cipher_create_caesar");
    auto create_vigenere = (CreateVigenere)GetProcAddress(dll, "cipher_create_vigenere");
    auto encrypt = (CipherEncrypt)GetProcAddress(dll, "cipher_encrypt");
    auto decrypt = (CipherDecrypt)GetProcAddress(dll, "cipher_decrypt");
    auto destroy = (CipherDestroy)GetProcAddress(dll, "cipher_destroy");
    auto free_str = (CipherFree)GetProcAddress(dll, "cipher_free");

    if (!create_caesar || !create_vigenere || !encrypt || !decrypt || !destroy || !free_str) {
        std::cout << "Error: could not load functions from DLL\n";
        FreeLibrary(dll);
        return 1;
    }

    while (true) {
        std::cout << "\nChoose cipher:\n";
        std::cout << "1. Caesar\n";
        std::cout << "2. Vigenere\n";
        std::cout << "0. Exit\n";
        std::cout << "> ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Error: enter a number\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice == 0) break;

        if (choice != 1 && choice != 2) {
            std::cout << "Error: enter 0, 1 or 2\n";
            continue;
        }

        cipher_type* cipher = nullptr;

        if (choice == 1) {
            std::cout << "Enter key (number): ";
            std::cout << "> ";
            int key;
            if (!(std::cin >> key)) {
                std::cout << "Error: key must be a number\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            std::cin.ignore();
            cipher = create_caesar(key);
        }
        else {
            std::cout << "Enter key (word): ";
            std::cout << "> ";
            std::string key;
            std::getline(std::cin, key);
            if (key.empty()) {
                std::cout << "Error: key cannot be empty\n";
                continue;
            }
            cipher = create_vigenere(key.c_str());
        }

        std::cout << "Choose operation:\n";
        std::cout << "1. Encrypt\n";
        std::cout << "2. Decrypt\n";
        std::cout << "> ";
        int operation;
        if (!(std::cin >> operation) || (operation != 1 && operation != 2)) {
            std::cout << "Error: enter 1 or 2\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            destroy(cipher);
            continue;
        }
        std::cin.ignore();

        std::cout << "Enter text: ";
        std::cout << "> ";
        std::string text;
        std::getline(std::cin, text);
        if (text.empty()) {
            std::cout << "Error: text cannot be empty\n";
            destroy(cipher);
            continue;
        }

        char* result = nullptr;
        if (operation == 1)
            result = encrypt(cipher, text.c_str());
        else
            result = decrypt(cipher, text.c_str());

        std::cout << "Result: " << result << "\n";

        free_str(result); // звільняє рядок з результатом
        destroy(cipher); // видаляє об'єкт шифру
    }

    FreeLibrary(dll); // вивантажуємо DLL з пам'яті
    return 0;
}