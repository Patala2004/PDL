#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <set>

using namespace std;

enum class token_ids{
    LLAVE_ABIERTA,          // {
    LLAVE_CERRADA,          // }
    PARENTESIS_ABIERTA,     // (
    PARENTESIS_CERRADA,     // )
    COMA,                   // ,
    PUNTO_Y_COMA,           // ;
    OP_RELACIONAL_IGUAL,  // ==
    OP_LOGICO_AND,         // &&
    OP_ARITMETICO_RESTA,    // -
    OP_ARITMETICO_SUMA,     // +
    OP_ASIGNACION_SIMPLE,   // =
    OP_ASIGNACION_SUMA,     // +=
    CADENA,                 // "..."
    NUMERO,                 // 0123456789
    IDENTIFICADOR,          // varx
    // Palabras reservadas:
    PAL_RES_BOOL,           // boolean
    PAL_RES_FOR,            // for
    PAL_RES_FUNCTION,       // function
    PAL_RES_IF,             // if
    PAL_RES_INPUT,          // input
    PAL_RES_OUTPUT,         // output
    PAL_RES_RETURN,         // return
    PAL_RES_STRING,         // string
    PAL_RES_VAR,            // var
    PAL_RES_VOID,           // void
    PAL_RES_INT,
    ERROR_TOKEN_NOT_RECOGNIZED,
    ENDOFFILE
};
enum class reglas{
    S,  // 0
    B,  // 1
    D,  // 2
    T,  // 3
    C,  // 4
    R,  // 5
    U,  // 6
    F1, // 7
    F2, // 8
    Q,  // 9
    H,  // 10
    D1, // 11
    L,  // 12
    R1, // 13
    R2, // 14
    A,  // 15
    O,  // 16
    A1, // 17
    A2, // 18
    A3, // 19
    U2, // 20
    U1, // 21
    D2, // 22
    D3, // 23
    D4  // 24
};
map<reglas,set<token_ids>> mapaFirst;
map<reglas,set<token_ids>> mapaFollow;
int main(){
    mapaFirst[reglas::S] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF, 
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_FUNCTION, token_ids::PAL_RES_INPUT, 
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};


    // Regla B
    mapaFirst[reglas::B] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF, 
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_FUNCTION, token_ids::PAL_RES_INPUT, 
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};

    // Regla D
    mapaFirst[reglas::D] = {token_ids::PAL_RES_FUNCTION};

    // Regla T
    mapaFirst[reglas::T] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_INT, token_ids::PAL_RES_STRING};

    // Regla C
    mapaFirst[reglas::C] = {token_ids::PUNTO_Y_COMA, token_ids::OP_ASIGNACION_SUMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla R
    mapaFirst[reglas::R] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, token_ids::CADENA};

    // Regla U
    mapaFirst[reglas::U] = {token_ids::IDENTIFICADOR, token_ids::PAL_RES_INPUT, token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};

    // Regla F1
    mapaFirst[reglas::F1] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR};

    // Regla F2
    mapaFirst[reglas::F2] = {token_ids::IDENTIFICADOR};

    // Regla Q
    mapaFirst[reglas::Q] = { token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, 
                            token_ids::PAL_RES_IF, token_ids::PAL_RES_FOR, token_ids::PAL_RES_INPUT, 
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};
    // Regla H
    mapaFirst[reglas::H] = {token_ids::PAL_RES_VOID, token_ids::PAL_RES_BOOL, token_ids::PAL_RES_INT, token_ids::PAL_RES_STRING};

    // Regla D1
    mapaFirst[reglas::D1] = {token_ids::PAL_RES_VAR};  // Cambié lambda por un valor específico

    // Regla L
    mapaFirst[reglas::L] = {token_ids::OP_ASIGNACION_SUMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla R1
    mapaFirst[reglas::R1] = {token_ids::IDENTIFICADOR, token_ids::NUMERO, token_ids::CADENA};

    // Regla R2
    mapaFirst[reglas::R2] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_AND, 
                             token_ids::OP_ARITMETICO_RESTA, token_ids::OP_ARITMETICO_SUMA};

    // Regla A
    mapaFirst[reglas::A] = {token_ids::PARENTESIS_ABIERTA};  // Cambié lambda por un valor específico

    // Regla O
    mapaFirst[reglas::O] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_AND, 
                            token_ids::OP_ARITMETICO_RESTA, token_ids::OP_ARITMETICO_SUMA};

    // Regla A1
    mapaFirst[reglas::A1] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, 
                             token_ids::CADENA};  // Cambié lambda por un valor específico

    // Regla A2
    mapaFirst[reglas::A2] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, 
                             token_ids::NUMERO, token_ids::CADENA};

    // Regla A3
    mapaFirst[reglas::A3] = {token_ids::COMA};  // Cambié lambda por un valor específico

    // Regla U2
    mapaFirst[reglas::U2] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, 
                             token_ids::NUMERO, token_ids::CADENA};  // Cambié lambda por un valor específico

    // Regla U1
    mapaFirst[reglas::U1] = {token_ids::PARENTESIS_ABIERTA, token_ids::OP_ASIGNACION_SUMA, 
                             token_ids::OP_ASIGNACION_SIMPLE};  // Cambié lambda por un valor específico

    // Regla D2
    mapaFirst[reglas::D2] = {token_ids::PAL_RES_VAR};

    // Regla D3
    mapaFirst[reglas::D3] = {token_ids::PAL_RES_VAR};

    // Regla D4
    mapaFirst[reglas::D4] = {token_ids::COMA};

    // FOLLOW de A1
    mapaFollow[reglas::A1] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de A2
    mapaFollow[reglas::A2] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de A3
    mapaFollow[reglas::A3] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de U2
    mapaFollow[reglas::U2] = {token_ids::PUNTO_Y_COMA};  // ; 

    // FOLLOW de F1
    mapaFollow[reglas::F1] = {token_ids::PUNTO_Y_COMA};  // ; 

    // FOLLOW de F2
    mapaFollow[reglas::F2] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de R
    mapaFollow[reglas::R] = {token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA,token_ids::COMA};  // ) , ;

    // FOLLOW de R2
    mapaFollow[reglas::R2] = {token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA,token_ids::COMA};  // ) , ;

    // FOLLOW de R1
    mapaFollow[reglas::R1] = {token_ids::OP_LOGICO_AND, token_ids::PARENTESIS_CERRADA, token_ids::OP_ARITMETICO_SUMA, 
                              token_ids::COMA, token_ids::OP_ARITMETICO_RESTA, token_ids::PUNTO_Y_COMA, token_ids::OP_RELACIONAL_IGUAL};  // && ) + , - ; ==

    // FOLLOW de A
    mapaFollow[reglas::A] = {token_ids::OP_LOGICO_AND, token_ids::PARENTESIS_CERRADA, token_ids::OP_ARITMETICO_SUMA, 
                             token_ids::COMA, token_ids::OP_ARITMETICO_RESTA, token_ids::PUNTO_Y_COMA, token_ids::OP_RELACIONAL_IGUAL};  // && ) + , - ; ==

    // FOLLOW de D1
    mapaFollow[reglas::D1] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de D2
    mapaFollow[reglas::D2] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de D4
    mapaFollow[reglas::D4] = {token_ids::PARENTESIS_CERRADA};  // ) 

    // FOLLOW de Q
    mapaFollow[reglas::Q] = {token_ids::LLAVE_CERRADA}; // }
    return 0;
}

