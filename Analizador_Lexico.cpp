#include <iostream>
#include <array>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
#include <fstream>

using namespace std;

template <typename T>
bool contains(T list[], int size, T elem) {
    for (int i = 0; i < size; ++i) {
        if (list[i] == elem) {
            return true;
        }
    }
    return false;
}

enum class token_ids{
    LLAVE_ABIERTA,          // {
    LLAVE_CERRADA,          // }
    PARENTESIS_ABIERTA,     // (
    PARENTESIS_CERRADA,     // )
    COMA,                   // ,
    PUNTO_Y_COMA,           // ;
    OP_LOGICO_NEGACION,     // !
    OP_RELACIONAL_IGUAL,  // ==
    OP_LOGICO_ANDS,         // &&
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
    PAL_RES_VOID            // void
};


// Function to convert enum to string
std::string tokenToString(token_ids id) {
    switch (id) {
        case token_ids::LLAVE_ABIERTA: return "LLAVE_ABIERTA";
        case token_ids::LLAVE_CERRADA: return "LLAVE_CERRADA";
        case token_ids::PARENTESIS_ABIERTA: return "PARENTESIS_ABIERTA";
        case token_ids::PARENTESIS_CERRADA: return "PARENTESIS_CERRADA";
        case token_ids::COMA: return "COMA";
        case token_ids::PUNTO_Y_COMA: return "PUNTO_Y_COMA";
        case token_ids::OP_LOGICO_NEGACION: return "OP_LOGICO_NEGACION";
        case token_ids::OP_RELACIONAL_IGUAL: return "OP_RELACIONAL_IGUAL";
        case token_ids::OP_LOGICO_ANDS: return "OP_LOGICO_ANDS";
        case token_ids::OP_ARITMETICO_RESTA: return "OP_ARITMETICO_RESTA";
        case token_ids::OP_ARITMETICO_SUMA: return "OP_ARITMETICO_SUMA";
        case token_ids::OP_ASIGNACION_SIMPLE: return "OP_ASIGNACION_SIMPLE";
        case token_ids::OP_ASIGNACION_SUMA: return "OP_ASIGNACION_SUMA";
        case token_ids::CADENA: return "CADENA";
        case token_ids::NUMERO: return "NUMERO";
        case token_ids::IDENTIFICADOR: return "IDENTIFICADOR";
        case token_ids::PAL_RES_BOOL: return "PAL_RES_BOOL";
        case token_ids::PAL_RES_FOR: return "PAL_RES_FOR";
        case token_ids::PAL_RES_FUNCTION: return "PAL_RES_FUNCTION";
        case token_ids::PAL_RES_IF: return "PAL_RES_IF";
        case token_ids::PAL_RES_INPUT: return "PAL_RES_INPUT";
        case token_ids::PAL_RES_OUTPUT: return "PAL_RES_OUTPUT";
        case token_ids::PAL_RES_RETURN: return "PAL_RES_RETURN";
        case token_ids::PAL_RES_STRING: return "PAL_RES_STRING";
        case token_ids::PAL_RES_VAR: return "PAL_RES_VAR";
        case token_ids::PAL_RES_VOID: return "PAL_RES_VOID";
        default: return "UNKNOWN";
    }
}

void generarToken(token_ids id, int valor){
    std::cout << "<" << tokenToString(id) << ", " << valor << ">" << endl;
}
void generarToken(token_ids id, string valor){
    std::cout << "<" << tokenToString(id) << ", " << '\"' << valor << '\"' << ">" << endl;
}
void generarToken(token_ids id){
    std::cout << "<" << tokenToString(id) << ", " << "-" << ">" << endl;
}


