#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>
#include "aux_enums.hpp"
#include "Analizador_Lexico.hpp"

using namespace std;

template <typename T>
bool contains(T list[], int size, T elem)
{
    for (int i = 0; i < size; ++i)
    {
        if (list[i] == elem)
        {
            return true;
        }
    }
    return false;
}

// struct Tabla {
//     string texto;
//     int id;
// };

int contador = 0;

std::map<int, string> Tablas;

std::map<string, int> tabla;

int error(int cod_error, std::ifstream &file, std::streampos position, std::ofstream &err_file)
{
    file.clear();
    file.seekg(0, std::ios::beg);
    // Ver en que fila esta
    int line = 0;
    int column = 0;
    string a;
    // Get line num
    if (position == -1)
    { // if position == eol -> mirar todo
        while (getline(file, a))
        {
            line++;
        }
        column = a.length();
    }
    else
    {
        std::streampos lastline;
        while (file.tellg() != -1 && file.tellg() < position - (std::streampos)1)
        {
            line++;
            lastline = file.tellg();
            getline(file, a);
        }
        // tellg() is on the start of the line right before the line with the position
        file.clear();
        file.seekg(lastline);
        // Curr pos = line with postion
        while (file.tellg() != -1 && file.tellg() < position - (std::streampos)1)
        {
            column++;
            file.get();
        }
        // Check column
    }
    file.seekg(position - (std::streampos)1); // ir a la pos del char de error
    // Gett err message
    string err_msg = "";
    switch (cod_error)
    {
    case 1:
        err_msg = "Caracter invalido '&'. Querias poner operador logico and '&&'?";
        break;
    case 2:
        err_msg = "Cadena sin terminar. Por favor pon \" para cerrarla";
        break;
    case 3:
        err_msg = "Caracter invalido /";
        break;
    case 4:
        err_msg = "Comentario sin finalizar. Recuerda poner \\* Al final de todo";
        break;
    case 5:
        err_msg = "Character invalido '";
        err_msg += (char)file.peek();
        err_msg += '\'';
        break;
    case 6:
        err_msg = "Caracter invalido \'/\'. Querías iniciar un comentario de bloque /*...*/?";
        break;
    // Errores sintácticos
    case 7:
        err_msg = "Error sintáctico";
        break;
    case 8:
        err_msg = "Error sintáctico. Carácter inesperado: ";
        err_msg += (char)file.peek();

        break;
    case 9:
        err_msg = "Error sintáctico. Carácter inesperado ";
        break;
    }

    // Imprimir error
    err_file << "ERROR. COD: " << cod_error << " EN (" << line << "," << column << "):   " << err_msg << endl;
    // Volver a posición anterior
    file.seekg(position, std::ios::beg);
    return line;
}

Token generarToken(token_ids id, int valor, std::ofstream &token_file)
{
    token_file << "<" << tokenToString(id) << ", " << valor << ">" << endl;
    return Token(id,valor);
}
Token generarToken(token_ids id, string valor, std::ofstream &token_file)
{
    token_file << "<" << tokenToString(id) << ", " << '\"' << valor << '\"' << ">" << endl;
    return Token(id,valor);
}
Token generarToken(token_ids id, std::ofstream &token_file)
{
    token_file << "<" << tokenToString(id) << ", " << ">" << endl;
    return Token(id);
}

void crearTabla(string nombre_tabla, std::ofstream &tabla_file)
{
    // string texto = "";
    // Tabla t = {texto, contador}
    // Linea del identificador de la tabla
    string titulo = nombre_tabla + " " + '#' + " " + std::to_string(contador) + ':' + '\n' + '\n';
    // contador++;
    tabla_file << titulo;
}

