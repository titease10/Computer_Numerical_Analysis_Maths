/*
** EPITECH PROJECT, 2024
** cryptography
** File description:
**
*/

#ifndef INCLUDE_HPP_
#define INCLUDE_HPP_

#include <iostream>
#include <vector>

std::vector<uint8_t> hexStringToBytes(const std::string& hex);
std::vector<uint8_t> AES128Encrypt( std::vector<uint8_t> message,  std::vector<uint8_t> mainkey);
std::vector<uint8_t> AES128Decrypt(std::vector<uint8_t> ciphertext, std::vector<uint8_t> mainkey);

#endif /* !GAMEBOARD_HPP_ */
