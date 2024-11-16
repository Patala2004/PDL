#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>

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

token_ids str_to_token(string s){
    if(s == "LlaveAbierta"){
        return token_ids::LLAVE_CERRADA;
    }
    else if(s == "LlaveCerrada"){
        return token_ids::LLAVE_ABIERTA;
    }
    else if(s == "ParentesisAbierta"){
        return token_ids::PARENTESIS_ABIERTA;
    }
    else if(s == "ParentesisCerrada"){
        return token_ids::PARENTESIS_CERRADA;
    }
    else if(s == "ComaSimple"){
        return token_ids::COMA;
    }
    else if(s == "PuntoYComa"){
        return token_ids::PUNTO_Y_COMA;
    }
    else if(s == "OpRelacionalIgual"){
        return token_ids::OP_RELACIONAL_IGUAL;
    }
    else if(s == "OpLogicoAnd"){
        return token_ids::OP_LOGICO_AND;
    }
    else if(s == "OpAritmeticoResta"){
        return token_ids::OP_ARITMETICO_RESTA;
    }
    else if(s == "OpAritmeticoSuma"){
        return token_ids::OP_ARITMETICO_SUMA;
    }
    else if(s == "OpAsignacionSimple"){
        return token_ids::OP_ASIGNACION_SIMPLE;
    }
    else if(s == "OpAsignacionSuma"){
        return token_ids::OP_ASIGNACION_SUMA;
    }
    else if(s == "Cadena"){
        return token_ids::CADENA;
    }
    else if(s == "Numero"){
        return token_ids::NUMERO;
    }
    else if(s == "ID"){
        return token_ids::IDENTIFICADOR;
    }
    else if(s == "PalResBOOL"){
        return token_ids::PAL_RES_BOOL;
    }
    else if(s == "PalResFOR"){
        return token_ids::PAL_RES_FOR;
    }
    else if(s == "PalResFUNCTION"){
        return token_ids::PAL_RES_FUNCTION;
    }
    else if(s == "PalResIF"){
        return token_ids::PAL_RES_IF;
    }
    else if(s == "PalResINPUT"){
        return token_ids::PAL_RES_INPUT;
    }
    else if(s == "PalResOUTPUT"){
        return token_ids::PAL_RES_OUTPUT;
    }
    else if(s == "PalResRETURN"){
        return token_ids::PAL_RES_RETURN;
    }
    else if(s == "PalResSTRING"){
        return token_ids::PAL_RES_STRING;
    }
    else if(s == "PalResVAR"){
        return token_ids::PAL_RES_VAR;
    }
    else if(s == "PalResVOID"){
        return token_ids::PAL_RES_VOID;
    }
    else if(s == "PalResINT"){
        return token_ids::PAL_RES_INT;
    }
    else{
        return token_ids::ERROR_TOKEN_NOT_RECOGNIZED;
    }
}


token_ids getToken(std::ifstream& token_file){
    string token;
    if(!getline(token_file, token)){
        return token_ids::ENDOFFILE;
    }
    token = token.substr(1, token.size() - 2);
    token = token.substr(0, token.find(','));
    return str_to_token(token);
}



int main(){
    std::ifstream token_file("token.txt", std::ios::binary);
    string noTerminalState = "S";
    while(getToken(token_file) != token_ids::ENDOFFILE){
        if(noTerminalState == "S"){

        }
        else if(noTerminalState == "B"){

        }
        else if(noTerminalState == "D"){

        }
        else if(noTerminalState == "H"){

        }
        else if(noTerminalState == "T"){

        }
        else if(noTerminalState == "C"){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
        else if(noTerminalState == ""){

        }
    }
}