/**
    UNIVERSIDADE DE S�O PAULO - ICMC
    DEPARTAMENTO DE CI�NCIAS DE COMPUTA��O
    SCC0261 Multim�dia - 1o Sem/2016


    @author Matheus Gomes da Silva Horta - 8532321
            B�rbara Darques Barros       - 7243081
*/
#include "runLength.hpp"
#include "util.hpp"

void RLencode(string &inputText, FILE *output, string *compressedOut) {

    // vetor para armazenar os caracteres, sem repeti��es
    string characters;
    // vetor para armazenar apenas as repeti��es de cada caracter
    vector<int> repetitions;
    // string para armazenar as repeti��es comprimidas em bytes
    string compressedReps;
    // vetor de booleanos para representar as repeti��es em formato binario
    vector<bool> booleanReps;


    int maxFreqBits = 31;
    int bit;
    int aux = 0;
    // Gera as repeti��es
    for( unsigned int i = 0; i < inputText.size(); ) {

        characters += inputText[i];
        repetitions.resize(characters.size());
        repetitions[aux]++;
        while(inputText[i] == inputText[i+1]) {
            repetitions[aux]++;
            i++;
        }
        i++;
        aux++;
    }

    // calcula qual o maior valor de bits que uma repeti��o pode ocupar
    vector<int> auxVector = repetitions;
    sort(auxVector.begin(), auxVector.end(),isGreaterNum);
    int largest = auxVector[0];

    do {
        bit = readBit(&largest,&maxFreqBits);
        maxFreqBits--;
    } while(bit != 1);
    maxFreqBits+=2;

    // gera o vetor binario com as repeti��es
    for(unsigned int i =0 ; i < repetitions.size(); i ++) {

        for(int k=0; k < maxFreqBits; k++){
            bit = readBit(&repetitions[i],&k);
            booleanReps.push_back(bit);
        }
    }

    // comprime o vetor binario em uma string byte a byte
    compressedReps = compressBooleanArray(booleanReps);

    // concatena o vetor de caracteres e a string comprimida de repeti��es
    *compressedOut = characters + compressedReps;

    int charactersQtd = characters.size();
    int compressedSize = compressedOut->size();
    // armazena informa��es que ser�o usadas
    fwrite(&maxFreqBits,sizeof(int),1,output);
    fwrite(&charactersQtd,sizeof(int),1,output);
    fwrite(&compressedSize,sizeof(int),1,output);
    fwrite(&compressedOut[0],compressedSize,1,output);


}

string RLdecode(string *compressedString, int *maxBitQtd, int *charactersQtd) {

    // separa a string de caracteres da string de repeti��es comprimida
    string characters(*compressedString,0,*charactersQtd);
    string compressedFreqs(*compressedString,*charactersQtd,compressedString->size()-1);
    string original = "";
    int bitRead;
    int numberOfReps = 0;
    int aux = 0;
    unsigned int index = 0;
    //percorre a string comprimida
    for( unsigned int i = 0; i <= compressedFreqs.size();i++) {
        // se chegou ao fim da string de caracteres, pare
        if(index == characters.size()) {
            break;
        }
        // percorre cada bit
        for(int k = 7; k >= 0; k --) {
            // auxiliar para teste se chegou no maximo de bits possiveis
            if(aux == *maxBitQtd) {
                for(int m = 0; m < numberOfReps; m ++) {
                    // replica o caracter de acordo com o numero de repeti��es
                    original += characters[index];
                    aux = 0;
                }
                numberOfReps = 0;
                index++;
            }
            // le o bit da esquerda para direita
            bitRead = readBit((int*)&compressedFreqs[i],&k);
            // adiciona o valor do bit na repeti��o
            if(bitRead == 1) {
                numberOfReps += pow(2,aux);
            }
            aux++;
            if(index == characters.size()) {
                break;
            }
        }
    }
    return original;
}
