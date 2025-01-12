#ifndef TOKEN_UTILS_HPP
#define TOKEN_UTILS_HPP

#include <string>
#include <variant>

using namespace std;


// Enumeration of token IDs
enum class token_ids
{
    LLAVE_ABIERTA,        // {
    LLAVE_CERRADA,        // }
    PARENTESIS_ABIERTA,   // (
    PARENTESIS_CERRADA,   // )
    COMA,                 // ,
    PUNTO_Y_COMA,         // ;
    OP_RELACIONAL_IGUAL,  // ==
    OP_LOGICO_ANDS,       // &&
    OP_ARITMETICO_RESTA,  // -
    OP_ARITMETICO_SUMA,   // +
    OP_ASIGNACION_SIMPLE, // =
    OP_ASIGNACION_SUMA,   // +=
    CADENA,               // "..."
    NUMERO,               // 0123456789
    IDENTIFICADOR,        // varx
    // Palabras reservadas:
    PAL_RES_BOOL,     // boolean
    PAL_RES_FOR,      // for
    PAL_RES_FUNCTION, // function
    PAL_RES_IF,       // if
    PAL_RES_INPUT,    // input
    PAL_RES_OUTPUT,   // output
    PAL_RES_RETURN,   // return
    PAL_RES_STRING,   // string
    PAL_RES_VAR,      // var
    PAL_RES_VOID,     // void
    PAL_RES_INT,
    ERROR_TOKEN_NOT_RECOGNIZED,
    ENDOFFILE
};

class Token
{
    public:
    token_ids id;
    variant<int,string,float> valor;

    Token(token_ids token_id, int value) : id(token_id), valor(value) {}
    Token(token_ids token_id, string value) : id(token_id), valor(value) {}
    Token(token_ids token_id, float value) : id(token_id), valor(value) {}
    Token(token_ids token_id) : id(token_id), valor("") {};
};

// Function to convert token_ids to string
std::string tokenToString(token_ids id);

std::string tokenToString2(token_ids id);


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
    R3, // 15
    R4, // 16
    R5, // 17
    A,  // 18
    O,  // 19
    A1, // 20
    A2, // 21
    U2, // 22
    U1, // 23
    D2, // 24
    D3, // 25
    D4,  // 26
    J // 27 
};

string reglasToString(reglas r);

#endif // TOKEN_UTILS_HPP