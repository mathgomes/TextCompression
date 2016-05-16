/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016
    main.cpp
    Objetivo: Realizar todas as chamadas de funções necessárias
    para receber e processar as entradas

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
*/
#include "burrowswheeler.h"
#include "huffman.hpp"
#include "runLength.hpp"
#include "compressor.hpp"
#include <string>
#include <sstream>

#define TRUE 1
#define FALSE 0

using namespace std;

/*
    Extensões           Métodos utilizados:
    dos arquivos:

    .huf                Huffman
    .rln                Run-Length
    .bwt                Burrows-Wheeler Transform
    .hrl                Huffman e Run-Length
    .hbw                Huffman e Burrows-Wheeler Transform
    .rbw                Run-Length e Burrows-Wheeler Transform
    .bhr                Todos

*/

int main(int argc, char *argv[]){
    //   1     2        3      4               5            6          7         8            9
    // encode -i entrada.txt -o nome_do_arquivo_binario --bwt=true --txtblck=15 --huffman=false --runl=false
    // decode -i arquivo_binario.bin -o saida.txt
    if(argc!=10){
        cout<<"\nPor favor insira o número correto de argumentos:\n\n\tencode -i arquivo_original.txt -o arquivo_binario --bwt=X --txtblck=X --huffman=X --runl=X\n";
        cout<<"\t\t\t\t\t\t  ou\n\t\t\tdecode -i arquivo_binario.<extensão> -o arquivo_descompactado.txt"<<endl<<endl;
        return -1;
    }
    string input_name(argv[3]), output_name(argv[5]), bwt(argv[6]), txtblck(argv[7]), huffman(argv[8]), runl(argv[9]), process(argv[1]);
    txtblck = txtblck.substr(10, txtblck.size()-10);

    int b = FALSE, h = FALSE, r = FALSE;
    if(!bwt.substr(6, bwt.size()-6).compare("true"))
        b = TRUE;
    if(!huffman.substr(10, huffman.size()-10).compare("true"))
        h = TRUE;
    if(!runl.substr(7, runl.size()-7).compare("true"))
        r = TRUE;
    if(!process.compare("encode")){


        if(b && h && r){
            cout<<"\nComprimindo usando todos os métodos...."<<endl;
            output_name+=".bhr";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            string bwt = output_ss.str(); // string que representa a saída do btw

            // header para guardar as informações uteis
            string header;

            // String codificada com huffman sem compressão
            string encodedTextHUF;
            // String codificada com huffman comprimida
            char *compressedHUF;
            // Tamanho do vetor da string comprimida
            int compressedSizeHUF;

            // String codificada com run length ( estrutura letra->repetição)
            vector<codedSymbol> encodedTextRL;
            // vetor de booleanos representando os valores não comprimidos
            // das repetições de cada caracter
            vector<bool> booleanReps;
            // vetor representando os valores comprimidos de cada repetição
            char *compressedReps;
            // tamanho do vetor de valroes comprimidos
            int sizeCompressedRL;

            readInputFile(input_name,originalText);

            RLencode(bwt,encodedTextRL,booleanReps,header);
            compressedReps = RLcompress(encodedTextRL,booleanReps,&sizeCompressedRL);
            stringstream sstr2;
            int i = 0;
            for( codedSymbol s : encodedTextRL) {

                sstr2 << s.symbol;
                sstr2 << compressedReps[i];
                i++;
            }
            string outputRL = sstr2.str();
            HUFencode(outputRL,encodedTextHUF,header);
            compressedHUF = HUFcompress(encodedTextHUF,&compressedSizeHUF);
            writeToFileHUF(header,output_name,&compressedSizeHUF,compressedHUF);


        } else if (b && h){
            cout<<"\nComprimindo usando BWT e Huffman..."<<endl;
            output_name+=".hbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            string bwt = output_ss.str(); // string que representa a saída do btw

            string header;
            string originalText;
            string encodedText;
            char *compressedHUF;
            int compressedSize;

            readInputFile(input_name,originalText);
            HUFencode(bwt,encodedText,header);
            compressedHUF = HUFcompress(encodedText,&compressedSize);
            writeToFileHUF(header,output_name,&compressedSize,compressedHUF);

        } else if(b && r){
            cout<<"\nComprimindo usando BWT e Run-Length..."<<endl;
            output_name+=".rbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            string bwt = output_ss.str(); // string que representa a saída do btw

            string header;
            string originalText;

            vector<codedSymbol> encodedText;
            vector<bool> booleanReps;
            char *compressedReps;
            int sizeCompressed;

            RLencode(bwt,encodedText,booleanReps,header);
            compressedReps = RLcompress(encodedText,booleanReps,&sizeCompressed);
            writeToFileRL(output_name,header,compressedReps,&sizeCompressed,encodedText);

        } else if(h && r){
            cout<<"\nComprimindo usando Huffman e Run-Length..."<<endl;
            output_name+=".hrl";

            string header;
            string originalText;

            string encodedTextHUF;
            char *compressedHUF;
            int compressedSizeHUF;

            vector<codedSymbol> encodedText;
            vector<bool> booleanReps;
            char *compressedReps;
            int sizeCompressedRL;

            readInputFile(input_name,originalText);

            HUFencode(originalText,encodedTextHUF,header);
            compressedHUF = HUFcompress(encodedTextHUF,&compressedSizeHUF);
            string compressedHUFstr(compressedHUF);

            RLencode(originalText,encodedText,booleanReps,header);
            compressedReps = RLcompress(encodedText,booleanReps,&sizeCompressedRL);
            writeToFileRL(output_name,header,compressedReps,&sizeCompressedRL,encodedText);



        } else if(b){
            cout<<"\nCodificando usando Burrows-Wheeler Transform..."<<endl;
            output_name+=".bwt";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
        } else if(h){
            output_name+=".huf";
            cout<<"\nComprimindo usando Huffman..."<<endl;

            string header;
            string originalText;
            string encodedText;
            char *compressedHUF;
            int compressedSize;

            readInputFile(input_name,originalText);
            HUFencode(originalText,encodedText,header);
            compressedHUF = HUFcompress(encodedText,&compressedSize);
            writeToFileHUF(header,output_name,&compressedSize,compressedHUF);


        } else if(r){
            output_name+=".rln";
            cout<<"\nComprimindo usando Run-Length..."<<endl;

            string header;
            string originalText;

            vector<codedSymbol> encodedText;
            vector<bool> booleanReps;
            char *compressedReps;
            int sizeCompressed;

            readInputFile(input_name,originalText);
            RLencode(originalText,encodedText,booleanReps,header);
            compressedReps = RLcompress(encodedText,booleanReps,&sizeCompressed);
            writeToFileRL(output_name,header,compressedReps,&sizeCompressed,encodedText);
        }
    } else if (!process.compare("decode")){
        string file_ext = input_name.substr(input_name.size()-4, 4); // extensão do arquivo
        if(!file_ext.compare(".bhr")){
            cout<<"\nDescomprimindo usando todos os métodos..."<<endl;


            string result; // string resultado dos métodos anteriores

            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if (!file_ext.compare(".hbw")){
            cout<<"\nDescomprimindo usando BWT e Huffman..."<<endl;


            string result; // string resultado dos métodos anteriores

            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if(!file_ext.compare(".rbw")){
            cout<<"\nDescomprimindo usando BWT e Run-Length..."<<endl;


            string result; // string resultado dos métodos anteriores

            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if(!file_ext.compare(".hrl")){
            cout<<"\nDescomprimindo usando Huffman e Run-Length..."<<endl;


        } else if(!file_ext.compare(".bwt")){
            cout<<"\nDecodificando usando Burrows-Wheeler Transform..."<<endl;
            ifstream input_file;
            input_file.open(input_name.c_str(), ios::binary | ios::in);

            if(!input_file.is_open()){
                cout<<"Arquivo de entrada não encontrado."<<endl;
                return -1;
            }
            stringstream input_ss;
            input_ss<<input_file.rdbuf();
            input_file.close();
            BWTdecode(input_ss, output_name);
        } else if(!file_ext.compare(".huf")){
            cout<<"\nDescomprimindo usando Huffman..."<<endl;


        } else if(!file_ext.compare(".rln")){
            cout<<"\nDescomprimindo usando Run-Length..."<<endl;

            int maxFreqBits;
            int sizeCharactersArray;
            int sizeCompressedArray;
            string header;
            FILE *arq;
            arq = fopen(input_name.c_str(),"rb");
            // guardar o tamanho do header antes
            int res1 = fread(&header[0],sizeof(int),1,arq);
            int res2 = fread(&sizeCharactersArray,sizeof(int),1,arq);
            int res3 = fread(&sizeCompressedArray,sizeof(int),1,arq);

            string charactersRL;
            charactersRL.resize(sizeCharactersArray);
            string compressedRL;
            compressedRL.resize(sizeCompressedArray);

            fread(&charactersRL[0],sizeCharactersArray*sizeof(char),1,arq);
            fread(&compressedRL[0],sizeCompressedArray*sizeof(char),1,arq);

            string result = decompressRL(charactersRL,compressedRL,&maxFreqBits);


        } else {
            cout<<"\nPor favor insira um arquivo com extensão válida.\n"<<endl;
        }
    }
    cout<<"Fim do Processo.\n\n";
    return 0;
}