void meterToken(token_ids id, string lex, int desplazamiento, std::ofstream &tabla_file)
{
    // Si el token no es un identificador no se anade a la Tabla de simbolos
    // if de asegurarse
    if (tokenToString(id) == "ID")
    {
        // No esta el token en la tabla
        if (tabla.find(lex) == tabla.end())
        {
            string texto = "";
            texto += "* LEXEMA: '" + lex + "'" + '\n';
            texto += "    +despl: " + std::to_string(desplazamiento) + '\n';
            tabla_file << texto;
            tabla.insert_or_assign(lex, desplazamiento);
        }
        else
        {
            std::map<string, int>::iterator it = tabla.find(lex);
            int desp = it->second;
        }
    }
}
// palabras reservadas


    AnalizadorLexico::AnalizadorLexico(const std::string &input_file) : estado(0), valor_numerico(0), valor_cadena(""), num_linea(1), linea(1), linea_last_tok(1), linea_last_finished_tok(1), pos_tabla_simbolos(0), desplazamiento(0), eof(false)
    {
        // Open files
        file.open(input_file, std::ios::binary);
        token_file.open("token.txt", std::ios::trunc);
        err_file.open("errores.txt", std::ios::trunc);
        tabla_file.open("tabla.txt", std::ios::trunc);

        // Error checking for file streams
        if (!file.is_open())
            throw std::runtime_error("Error: Could not open the file!");
        if (!token_file)
            throw std::runtime_error("Error: Could not open token file!");
        if (!err_file)
            throw std::runtime_error("Error: Could not open error file!");
        if (!tabla_file)
            throw std::runtime_error("Error: Could not open symbol table file!");

        // Prepare reserved words
        palResMap = {
            {"boolean", token_ids::PAL_RES_BOOL}, {"for", token_ids::PAL_RES_FOR}, {"function", token_ids::PAL_RES_FUNCTION}, {"if", token_ids::PAL_RES_IF}, {"input", token_ids::PAL_RES_INPUT}, {"output", token_ids::PAL_RES_OUTPUT}, {"return", token_ids::PAL_RES_RETURN}, {"string", token_ids::PAL_RES_STRING}, {"var", token_ids::PAL_RES_VAR}, {"void", token_ids::PAL_RES_VOID}, {"int", token_ids::PAL_RES_INT}};

        // Set final states
        finales = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 13, 14, 16, 26, 22, 20, 18};
    }

    // DESTRUCTOR NO TRIVIAL LETS GOOO
    AnalizadorLexico::~AnalizadorLexico()
    {
        // Close files
        if (file.is_open())
            file.close();
        if (token_file.is_open())
            token_file.close();
        if (err_file.is_open())
            err_file.close();
        if (tabla_file.is_open())
            tabla_file.close();
    }

    Token AnalizadorLexico::processNextChar()
    {

        bool tokenGenerated = false;

        char digitos[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}; // size = 10
        char abc[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        char delimitadores[] = {';', '\n', ' ', '\t', '\0'}; // size = 5
        char valid[] = {'\n', ' ', '\t', '\0', '\b', '\r'};  // Chars validos no mirados en otra condición

        if (eof)
        {
            return Token(token_ids::ENDOFFILE);
        }

        Token res_token = Token(token_ids::ENDOFFILE);

        while (!tokenGenerated)
        {
            if (!file.get(a))
            {
                eof = true;
                // Handle EOF state transitions
                switch (estado)
                {
                case 9:
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
                    estado = 11;
                    break;
                case 12:
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
                    estado = 14;
                    break;
                case 15:
                    error(1, file, file.tellg(), err_file); // Unfinished &&
                    break;
                case 17:
                    estado = 18;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::NUMERO, valor_numerico, token_file);
                    break;
                case 19:
                    estado = 20;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::IDENTIFICADOR, valor_cadena, token_file);
                    break;
                case 21:
                    error(2, file, file.tellg(), err_file); // Unfinished string "..." (last " missing)
                    break;
                case 23:
                    error(3, file, file.tellg(), err_file); // '/' sin nada mas (no existe operador de division aqui)
                    break;
                case 24:
                    error(4, file, file.tellg(), err_file); // Comentario sin finalizar /* ...
                    break;
                case 25:
                    error(4, file, file.tellg(), err_file); // Comentario sin finalizar /*...*
                    break;
                }
                linea_last_finished_tok = linea_last_tok;
                linea_last_tok = linea;
                return res_token;
            }


            if(a == '\n'){
                AnalizadorLexico::linea++;
            }

            // Main processing logic (refactor the switch-case from your code)

            switch (estado)
            {
            case 0:
                if (a == '{')
                {
                    estado = 1;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::LLAVE_ABIERTA, token_file);
                }
                else if (a == '}')
                {
                    estado = 2;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::LLAVE_CERRADA, token_file);
                }
                else if (a == '(')
                {
                    estado = 3;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::PARENTESIS_ABIERTA, token_file);
                }
                else if (a == ')')
                {
                    estado = 4;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::PARENTESIS_CERRADA, token_file);
                }
                else if (a == ',')
                {
                    estado = 5;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::COMA, token_file);
                }
                else if (a == ';')
                {
                    estado = 6;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::PUNTO_Y_COMA, token_file);
                }
                else if (a == '-')
                {
                    estado = 8;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ARITMETICO_RESTA, token_file);
                }
                else if (a == '+')
                {
                    estado = 9;
                }
                else if (a == '=')
                {
                    estado = 12;
                }
                else if (a == '&')
                {
                    estado = 15;
                }
                // Comentario
                else if (a == '/')
                {
                    estado = 23;
                }
                // Strings
                else if (a == '"')
                {
                    valor_cadena = "";
                    estado = 21;
                }
                // digitos
                else if (contains(digitos, 10, a))
                {
                    valor_numerico = a - '0';
                    estado = 17;
                }
                // variables y pals reservadas
                else if (contains(abc, 52, a))
                {
                    valor_cadena += a;
                    estado = 19;
                }
                else if (!contains(valid, 8, a))
                {
                    estado = 0;
                    file.clear();
                    error(5, file, file.tellg(), err_file);
                }
                break;
                // Si no -> el estado se mantiene en 0, lee el char y no hace nada y luego continua

            // case 1 - 8 son estados finales -> no se puede llegar a este punto con estado == uno de esos
            case 9:
                // estamos en +
                if (a == '=')
                {
                    estado = 10;
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ASIGNACION_SUMA, token_file);
                }
                else
                {
                    // No es lectura -> retroceder en uno
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
                    file.seekg(-1, std::ios::cur);
                    estado = 11;
                }
                break;
            // Case 10 y 11 son estados finales
            case 12:
                // estamos en =
                if (a == '=')
                {
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_RELACIONAL_IGUAL, token_file);
                    estado = 13;
                }
                else
                {
                    // No es lectura -> retroceder en uno
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
                    file.seekg(-1, std::ios::cur);
                    estado = 14;
                }
                break;
            // case 13 y 14 son estados finales
            case 15:
                // Estamos en &
                if (a == '&')
                {
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::OP_LOGICO_ANDS, token_file);
                    estado = 16;
                }
                else
                {
                    error(1, file, file.tellg() - (std::streampos)1, err_file);
                    // file.seekg(-1,std::ios::cur); se retrocede en el error
                    estado = 0;
                    // Lanzar error léxicos
                }
                break;
            // 16 es estado final
            case 17:
                // estamos en un numero entre 0 e infinito de d
                if (contains(digitos, 10, a))
                {
                    valor_numerico = valor_numerico * 10 + (a - '0');
                    estado = 17;
                }
                else
                {
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::NUMERO, valor_numerico, token_file);
                    valor_numerico = 0;
                    file.seekg(-1, std::ios::cur);
                    estado = 18;
                }
                break;
            // 18 es un estado finak
            case 19:
                // estamos en l
                if (contains(abc, 52, a) || contains(digitos, 10, a) || a == '_')
                {
                    valor_cadena += a;
                    estado = 19;
                }
                else
                {
                    std::map<std::string, token_ids>::iterator pal_res_id_it = palResMap.find(valor_cadena);
                    if (pal_res_id_it != palResMap.end())
                    {
                        tokenGenerated = true;
                        res_token = generarToken(pal_res_id_it->second, token_file);
                        desplazamiento++;
                    }
                    else
                    {
                        tokenGenerated = true;
                        res_token = generarToken(token_ids::IDENTIFICADOR, valor_cadena, token_file);
                        meterToken(token_ids::IDENTIFICADOR, valor_cadena, desplazamiento, tabla_file); // Meter a TS
                        pos_tabla_simbolos++;
                        desplazamiento++;
                    }
                    valor_cadena = "";
                    file.seekg(-1, std::ios::cur);
                    estado = 20;
                }
                break;
            // 20 es estado final
            case 21:
                // estamos en "
                if (a == '"')
                {
                    tokenGenerated = true;
                    res_token = generarToken(token_ids::CADENA, valor_cadena, token_file);
                    valor_cadena = "";
                    estado = 22;
                }
                else
                {
                    valor_cadena += a;
                    estado = 21;
                }
                break;
            // 22 es un estado final
            case 23:
                // estamos en /
                if (a == '*')
                {
                    estado = 24;
                }
                else
                {
                    // error
                    estado = 0;
                    error(6, file, file.tellg(), err_file);
                }
                break;
            case 24:
                // estamos en /* ...
                if (a == '*')
                {
                    estado = 25;
                }
                else
                {
                    estado = 24;
                }
                break;
            case 25:
                // estamos en /* ... *
                if (a == '*')
                {
                    estado = 25;
                }
                else if (a == '/')
                {
                    estado = 26;
                }
                else
                {
                    estado = 24;
                }
                break;
                // 26 es un estado final
            }

            // Reset to initial state if we hit a final state
            if (std::find(finales.begin(), finales.end(), estado) != finales.end())
            {
                estado = 0;
            }
        }

        linea_last_finished_tok = linea_last_tok;
        linea_last_tok = linea;
        return res_token; // Indicate that processing can continue
    }


