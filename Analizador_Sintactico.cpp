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
#include "aux_enums.hpp"
#include "Analizador_Lexico.hpp"
#include <optional>

using namespace std;

map<reglas, set<token_ids>> mapaFirst;
map<reglas, set<token_ids>> mapaFollow;

AnalizadorLexico analizador("hola.txt");

int popularMapa()
{
    // Regla J
    mapaFirst[reglas::J] = {token_ids::OP_ARITMETICO_SUMA, token_ids::OP_ARITMETICO_RESTA};
    // Regla S
    mapaFirst[reglas::S] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF,
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_FUNCTION, token_ids::PAL_RES_INPUT,
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};

    // Regla B
    mapaFirst[reglas::B] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF,
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_INPUT,
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};

    // Regla D
    mapaFirst[reglas::D] = {token_ids::PAL_RES_FUNCTION};

    // Regla T
    mapaFirst[reglas::T] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_INT, token_ids::PAL_RES_STRING};

    // Regla C
    mapaFirst[reglas::C] = {token_ids::PUNTO_Y_COMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla R
    mapaFirst[reglas::R] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, token_ids::CADENA};
    // Regla R1
    mapaFirst[reglas::R1] = {token_ids::OP_LOGICO_ANDS};
    // Regla R2
    mapaFirst[reglas::R2] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, token_ids::CADENA};
    // Regla R3
    mapaFirst[reglas::R3] = {token_ids::OP_RELACIONAL_IGUAL};
    // Regla R4
    mapaFirst[reglas::R4] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, token_ids::CADENA};
    // Regla R5
    mapaFirst[reglas::R5] = {token_ids::OP_ARITMETICO_SUMA, token_ids::OP_ARITMETICO_RESTA};
    // Regla U
    mapaFirst[reglas::U] = {token_ids::IDENTIFICADOR, token_ids::PAL_RES_INPUT, token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};

    // Regla F1
    mapaFirst[reglas::F1] = {token_ids::IDENTIFICADOR};

    // Regla F2
    mapaFirst[reglas::F2] = {token_ids::IDENTIFICADOR};

    // Regla Q
    mapaFirst[reglas::Q] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR,
                            token_ids::PAL_RES_IF, token_ids::PAL_RES_FOR, token_ids::PAL_RES_INPUT,
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN};
    // Regla H
    mapaFirst[reglas::H] = {token_ids::PAL_RES_VOID, token_ids::PAL_RES_BOOL, token_ids::PAL_RES_INT, token_ids::PAL_RES_STRING};

    // Regla D1
    mapaFirst[reglas::D1] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_STRING, token_ids::PAL_RES_INT, token_ids::PAL_RES_VOID}; // Cambié lambda por un valor específico

    // Regla L
    mapaFirst[reglas::L] = {token_ids::OP_ASIGNACION_SUMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla A
    mapaFirst[reglas::A] = {token_ids::PARENTESIS_ABIERTA}; // Cambié lambda por un valor específico

    // Regla O
    mapaFirst[reglas::O] = {token_ids::PARENTESIS_ABIERTA, token_ids::CADENA, token_ids::IDENTIFICADOR, token_ids::NUMERO};

    // Regla A1
    mapaFirst[reglas::A1] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO,
                             token_ids::CADENA}; // Cambié lambda por un valor específico

    // Regla A2
    mapaFirst[reglas::A2] = {token_ids::COMA};

    // Regla U2
    mapaFirst[reglas::U2] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA,
                             token_ids::NUMERO, token_ids::CADENA}; // Cambié lambda por un valor específico

    // Regla U1
    mapaFirst[reglas::U1] = {token_ids::PARENTESIS_ABIERTA, token_ids::OP_ASIGNACION_SUMA,
                             token_ids::OP_ASIGNACION_SIMPLE}; // Cambié lambda por un valor específico

    // Regla D2
    mapaFirst[reglas::D2] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_STRING, token_ids::PAL_RES_INT};

    // Regla D3
    mapaFirst[reglas::D3] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_STRING, token_ids::PAL_RES_INT};

    // Regla D4
    mapaFirst[reglas::D4] = {token_ids::COMA};

    // FOLLOW de A1
    mapaFollow[reglas::A1] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de A2
    mapaFollow[reglas::A2] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de U2
    mapaFollow[reglas::U2] = {token_ids::PUNTO_Y_COMA}; // ;

    // FOLLOW de F1
    mapaFollow[reglas::F1] = {token_ids::PUNTO_Y_COMA}; // ;

    // FOLLOW de F2
    mapaFollow[reglas::F2] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de R
    mapaFollow[reglas::R] = {token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA}; // ) , ;
    // FOLLOW de R1
    mapaFollow[reglas::R1] = {token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA}; // ) , ;
    // FOLLOW de R2
    mapaFollow[reglas::R2] = {token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA}; // ) , ;
    // FOLLOW de R3
    mapaFollow[reglas::R3] = {token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA};
    // FOLLOW de R4
    mapaFollow[reglas::R4] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA};
    // FOLLOW de R5
    mapaFollow[reglas::R5] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA};
    // FOLLOW de O
    mapaFollow[reglas::O] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA,
                             token_ids::OP_ARITMETICO_RESTA, token_ids::OP_ARITMETICO_SUMA};
    // FOLLOW de A
    mapaFollow[reglas::A] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::PUNTO_Y_COMA, token_ids::COMA,
                             token_ids::OP_ARITMETICO_RESTA, token_ids::OP_ARITMETICO_SUMA};

    // FOLLOW de D1
    mapaFollow[reglas::D1] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de D2
    mapaFollow[reglas::D2] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de D4
    mapaFollow[reglas::D4] = {token_ids::PARENTESIS_CERRADA}; // )

    // FOLLOW de Q
    mapaFollow[reglas::Q] = {token_ids::LLAVE_CERRADA}; // }
    return 0;
}

