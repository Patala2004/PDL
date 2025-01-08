#ifndef ANALIZADORLEXICO_HPP
#define ANALIZADORLEXICO_HPP

#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "aux_enums.hpp"

// Namespace usage

// Class declaration
class AnalizadorLexico
{
private:
    std::ifstream file;
    std::ofstream token_file, err_file, tabla_file;

    int estado;
    int valor_numerico;
    std::string valor_cadena;
    int num_linea;
    int pos_tabla_simbolos;
    int desplazamiento;
    char a;
    bool eof;

    std::map<std::string, token_ids> palResMap;
    std::vector<int> finales;

public:
    int linea;
    // Constructor
    AnalizadorLexico(const std::string &input_file);

    // Destructor
    ~AnalizadorLexico();

    // Public method to process characters
    Token processNextChar();

    int sintax_error(int cod);

};

int error(int cod_error, std::ifstream &file, std::streampos position, std::ofstream &err_file);

void sintax_error(int cod);

#endif // ANALIZADORLEXICO_HPP
