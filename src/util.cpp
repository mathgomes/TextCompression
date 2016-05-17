/**
    UNIVERSIDADE DE S�O PAULO - ICMC
    DEPARTAMENTO DE CI�NCIAS DE COMPUTA��O
    SCC0261 Multim�dia - 1o Sem/2016

    @author Matheus Gomes da Silva Horta - 8532321
            B�rbara Darques Barros       - 7243081
*/
#include "util.hpp"



bool isGreaterNum (int i,int j) {
    return (i>j);
}
void readInputFile(string& fInput_name, string &inputText) {

    FILE *input;
    input = fopen(fInput_name.c_str(),"r");
    if( input == NULL) {
        printf("Arquivo n�o existe");
    }

    fseek(input,0,SEEK_END);
    inputText.resize(ftell(input));
    rewind(input);
    fread(&inputText[0],inputText.size(),1,input);
    fclose(input);
}

int readBit(int *c, int *offset) {
    int bit = (*c >> *offset) & 0x01;
    return bit;
}

string compressBooleanArray(vector<bool> &bArray) {

    int counter = 1;
    char offset = 7;
    string buffer;
    buffer.resize(counter);


    for(const bool &b : bArray) {
        // percorre um bloco de 8 bits da string de booleanos e
        // ent�o aloca um novo byte no buffer de compress�o
        if(offset == -1) {
            offset = 7;
            buffer.resize(++counter);
        }
        buffer[counter-1] |= b << offset;
        offset--;
    }
    return buffer;
}