token_ids str_to_token(string s)
{
    if (s == "LlaveAbierta")
    {
        return token_ids::LLAVE_ABIERTA;
    }
    else if (s == "LlaveCerrada")
    {
        return token_ids::LLAVE_CERRADA;
    }
    else if (s == "ParentesisAbierta")
    {
        return token_ids::PARENTESIS_ABIERTA;
    }
    else if (s == "ParentesisCerrada")
    {
        return token_ids::PARENTESIS_CERRADA;
    }
    else if (s == "ComaSimple")
    {
        return token_ids::COMA;
    }
    else if (s == "PuntoYComa")
    {
        return token_ids::PUNTO_Y_COMA;
    }
    else if (s == "OpRelacionalIgual")
    {
        return token_ids::OP_RELACIONAL_IGUAL;
    }
    else if (s == "OpLogicoAnd")
    {
        return token_ids::OP_LOGICO_ANDS;
    }
    else if (s == "OpAritmeticoResta")
    {
        return token_ids::OP_ARITMETICO_RESTA;
    }
    else if (s == "OpAritmeticoSuma")
    {
        return token_ids::OP_ARITMETICO_SUMA;
    }
    else if (s == "OpAsignacionSimple")
    {
        return token_ids::OP_ASIGNACION_SIMPLE;
    }
    else if (s == "OpAsignacionSuma")
    {
        return token_ids::OP_ASIGNACION_SUMA;
    }
    else if (s == "Cadena")
    {
        return token_ids::CADENA;
    }
    else if (s == "Numero")
    {
        return token_ids::NUMERO;
    }
    else if (s == "ID")
    {
        return token_ids::IDENTIFICADOR;
    }
    else if (s == "PalResBOOL")
    {
        return token_ids::PAL_RES_BOOL;
    }
    else if (s == "PalResFOR")
    {
        return token_ids::PAL_RES_FOR;
    }
    else if (s == "PalResFUNCTION")
    {
        return token_ids::PAL_RES_FUNCTION;
    }
    else if (s == "PalResIF")
    {
        return token_ids::PAL_RES_IF;
    }
    else if (s == "PalResINPUT")
    {
        return token_ids::PAL_RES_INPUT;
    }
    else if (s == "PalResOUTPUT")
    {
        return token_ids::PAL_RES_OUTPUT;
    }
    else if (s == "PalResRETURN")
    {
        return token_ids::PAL_RES_RETURN;
    }
    else if (s == "PalResSTRING")
    {
        return token_ids::PAL_RES_STRING;
    }
    else if (s == "PalResVAR")
    {
        return token_ids::PAL_RES_VAR;
    }
    else if (s == "PalResVOID")
    {
        return token_ids::PAL_RES_VOID;
    }
    else if (s == "PalResINT")
    {
        return token_ids::PAL_RES_INT;
    }
    else
    {
        return token_ids::ERROR_TOKEN_NOT_RECOGNIZED;
    }
}

ifstream token_file("token.txt", std::ios::binary);
ofstream parse_file("parse.txt", std::ios::binary);

// variables globales semanticas
bool zona_decl = false;
int despG = 0;
int despL = 0;
// tsg
int TSG = NULL;
// tsl
int TSL = NULL;



void error(token_ids token, reglas estado)
{
    // cerr << "TOKEN " << tokenToString(token) << " NO ACEPTADO EN EL ESTADO " << reglasToString(estado) <<endl;
    int linea = analizador.sintax_error(1);
    cout << "ERROR SINTACTICO EN LA LINEA " << linea << " CON EL TOKEN " << tokenToString(token) << endl;
    exit(0);
}




// Funciones semanticas

string BuscaTipo(string id){
    return "TIPO";
}
string BuscaTipoFuncParams(string id){
    return "TIPO,TIPO";
}
string BuscaTipoFuncRet(string id){
    return "TIPO";
}