int main(int argc, char* argv[]){

    if(argc < 2){
        cerr << "Error: Tienes que pasar un archivo" << std::endl;
    }

    std::ifstream file(argv[1]); 
    
    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    else{
        cout << "El archivo se ha abierto correctamente" << endl;
    }

    // Variables del AFD
    int estado = 0;
    int finales[] = {1,2,3,4,5,6,7,8,10,11,13,14,16,26,22,20,18}; // size = 17
    // Abecedarios
    char digitos[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}; // size = 10
    char abc[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
                  // size = 52
    char delimitadores[] = {';','\n',' ', '\t', '\0'}; // size = 5
    
    char a;
    while(file >> a){
        // a is the next char from the file
        // file.seekg(-1, std::ios::cur); to go back one position (in case we dont want to do a reading operation)

        switch(estado){
            case 0: 
                if(a == '{'){
                    estado = 1;
                    generarToken(token_ids::LLAVE_ABIERTA);
                }
                else if(a == '}'){
                    estado = 2;
                    generarToken(token_ids::LLAVE_CERRADA);
                }
                else if(a == '('){
                    estado = 3; 
                    generarToken(token_ids::PARENTESIS_ABIERTA);
                }
                else if(a == ')'){
                    estado = 4; 
                    generarToken(token_ids::PARENTESIS_CERRADA);
                }
                else if(a == ','){
                    estado = 5; 
                    generarToken(token_ids::COMA);
                }
                else if(a == ';'){
                    estado = 6; 
                    generarToken(token_ids::PUNTO_Y_COMA);
                }
                else if(a == '!'){
                    estado = 7; 
                    generarToken(token_ids::OP_LOGICO_NEGACION);
                }
                else if(a == '-'){
                    estado = 8; 
                    generarToken(token_ids::OP_ARITMETICO_RESTA);
                }
                else if(a == '+'){
                    estado = 9;
                }
                else if(a == '='){
                    estado = 12;
                }
                else if(a == '&'){
                    estado = 15;
                }
                // Comentario
                else if(a == '/'){
                    estado = 23;
                }
                // Strings
                else if(a == '"'){
                    estado = 21;
                }
                // digitos
                else if(contains(digitos, 10,  a)){
                    estado = 17;
                }
                // variables y pals reservadas
                else if(contains(abc, 52, a)){
                    estado = 19;
                }
                break;
                // Si no -> el estado se mantiene en 0, lee el char y no hace nada y luego continua
            
            // case 1 - 8 son estados finales -> no se puede llegar a este punto con estado == uno de esos
            case 9: 
                // estamos en +
                if(a == '='){
                    estado = 10;
                    generarToken(token_ids::OP_ASIGNACION_SUMA);
                }
                else{
                    // No es lectura -> retroceder en uno
                    generarToken(token_ids::OP_ARITMETICO_SUMA);
                    file.seekg(-1, std::ios::cur);
                    estado = 11;
                }
                break;
            // Case 10 y 11 son estados finales
            case 12: 
                // estamos en =
                if(a == '='){
                    generarToken(token_ids::OP_RELACIONAL_IGUAL);
                    estado = 13;
                }
                else{
                    // No es lectura -> retroceder en uno
                    generarToken(token_ids::OP_ASIGNACION_SIMPLE);
                    file.seekg(-1, std::ios::cur);
                    estado = 14;
                }
                break;
            // case 13 y 14 son estados finales
            case 15: 
                // Estamos en &
                if(a == '&'){
                    generarToken(token_ids::OP_LOGICO_ANDS);
                    estado = 16;
                }
                else{
                    // Lanzar error léxicos
                }
                break;
            // 16 es estado final
            case 17: 
                // estamos en un numero entre 0 e infinito de d
                if(contains(digitos, 10, a)){
                    estado = 17;
                }
                else{
                    // GENTOKEN NUMERO
                    file.seekg(-1, std::ios::cur); // no es operacion de lectura
                    estado = 18;
                }
                break;
            // 18 es un estado finak
            case 19: 
                // estamos en l
                if(contains(abc, 52, a)){
                    estado = 19;
                }
                else{
                    // GENTOKEN VAR O PAL RESERVADA
                    file.seekg(-1, std::ios::cur); // no se lee -> retrocedemos uni
                    estado = 20;
                }
                break;
            // 20 es estado final
            case 21: 
                // estamos en "
                if(a == '"'){
                    // GENTOKEN STRING
                    estado = 22;
                }
                else{
                    estado = 21;
                }
                break;
            // 22 es un estado final
            case 23: 
                // estamos en /
                if(a == '*'){
                    estado = 24;
                }
                break;
            case 24: 
                // estamos en /* ...
                if(a == '*'){
                    estado = 25;
                }
                else{
                    estado = 24;
                }
                break;
            case 25: 
                // estamos en /* ... *
                if(a == '*'){
                    estado = 25;
                }
                else if(a == '/'){
                    estado = 26;
                }
                else{
                    estado = 24;
                }
                break;
            // 26 es un estado final
        }

        cout << estado << endl;


        if(contains(finales, 17, estado)){
            estado = 0; // Si el estado al que ha llegado anteriormente es final -> vuelve al estado inicial
        }
    }
    // Actualizar estado con EOF
    if(file.eof()){
        switch(estado){
            case 9: 
                estado = 11;
                break;
            case 12: 
                estado = 14;
                break;
            case 15: 
                // Lanzar error lexico
                break;
            case 17: 
                estado = 18;
                break;
            case 19: 
                estado = 20;
                break;
            case 21: 
                // Lanzar error lexico
                break;
            case 23: 
                // Lanzar error lexico
                break;
            case 24: 
                // Lanzar error lexico
                break;
            case 25: 
                // Lanzar error lexico
                break;
        }
    }
    
    cout << estado << endl;

    return 1;
}