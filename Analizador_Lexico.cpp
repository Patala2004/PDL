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

template <typename T>
bool contains(T list[], int size, T elem) {
    for (int i = 0; i < size; ++i) {
        if (list[i] == elem) {
            return true;
        }
    }
    return false;
}

//struct Tabla {
//    string texto;
//    int id;
//};

int contador=0;

std::map <int, string> Tablas;

enum class token_ids{
    LLAVE_ABIERTA,          // {
    LLAVE_CERRADA,          // }
    PARENTESIS_ABIERTA,     // (
    PARENTESIS_CERRADA,     // )
    COMA,                   // ,
    PUNTO_Y_COMA,           // ;
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
    PAL_RES_VOID,           // void
    PAL_RES_INT
};
std::map <string, int> tabla;

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

int error(int cod_error, std::ifstream& file, std::streampos position, std::ofstream& err_file){
    file.clear();
    file.seekg(0,std::ios::beg);
    // Ver en que fila esta
    int line = 0;
    int column = 0;
    string a;
    // Get line num
    if(position == -1){ // if position == eol -> mirar todo
        while(getline(file,a)){
            line++;
        }
        column = a.length();
    }
    else{
        std::streampos lastline;
        while(file.tellg() < position - (std::streampos)1){
            line++;
            lastline = file.tellg();
            getline(file, a);
        }
        // tellg() is on the start of the line right before the line with the position
        file.seekg(lastline);
        // Curr pos = line with postion 
        while(file.tellg() < position-(std::streampos)1){
            column++;
            file.get();
        }
        // Check column
    }
    file.seekg(position - (std::streampos)1); // ir a la pos del char de error
    // Gett err message
    string err_msg = "";
    switch(cod_error){
        case 1: err_msg = "Caracter invalido '&'. Querias poner operador logico and '&&'?"; break;
        case 2: err_msg = "Cadena sin terminar. Por favor pon \" para cerrarla"; break;
        case 3: err_msg = "Caracter invalido /"; break;
        case 4: err_msg = "Comentario sin finalizar. Recuerda poner \\* Al final de todo"; break;
        case 5: err_msg = "Character invalido '"; err_msg += (char) file.peek(); err_msg += '\''; break;
        case 6: err_msg = "Caracter invalido \'/\'. Querías iniciar un comentario de bloque /*...*/?"; break;
    }
    // Imprimir error
    err_file << "ERROR LEXICO CON CODIGO: " << cod_error << " EN (" << line << "," << column << "):   " << err_msg << endl; 
    // Volver a posición anterior
    file.seekg(position,std::ios::beg);
    return 0;
}

void generarToken(token_ids id, int valor, std::ofstream& token_file){
    token_file << "<" << tokenToString(id) << ", " << valor << ">" << endl;
}
void generarToken(token_ids id, string valor, std::ofstream& token_file){
    token_file << "<" << tokenToString(id) << ", " << '\"' << valor << '\"' << ">" << endl;
}
void generarToken(token_ids id, std::ofstream& token_file){
    token_file << "<" << tokenToString(id) << ", " << ">" << endl;
}

void crearTabla(string nombre_tabla, std::ofstream& tabla_file){
    //string texto = "";
    //Tabla t = {texto, contador}
    //Linea del identificador de la tabla
    string titulo= nombre_tabla + " " + '#' + " "+  std::to_string(contador) + ':' + '\n'+'\n';
    //contador++;
    tabla_file << titulo;
}


void meterToken(token_ids id, string lex, int desplazamiento, std::ofstream& tabla_file){
    //Si el token no es una Cadena o un numero o un identificador no se anade a la Tabla de simbolos
    //if de asegurarse
    if(tokenToString(id)=="Cadena" || tokenToString(id)=="Numero" || tokenToString(id)=="ID"){
        //No esta el token en la tabla
        if(tabla.find(lex)==tabla.end()){
            string texto= "";
            texto+="* LEXEMA: '" +lex+"'"+'\n'; 
            texto+="    +despl: " + std::to_string(desplazamiento)+'\n';
            tabla_file << texto;
            tabla.insert_or_assign(lex, desplazamiento); 
        }
        else{
            std::map<string, int>::iterator it = tabla.find(lex);
            int desp = it->second;
            cout << "El token ya esta en la tabla de simbolos, su posicion es: " + std::to_string(desp)+'\n';
        }
    }
    
}
// palabras reservadas