void AñadeTipo(string id, string tipo){

}
void AñadeDespl(string id, int despl){

}
void AñadeTipoFunc(string id, string tipoParam, string tipoRet){

}
void AñadeEtiq(string id, string etiq){

}

int crearTabla(){
    return NULL;
}
void liberarTabla(int &tabla){
    tabla = NULL;
}

int etiqcounter = 0;
string nuevaetiq(){
    return "" + etiqcounter++;
}

// compara token actual con un token, lanza error y finaliza programa si no es y avanza al siguiente token si si es
bool equipara(Token &token, token_ids a_equiparar, reglas estado)
{
    if (token.id != a_equiparar)
    {
        int linea = analizador.sintax_error(1);
        cerr << "TOKEN " << tokenToString(token.id) << " NO ES IGUAL A " << tokenToString(a_equiparar) << "EN EL ESTADO "
             << reglasToString(estado) << " en la linea: " << linea << endl;
        exit(0);
    }
    // cout << tokenToString(token) << endl;
    token = analizador.processNextChar(); // avanzamos el token fuera de donde nos llamaron
    return true;
}

bool noTerminal(reglas NT, Token &token, map<string,string>* atrs_semanticos = nullptr)
{

    // cout << reglasToString(NT) << endl;
    // cout << atrs_semanticos << endl;

    // filestream_parse << NT_To_Parse(NT) << endl;

    switch (NT)
    {
    case reglas::S:
        /*
        S -> B S
        S -> D S
        S -> lambda
        */
        if (mapaFirst[reglas::B].find(token.id) != mapaFirst[reglas::B].end())
        {
            // S -> B S
            // token se encuentra en first de B
            parse_file << 1 << " ";
            map<string,string> B = {}; // para que no salte error
            noTerminal(reglas::B, token, &B);
            noTerminal(reglas::S, token);
        }
        else if (mapaFirst[reglas::D].find(token.id) != mapaFirst[reglas::D].end())
        {
            // S -> D S
            parse_file << 2 << " ";
            noTerminal(reglas::D, token);
            noTerminal(reglas::S, token);
        }
        else if (token.id == token_ids::ENDOFFILE)
        {
            // S -> lambda
            // regla lambda -> Ver si token € FOLLOW(S)
            // FOLLOW(S) = {$}
            // x € FOLLOW(S) es lo mismo que x == EOF
            // No hay que hacer nada, ya que no se avanza por ningun sitio
            parse_file << 3 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::B:
        /*
        B -> var T id C
        B -> if ( R ) U
        B -> U
        B -> for ( F1 ; R ; F2 ) { Q }
        */


        if (token.id == token_ids::PAL_RES_VAR)
        {
            // var T id C
            parse_file << 4 << " ";

            // semantico
            zona_decl = true;
            //finsemantico

            map<string,string> T = {};
                        
            equipara(token, token_ids::PAL_RES_VAR, NT); // compara, lanza error si no es y avanza un token
            noTerminal(reglas::T, token, &T);
            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);

            // semantico
            string idtipo = BuscaTipo(id);
            // El lexico debe de haber metido al token en la tabla que corresponde y lanzado error si ya existia en la tabla local (o global si no hay local)
            if(idtipo == "null"){ // Si el token en la TSL no tiene tipo
                AñadeTipo(id,T["tipo"]);
                if(TSL == NULL){
                    AñadeDespl(id,despG);
                    despG += stoi(T["ancho"]);
                }
                else{
                    AñadeDespl(id,despL);
                    despL += stoi(T["ancho"]);
                }
            }
            else{
                // cout << "ERROR SEMANTICO: LA VARIABLE YA HA SIDO DECLARADA" << endl;
                // exit(0);
            }
            zona_decl = false;
            //finsemantico
            
            map<string,string> C = {};

            noTerminal(reglas::C, token, &C );

            // semantico
            if(T["tipo"] != C["tipo"] && C["tipo"] != "vacio"){
                // cout << "ERROR SEMANTICO: LA VARIABLE ASIGNADA NO COINCIDE CON EL TIPO DE LA ASIGNACION" << endl;
                // exit(0);
            }
            
        }
        else if (token.id == token_ids::PAL_RES_IF)
        {
            // B -> if ( R ) U
            parse_file << 5 << " ";

            map<string,string> R = {};
            map<string,string> U = {};
            equipara(token, token_ids::PAL_RES_IF, NT);
            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            noTerminal(reglas::R, token, &R);

            // semantico
            U["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            if(R["tipo"] != "booleano"){
                // cout << "ERROR SEMANTICO: LA CONDICION TIENE QUE SER UNA EXPRESION BOOLEANA" << endl;
                // exit(0);
            }
            // finsemantico

            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            noTerminal(reglas::U, token, &U);
        }
        else if (mapaFirst[reglas::U].find(token.id) != mapaFirst[reglas::U].end())
        {
            // B -> U
            parse_file << 6 << " ";
            //semantico
            map<string,string> U = {};
            U["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            //finsemantico
            noTerminal(reglas::U, token, &U);
        }
        else if (token.id == token_ids::PAL_RES_FOR)
        {
            // B -> for ( F1 ; R ; F2 ) { Q }
            parse_file << 7 << " ";
            map<string,string> Q = {};
            Q["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            equipara(token, token_ids::PAL_RES_FOR, NT);
            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            noTerminal(reglas::F1, token);
            equipara(token, token_ids::PUNTO_Y_COMA, NT);

            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);

            //semantico
            if(R["tipo"]!="booleano"){
                // cout << "ERROR SEMANTICO: LA CONDICION TIENE QUE SER UNA EXPRESION BOOLEANA" << endl;
                // exit(0);
            }

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
            noTerminal(reglas::F2, token);
            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::LLAVE_ABIERTA, NT);
            noTerminal(reglas::Q, token, &Q);
            equipara(token, token_ids::LLAVE_CERRADA, NT);
        }
        else
        {
            cout << "hola";
            error(token.id, NT);
        }
        break;
    case reglas::D:
        /*
        D -> function H id ( D1 ) { Q }
        */
        if (token.id == token_ids::PAL_RES_FUNCTION)
        {
            // D -> function H id ( D1 ) { Q }
            parse_file << 8 << " ";


            equipara(token, token_ids::PAL_RES_FUNCTION, NT);

            //semantico
            zona_decl = true;
            //finsemantico

            map<string,string> H = {};
            map<string,string> Q = {};
            noTerminal(reglas::H, token, &H);
            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);

            //semantico
            TSL = crearTabla();
            despL = 0;
            //finsemantico

            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);

            map<string,string> D1 = {};
            noTerminal(reglas::D1, token, &D1);

            //semantico
            AñadeTipoFunc(id, D1["tipo"], H["tipo"]);
            AñadeEtiq(id,nuevaetiq());
            zona_decl = false;
            Q["tipo"] = H["tipo"];
            //finsemantico

            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::LLAVE_ABIERTA, NT);
            noTerminal(reglas::Q, token, &Q);
            equipara(token, token_ids::LLAVE_CERRADA, NT);

            //semantico
            liberarTabla(TSL);
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::H:
        /*
        H -> T
        H -> void
        */
        if (mapaFirst[reglas::T].find(token.id) != mapaFirst[reglas::T].end())
        {
            // H -> T
            parse_file << 9 << " ";

            map<string,string> T;
            noTerminal(reglas::T, token, &T);

            //semantico
            (*atrs_semanticos)["tipo"] = T["tipo"];
            //finsemantico
        }
        else if (token.id == token_ids::PAL_RES_VOID)
        {
            // H -> void
            parse_file << 10 << " ";
            equipara(token, token_ids::PAL_RES_VOID, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "void";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::T:
        /*
        T -> boolean
        T -> int
        T -> string
        */
        if (token.id == token_ids::PAL_RES_BOOL)
        {
            // T -> boolean
            parse_file << 11 << " ";
            equipara(token, token_ids::PAL_RES_BOOL, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "booleano";
            (*atrs_semanticos)["ancho"] = "1";
            //finsemantico            
        }
        else if (token.id == token_ids::PAL_RES_INT)
        {
            // T -> int
            parse_file << 12 << " ";
            equipara(token, token_ids::PAL_RES_INT, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "entero";
            (*atrs_semanticos)["ancho"] = "1";
            //finsemantico
        }
        else if (token.id == token_ids::PAL_RES_STRING)
        {
            // T -> string
            parse_file << 13 << " ";
            equipara(token, token_ids::PAL_RES_STRING, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "cadena";
            (*atrs_semanticos)["ancho"] = "64";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::C:
        /*
        C -> ;
        C -> = R ;
        */
        if (token.id == token_ids::PUNTO_Y_COMA)
        {
            // C -> ;
            parse_file << 14 << " ";
            equipara(token, token_ids::PUNTO_Y_COMA, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "vacio";
            //finsemantico
        }
        else if (token.id == token_ids::OP_ASIGNACION_SIMPLE)
        {
            // C -> = R ;
            parse_file << 15 << " ";
            equipara(token, token_ids::OP_ASIGNACION_SIMPLE, NT);
            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);

            //semantico
            (*atrs_semanticos)["tipo"] = R["tipo"];
            //finsemantico

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::L:
        /*
        L -> +=
        L -> =
        */
        if (token.id == token_ids::OP_ASIGNACION_SUMA)
        {
            // L -> +=
            parse_file << 16 << " ";

            equipara(token, token_ids::OP_ASIGNACION_SUMA, NT);

            //semantico
            (*atrs_semanticos)["operador"] = "suma";
            //finsemantico
        }
        else if (token.id == token_ids::OP_ASIGNACION_SIMPLE)
        {
            // L -> =
            parse_file << 17 << " ";
            equipara(token, token_ids::OP_ASIGNACION_SIMPLE, NT);
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::R:
        /*
        R -> R2 R1
        */
        if (mapaFirst[reglas::R2].find(token.id) != mapaFirst[reglas::R2].end())
        {
            // R -> R2 R1
            parse_file << 18 << " ";

            map<string,string> R2 = {};
            noTerminal(reglas::R2, token, &R2);
            map<string,string> R1 = {};

            //semantico
            R1["tipo"] = R2["tipo"]; // Le pasamos a R1 el tipo de R2 para que, en caso de que haya un and, comrpuebe si es booleana la parte de la izquierda o no
            // Esto es necesario para que se puedan leer los tipos de izquierda a derecha en caso de que haya varios ands
            //finsemantico

            noTerminal(reglas::R1, token, &R1);

            //semantico
            if(R1["tipo"] != "vacio"){
                (*atrs_semanticos)["tipo"] = "booleano";
            }
            else{
                (*atrs_semanticos)["tipo"] = R2["tipo"];
            }
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::R1:
        /*
       R1 -> && R2 R1
       R1 -> lambda
        */
        if (token.id == token_ids::OP_LOGICO_ANDS)
        {
            // R1 -> && R2 R1
            parse_file << 19 << " ";

            //semantico
            if((*atrs_semanticos)["tipo"] != "booleano"){
                // cout << "ERROR SEMANTICO: VALOR NO BOOLEANO EN UN AND" << endl;
            }
            //finsemantico

            equipara(token, token_ids::OP_LOGICO_ANDS, NT);
            map<string,string> R2 = {};
            noTerminal(reglas::R2, token, &R2);

            //semantico
            if(R2["tipo"] != "booleano"){
                // cout << "ERROR SEMANTICO: VALOR NO BOOLEANO EN UN AND EN LA PARTE DERECHA" << endl;
            }
            //nosemantico

            map<string,string> R1 = {};
            
            //semantico
            R1["tipo"] = "booleano"; // Si hay mas ands indicamos que la parte izquierda es (correctamente) booleana, ya que es el resultado de otro and
            //finsemantico

            noTerminal(reglas::R1, token, &R1);
        }
        else if (mapaFollow[reglas::R1].find(token.id) != mapaFollow[reglas::R1].end())
        {
            // R1 -> lambda
            parse_file << 20 << " ";
            
            //semantico
            (*atrs_semanticos)["tipo"] = "vacio";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::R2:
        /*
        R2 -> R4 R3
        */
        if (mapaFirst[reglas::R4].find(token.id) != mapaFirst[reglas::R4].end())
        {
            // R2 -> R4 R3
            parse_file << 21 << " ";

            map<string,string> R4 = {};
            map<string,string> R3 = {};
            noTerminal(reglas::R4, token, &R4);

            //semantico
            R3["tipo"] = R4["tipo"];
            //finsemantico

            noTerminal(reglas::R3, token, &R3);
            //semantico
            if(R3["tipo"] != "vacio"){
                (*atrs_semanticos)["tipo"] = "booleano";
            }
            else{
                (*atrs_semanticos)["tipo"] = R4["tipo"];
            }
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::R3:
        /*
        R3 -> == R4 R3
        R3 -> lambda
        */
        if (token.id == token_ids::OP_RELACIONAL_IGUAL)
        {
            // R3 -> == R4 R3
            parse_file << 22 << " ";

            equipara(token, token_ids::OP_RELACIONAL_IGUAL, NT);
            map<string,string> R4 = {};
            noTerminal(reglas::R4, token, &R4);
            map<string,string> R3 = {};
            
            //semantico
            if((*atrs_semanticos)["tipo"] != R4["tipo"]){
                // cout << "ERROR SEMANTICO: NO PUEDES IGUALAR DATOS DE DISTINTOS TIPOS" << endl;
                // exit(0);
            }
            R3["tipo"] = "booleano"; // Si sigue habiendo mas comparaciones (x == y == z) la parte izquierda va a ser el booleana porque es el resultado de una comparacion
            //finsemantico

            noTerminal(reglas::R3, token, &R3);
        }
        else if (mapaFollow[reglas::R3].find(token.id) != mapaFollow[reglas::R3].end())
        {
            // R3 -> lambda
            parse_file << 23 << " ";

            //semantico
            (*atrs_semanticos)["tipo"] = "vacio";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::R4:
        /*
        R4 -> O R5
        */
        if (mapaFirst[reglas::O].find(token.id) != mapaFirst[reglas::O].end())
        {
            // R4 -> O R5
            parse_file << 24 << " ";
            map<string,string> O = {};
            noTerminal(reglas::O, token, &O);
            map<string,string> R5 = {};

            //semantico
            R5["tipo"] = O["tipo"];
            (*atrs_semanticos)["tipo"] = O["tipo"];
            //finsemantico

            noTerminal(reglas::R5, token, &R5);
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::R5:
        /*
        R5 -> J O R5
        R5 -> lambda
        */
        if (mapaFirst[reglas::J].find(token.id) != mapaFirst[reglas::J].end())
        {
            // R5 -> J O R5
            parse_file << 25 << " ";

            if((*atrs_semanticos)["tipo"] != "entero"){
                // cout << "ERROR SEMANTICO: OPERACION ARITMETICA CON DATO NO ENTERO" << endl;
                // exit(0);
            }
            noTerminal(reglas::J, token);
            map<string,string> O = {};
            noTerminal(reglas::O, token, &O);
            map<string,string> R5 = {};

            //semantico
            if(O["tipo"] != "entero"){
                // cout << "ERROR SEMANTICO: OPERACION ARITMETICA CON DATO NO ENTERO A LA DERECHA" << endl;
                // exit(0);
            }
            R5["tipo"] = "entero"; // si hay mas operaciones aritmeticas la parte izquierda sera el resultado de otra op. aritm. -> entero
            //finsemantico

            noTerminal(reglas::R5, token, &R5);
        }
        else if (mapaFollow[reglas::R5].find(token.id) != mapaFollow[reglas::R5].end())
        {
            // R5 -> lambda
            parse_file << 26 << " ";

            //semantico
            (*atrs_semanticos)["tipo"] = "vacio";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::J:
        /*
        J -> +
        J -> -
        */
        if (token.id == token_ids::OP_ARITMETICO_SUMA)
        {
            // J -> +
            parse_file << 27 << " ";
            equipara(token, token_ids::OP_ARITMETICO_SUMA, NT);
        }
        else if (token.id == token_ids::OP_ARITMETICO_RESTA)
        {
            // J -> -
            parse_file << 28 << " ";
            equipara(token, token_ids::OP_ARITMETICO_RESTA, NT);
        }
        else
        {
            error(token.id, NT);
        }
        break;
    case reglas::O:
        /*
        O -> ( R )
        O -> id A
        O -> numero
        O -> cadena
        */
        if (token.id == token_ids::PARENTESIS_ABIERTA)
        {
            // O -> ( R )
            parse_file << 29 << " ";
            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);
            equipara(token, token_ids::PARENTESIS_CERRADA, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = R["tipo"];
            //finsemantico
        }
        else if (token.id == token_ids::IDENTIFICADOR)
        {
            // O -> id A
            parse_file << 30 << " ";
            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);
            map<string,string> A = {};
            noTerminal(reglas::A, token, &A);

            //semantico
            if(A["tipo"] != ""){ // Si a A SI se le ha asignado algun tipo 
                if(A["tipo"] == BuscaTipoFuncParams(id)){ // si los tipos de los argumentos coincide con el de los parametros
                    (*atrs_semanticos)["tipo"] = BuscaTipoFuncRet(id); // tipo de O es el tipo de retorno de la func
                }
                else{
                    // cout << "ERROR SEMANTICO: LOS PARAMETROS NO SON CORRECTOS PARA ESTA FUNCION" << endl;
                    // exit(0);
                }
            }
            else{
                // Entonces es una variable, no una func
                (*atrs_semanticos)["tipo"] = BuscaTipo(id);
            }
            //finsemantico
        }
        else if (token.id == token_ids::NUMERO)
        {
            // O -> numero
            parse_file << 31 << " ";
            equipara(token, token_ids::NUMERO, NT);
            
            //semantico
            (*atrs_semanticos)["tipo"] = "entero";
            //finsemantico
        }
        else if (token.id == token_ids::CADENA)
        {
            // O -> cadena
            parse_file << 32 << " ";
            equipara(token, token_ids::CADENA, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "cadena";
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::A:
        /*
        A -> ( A1 )
        A -> lambda
        */
        if (token.id == token_ids::PARENTESIS_ABIERTA)
        {
            // A -> ( A1 )
            parse_file << 33 << " ";
            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            map<string,string> A1 = {};
            noTerminal(reglas::A1, token, &A1);

            // semantico
            (*atrs_semanticos)["tipo"] = A1["tipo"];
            //finsemantico

            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
        }
        else if (mapaFollow[reglas::A].find(token.id) != mapaFollow[reglas::A].end())
        {
            // A -> lambda
            parse_file << 34 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::A1:
        /*
        A1 -> R A2
        A1 -> lambda
        */
        if (mapaFirst[reglas::R].find(token.id) != mapaFirst[reglas::R].end())
        {
            // A1 -> R A2
            parse_file << 35 << " ";
            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);
            map<string,string> A2 = {};
            noTerminal(reglas::A2, token, &A2);

            //semantico
            if(A2["tipo"] == ""){
                (*atrs_semanticos)["tipo"] = R["tipo"];
            }
            else{
                (*atrs_semanticos)["tipo"] = R["tipo"] + "," + A2["tipo"];
            }
            //finsemantico
        }
        else if (mapaFollow[reglas::A1].find(token.id) != mapaFollow[reglas::A1].end())
        {
            // A1 -> lambda
            parse_file << 36 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::A2:
        /*
        A2 -> , R A2
        A2 -> lambda
        */
        if (token.id == token_ids::COMA)
        {
            // A2 -> , R A2
            parse_file << 37 << " ";
            equipara(token, token_ids::COMA, NT);
            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);
            map<string,string> A2 = {};
            noTerminal(reglas::A2, token, &A2);

            //string
            if(A2["tipo"] == ""){
                (*atrs_semanticos)["tipo"] = R["tipo"];
            }
            else{
                (*atrs_semanticos)["tipo"] = R["tipo"] + "," + A2["tipo"];
            }
        }
        else if (mapaFollow[reglas::A2].find(token.id) != mapaFollow[reglas::A2].end())
        {
            // A2 -> lambda
            parse_file << 38 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::U:
        /*
        U -> input id ;
        U -> output R ;
        U -> return U2 ;
        U -> id U1
        */
        if (token.id == token_ids::PAL_RES_INPUT)
        {
            // U -> input id ;
            parse_file << 39 << " ";
            equipara(token, token_ids::PAL_RES_INPUT, NT);
            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);

            //semantico
            string tipo = BuscaTipo(id);
            if(tipo != "entero" && tipo != "cadena"){
                // cout << "ERROR SEMANTICO: SOLO SE PUEDEN LEER ENTEROS O CADENAS USANDO INPUT" << endl;
                // exit(0);
            }
            //finsemantico

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else if (token.id == token_ids::PAL_RES_OUTPUT)
        {
            // U -> output R ;
            parse_file << 40 << " ";
            equipara(token, token_ids::PAL_RES_OUTPUT, NT);
            map<string,string> R = {};
            noTerminal(reglas::R, token, &R);

            //semantico
            if(R["tipo"] != "entero" && R["tipo"] != "cadena"){
                // cout << "ERROR SEMANTICO: SOLO SE PUEDEN IMPRIMIR ENTEROS O CADENAS" << endl;
                // exit(0);
            }
            //finsemantico

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else if (token.id == token_ids::PAL_RES_RETURN)
        {
            // U -> return U2 ;
            parse_file << 41 << " ";
            equipara(token, token_ids::PAL_RES_RETURN, NT);

            //semantico
            map<string,string> U2 = {};
            U2["tipo"] = (*atrs_semanticos)["tipoRet"];
            if(TSL == NULL){
                // cout << "ERROR SEMANTICO: SOLO SE PUEDEN USAR RETURNS DENTRO DE FUNCIONES" << endl;
                // exit(0)
            }
            //finsemantico

            noTerminal(reglas::U2, token, &U2);

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else if (token.id == token_ids::IDENTIFICADOR)
        {
            // U -> id U1
            parse_file << 42 << " ";

            map<string,string> U1 = {};

            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);
            noTerminal(reglas::U1, token,&U1);

            if(U1["tipo"] != BuscaTipo(id)){
                // ERROR SEMANTICO
            }
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::U1:
        /*
        U1 -> L R ;
        U1 -> ( A1 ) ;
        */
        if (mapaFirst[reglas::L].find(token.id) != mapaFirst[reglas::L].end())
        {
            // U1 -> L R ;
            parse_file << 43 << " ";
            map<string,string> L = {};
            map<string,string> R = {};
            noTerminal(reglas::L, token,&L);
            noTerminal(reglas::R, token,&R);
            //semantico
            if(L["operador"] == "suma" && R["tipo"] != "entero"){
                // ERROR SEMANTICO
            }else{
                (*atrs_semanticos)["tipo"] = R["tipo"];
            }
            //fin semantico
            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else if (token.id == token_ids::PARENTESIS_ABIERTA)
        {
            // U1 -> ( A1 ) ;
            parse_file << 44 << " ";

            map<string,string> A1 = {};

            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            noTerminal(reglas::A1, token,&A1);
            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::PUNTO_Y_COMA, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = A1["tipo"];
            //finsemantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::U2:
        /*
        U2 -> R
        U2 -> lambda
        */
        if (mapaFirst[reglas::R].find(token.id) != mapaFirst[reglas::R].end())
        {
            // U2 -> R
            parse_file << 45 << " ";
            map<string,string> R = {};
            noTerminal(reglas::R, token,&R);

            //semantico
            if((*atrs_semanticos)["tipoRet"] != R["tipo"]){
                // cout << "El tipo del return no coincide con el valor de retorno de la funcion" ;
                // exit(0);
            }
            (*atrs_semanticos)["tipo"] = R["tipo"];
            //fin semantico
        }
        else if (mapaFollow[reglas::U2].find(token.id) != mapaFollow[reglas::U2].end())
        {
            // U2 -> lambda
            parse_file << 46 << " ";
            //semantico
            (*atrs_semanticos)["tipo"] = "void";
            //fin semantico
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::F1:
        /*
        F1 -> id = R
        F1 -> lambda
        */
        if (token.id == token_ids::IDENTIFICADOR)
        {
            // F1 -> id = R
            parse_file << 47 << " ";

            map<string,string> R = {};

            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);
            equipara(token, token_ids::OP_ASIGNACION_SIMPLE, NT);
            noTerminal(reglas::R, token,&R);

            //semantico
            if(R["tipo"] != BuscaTipo(id)){
                // ERROR SEMANTICO
            }
            //finsemantico
        }
        else if (mapaFollow[reglas::F1].find(token.id) != mapaFollow[reglas::F1].end())
        {
            // F1 -> lambda
            parse_file << 48 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::F2:
        /*
        F2 -> id L R
        F2 -> lambda
        */
        if (token.id == token_ids::IDENTIFICADOR)
        {
            // F2 -> id L R
            parse_file << 49 << " ";
            map<string,string> R = {};
            map<string,string> L = {};

            string id = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);
            noTerminal(reglas::L, token,&L);
            noTerminal(reglas::R, token,&R);

            //semantico
            if(L["operador"] == "suma" && R["tipo"] != "entero"){
                // ERROR SEMANTICO
            }

            if(R["tipo"] != BuscaTipo(id)){
                // ERROR SEMANTICO
            }
            //finsemantico
        }
        else if (mapaFollow[reglas::F2].find(token.id) != mapaFollow[reglas::F2].end())
        {
            // F2 -> lambda
            parse_file << 50 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::Q:
        /*
        Q -> B Q
        Q -> lambda
        */
        if (mapaFirst[reglas::B].find(token.id) != mapaFirst[reglas::B].end())
        {
            // Q -> B Q
            parse_file << 51 << " ";

            map<string,string> B = {};
            map<string,string> Q = {};
            //semantico
            B["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            Q["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            //finsemantico

            noTerminal(reglas::B, token, &B);
            noTerminal(reglas::Q, token, &Q);


            /*
            {
        B.tipoRet := Q.tipoRet
        Q'.tipoRet := Q.tipoRet
        }
        */
        }
        else if (mapaFollow[reglas::Q].find(token.id) != mapaFollow[reglas::Q].end())
        {
            // Q -> lambda
            parse_file << 52 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::D1:
        /*
        D1 -> D2
        D1 -> void
        */
        if (mapaFirst[reglas::D2].find(token.id) != mapaFirst[reglas::D2].end())
        {
            // D1 -> D2
            parse_file << 53 << " ";
            noTerminal(reglas::D2, token);
        }
        else if (token.id == token_ids::PAL_RES_VOID)
        {
            // D1 -> void
            parse_file << 54 << " ";
            equipara(token, token_ids::PAL_RES_VOID, NT);
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::D2:
        /*
        D2 -> D3 D4
        */
        if (mapaFirst[reglas::D3].find(token.id) != mapaFirst[reglas::D3].end())
        {
            // D2 -> D3 D4
            parse_file << 55 << " ";
            noTerminal(reglas::D3, token);
            noTerminal(reglas::D4, token);
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::D3:
        /*
        D3 -> T id
        */
        if (mapaFirst[reglas::T].find(token.id) != mapaFirst[reglas::T].end())
        {
            // D3 -> T id
            parse_file << 56 << " ";
            noTerminal(reglas::T, token);
            equipara(token, token_ids::IDENTIFICADOR, NT);
        }
        else
        {
            error(token.id, NT);
        }
        break;

    case reglas::D4:
        /*
        D4 -> , D2
        D4 -> lambda
        */
        if (token.id == token_ids::COMA)
        {
            // D4 -> , D2
            parse_file << 57 << " ";
            equipara(token, token_ids::COMA, NT);
            noTerminal(reglas::D2, token);
        }
        else if (mapaFollow[reglas::D4].find(token.id) != mapaFollow[reglas::D4].end())
        {
            // D4 -> lambda
            parse_file << 58 << " ";
        }
        else
        {
            error(token.id, NT);
        }
        break;

    default:
        cerr << "REGLA SIN MANEJAR" << endl;
        exit(0);
    }
    return true;
}

int main()
{
    popularMapa();
    reglas noTerminalState = reglas::S; // empieza en el axioma S
    Token token = analizador.processNextChar();
    parse_file << "descendente ";
    // cosas semanticas de S'
    // {TSG=CreaTabla(); desplG=0}
    noTerminal(noTerminalState, token);
    // {LiberaTabla(TSG)}
}
