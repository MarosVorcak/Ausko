#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <stdexcept>

uint32_t ipToUint32(const std::string& ip) {
    uint32_t result = 0;
    std::istringstream iss(ip);
    std::string octet;

    for (int i = 0; i < 4; ++i) {
        if (!std::getline(iss, octet, '.')) {
            throw std::invalid_argument("Invalid IP address format");
        }
        int value = std::stoi(octet);
        if (value < 0 || value > 255) {
            throw std::out_of_range("Octet value out of range");
        }
        result = (result << 8) | value;
    }

    return result;
}

bool doesIPMatch(uint32_t prefixIp, int prefixMask, uint32_t comparedIp) {
    if (prefixMask == 0) return true;
    if (prefixMask > 32) prefixMask = 32;

    uint32_t mask = (prefixMask == 32) ? 0xFFFFFFFF : ~(0xFFFFFFFF >> prefixMask);
    return (prefixIp & mask) == (comparedIp & mask);
}

