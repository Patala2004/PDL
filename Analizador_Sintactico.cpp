#include <iostream>
#include <sstream>
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


std::ostream& operator<<(std::ostream& os, const Entrada& e) {

    if(e.tipo == "funcion"){
        os << " * '" << e.nombre << "'" << endl;
        
        os << "   + tipo:  '" << e.tipo <<"'" << endl;

        int numParam = e.tipoParams == "void"? 0:count(e.tipoParams.begin(), e.tipoParams.end(), ',') + 1;
        
        os << "       + numParam:  " << numParam << endl;

        stringstream ss(e.tipoParams);
        for(int i = 0; i < numParam; i++){
            string aux;
            getline(ss, aux, ',');
            os << "          + tipoParam" << to_string(i+1) << ":  '" << aux << "'" << endl;
        }

        os << "        + tipoRetorno:  '" << e.tipoRetorno << "'" << endl;

        os << "        + etiqFuncion:  '" << e.etiqfuncion << "'" << endl;

        os << "   --------------------------" << endl;
    }
    else{
        os << " * '" << e.nombre << "'" << endl; 
        if(e.tipo == "null"){
            os << "   + tipo:  '-'" << endl;
        }
        else{
            os << "   + tipo:  '" << e.tipo <<"'" << endl;
        }
        os << "   + despl:  " << e.desplazamiento << endl;

        os << "   --------------------------" << endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tabla& t) {
    // if(t.entradas.empty()){
    //     return os;
    // }
    os << t.nombre << " #" << t.contador <<":" << endl << endl << endl;
    for(Entrada e : t.entradas){
        os << e;
    }
    return os;
}


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
Tabla* TSG = new Tabla();
// tsl
Tabla* TSL = nullptr;
int contadorTablas = 0;

std::ofstream ficheroTS("TablaSimbolos.txt", std::ios::out | std::ios::trunc);






void error(token_ids token, reglas estado, string msgError)
{
    // cerr << "TOKEN " << tokenToString(token) << " NO ACEPTADO EN EL ESTADO " << reglasToString(estado) <<endl;
    int linea = analizador.linea_last_finished_tok;
    cout << "ERROR SINTACTICO EN LA LINEA " << linea << ": " << msgError << endl;
    exit(0);
}




// Funciones semanticas

string BuscaTipo(string id){
    return TSG->BuscaTipo(id);
}
Entrada& BuscaEntrada(string id, bool asignacion = false){
    if(TSL != nullptr && (TSL->BuscaEntrada(id).tipo != "null" || asignacion)){
        // Quiero saber si una entrada esta en TSL y su valor si:
        //      1. Existe TSL
        //      2. Existe una entrada en TSL o no existe PERO estoy asignando (quiero saber que hay huco para asignar)
        return TSL->BuscaEntrada(id);
    }
    return TSG->BuscaEntrada(id);
}
Entrada& BuscaEntradaFunc(string id){
    return TSG->BuscaEntradaFunc(id);
}
Entrada& BuscaTipoFuncParams(string id){
    return TSG->BuscaTipoFuncParams(id);
}
Entrada& BuscaTipoFuncRet(string id){
    return TSG->BuscaTipoFuncRet(id);
}

void AñadeTipo(string id, string tipo){
    TSG->AñadeTipo(BuscaEntrada(id),tipo);
}
void AñadeDespl(string id, int despl){
    TSG->AñadeDespl(BuscaEntrada(id),despl);
}
void AñadeTipoFunc(string id, string tipoParam, string tipoRet){
    TSG->AñadeTipoFunc(BuscaEntrada(id),tipoParam, tipoRet);
}
void AñadeEtiq(string id, string etiq){
    Entrada &e = BuscaEntrada(id);
    cout << e.tipo << endl;
    TSG->AñadeEtiq(e, etiq);
}

Entrada& AñadeEntrada(string id, Tabla* tabla){
    if(tabla == TSG){
        return TSG->AñadeEntrada(id);
    }
    else if(tabla == nullptr){
        cout << "INTENTANDO METER EN UNA TABLA NO EXISTENTE" << endl;
        exit(0);
    }
    else if(tabla == TSL){
        return TSL->AñadeEntrada(id);
    }
    else{
        throw runtime_error("TABLA NO NULA PERO TAMPOCO ES TSL O TSG");
    }
    return TSG->AñadeEntrada(id);
}

Tabla* crearTabla(string nombre = "TABLA SIN NOMBRE"){
    Tabla* ret = new Tabla();
    ret->contador = contadorTablas++;
    ret->nombre = nombre;
    return ret;
}

Tabla* liberarTabla(){
    ficheroTS << *TSL << endl;
    return nullptr;
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
        int linea = analizador.linea_last_finished_tok;
        cout << "ERROR SINTACTICO EN LA LINEA " << linea << ": esperada " <<tokenToString2(a_equiparar) << ", recibido " << tokenToString2(token.id) << endl;
        // cerr << "TOKEN " << tokenToString(token.id) << " NO ES IGUAL A " << tokenToString(a_equiparar) << "EN EL ESTADO "
        //      << reglasToString(estado) << " en la linea: " << linea << endl;
        exit(0);
    }
    // cout << tokenToString(token) << endl;
    token = analizador.processNextChar(); // avanzamos el token fuera de donde nos llamaron
    return true;
}

