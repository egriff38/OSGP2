//
// Created by Eshin Griffith on 11/3/17.
//

/* Hex_Util contains functions for converting between hex, binary, and decimal respectively.
 * All of the names should be intuitive. 
 */

#ifndef PHASE_2_HEX_UTIL_H
#define PHASE_2_HEX_UTIL_H
#include<string>
namespace Hex_Util
{

    // Hex to Binary
    std::string hex_to_binary(std::string hex_input); //converts Hex values to 32-bit binary long
    std::string hex_char_to_binary(char hex);

    // Hex to Decimal
    int hex_to_decimal(std::string hex_input);
    int hex_char_to_decimal(char hexChar);


    // Binary to Hex
    std::string binary_to_hex(std::string bin_input);
    char four_bits_to_hex(std::string binary);

    // Binary to Decimal
    int binary_to_decimal(std::string bin_input);

    // Decimal to Binary

    // Decimal to Hex (string)
    std::string decimal_to_hex(int decimalInput);

    // String to decimal

    std::string bool_to_string(bool s);
};

#endif //PHASE_2_HEX_UTIL_H
