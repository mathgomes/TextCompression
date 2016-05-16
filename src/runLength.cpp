/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016
    runLength.cpp
    Objetivo: Codificar e decodificar cadeias de caracteres
    usando o método run length.

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
*/
#include "compressor.hpp"

using namespace std;



void RLencode(string& simbols,vector<codedSymbol> &resultRL,
    vector<bool>& compressedReps, string &header) {

    resultRL = generateReps(simbols);
    int resultRLsize = resultRL.size();
    compressedReps = compressRLreps(resultRL,resultRLsize,header);
}

char* RLcompress(vector<codedSymbol>& resultRL,vector<bool> &booleanReps,
    int *sizeCompressed) {
    char* compressedReps;
    compressedReps = compressBooleanArray(booleanReps,sizeCompressed);
    return compressedReps;
}
void writeToFileRL(string &output, string &header, char *compressedReps,
    int *sizeCompressed,vector<codedSymbol>& resultRL) {

    string charactersRL;
    for( codedSymbol cS : resultRL) {
        charactersRL += cS.symbol;
    }

    int sizeCharacters = charactersRL.size();

    FILE *arq;
    arq = fopen(output.c_str(),"wb");
    // escreve o header
    fwrite(&header[0],header.size(),1,arq);
    // escreve a quantidade de caracteres ( para leitura posteriormente)
    fwrite(&sizeCharacters,sizeof(int),1,arq);
    // escreve o tamanho do vetor comprimido de repetições
    fwrite(&sizeCompressed,sizeof(int),1,arq);
    // escreve o vetor de caracteres
    fwrite(&charactersRL[0],sizeCharacters*sizeof(char),1,arq);
    // escreve o vetor comprimido
    fwrite(&compressedReps[0],*sizeCompressed * sizeof(char),1,arq);

    fclose(arq);

}
vector<codedSymbol> generateReps(string &symbols) {

    vector<codedSymbol> encodedSymbols;
    codedSymbol *s;
    for( unsigned int i = 0; i < symbols.size(); ) {
        s = new codedSymbol;
        s->symbol = symbols[i];
        s->reps = 1;

        while(symbols[i] == symbols[i+1]) {

            s->reps++;
            i++;
        }
        encodedSymbols.push_back(*s);
        i++;
    }
    return encodedSymbols;
}


