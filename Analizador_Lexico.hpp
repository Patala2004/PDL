#ifndef ANALIZADORLEXICO_HPP
#define ANALIZADORLEXICO_HPP

#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "aux_enums.hpp"

// Namespace usage
using namespace std;

// Class declaration

class Entrada{
    public:
    string nombre;
    string tipo;
    int desplazamiento;

    string tipoRetorno;
    string tipoParams;
    string etiqfuncion;
    int numParam;

    Entrada(string n);
};

class Tabla{
    public: 

    string nombre;
    int contador = -1;

    list<Entrada> entradas = {};

    string BuscaTipo(string id);

    Entrada& BuscaEntrada(string id);

    Entrada& BuscaEntradaFunc(string id);

    Entrada& BuscaTipoFuncParams(string id);

    Entrada& BuscaTipoFuncRet(string id);

    Entrada& AñadeEntrada(string id);

    void AñadeTipo(Entrada& e, string tipo);

    void AñadeDespl(Entrada& e, int despl);

    void AñadeTipoFunc(Entrada& e, string tipoParam, string tipoRet);

    void AñadeEtiq(Entrada& e, string etiq);

    string nuevaEtiq();

    private:
    int nfun = 0;
};



class AnalizadorLexico
{
private:
    std::ofstream token_file;

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
    int linea_last_tok;
    int linea_last_finished_tok;
    std::ifstream file;

    Tabla* tsg;
    Tabla* tsl;
    // Constructor
    AnalizadorLexico(const std::string &input_file);

    // Destructor
    ~AnalizadorLexico();

    // Public method to process characters
    Token processNextChar();
    void abreFichero(const std::string &input_file);

    int sintax_error(int cod);

};

int error(int cod_error, std::ifstream &file, std::streampos position, std::ofstream &err_file);

void sintax_error(int cod);

#endif // ANALIZADORLEXICO_HPP
