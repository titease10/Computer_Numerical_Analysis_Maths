#include "include.hpp"
#include <string>
#include <iomanip>
#include <cstring>

void printHelp(void) {
    std::cout << "USAGE\n\t.mypgp [-xor | -aes | -rsa | -pgp] [-c | -d] [-b] KEY\n\tthe MESSAGE is read from standard input\nDESCRIPTION\n\t-xor\tcomputation using XOR algorithm\n\t-aes\tcomputation using AES algorithm\n\t-rsa\tcomputation using RSA algorithm\n\t-pgp\tcomputation using both RSA and AES algorithm\n\t-c\tMESSAGE is clear and we want to cipher it\n\t-d\tMESSAGE is ciphered and we want to decipher it\n\t-b\tblock mode: for xor and aes, only works on one block\n\t\tMESSAGE and KEY must be of the same size\n\t-g P Q\tfor RSA only: generate a public and private key\n\t\tpair from the prime number P and Q" << std::endl;
}

int checkArgs(int argc, char* argv[])
{
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printHelp();
        return 0;
    }
    if (strcmp(argv[1], "-xor") == 0 && argc == 5) {
        if (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-d") == 0) {
            if (strcmp(argv[3], "-b") == 0) {
                return 0;
            }
            return 1;
        }
        return 1;
    }
    if (strcmp(argv[1], "-aes") == 0 && (argc == 4 || argc == 5)) {
        if (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-d") == 0) {
            if (argc == 5 && strcmp(argv[3], "-b") == 0)
                return 0;
            else if (argc == 4)
                return 0;
            return 1;
        }
        return 1;
    }
    if (strcmp(argv[1], "-rsa") == 0 && (argc == 4 || argc == 5)) {
        if ((strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-d")) && argc == 4)
            return 0;
        else if (strcmp(argv[2], "-g") == 0 && argc == 5)
            return 0;
        return 1;
    }
    return 1;
}

std::vector<uint8_t> xorMessage(std::vector<uint8_t> message, std::vector<uint8_t> key)
{
    std::vector<uint8_t> ciphered;
    for (size_t i = 0; i < message.size(); ++i) {
        uint8_t encryptedByte = message[i] ^ key[i];
        ciphered.push_back(encryptedByte);
    }

    return ciphered;
}

std::vector<std::vector<uint8_t>> DivideVector(const std::vector<uint8_t> big) {
    std::vector<std::vector<uint8_t>> dividedVector;
    size_t startIndex = 0;

    while (startIndex < big.size()) {
        size_t endIndex = startIndex + 16;
        if (endIndex > big.size()) {
            endIndex = big.size();
        }
        std::vector<uint8_t> partOfBig(big.begin() + startIndex, big.begin() + endIndex);
        dividedVector.push_back(partOfBig);
        startIndex = endIndex;
    }
    return dividedVector;
}

int callAes(std::vector<uint8_t> message, std::vector<uint8_t> key, char **argv)
{
    if (key.size() != 16)
        return 84;
    std::vector<uint8_t> res;
    if (strcmp(argv[2], "-c") == 0) {
        if (strcmp(argv[3], "-b") != 0) {
            std::vector<std::vector<uint8_t>> divMessage = DivideVector(message);
            for (std::vector<uint8_t> div : divMessage) {
                std::vector<uint8_t> tmp = AES128Encrypt(div, key);
                res.insert(res.end(), tmp.begin(), tmp.end());
            }
        } else {
            if (message.size() != key.size())
                return 84;
            res = AES128Encrypt(message, key);
        }
    } else {
        if (strcmp(argv[3], "-b") != 0) {
            std::vector<std::vector<uint8_t>> divMessage = DivideVector(message);
            for (std::vector<uint8_t> div : divMessage) {
                std::vector<uint8_t> tmp = AES128Decrypt(div, key);
                res.insert(res.end(), tmp.begin(), tmp.end());
            }
        } else {
            if (message.size() != key.size())
                return 84;
            res = AES128Decrypt(message, key);
        }
    }
    for (uint8_t byte : res) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::endl;
    return 0;
}

int main(int argc, char* argv[])
{
    if (checkArgs(argc, argv) != 0)
        return (84);

    if (strcmp(argv[1], "-rsa") == 0 && strcmp(argv[2],"-g") == 0) {
        std::string hexP = argv[3];
        std::string hexQ = argv[4];
        std::vector<uint8_t> P = hexStringToBytes(hexP);
        std::vector<uint8_t> Q = hexStringToBytes(hexQ);
        // calcule and print public and private keys
        return (0);
    }
    std::string hexMessage;
    std::cin >> hexMessage;
    std::string hexKey = argv[argc - 1];
    std::vector<uint8_t> message = hexStringToBytes(hexMessage);
    std::vector<uint8_t> key = hexStringToBytes(hexKey);
    if (strcmp(argv[1], "-xor") == 0) {
        if (hexMessage.size() != hexKey.size())
            return 84;
        std::vector<uint8_t> xorMessageBytes = xorMessage(message, key);
        for (uint8_t byte : xorMessageBytes) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        std::cout << std::endl;
    }
    else if (strcmp(argv[1], "-aes") == 0) {
        if (callAes(message, key, argv) != 0)
            return 84;
    }
    return 0;
}