int AnalizadorLexico::sintax_error(int cod)
{
    int linea = error(cod, file, file.tellg(), err_file);
    return linea;
}

int main3(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: You must provide a file name." << std::endl;
        return -1;
    }

    try
    {
        AnalizadorLexico analyzer(argv[1]);
        while (analyzer.processNextChar().id != token_ids::ENDOFFILE)
        {
            // Continuously process characters
        }
        std::cout << "Tokens generated successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
/*
int main2(int argc, char *argv[])
{
    // Preparar palabras reservadas
    std::map<std::string, token_ids> palResMap;
    palResMap["boolean"] = token_ids::PAL_RES_BOOL;
    palResMap["for"] = token_ids::PAL_RES_FOR;
    palResMap["function"] = token_ids::PAL_RES_FUNCTION;
    palResMap["if"] = token_ids::PAL_RES_IF;
    palResMap["input"] = token_ids::PAL_RES_INPUT;
    palResMap["output"] = token_ids::PAL_RES_OUTPUT;
    palResMap["return"] = token_ids::PAL_RES_RETURN;
    palResMap["string"] = token_ids::PAL_RES_STRING;
    palResMap["var"] = token_ids::PAL_RES_VAR;
    palResMap["void"] = token_ids::PAL_RES_VOID;
    palResMap["int"] = token_ids::PAL_RES_INT;

    if (argc < 2)
    {
        cerr << "Error: Tienes que pasar un archivo" << std::endl;
    }

    std::ifstream file(argv[1], std::ios::binary);

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return -1;
    }
    else
    {
        cout << "El archivo se ha abierto correctamente" << endl;
    }

    // Crear archivo para los tokens generados
    std::ofstream token_file("token.txt", std::ios::trunc); // Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.

    // Check if the file is successfully opened
    if (!token_file)
    {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }

    // Crear archivo para los errores
    std::ofstream err_file("errores.txt", std::ios::trunc); // Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.

    // Check if the file is successfully opened
    if (!err_file)
    {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }

    // Crear archivo para los tokens generados
    std::ofstream tabla_file("tabla.txt", std::ios::trunc); // Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.

    // Check if the file is successfully opened
    if (!tabla_file)
    {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }
    crearTabla("Tabla Inicial", tabla_file);
    // Variables del AFD
    int estado = 0;
    int finales[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 13, 14, 16, 26, 22, 20, 18}; // size = 17
    // Abecedarios
    //
    char digitos[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}; // size = 10
    //
    char abc[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    // size = 52
    char delimitadores[] = {';', '\n', ' ', '\t', '\0'}; // size = 5
    //
    char valid[] = {'\n', ' ', '\t', '\0', '\b', '\r'};  // Chars validos no mirados en otra condición

    char a; //
    int valor_numerico = 0;
    string valor_cadena = "";
    bool eof = true;
    int num_linea = 1; // Cambiar a 0 si las lineas empiezan en 0. Por ahora asumo que empiezan en 1
    int pos_tabla_simbolos = 0;
    int desplazamiento = 0; // igual que el de arriba pero quiero jugar con el a mi manera
    while (file.get(a))
    {
        switch (estado)
        {
        case 0:
            if (a == '{')
            {
                estado = 1;
                tokenGenerated = true;
                res_token = generarToken(token_ids::LLAVE_ABIERTA, token_file);
            }
            else if (a == '}')
            {
                estado = 2;
                tokenGenerated = true;
                res_token = generarToken(token_ids::LLAVE_CERRADA, token_file);
            }
            else if (a == '(')
            {
                estado = 3;
                tokenGenerated = true;
                res_token = generarToken(token_ids::PARENTESIS_ABIERTA, token_file);
            }
            else if (a == ')')
            {
                estado = 4;
                tokenGenerated = true;
                res_token = generarToken(token_ids::PARENTESIS_CERRADA, token_file);
            }
            else if (a == ',')
            {
                estado = 5;
                tokenGenerated = true;
                res_token = generarToken(token_ids::COMA, token_file);
            }
            else if (a == ';')
            {
                estado = 6;
                tokenGenerated = true;
                res_token = generarToken(token_ids::PUNTO_Y_COMA, token_file);
            }
            else if (a == '-')
            {
                estado = 8;
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ARITMETICO_RESTA, token_file);
            }
            else if (a == '+')
            {
                estado = 9;
            }
            else if (a == '=')
            {
                estado = 12;
            }
            else if (a == '&')
            {
                estado = 15;
            }
            // Comentario
            else if (a == '/')
            {
                estado = 23;
            }
            // Strings
            else if (a == '"')
            {
                valor_cadena = "";
                estado = 21;
            }
            // digitos
            else if (contains(digitos, 10, a))
            {
                valor_numerico = a - '0';
                estado = 17;
            }
            // variables y pals reservadas
            else if (contains(abc, 52, a))
            {
                valor_cadena += a;
                estado = 19;
            }
            else if (!contains(valid, 8, a))
            {
                estado = 0;
                file.clear();
                error(5, file, file.tellg(), err_file);
            }
            break;
            // Si no -> el estado se mantiene en 0, lee el char y no hace nada y luego continua

        // case 1 - 8 son estados finales -> no se puede llegar a este punto con estado == uno de esos
        case 9:
            // estamos en +
            if (a == '=')
            {
                estado = 10;
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ASIGNACION_SUMA, token_file);
            }
            else
            {
                // No es lectura -> retroceder en uno
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
                file.seekg(-1, std::ios::cur);
                estado = 11;
            }
            break;
        // Case 10 y 11 son estados finales
        case 12:
            // estamos en =
            if (a == '=')
            {
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_RELACIONAL_IGUAL, token_file);
                estado = 13;
            }
            else
            {
                // No es lectura -> retroceder en uno
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
                file.seekg(-1, std::ios::cur);
                estado = 14;
            }
            break;
        // case 13 y 14 son estados finales
        case 15:
            // Estamos en &
            if (a == '&')
            {
                tokenGenerated = true;
                res_token = generarToken(token_ids::OP_LOGICO_ANDS, token_file);
                estado = 16;
            }
            else
            {
                error(1, file, file.tellg() - (std::streampos)1, err_file);
                // file.seekg(-1,std::ios::cur); se retrocede en el error
                estado = 0;
                // Lanzar error léxicos
            }
            break;
        // 16 es estado final
        case 17:
            // estamos en un numero entre 0 e infinito de d
            if (contains(digitos, 10, a))
            {
                valor_numerico = valor_numerico * 10 + (a - '0');
                estado = 17;
            }
            else
            {
                tokenGenerated = true;
                res_token = generarToken(token_ids::NUMERO, valor_numerico, token_file);
                valor_numerico = 0;
                file.seekg(-1, std::ios::cur);
                estado = 18;
            }
            break;
        // 18 es un estado finak
        case 19:
            // estamos en l
            if (contains(abc, 52, a) || contains(digitos, 10, a))
            {
                valor_cadena += a;
                estado = 19;
            }
            else
            {
                std::map<std::string, token_ids>::iterator pal_res_id_it = palResMap.find(valor_cadena);
                if (pal_res_id_it != palResMap.end())
                {
                    meterToken(pal_res_id_it->second, valor_cadena, desplazamiento, tabla_file);
                    tokenGenerated = true;
                res_token = generarToken(pal_res_id_it->second, token_file);
                    desplazamiento++;
                }
                else
                {
                    tokenGenerated = true;
                res_token = generarToken(token_ids::IDENTIFICADOR, pos_tabla_simbolos, token_file);
                    meterToken(token_ids::IDENTIFICADOR, valor_cadena, desplazamiento, tabla_file);
                    pos_tabla_simbolos++;
                    desplazamiento++;
                }
                valor_cadena = "";
                file.seekg(-1, std::ios::cur);
                estado = 20;
            }
            break;
        // 20 es estado final
        case 21:
            // estamos en "
            if (a == '"')
            {
                tokenGenerated = true;
                res_token = generarToken(token_ids::CADENA, valor_cadena, token_file);
                valor_cadena = "";
                estado = 22;
            }
            else
            {
                valor_cadena += a;
                estado = 21;
            }
            break;
        // 22 es un estado final
        case 23:
            // estamos en /
            if (a == '*')
            {
                estado = 24;
            }
            else
            {
                // error
                estado = 0;
                error(6, file, file.tellg(), err_file);
            }
            break;
        case 24:
            // estamos en /* ...
            if (a == '*')
            {
                estado = 25;
            }
            else
            {
                estado = 24;
            }
            break;
        case 25:
            // estamos en /* ... *
            if (a == '*')
            {
                estado = 25;
            }
            else if (a == '/')
            {
                estado = 26;
            }
            else
            {
                estado = 24;
            }
            break;
            // 26 es un estado final
        }

        if (contains(finales, 17, estado))
        {
            estado = 0; // Si el estado al que ha llegado anteriormente es final -> vuelve al estado inicial
        }
    }
    // Actualizar estado con EOF
    switch (estado)
    {
    case 9:
        tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
        estado = 11;
        break;
    case 12:
        tokenGenerated = true;
                res_token = generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
        estado = 14;
        break;
    case 15:
        error(1, file, file.tellg(), err_file); // Unfinished &&
        break;
    case 17:
        estado = 18;
        tokenGenerated = true;
                res_token = generarToken(token_ids::NUMERO, valor_numerico, token_file);
        break;
    case 19:
        estado = 20;
        tokenGenerated = true;
                res_token = generarToken(token_ids::IDENTIFICADOR, valor_cadena, token_file);
        break;
    case 21:
        error(2, file, file.tellg(), err_file); // Unfinished string "..." (last " missing)
        break;
    case 23:
        error(3, file, file.tellg(), err_file); // '/' sin nada mas (no existe operador de division aqui)
        break;
    case 24:
        error(4, file, file.tellg(), err_file); // Comentario sin finalizar /* ...
        break;
    case 25:
        error(4, file, file.tellg(), err_file); // Comentario sin finalizar /*...*
        break;
    }
    cout << "Tokens se han generado correctamente" << endl;
    return 1;
}
*/