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

