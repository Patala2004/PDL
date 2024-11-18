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

using namespace std;




map<reglas,set<token_ids>> mapaFirst;
map<reglas,set<token_ids>> mapaFollow;

AnalizadorLexico analizador("hola.txt");

int popularMapa(){
    mapaFirst[reglas::S] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF, 
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_FUNCTION, token_ids::PAL_RES_INPUT, 
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN,token_ids::NUMERO, token_ids::CADENA};


    // Regla B
    mapaFirst[reglas::B] = {token_ids::PAL_RES_VAR, token_ids::IDENTIFICADOR, token_ids::PAL_RES_IF, 
                            token_ids::PAL_RES_FOR, token_ids::PAL_RES_INPUT, 
                            token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN,token_ids::NUMERO, token_ids::CADENA};

    // Regla D
    mapaFirst[reglas::D] = {token_ids::PAL_RES_FUNCTION};

    // Regla T
    mapaFirst[reglas::T] = {token_ids::PAL_RES_BOOL, token_ids::PAL_RES_INT, token_ids::PAL_RES_STRING};

    // Regla C
    mapaFirst[reglas::C] = {token_ids::PUNTO_Y_COMA, token_ids::OP_ASIGNACION_SUMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla R
    mapaFirst[reglas::R] = {token_ids::IDENTIFICADOR, token_ids::PARENTESIS_ABIERTA, token_ids::NUMERO, token_ids::CADENA};

    // Regla U
    mapaFirst[reglas::U] = {token_ids::IDENTIFICADOR, token_ids::PAL_RES_INPUT, token_ids::PAL_RES_OUTPUT, token_ids::PAL_RES_RETURN,token_ids::NUMERO, token_ids::CADENA};

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
    mapaFirst[reglas::D1] = {token_ids::PAL_RES_BOOL,token_ids::PAL_RES_STRING,token_ids::PAL_RES_INT,token_ids::PAL_RES_VOID};  // Cambié lambda por un valor específico

    // Regla L
    mapaFirst[reglas::L] = {token_ids::OP_ASIGNACION_SUMA, token_ids::OP_ASIGNACION_SIMPLE};

    // Regla R1
    mapaFirst[reglas::R1] = {token_ids::IDENTIFICADOR, token_ids::NUMERO, token_ids::CADENA, token_ids::PARENTESIS_ABIERTA};

    // Regla R2
    mapaFirst[reglas::R2] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, 
                             token_ids::OP_ARITMETICO_RESTA, token_ids::OP_ARITMETICO_SUMA};

    // Regla A
    mapaFirst[reglas::A] = {token_ids::PARENTESIS_ABIERTA};  // Cambié lambda por un valor específico

    // Regla O
    mapaFirst[reglas::O] = {token_ids::OP_RELACIONAL_IGUAL, token_ids::OP_LOGICO_ANDS, 
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
    mapaFirst[reglas::D2] = {token_ids::PAL_RES_BOOL,token_ids::PAL_RES_STRING,token_ids::PAL_RES_INT};

    // Regla D3
    mapaFirst[reglas::D3] = {token_ids::PAL_RES_BOOL,token_ids::PAL_RES_STRING,token_ids::PAL_RES_INT};

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
    mapaFollow[reglas::R1] = {token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::OP_ARITMETICO_SUMA, 
                              token_ids::COMA, token_ids::OP_ARITMETICO_RESTA, token_ids::PUNTO_Y_COMA, token_ids::OP_RELACIONAL_IGUAL};  // && ) + , - ; ==

    // FOLLOW de A
    mapaFollow[reglas::A] = {token_ids::OP_LOGICO_ANDS, token_ids::PARENTESIS_CERRADA, token_ids::OP_ARITMETICO_SUMA, 
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

token_ids str_to_token(string s){
    if(s == "LlaveAbierta"){
        return token_ids::LLAVE_ABIERTA;
    }
    else if(s == "LlaveCerrada"){
        return token_ids::LLAVE_CERRADA;
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
        return token_ids::OP_LOGICO_ANDS;
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


ifstream token_file("token.txt", std::ios::binary);
ofstream parse_file("parse.txt", std::ios::binary);


void error(token_ids token, reglas estado){
    //cerr << "TOKEN " << tokenToString(token) << " NO ACEPTADO EN EL ESTADO " << reglasToString(estado) <<endl;
    int linea = analizador.sintax_error(1);
    cout << "ERROR SINTACTICO EN LA LINEA " << linea << " CON EL TOKEN " << tokenToString(token) << endl;
    exit(0);
}


// compara token actual con un token, lanza error y finaliza programa si no es y avanza al siguiente token si si es 
bool equipara(token_ids& token, token_ids a_equiparar, reglas estado){
    if(token != a_equiparar){
        cerr << "TOKEN " << tokenToString(token) << " NO ES IGUAL A " << tokenToString(a_equiparar) << "EN EL ESTADO "
        << reglasToString(estado) <<endl;
        exit(0);
    }
    //cout << tokenToString(token) << endl;
    token = analizador.processNextChar(); // avanzamos el token fuera de donde nos llamaron
    return true;
}

bool noTerminal(reglas NT, token_ids& token){

    // filestream_parse << NT_To_Parse(NT) << endl;

    switch(NT){
        case reglas::S:
            /*
            S -> B S
            S -> D S 
            S -> lambda
            */
            if(mapaFirst[reglas::B].find(token) != mapaFirst[reglas::B].end()){
                // S -> B S
                // token se encuentra en first de B
                parse_file << 1 << " ";
                noTerminal(reglas::B, token);
                noTerminal(reglas::S, token);
            }
            else if(mapaFirst[reglas::D].find(token) != mapaFirst[reglas::D].end()){
                // S -> D S 
                parse_file << 2 << " ";
                noTerminal(reglas::D, token);
                noTerminal(reglas::S, token);
            }
            else if(token == token_ids::ENDOFFILE){
                // S -> lambda
                // regla lambda -> Ver si token € FOLLOW(S)
                // FOLLOW(S) = {$}
                // x € FOLLOW(S) es lo mismo que x == EOF
                // No hay que hacer nada, ya que no se avanza por ningun sitio
                parse_file << 3 << " ";
            }
            else{
                error(token, NT);
            }
            break;
        case reglas::B:
            /*
            B -> var T id C 
            B -> if ( R ) U
            B -> U
            B -> for ( F1 ; R ; F2 ) { Q }
            */
            if(token == token_ids::PAL_RES_VAR){
                // var T id C
                parse_file << 4 << " ";
                equipara(token, token_ids::PAL_RES_VAR, NT); // compara, lanza error si no es y avanza un token
                noTerminal(reglas::T, token);
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::C, token);
            }
            else if(token == token_ids::PAL_RES_IF){
                // B -> if ( R ) U
                parse_file << 5 << " ";
                equipara(token, token_ids::PAL_RES_IF, NT);
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
                noTerminal(reglas::U, token);
            }
            else if(mapaFirst[reglas::U].find(token) != mapaFirst[reglas::U].end()){
                // B -> U
                parse_file << 6 << " ";
                noTerminal(reglas::U, token);
            }
            else if(token == token_ids::PAL_RES_FOR){
                // B -> for ( F1 ; R ; F2 ) { Q }
                parse_file << 7 << " ";
                equipara(token, token_ids::PAL_RES_FOR, NT);
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::F1, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
                noTerminal(reglas::F2, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
                equipara(token, token_ids::LLAVE_ABIERTA, NT);
                noTerminal(reglas::Q, token);
                equipara(token, token_ids::LLAVE_CERRADA, NT);
            }
            else{
                cout << "hola";
                error(token, NT);
            }
            break;
        case reglas::D:
            /*
            D -> function H id ( D1 ) { Q }
            */
            if(token == token_ids::PAL_RES_FUNCTION){
                // D -> function H id ( D1 ) { Q }
                parse_file << 8 << " ";
                equipara(token, token_ids::PAL_RES_FUNCTION, NT);
                noTerminal(reglas::H, token);
                equipara(token, token_ids::IDENTIFICADOR, NT);
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::D1, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
                equipara(token, token_ids::LLAVE_ABIERTA, NT);
                noTerminal(reglas::Q, token);
                equipara(token, token_ids::LLAVE_CERRADA, NT);
            }
            else{
                error(token, NT);
            }
            break;
        case reglas::H:
                /*
                H -> T
                H -> void
                */
            if(mapaFirst[reglas::T].find(token) != mapaFirst[reglas::T].end()){
                // H -> T
                parse_file << 9 << " ";
                noTerminal(reglas::T, token);
            }
            else if(token == token_ids::PAL_RES_VOID){
                // H -> void
                parse_file << 10 << " ";
                equipara(token, token_ids::PAL_RES_VOID, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::T:
            /*
            T -> boolean
            T -> int
            T -> string
            */
            if(token == token_ids::PAL_RES_BOOL){
                // T -> boolean
                parse_file << 11 << " ";
                equipara(token, token_ids::PAL_RES_BOOL, NT);
            }
            else if(token == token_ids::PAL_RES_INT){
                // T -> int
                parse_file << 12 << " ";
                equipara(token, token_ids::PAL_RES_INT, NT);
            }
            else if(token == token_ids::PAL_RES_STRING){
                // T -> string
                parse_file << 13 << " ";
                equipara(token, token_ids::PAL_RES_STRING, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::C:
            /*
            C -> ; 
            C -> L R ;
            */
            if(token == token_ids::PUNTO_Y_COMA){
                // C -> ; 
                parse_file << 14 << " ";
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(mapaFirst[reglas::L].find(token) != mapaFirst[reglas::L].end()){
                // C -> L R ;
                parse_file << 15 << " ";
                noTerminal(reglas::L, token);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::L:
            /*
            L -> += 
            L -> =
            */
            if(token == token_ids::OP_ASIGNACION_SUMA){
                // L -> += 
                parse_file << 16 << " ";
                equipara(token, token_ids::OP_ASIGNACION_SUMA, NT);
            }
            else if(token == token_ids::OP_ASIGNACION_SIMPLE){
                // L -> =
                parse_file << 17 << " ";
                equipara(token, token_ids::OP_ASIGNACION_SIMPLE, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::R:
            /*
            R -> R1 R2
            */
            if(mapaFirst[reglas::R1].find(token) != mapaFirst[reglas::R1].end()){
                // R -> R1 R2
                parse_file << 18 << " ";
                noTerminal(reglas::R1, token);
                noTerminal(reglas::R2, token);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::R1:
            /*
            R1 -> ( R )
            R1 -> id A 
            R1 -> numero 
            R1 -> cadena
            */
            if(token == token_ids::PARENTESIS_ABIERTA){
                // R1 -> ( R )
                parse_file << 19 << " ";
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            }
            else if(token == token_ids::IDENTIFICADOR){
                // R1 -> id A 
                parse_file << 20 << " ";
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::A, token);
            }
            else if(token == token_ids::NUMERO){
                // R1 -> numero 
                parse_file << 21 << " ";
                equipara(token, token_ids::NUMERO, NT);
            }
            else if(token == token_ids::CADENA){
                // R1 -> cadena
                parse_file << 22 << " ";
                equipara(token, token_ids::CADENA, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::R2:
            /*
            R2 -> O R 
            R2 -> lambda
            */
            if(mapaFirst[reglas::O].find(token) != mapaFirst[reglas::O].end()){
                // R2 -> O R 
                parse_file << 23 << " ";
                noTerminal(reglas::O, token);
                noTerminal(reglas::R, token);
            }
            else if(mapaFollow[reglas::R2].find(token) != mapaFollow[reglas::R2].end()){
                // R2 -> lambda
                parse_file << 24 << " ";
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::O:
            /*
            O -> == 
            O -> && 
            O -> + 
            O -> -
            */
            if(token == token_ids::OP_RELACIONAL_IGUAL){
                // O -> == 
                parse_file << 25 << " ";
                equipara(token, token_ids::OP_RELACIONAL_IGUAL, NT);
            }
            else if(token == token_ids::OP_LOGICO_ANDS){
                // O -> && 
                parse_file << 26 << " ";
                equipara(token, token_ids::OP_LOGICO_ANDS, NT);
            }
            else if(token == token_ids::OP_ARITMETICO_SUMA){
                // O -> + 
                parse_file << 27 << " ";
                equipara(token, token_ids::OP_ARITMETICO_SUMA, NT);
            }
            else if(token == token_ids::OP_ARITMETICO_RESTA){
                // O -> -
                parse_file << 28 << " ";
                equipara(token, token_ids::OP_ARITMETICO_RESTA, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::A:
            /*
            A -> ( A1 ) 
            A -> lambda
            */ 
            if(token == token_ids::PARENTESIS_ABIERTA){
                // A -> ( A1 )
                parse_file << 29 << " ";
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::A1, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            }
            else if(mapaFollow[reglas::A].find(token) != mapaFollow[reglas::A].end()){
                // A -> lambda
                parse_file << 30 << " ";
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::A1:
            /*
            A1 -> A2 
            A1 -> lambda
            */
            if(mapaFirst[reglas::A2].find(token) != mapaFirst[reglas::A2].end()){
                // A1 -> A2 
                parse_file << 31 << " ";
                noTerminal(reglas::A2, token);
            }
            else if(mapaFollow[reglas::A1].find(token) != mapaFollow[reglas::A1].end()){
                // A1 -> lambda
                parse_file << 32 << " ";
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::A2:
            /*
            A2 -> R A3
            */
            if(mapaFirst[reglas::R].find(token) != mapaFirst[reglas::R].end()){
                // A2 -> R A3
                parse_file << 33 << " ";
                noTerminal(reglas::R, token);
                noTerminal(reglas::A3, token);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::A3:
            /*
            A3 -> , A2
            A3 -> lambda
            */
            if(token == token_ids::COMA){
                // A3 -> , A2
                parse_file << 34 << " ";
                equipara(token, token_ids::COMA, NT);
                noTerminal(reglas::A2, token);
            }
            else if(mapaFollow[reglas::A3].find(token) != mapaFollow[reglas::A3].end()){
                // A3 -> lambda
                parse_file << 35 << " ";
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::U:
            /*
            U -> cadena R2 ;
            U -> numero R2 ;
            U -> input id ; 
            U -> output R ; 
            U -> return U2 ; 
            U -> id U1
            */
            if(token == token_ids::CADENA){
                //U -> cadena R2 ;
                parse_file << 36 << " ";
                equipara(token, token_ids::CADENA, NT);
                noTerminal(reglas::R2, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::NUMERO){
                //U -> numero R2 ;
                parse_file << 37 << " ";
                equipara(token, token_ids::NUMERO, NT);
                noTerminal(reglas::R2, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::PAL_RES_INPUT){
                // U -> input id ; 
                parse_file << 38 << " ";
                equipara(token, token_ids::PAL_RES_INPUT, NT);
                equipara(token, token_ids::IDENTIFICADOR, NT);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::PAL_RES_OUTPUT){
                // U -> output R ; 
                parse_file << 39 << " ";
                equipara(token, token_ids::PAL_RES_OUTPUT, NT);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::PAL_RES_RETURN){
                // U -> return U2 ; 
                parse_file << 40 << " ";
                equipara(token, token_ids::PAL_RES_RETURN, NT);
                noTerminal(reglas::U2, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::IDENTIFICADOR){
                // U -> id U1
                parse_file << 41 << " ";
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::U1, token);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::U1:
            /*
            U1 -> L R ; 
            U1 -> ( A1 ) ;
            */
            if(mapaFirst[reglas::L].find(token) != mapaFirst[reglas::L].end()){
                // U1 -> L R ; 
                parse_file << 42 << " ";
                noTerminal(reglas::L, token);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else if(token == token_ids::PARENTESIS_ABIERTA){
                // U1 -> ( A1 ) ;
                parse_file << 43 << " ";
                equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
                noTerminal(reglas::A1, token);
                equipara(token, token_ids::PARENTESIS_CERRADA, NT);
                equipara(token, token_ids::PUNTO_Y_COMA, NT);
            }
            else{
                error(token, NT);
            }
            break;

        case reglas::U2:
            /*
            U2 -> R
            U2 -> lambda
            */
            if(mapaFirst[reglas::R].find(token) != mapaFirst[reglas::R].end()){
                // U2 -> R
                parse_file << 44 << " ";
                noTerminal(reglas::R, token);
            }
            else if(mapaFollow[reglas::U2].find(token) != mapaFollow[reglas::U2].end()){
                // U2 -> lambda
                parse_file << 45 << " ";
            }
            else{
                error(token, NT);
            }     
            break;       

        case reglas::F1:
            /*
            F1 -> var T id L R 
            F1 -> id L R 
            F1 -> lambda
            */
            if(token == token_ids::PAL_RES_VAR){
                // F1 -> var T id L R 
                parse_file << 46 << " ";
                equipara(token, token_ids::PAL_RES_VAR, NT);
                noTerminal(reglas::T, token);
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::L, token);
                noTerminal(reglas::R, token);
            }       
            else if(token == token_ids::IDENTIFICADOR){
                // F1 -> id L R 
                parse_file << 47 << " ";
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::L, token);
                noTerminal(reglas::R, token);
            }
            else if(mapaFollow[reglas::F1].find(token) != mapaFollow[reglas::F1].end()){
                // F1 -> lambda
                parse_file << 48 << " ";
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::F2:
            /*
            F2 -> id L R 
            F2 -> lambda
            */
            if(token == token_ids::IDENTIFICADOR){
                // F2 -> id L R 
                parse_file << 49 << " ";
                equipara(token, token_ids::IDENTIFICADOR, NT);
                noTerminal(reglas::L, token);
                noTerminal(reglas::R, token);
            }
            else if(mapaFollow[reglas::F2].find(token) != mapaFollow[reglas::F2].end()){
                // F2 -> lambda
                parse_file << 50 << " ";
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::Q:
            /*
            Q -> B Q 
            Q -> lambda
            */
            if(mapaFirst[reglas::B].find(token) != mapaFirst[reglas::B].end()){
                // Q -> B Q 
                parse_file << 51 << " ";
                noTerminal(reglas::B, token);
                noTerminal(reglas::Q, token);
            }
            else if(mapaFollow[reglas::Q].find(token) != mapaFollow[reglas::Q].end()){
                // Q -> lambda
                parse_file << 52 << " ";
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::D1:
            /*
            D1 -> D2
            D1 -> void
            */
            if(mapaFirst[reglas::D2].find(token) != mapaFirst[reglas::D2].end()){
                // D1 -> D2
                parse_file << 53 << " ";
                noTerminal(reglas::D2, token);
            }
            else if(token == token_ids::PAL_RES_VOID){
                // D1 -> void
                parse_file << 54 << " ";
                equipara(token, token_ids::PAL_RES_VOID, NT);
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::D2:
            /*
            D2 -> D3 D4
            */
            if(mapaFirst[reglas::D3].find(token) != mapaFirst[reglas::D3].end()){
                // D2 -> D3 D4
                parse_file << 55 << " ";
                noTerminal(reglas::D3, token);
                noTerminal(reglas::D4, token);
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::D3:
            /*
            D3 -> T id
            */
            if(mapaFirst[reglas::T].find(token) != mapaFirst[reglas::T].end()){
                // D3 -> T id
                parse_file << 56 << " ";
                noTerminal(reglas::T, token);
                equipara(token, token_ids::IDENTIFICADOR, NT);
            }
            else{
                error(token, NT);
            }  
            break;

        case reglas::D4:
            /*
            D4 -> , D2
            D4 -> lambda
            */
            if(token == token_ids::COMA){
                // D4 -> , D2
                parse_file << 57 << " ";
                equipara(token, token_ids::COMA, NT);
                noTerminal(reglas::D2, token);
            }
            else if(mapaFollow[reglas::D4].find(token) != mapaFollow[reglas::D4].end()){
                // D4 -> lambda
                parse_file << 58 << " ";
            }
            else{
                error(token, NT);
            }  
            break;

        default:
            cerr << "REGLA SIN MANEJAR" << endl;
            exit(0);
        
    }
    return true;
}



int main(){
    popularMapa();
    reglas noTerminalState = reglas::S; // empieza en el axioma S
    token_ids token = analizador.processNextChar();
    parse_file << "descendente ";
    noTerminal(noTerminalState, token);
}