int auxi = 0;
bool noTerminal(reglas NT, Token &token, map<string,string>* atrs_semanticos = nullptr)
{

    // cout << reglasToString(NT) << " " << auxi++ << endl;
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
            error(token.id, NT, "fichero terminado con contenido invalido");
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
            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);
            Entrada& idtemp = BuscaEntrada(get<string>(iden.valor), true);

            // semantico
            // El lexico debe de haber metido al token en la tabla que corresponde y lanzado error si ya existia en la tabla local (o global si no hay local)
            if(idtemp.tipo == "null"){ // Si el token en la TSL no tiene tipo
                Entrada& id = AñadeEntrada(get<string>(iden.valor), TSL==nullptr? TSG:TSL);
                //AñadeTipo(id,T["tipo"]);
                id.tipo = T["tipo"];
                if(TSL == nullptr){
                    //AñadeDespl(id,despG);
                    id.desplazamiento = despG;
                    despG += stoi(T["ancho"]);
                }
                else{
                    //AñadeDespl(id,despL);
                    id.desplazamiento = despL;
                    despL += stoi(T["ancho"]);
                }
            }
            else{
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA VARIABLE YA HA SIDO DECLARADA EN LA LINEA " << analizador.linea_last_finished_tok << endl;
                exit(0);
            }
            zona_decl = false;
            //finsemantico
            
            map<string,string> C = {};

            noTerminal(reglas::C, token, &C );

            // semantico
            if(T["tipo"] != C["tipo"] && C["tipo"] != "vacio"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA VARIABLE ASIGNADA NO COINCIDE CON EL TIPO DE LA ASIGNACION" << endl;
                exit(0);
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
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA CONDICION TIENE QUE SER UNA EXPRESION BOOLEANA" << endl;
                exit(0);
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
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA CONDICION TIENE QUE SER UNA EXPRESION BOOLEANA" << endl;
                exit(0);
            }
            //finsemantico

            equipara(token, token_ids::PUNTO_Y_COMA, NT);
            noTerminal(reglas::F2, token);
            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::LLAVE_ABIERTA, NT);
            noTerminal(reglas::Q, token, &Q);
            equipara(token, token_ids::LLAVE_CERRADA, NT);
        }
        else
        {
            error(token.id, NT, "esperado ;");
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
            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);
            Entrada& idtemp = BuscaEntradaFunc(get<string>(iden.valor)); // Para revisar si existe ya una func con el mismo nombre

            //semantico
            if(idtemp.tipo != "null"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA FUNCION YA HA SIDO DECLARADA" << endl;
                exit(0);
            }

            Entrada& id = AñadeEntrada(get<string>(iden.valor), TSG); // AÑadimos a la tabnla
            TSL = crearTabla("TABLA DE LA FUNCION " + get<string>(iden.valor));
            despL = 0;
            //finsemantico

            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);

            map<string,string> D1 = {};
            noTerminal(reglas::D1, token, &D1);

            //semantico
            //AñadeTipoFunc(id, D1["tipo"], H["tipo"]);
            id.tipo = "funcion";
            id.tipoRetorno = H["tipo"];
            id.tipoParams = D1["tipo"];
            id.etiqfuncion = TSG->nuevaEtiq();
            id.desplazamiento = 0;
            zona_decl = false;
            Q["tipoRet"] = H["tipo"];
            //finsemantico

            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::LLAVE_ABIERTA, NT);
            noTerminal(reglas::Q, token, &Q);
            equipara(token, token_ids::LLAVE_CERRADA, NT);

            //semantico
            TSL = liberarTabla();
            //finsemantico
        }
        else
        {
            error(token.id, NT, "Esperada declaración de funcion");
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
            error(token.id, NT, "esperado tipo de funcion");
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
            error(token.id, NT, "esperado tipo entero, booleano o cadena");
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
            error(token.id, NT, "esperado ;");
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

            //semantico
            (*atrs_semanticos)["operador"] = "asignacion";
        }
        else
        {
            error(token.id, NT, "Esperado operador de asignación = o +=");
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
            error(token.id, NT, "Esperada una expresion");
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
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": VALOR NO BOOLEANO EN UN AND" << endl;
                exit(0);
            }
            //finsemantico

            equipara(token, token_ids::OP_LOGICO_ANDS, NT);
            map<string,string> R2 = {};
            noTerminal(reglas::R2, token, &R2);

            //semantico
            if(R2["tipo"] != "booleano"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": VALOR NO BOOLEANO EN UN AND EN LA PARTE DERECHA" << endl;
                exit(0);
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
            error(token.id, NT, "esperado operador lógico AND");
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
            error(token.id, NT, "esperado ;");
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
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": NO PUEDES IGUALAR DATOS DE DISTINTOS TIPOS" << endl;
                exit(0);
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
            error(token.id, NT, "esperado operador lógico ==");
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
            error(token.id, NT, "esperado operación, variable, función, número entero o cadena");
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
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": OPERACION ARITMETICA CON DATO NO ENTERO" << endl;
                exit(0);
            }
            noTerminal(reglas::J, token);
            map<string,string> O = {};
            noTerminal(reglas::O, token, &O);
            map<string,string> R5 = {};

            //semantico
            if(O["tipo"] != "entero"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": OPERACION ARITMETICA CON DATO NO ENTERO A LA DERECHA" << endl;
                exit(0);
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
            error(token.id, NT, "esperado operador aritmetico + o -");
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
            error(token.id, NT, "esperado operador aritmetico + o -");
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
            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);
            map<string,string> A = {};
            noTerminal(reglas::A, token, &A);

            //semantico

            if(A["tipo"] != ""){ // Si a A SI se le ha asignado algun tipo 
                Entrada& id = BuscaEntradaFunc(get<string>(iden.valor));
                if(id.tipo == "null"){
                    cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LA FUNCION NO HA SIDO DECLARADA" << endl;
                    exit(0);
                }
                if(A["tipo"] == id.tipoParams){ // si los tipos de los argumentos coincide con el de los parametros
                    (*atrs_semanticos)["tipo"] = id.tipoRetorno; // tipo de O es el tipo de retorno de la func
                }
                else{
                    cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": LOS PARAMETROS NO SON CORRECTOS PARA ESTA FUNCION" << endl;
                    exit(0);
                }
            }
            else{
                Entrada& idtemp = BuscaEntrada(get<string>(iden.valor));
                // Entonces es una variable, no una func
                if(idtemp.tipo == "null"){
                    Entrada& id = AñadeEntrada(get<string>(iden.valor), TSG);
                    id.tipo = "entero";
                    (*atrs_semanticos)["tipo"] = "entero";
                    id.desplazamiento = despG;
                    despG += 1;
                }
                else{
                    (*atrs_semanticos)["tipo"] = idtemp.tipo;
                }
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
            error(token.id, NT, "esperado operacion, variable, funcion, numero entero o cadena");
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
            error(token.id, NT, "esperada llamada a parametros de una funcion");
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
            (*atrs_semanticos)["tipo"] = "void";
        }
        else
        {
            error(token.id, NT, "esperado parametro de funcion");
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
            error(token.id, NT,"esperado parametro de funcion");
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
            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);

            //semantico
            Entrada& id = BuscaEntrada(get<string>(iden.valor));
            if(id.tipo == "null"){
                Entrada& id2 = AñadeEntrada(get<string>(iden.valor), TSG);
                id2.tipo = "entero";
                id2.desplazamiento = despG;
                despG++;
            }
            else if(id.tipo != "entero" && id.tipo != "cadena"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": SOLO SE PUEDEN LEER ENTEROS O CADENAS USANDO INPUT" << endl;
                exit(0);
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
                cout << R["tipo"] << endl;
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": SOLO SE PUEDEN IMPRIMIR ENTEROS O CADENAS" << endl;
                exit(0);
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
            U2["tipoRet"] = (*atrs_semanticos)["tipoRet"];
            if(TSL == nullptr){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": SOLO SE PUEDEN USAR RETURNS DENTRO DE FUNCIONES" << endl;
                exit(0);
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

            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);

            //semantico
            string tipo = BuscaEntrada(get<string>(iden.valor)).tipo;
            U1["tipo"] = tipo;
            U1["nombreVar"] = get<string>(iden.valor); 
            U1["tipoParams"] = BuscaEntradaFunc(get<string>(iden.valor)).tipoParams;
            //finsemantico

            noTerminal(reglas::U1, token,&U1);

            // //semantico
            // if(U1["modo"] == "asignacion" && tipo == "null"){ // NO VUELVO A HACER BUSCAENTRADA CON ASIG = TRUE PORQUE SI ESTA EN EL GLOBAL NO LO QUIERO ASIGNAR AL LOCAL
            //     // si variable no existe crearla
            //     Entrada& id = AñadeEntrada(get<string>(iden.valor),TSG);
            //     id.tipo = U1["tipo"]; // ha sido sobreescrito por el valor de R["tipo"] en U1
            //     int ancho = -2;
            //     if(id.tipo == "entero"){
            //         ancho = 1;
            //     }
            //     else if(id.tipo == "cadena"){
            //         ancho = 64;
            //     }
            //     else if(id.tipo == "booleano"){
            //         ancho = 1;
            //     }
            //     else{
            //         cout << "TIPO DE VAR RARO: " << id.tipo << endl;
            //     }
                
            //     id.desplazamiento = despG;
            //     despG += ancho;
            // }
        }
        else
        {
            error(token.id, NT, "esperada operacion input, output, return, una variable o llamada a funcion");
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
            //semantico
            if(L["operador"] == "suma" && (*atrs_semanticos)["tipo"] == "null"){
                // variable global tipo entera
                (*atrs_semanticos)["tipo"] = "entero";
                Entrada& id = AñadeEntrada((*atrs_semanticos)["nombreVar"], TSG);
                id.tipo = "entero";
                id.desplazamiento = despG;
                despG++;
            }
            else if(L["operador"] == "suma" && (*atrs_semanticos)["tipo"] != "entero"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": NO SE PUEDE USAR OPERADOR DE ASIGNACION SUMA PARA VAR NO ENTERA" << endl;
                exit(0);
            }
            //finsemantico
            noTerminal(reglas::R, token,&R);
            //semantico
            if(L["operador"] == "suma" && R["tipo"] != "entero"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": ASIGNACION-SUMA CON ELEMENTO NO ENTERO" << endl;
                exit(0);
            }else{
                if((*atrs_semanticos)["tipo"] != "null" && (*atrs_semanticos)["tipo"] != R["tipo"]){
                    cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": ASIGNACION A UNA VARIABLE DE UN TIPO CON UN VALOR DE OTRO" << endl;
                    exit(0);
                }
                else if((*atrs_semanticos)["tipo"] == "null"){
                    // Crear variable del tipo que sea R
                    Entrada& id = AñadeEntrada((*atrs_semanticos)["nombreVar"], TSL==nullptr? TSG:TSL);
                    id.tipo = R["tipo"];
                    if(TSL == nullptr){
                        id.desplazamiento = despL;
                        if(id.tipo == "entero") despL+= 1;
                        else if(id.tipo == "cadena") despL+= 64;
                        else if(id.tipo == "booleano") despL += 1;
                        else cout << "TIPO RARO" << endl;
                    }
                    else{
                        id.desplazamiento = despG;
                        if(id.tipo == "entero") despG+= 1;
                        else if(id.tipo == "cadena") despG+= 64;
                        else if(id.tipo == "booleano") despG += 1;
                        else cout << "TIPO RARO" << endl;
                    }
                }
                (*atrs_semanticos)["tipo"] = R["tipo"];
            }
            //fin semantico
            equipara(token, token_ids::PUNTO_Y_COMA, NT);
            //semantico
            (*atrs_semanticos)["modo"] = "asignacion";
            //finsemantico
        }
        else if (token.id == token_ids::PARENTESIS_ABIERTA)
        {
            // U1 -> ( A1 ) ;
            parse_file << 44 << " ";

            map<string,string> A1 = {};

            equipara(token, token_ids::PARENTESIS_ABIERTA, NT);
            //semantico
            if((*atrs_semanticos)["tipoParams"] == "null"){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": NO EXISTE ESTA FUNCION" << endl;
                exit(0);
            }
            //finsemantico
            noTerminal(reglas::A1, token,&A1);
            //semantico
            if(A1["tipo"] != (*atrs_semanticos)["tipoParams"]){
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": PARAMETROS INCORRECTOS" << endl;
                exit(0);
            }
            //finsemantico
            equipara(token, token_ids::PARENTESIS_CERRADA, NT);
            equipara(token, token_ids::PUNTO_Y_COMA, NT);
        }
        else
        {
            error(token.id, NT, "esperada asignación o parametros de funcion");
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
                cout << "ERROR SEMANTICO EN LA LINEA: " << analizador.linea_last_finished_tok << " El tipo del return no coincide con el valor de retorno de la funcion" << endl ;
                exit(0);
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
            error(token.id, NT, "esperado operación o valor");
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

            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);
            equipara(token, token_ids::OP_ASIGNACION_SIMPLE, NT);
            noTerminal(reglas::R, token,&R);

            //semantico
            string tipo = BuscaEntrada(get<string>(iden.valor), false).tipo;
            if(tipo == "null"){ // false para no asignar al TSL si la var existe el el TSG
                // SI no existe -> crear
                Entrada& id = AñadeEntrada(get<string>(iden.valor), TSL == nullptr? TSG:TSL);
                id.tipo = R["tipo"];
                int desplazamiento = 0;
                if(id.tipo == "entero"){
                    desplazamiento = 1;
                }
                else if(id.tipo == "booleano"){
                    desplazamiento = 1;
                }
                else if(id.tipo == "cadena"){
                    desplazamiento = 64;
                }
                id.desplazamiento = desplazamiento;
            }
            else{
                // Si ya existe -> comprobar que el valor asignado sea del mismo tipo a la var existente
                if(R["tipo"] !=tipo){
                    throw runtime_error("ERROR SEMANTICO EN LA LINEA " + to_string(analizador.linea_last_finished_tok) + ": ASIGNACION DE DOS TIPOS DIFERENTES");
                }
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
            error(token.id, NT, "esperada asignación de variable");
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

            string idnombre = get<string>(token.valor);
            equipara(token, token_ids::IDENTIFICADOR, NT);
            noTerminal(reglas::L, token,&L);
            // semantico
            string tipo;
            Entrada& idtemp = BuscaEntrada(idnombre);
            if(idtemp.tipo == "null" && L["operador"] == "suma"){
                // No existe la var todavia -> Se añade como entero global
                tipo = "entero";
                Entrada& id = AñadeEntrada(idnombre, TSG);
                id.tipo = "entero";
                id.desplazamiento = despG;
                despG += 1;
            }
            else if(idtemp.tipo != "entero" && L["operador"] == "suma"){
                // se usa += con una var no entera
                cout << "ERROR SEMANTICO EN LA LINEA: " << analizador.linea_last_finished_tok << " No se puede usar el operador += con variables no enteras" << endl;
                exit(0);
            }
            else if(idtemp.tipo != "null") tipo = idtemp.tipo;
            noTerminal(reglas::R, token,&R);
            if(idtemp.tipo == "null" && L["operador"] == "asignacion"){
                tipo = R["tipo"];
                Entrada& id = AñadeEntrada(idnombre, TSL==nullptr? TSG:TSL);
                id.tipo = tipo;
                id.desplazamiento = despG;
                if(tipo == "entero") despG+=1;
                else if(tipo == "cadena") despG+=64;
                else if(tipo == "booleano") despG+=1;
                else cout << "TIPO RARO?" <<endl;
            }

            //semantico AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

            if(L["operador"] == "suma" && R["tipo"] != "entero"){
                cout << "ERROR SEMANTICO EN LA LINEA: " << analizador.linea_last_finished_tok << " No puedes hacer asignacion suma con algo que no sean enteros" << endl ;
                exit(0);
            }

            if(R["tipo"] != tipo){
                cout << "ERROR SEMANTICO EN LA LINEA: " << analizador.linea_last_finished_tok << " No puedes hacer asignacion de distintos tipos" << endl ;
                exit(0);
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
            error(token.id, NT, "esperada operacion de asignacion de una variable");
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
            error(token.id, NT, "Esperado ;");
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

            map<string,string> D2 = {};
            noTerminal(reglas::D2, token, &D2);

            //semantico
            (*atrs_semanticos)["tipo"] = D2["tipo"];
            //finsemantico
        }
        else if (token.id == token_ids::PAL_RES_VOID)
        {
            // D1 -> void
            parse_file << 54 << " ";
            equipara(token, token_ids::PAL_RES_VOID, NT);

            //semantico
            (*atrs_semanticos)["tipo"] = "void";
            //finsemantico
        }
        else
        {
            error(token.id, NT, "Esperado inicializacion de parametro de funcion");
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

            map<string,string> D4 = {};
            map<string,string> D3 = {};
            noTerminal(reglas::D3, token, &D3);
            noTerminal(reglas::D4, token, &D4);

            if(D4["tipo"] == ""){
                (*atrs_semanticos)["tipo"] = D3["tipo"];
            }
            else{
                (*atrs_semanticos)["tipo"] = D3["tipo"] + "," + D4["tipo"];
            }
        }
        else
        {
            error(token.id, NT, "Esperado tipo del parametro");
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
            map<string,string> T = {};
            noTerminal(reglas::T, token, &T);
            Token iden = token;
            equipara(token, token_ids::IDENTIFICADOR, NT);

            //semantico
            Entrada& idtemp = BuscaEntrada(get<string>(iden.valor), true); // True para que si no esta en TSL no lo busque en TSG
            if(idtemp.tipo == "null"){ // Si lo ha metido el lexico pero todavia ningun semantico
                Entrada& id = AñadeEntrada(get<string>(iden.valor), TSL);
                id.tipo = T["tipo"];
                id.desplazamiento =despL;
                despL += stoi(T["ancho"]);
                (*atrs_semanticos)["tipo"] = T["tipo"];
            }
            else{
                cout << "ERROR SEMANTICO EN LA LINEA " << analizador.linea_last_finished_tok << ": VARIABLE YA DECLARADA EN LA LINEA " << analizador.linea_last_finished_tok << endl;
                exit(0);
            }
        }
        else
        {
            error(token.id, NT, "esperado tipo del parametro");
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
            map<string,string> D2 = {};
            noTerminal(reglas::D2, token, &D2);

            //semantico
            (*atrs_semanticos)["tipo"] = D2["tipo"];
            //finsemantico
        }
        else if (mapaFollow[reglas::D4].find(token.id) != mapaFollow[reglas::D4].end())
        {
            // D4 -> lambda
            parse_file << 58 << " ";
        }
        else
        {
            error(token.id, NT, "esperado fin de inicializacion de parametros");
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

    if(!ficheroTS.is_open()) {
        std::cerr << "Failed to open or create the file: TablaSimbolos.txt" << std::endl;
        return 1; // Return an error code
    }
    popularMapa();
    reglas noTerminalState = reglas::S; // empieza en el axioma S
    analizador.tsg = TSG;
    TSG->nombre = "TABLA GLOBAL";
    TSG->contador = contadorTablas++;
    Token token = analizador.processNextChar();

    parse_file << "descendente ";
    // cosas semanticas de S'
    // {TSG=CreaTabla(); desplG=0}
    noTerminal(noTerminalState, token);
    ficheroTS << *TSG << endl;
    // cout << *TSG << endl;
    // {LiberaTabla(TSG)}
}