int main(int argc, char* argv[]){
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

    if(argc < 2){
        cerr << "Error: Tienes que pasar un archivo" << std::endl;
    }

    std::ifstream file(argv[1], std::ios::binary); 
    
    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return -1;
    }
    else{
        cout << "El archivo se ha abierto correctamente" << endl;
    }

    // Crear archivo para los tokens generados
    std::ofstream token_file("token.txt", std::ios::trunc);//Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.

    // Check if the file is successfully opened
    if (!token_file) {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }

    // Crear archivo para los errores
    std::ofstream err_file("errores.txt", std::ios::trunc);//Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.
    
    // Check if the file is successfully opened
    if (!err_file) {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }

    // Crear archivo para los tokens generados
    std::ofstream tabla_file("tabla.txt", std::ios::trunc);//Abre el archivo de tokens en modo truncar -> borra contenido anterior. Si no existe lo crea.

    // Check if the file is successfully opened
    if (!tabla_file) {
        std::cerr << "Error opening the file." << std::endl;
        return -1;
    }
    crearTabla("Tabla Inicial", tabla_file);
    // Variables del AFD
    int estado = 0;
    int finales[] = {1,2,3,4,5,6,7,8,10,11,13,14,16,26,22,20,18}; // size = 17
    // Abecedarios
    char digitos[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}; // size = 10
    char abc[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
                  // size = 52
    char delimitadores[] = {';','\n',' ', '\t', '\0'}; // size = 5
    char valid[] = {'\n',' ', '\t', '\0', '\b', '\r'}; // Chars validos no mirados en otra condición
    
    char a;
    int valor_numerico = 0;
    string valor_cadena = "";
    bool eof = true;
    int num_linea = 1; // Cambiar a 0 si las lineas empiezan en 0. Por ahora asumo que empiezan en 1
    int pos_tabla_simbolos = 0;
    int desplazamiento =0 ; //igual que el de arriba pero quiero jugar con el a mi manera
    while(file.get(a)){
        switch(estado){
            case 0: 
                if(a == '{'){
                    estado = 1;
                    generarToken(token_ids::LLAVE_ABIERTA, token_file);
                }
                else if(a == '}'){
                    estado = 2;
                    generarToken(token_ids::LLAVE_CERRADA, token_file);
                }
                else if(a == '('){
                    estado = 3; 
                    generarToken(token_ids::PARENTESIS_ABIERTA, token_file);
                }
                else if(a == ')'){
                    estado = 4; 
                    generarToken(token_ids::PARENTESIS_CERRADA, token_file);
                }
                else if(a == ','){
                    estado = 5; 
                    generarToken(token_ids::COMA, token_file);
                }
                else if(a == ';'){
                    estado = 6; 
                    generarToken(token_ids::PUNTO_Y_COMA, token_file);
                }
                else if(a == '-'){
                    estado = 8; 
                    generarToken(token_ids::OP_ARITMETICO_RESTA, token_file);
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
                    valor_cadena = "";
                    estado = 21;
                }
                // digitos
                else if(contains(digitos, 10,  a)){
                    valor_numerico = a-'0';
                    estado = 17;
                }
                // variables y pals reservadas
                else if(contains(abc, 52, a)){
                    valor_cadena += a;
                    estado = 19;
                }
                else if(!contains(valid, 8, a)){
                    estado = 0;
                    file.clear();
                    error(5, file, file.tellg(), err_file);
                }
                break;
                // Si no -> el estado se mantiene en 0, lee el char y no hace nada y luego continua
            
            // case 1 - 8 son estados finales -> no se puede llegar a este punto con estado == uno de esos
            case 9: 
                // estamos en +
                if(a == '='){
                    estado = 10;
                    generarToken(token_ids::OP_ASIGNACION_SUMA, token_file);
                }
                else{
                    // No es lectura -> retroceder en uno
                    generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
                    file.seekg(-1,std::ios::cur);
                    estado = 11;
                }
                break;
            // Case 10 y 11 son estados finales
            case 12: 
                // estamos en =
                if(a == '='){
                    generarToken(token_ids::OP_RELACIONAL_IGUAL, token_file);
                    estado = 13;
                }
                else{
                    // No es lectura -> retroceder en uno
                    generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
                    file.seekg(-1,std::ios::cur);
                    estado = 14;
                }
                break;
            // case 13 y 14 son estados finales
            case 15: 
                // Estamos en &
                if(a == '&'){
                    generarToken(token_ids::OP_LOGICO_ANDS, token_file);
                    estado = 16;
                }
                else{
                    error(1, file, file.tellg() - (std::streampos) 1, err_file);
                    //file.seekg(-1,std::ios::cur); se retrocede en el error
                    estado = 0;
                    // Lanzar error léxicos
                }
                break;
            // 16 es estado final
            case 17: 
                // estamos en un numero entre 0 e infinito de d
                if(contains(digitos, 10, a)){
                    valor_numerico = valor_numerico*10 + (a-'0');
                    estado = 17;
                }
                else{
                    generarToken(token_ids::NUMERO, valor_numerico, token_file);
                    valor_numerico = 0;
                    file.seekg(-1,std::ios::cur);
                    estado = 18;
                }
                break;
            // 18 es un estado finak
            case 19: 
                // estamos en l
                if(contains(abc, 52, a) || contains(digitos, 10, a)){
                    valor_cadena += a;
                    estado = 19;
                }
                else{
                    std::map<std::string, token_ids>::iterator pal_res_id_it = palResMap.find(valor_cadena);
                    if(pal_res_id_it != palResMap.end()){
                        meterToken(pal_res_id_it->second, valor_cadena, desplazamiento,tabla_file);
                        generarToken(pal_res_id_it->second, token_file);
                        desplazamiento++;
                    }
                    else{
                        generarToken(token_ids::IDENTIFICADOR, pos_tabla_simbolos, token_file);
                        meterToken(token_ids::IDENTIFICADOR, valor_cadena, desplazamiento, tabla_file);
                        pos_tabla_simbolos++;
                        desplazamiento++;
                    }
                    valor_cadena = "";
                    file.seekg(-1,std::ios::cur);
                    estado = 20;
                }
                break;
            // 20 es estado final
            case 21: 
                // estamos en "
                if(a == '"'){
                    generarToken(token_ids::CADENA, valor_cadena, token_file);
                    valor_cadena = "";
                    estado = 22;
                }
                else{
                    valor_cadena += a;
                    estado = 21;
                }
                break;
            // 22 es un estado final
            case 23: 
                // estamos en /
                if(a == '*'){
                    estado = 24;
                }
                else{
                    // error
                    estado = 0;
                    error(6, file, file.tellg(), err_file);
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

        if(contains(finales, 17, estado)){
            estado = 0; // Si el estado al que ha llegado anteriormente es final -> vuelve al estado inicial
        }
    
    }
    // Actualizar estado con EOF
    switch(estado){
        case 9:
            generarToken(token_ids::OP_ARITMETICO_SUMA, token_file);
            estado = 11;
            break;
        case 12: 
            generarToken(token_ids::OP_ASIGNACION_SIMPLE, token_file);
            estado = 14;
            break;
        case 15: 
            error(1, file, file.tellg(), err_file); // Unfinished &&
            break;
        case 17:
            estado = 18;
            generarToken(token_ids::NUMERO, valor_numerico, token_file);
            break;
        case 19: 
            estado = 20;
            generarToken(token_ids::IDENTIFICADOR, valor_cadena, token_file);
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
    return 1;
}

