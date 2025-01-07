#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <variant>
#include "aux_enums.hpp"

using namespace std;




    


// Function to convert enum to string
std::string tokenToString(token_ids id) {
    switch (id) {
        case token_ids::LLAVE_ABIERTA: return "LlaveAbierta";
        case token_ids::LLAVE_CERRADA: return "LlaveCerrada";
        case token_ids::PARENTESIS_ABIERTA: return "ParentesisAbierta";
        case token_ids::PARENTESIS_CERRADA: return "ParentesisCerrada";
        case token_ids::COMA: return "ComaSimple";
        case token_ids::PUNTO_Y_COMA: return "PuntoYComa";
        case token_ids::OP_RELACIONAL_IGUAL: return "OpRelacionalIgual";
        case token_ids::OP_LOGICO_ANDS: return "OpLogicoAnd";
        case token_ids::OP_ARITMETICO_RESTA: return "OpAritmeticoResta";
        case token_ids::OP_ARITMETICO_SUMA: return "OpAritmeticoSuma";
        case token_ids::OP_ASIGNACION_SIMPLE: return "OpAsignacionSimple";
        case token_ids::OP_ASIGNACION_SUMA: return "OpAsignacionSuma";
        case token_ids::CADENA: return "Cadena";
        case token_ids::NUMERO: return "Numero";
        case token_ids::IDENTIFICADOR: return "ID";
        case token_ids::PAL_RES_BOOL: return "PalResBOOL";
        case token_ids::PAL_RES_FOR: return "PalResFOR";
        case token_ids::PAL_RES_FUNCTION: return "PalResFUNCTION";
        case token_ids::PAL_RES_IF: return "PalResIF";
        case token_ids::PAL_RES_INPUT: return "PalResINPUT";
        case token_ids::PAL_RES_OUTPUT: return "PalResOUTPUT";
        case token_ids::PAL_RES_RETURN: return "PalResRETURN";
        case token_ids::PAL_RES_STRING: return "PalResSTRING";
        case token_ids::PAL_RES_VAR: return "PalResVAR";
        case token_ids::PAL_RES_VOID: return "PalResVOID";
        case token_ids::PAL_RES_INT: return "PalResINT";
        default: return "UNKNOWN";
    }
}


string reglasToString(reglas r){
    switch(r){
        case reglas::S:     return "S";
        case reglas::B:     return "B";
        case reglas::D:     return "D";
        case reglas::T:     return "T";
        case reglas::C:     return "C";
        case reglas::R:     return "R";
        case reglas::U:     return "U";
        case reglas::F1:    return "F1";
        case reglas::F2:    return "F2";
        case reglas::Q:     return "Q";
        case reglas::H:     return "H";
        case reglas::D1:    return "D1";
        case reglas::L:     return "L";
        case reglas::R1:    return "R1";
        case reglas::R2:    return "R2";
        case reglas::A:     return "A";
        case reglas::O:     return "O";
        case reglas::A1:    return "A1";
        case reglas::A2:    return "A2";
        case reglas::U2:    return "U2";
        case reglas::U1:    return "U1";
        case reglas::D2:    return "D2";
        case reglas::D3:    return "D3";
        case reglas::D4:    return "D4";
        case reglas::J:     return "J";
        case reglas::R3:    return "R3";
        case reglas::R4:    return "R4";
        case reglas::R5:    return "R5";
        default: return "ERROR ESTADO NO ENCONTRADO";
    }
}