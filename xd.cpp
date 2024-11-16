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
std::string tokenToString(token_ids id) {
    switch (id) {
        case token_ids::LLAVE_ABIERTA: return "LlaveAbierta";
        case token_ids::LLAVE_CERRADA: return "LlaveCerrada";
        case token_ids::PARENTESIS_ABIERTA: return "ParentesisAbierta";
        case token_ids::PARENTESIS_CERRADA: return "ParentesisCerrada";
        case token_ids::COMA: return "ComaSimple";
        case token_ids::PUNTO_Y_COMA: return "PuntoYComa";
        case token_ids::OP_RELACIONAL_IGUAL: return "OpRelacionalIgual";
        case token_ids::OP_LOGICO_AND: return "OpLogicoAnd";
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

ifstream token_file("token.txt", std::ios::binary);

token_ids getToken(std::ifstream& token_file){
    string token;
    if(!getline(token_file, token)){
        return token_ids::ENDOFFILE;
    }
    token = token.substr(1, token.size() - 2);
    token = token.substr(0, token.find(','));
    //cout << token << endl;
    return str_to_token(token);
}

void error(){
    cerr << "ERROR, TOKEN NO ACEPTADO" << endl;
    exit(0);
}


// compara token actual con un token, lanza error y finaliza programa si no es y avanza al siguiente token si si es 
bool equipara(token_ids& token, token_ids a_equiparar){
    if(token != a_equiparar){
        error();
    }
    cout << tokenToString(token) << endl;
    token = getToken(token_file); // avanzamos el token fuera de donde nos llamaron
}

bool noTerminal(reglas NT, token_ids& token){
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
                noTerminal(reglas::B, token);
                noTerminal(reglas::S, token);
            }
            else if(mapaFirst[reglas::B].find(token) != mapaFirst[reglas::B].end()){
                // S -> D S 
                noTerminal(reglas::D, token);
                noTerminal(reglas::S, token);
            }
            else if(token == token_ids::ENDOFFILE){
                // S -> lambda
                // regla lambda -> Ver si token € FOLLOW(S)
                // FOLLOW(S) = {$}
                // x € FOLLOW(S) es lo mismo que x == EOF
                // No hay que hacer nada, ya que no se avanza por ningun sitio
            }
            else{
                error();
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
                equipara(token, token_ids::PAL_RES_VAR); // compara, lanza error si no es y avanza un token
                noTerminal(reglas::T, token);
                equipara(token, token_ids::IDENTIFICADOR);
                noTerminal(reglas::C, token);
            }
            else if(token == token_ids::PAL_RES_IF){
                // B -> if ( R ) U
                equipara(token, token_ids::PAL_RES_IF);
                equipara(token, token_ids::PARENTESIS_ABIERTA);
                noTerminal(reglas::R, token);
                equipara(token, token_ids::PARENTESIS_CERRADA);
                noTerminal(reglas::U, token);
            }
            else if(mapaFirst[reglas::U].find(token) != mapaFirst[reglas::U].end()){
                // B -> U
            }
            else if(token == token_ids::PAL_RES_FOR){
                // B -> for ( F1 ; R ; F2 ) { Q }
            }
            else{
                error();
            }
            break;
        case reglas::D:
            /*
            D -> function H id ( D1 ) { Q }
            */
            if(token == token_ids::PAL_RES_FUNCTION){
                // D -> function H id ( D1 ) { Q }
            }
            else{
                error();
            }
        case reglas::H:
                /*
                H -> T
                H -> void
                */
            if(mapaFirst[reglas::T].find(token) != mapaFirst[reglas::T].end()){
                // H -> T
            }
            else if(token == token_ids::PAL_RES_VOID){
                // H -> void
            }
            else{
                error();
            }

        case reglas::T:
            /*
            T -> boolean
            T -> int
            T -> string
            */
            if(token == token_ids::PAL_RES_BOOL){
                // T -> boolean
            }
            else if(token == token_ids::PAL_RES_INT){
                // T -> int
            }
            else if(token == token_ids::PAL_RES_STRING){
                // T -> string
            }
            else{
                error();
            }

        case reglas::C:
            /*
            C -> ; 
            C -> L R ;
            */
            if(token == token_ids::PUNTO_Y_COMA){
                // C -> ; 
            }
            else if(mapaFirst[reglas::L].find(token) != mapaFirst[reglas::L].end()){
                // C -> L R ;
            }
            else{
                error();
            }

        case reglas::L:
            /*
            L -> += 
            L -> =
            */
            if(token == token_ids::OP_ASIGNACION_SUMA){
                // L -> += 
            }
            else if(token == token_ids::OP_ASIGNACION_SIMPLE){
                // L -> =
            }
            else{
                error();
            }

        case reglas::R:
            /*
            R -> R1 R2
            R -> ( R )
            */
            if(mapaFirst[reglas::R1].find(token) != mapaFirst[reglas::R1].end()){
                // R -> R1 R2
            }
            else if(token == token_ids::PARENTESIS_ABIERTA){
                // R -> ( R )
            }
            else{
                error();
            }

        case reglas::R1:
            /*
            R1 -> id A 
            R1 -> numero 
            R1 -> cadena
            */
            if(token == token_ids::IDENTIFICADOR){
                // R1 -> id A 
            }
            else if(token == token_ids::NUMERO){
                // R1 -> numero 
            }
            else if(token == token_ids::CADENA){
                // R1 -> cadena
            }
            else{
                error();
            }

        case reglas::R2:
            /*
            R2 -> O R 
            R2 -> lambda
            */
            if(mapaFirst[reglas::O].find(token) != mapaFirst[reglas::O].end()){
                // R2 -> O R 
            }
            else if(){
                // R2 -> lambda
            }
            else{
                error();
            }

        case reglas::O:
            /*
            O -> == 
            O -> && 
            O -> + 
            O -> -
            */
            if(token == token_ids::OP_RELACIONAL_IGUAL){
                // O -> == 
            }
            else if(token == token_ids::OP_LOGICO_AND){
                // O -> && 
            }
            else if(token == token_ids::OP_ARITMETICO_SUMA){
                // O -> + 
            }
            else if(token == token_ids::OP_ARITMETICO_RESTA){
                // O -> -
            }
            else{
                error();
            }

        case reglas::A:
            /*
            A -> ( A1 ) 
            A -> lambda
            */ 
            if(token == token_ids::PARENTESIS_ABIERTA){
                // A -> ( A1 )
            }
            else if(){
                // A -> lambda
            }
            else{
                error();
            }

        case reglas::A1:
            /*
            A1 -> A2 
            A1 -> lambda
            */
            if(mapaFirst[reglas::A2].find(token) != mapaFirst[reglas::A2].end()){
                // A1 -> A2 
            }
            else if(){
                // A1 -> lambda
            }
            else{
                error();
            }

        case reglas::A2:
            /*
            A2 -> R A3
            */
            if(mapaFirst[reglas::A3].find(token) != mapaFirst[reglas::A3].end()){
                // A2 -> R A3
            }
            else{
                error();
            }

        case reglas::A3:
            /*
            A3 -> , A2
            A3 -> lambda
            */
            if(token == token_ids::COMA){
                // A3 -> , A2
            }
            else if(){
                // A3 -> lambda
            }
            else{
                error();
            }

        case reglas::U:
            /*
            U -> input id ; 
            U -> output R ; 
            U -> return U2 ; 
            U -> id U1
            */
            if(token == token_ids::PAL_RES_INPUT){
                // U -> input id ; 
            }
            else if(token == token_ids::PAL_RES_OUTPUT){
                // U -> output R ; 
            }
            else if(token == token_ids::PAL_RES_RETURN){
                // U -> return U2 ; 
            }
            else if(token == token_ids::IDENTIFICADOR){
                // U -> id U1
            }
            else{
                error();
            }

        case reglas::U1:
            /*
            U1 -> L R ; 
            U1 -> ( A1 ) ;
            */
            if(mapaFirst[reglas::L].find(token) != mapaFirst[reglas::L].end()){
                // U1 -> L R ; 
            }
            else if(token == token_ids::PARENTESIS_ABIERTA){
                // U1 -> ( A1 ) ;
            }
            else{
                error();
            }

        case reglas::U2:
            /*
            U2 -> R
            U2 -> lambda
            */
            if(mapaFirst[reglas::R].find(token) != mapaFirst[reglas::R].end()){
                // U2 -> R
            }
            else if(){
                // U2 -> lambda
            }
            else{
                error();
            }            

        case reglas::F1:
            /*
            F1 -> var T id L R 
            F1 -> id L R 
            F1 -> lambda
            */
            if(token == token_ids::PAL_RES_VAR){
                // F1 -> var T id L R 
            }
            else if(token == token_ids::IDENTIFICADOR){
                // F1 -> id L R 
            }
            else if(){
                // F1 -> lambda
            }
            else{
                error();
            }  

        case reglas::F2:
            /*
            F2 -> id L R 
            F2 -> lambda
            */
            if(token == token_ids::IDENTIFICADOR){
                // F2 -> id L R 
            }
            else if(){
                // F2 -> lambda
            }
            else{
                error();
            }  

        case reglas::Q:
            /*
            Q -> B Q 
            Q -> lambda
            */
            if(mapaFirst[reglas::B].find(token) != mapaFirst[reglas::B].end()){
                // Q -> B Q 
            }
            else if(){
                // Q -> lambda
            }
            else{
                error();
            }  

        case reglas::D1:
            /*
            D1 -> D2
            D1 -> lambda
            */
            if(mapaFirst[reglas::D2].find(token) != mapaFirst[reglas::D2].end()){
                // D1 -> D2
            }
            else if(){
                // D1 -> lambda
            }
            else{
                error();
            }  

        case reglas::D2:
            /*
            D2 -> D3 D4
            */
            if(mapaFirst[reglas::D3].find(token) != mapaFirst[reglas::D3].end()){
                // D2 -> D3 D4
            }
            else{
                error();
            }  

        case reglas::D3:
            /*
            D3 -> var T id
            */
            if(token == token_ids::PAL_RES_VAR){
                // D3 -> var T id
            }
            else{
                error();
            }  

        case reglas::D4:
            /*
            D4 -> , D2
            D4 -> lambda
            */
            if(token == token_ids::COMA){
                // D4 -> , D2
            }
            else if(){
                // D4 -> lambda
            }
            else{
                error();
            }  

        default:
            cerr << "REGLA SIN MANEJAR" << endl;
            exit(0);
        
    }

}



int main(){


    reglas noTerminalState = reglas::S;
    token_ids token = getToken(token_file);
    while(token != token_ids::ENDOFFILE){
        switch(noTerminalState){
            case reglas::S:
                break;
            case reglas::B:
                break;
            case reglas::D:
                break;
            case reglas::T:
                break;
            case reglas::C:
                break;
            case reglas::F1:
                break;
            case reglas::F2:
                break;
            case reglas::Q:
                break;
            case reglas::H:
                break;
            case reglas::D1:
                break;
            case reglas::L:
                break;
            case reglas::R1:
                break;
            case reglas::R2:
                break;
            case reglas::A:
                break;
            case reglas::A1:
                break;
            case reglas::A2:
                break;
            case reglas::A3:
                break;
            case reglas::U2:
                break;
            case reglas::U1:
                break;
            case reglas::D2:
                break;
            case reglas::D3:
                break;
            case reglas::D4:
                break;
            default:
                cerr << "REGLA NO TERMINAL SIN MANEJAR" << endl;
                return -1;
        }



        token = getToken(token_file);
    }
}