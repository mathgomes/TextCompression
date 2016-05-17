#include "burrowswheeler.h"
#include "runlength.h"
#include "huffman.h"
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
    // encode -i entrada.txt -o nome_do_arquivo_binario --bwt=true --txtblck=15 --huffman=true --runl=true 
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
            stringstream bwt_output_ss, rl_output_ss, output_ss;
            // aplica BWT
            BWTencode(input_name, bwt_output_ss, block_size);
            // aplica Run-Length
            RLcompress(bwt_output_ss, rl_output_ss);
            // aplica Huffman
            applyHuffman(rl_output_ss, output_ss);
            // salva em arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
            
        } else if (b && h){
            cout<<"\nComprimindo usando BWT e Huffman..."<<endl;
            output_name+=".hbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss, bwt_output_ss;
            // aplica BWT
            BWTencode(input_name, bwt_output_ss, block_size);
            // aplica Huffman
            applyHuffman(bwt_output_ss, output_ss);
            // salva em arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();

        } else if(b && r){
            cout<<"\nComprimindo usando BWT e Run-Length..."<<endl;
            output_name+=".rbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream bwt_output_ss, rl_output_ss;
            // aplica BWT
            BWTencode(input_name, bwt_output_ss, block_size);
            // aplica Run-Length
            RLcompress(bwt_output_ss, rl_output_ss);
            // salva em arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<rl_output_ss.rdbuf();
            output.close();
        } else if(h && r){
            cout<<"\nComprimindo usando Huffman e Run-Length..."<<endl;
            output_name+=".hrl";
            
            stringstream input_ss, rl_output_ss, huf_output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            applyHuffman(input_ss, huf_output_ss);
            RLcompress(huf_output_ss, rl_output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<rl_output_ss.rdbuf();
            output.close();
            
        } else if(b){
            cout<<"\nCodificando usando Burrows-Wheeler Transform..."<<endl;
            output_name+=".bwt";
            int block_size;
            // passa o tamanho do bloco de string pra int
            stringstream sstr(txtblck);
            sstr>>block_size;
            //-------------------------------------------
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
        } else if(h){
            output_name+=".huf";
            cout<<"\nComprimindo usando Huffman..."<<endl;
            
            stringstream input_ss, output_ss, output_ss2;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            applyHuffman(input_ss, output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
            
        } else if(r){
            output_name+=".rln";
            cout<<"\nComprimindo usando Run-Length..."<<endl;
            
            stringstream input_ss, output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            RLcompress(input_ss, output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
        }
    } else if (!process.compare("decode")){
        string file_ext = input_name.substr(input_name.size()-4, 4); // extensão do arquivo
        if(!file_ext.compare(".bhr")){
            cout<<"\nDescomprimindo usando todos os métodos..."<<endl;
            stringstream input_ss, huf_output_ss, rl_output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            // aplica Huffman
            decodeHuffman(input_ss, huf_output_ss);
            // aplica Run-Length
            RLdecompress(huf_output_ss, rl_output_ss);
            // aplica BWT
            BWTdecode(rl_output_ss, output_name);
        } else if (!file_ext.compare(".hbw")){
            cout<<"\nDescomprimindo usando BWT e Huffman..."<<endl;
            
            stringstream input_ss, output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            decodeHuffman(input_ss, output_ss);
            BWTdecode(output_ss, output_name);
        } else if(!file_ext.compare(".rbw")){
            cout<<"\nDescomprimindo usando BWT e Run-Length..."<<endl;
            
            stringstream input_ss, rl_output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            RLdecompress(input_ss, rl_output_ss);
            BWTdecode(rl_output_ss, output_name);
        } else if(!file_ext.compare(".hrl")){
            cout<<"\nDescomprimindo usando Huffman e Run-Length..."<<endl;
            
            stringstream input_ss, rl_output_ss, huf_output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            RLdecompress(input_ss, rl_output_ss);
            decodeHuffman(rl_output_ss, huf_output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<huf_output_ss.rdbuf();
            output.close();
            
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
            stringstream input_ss, output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            decodeHuffman(input_ss, output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
        } else if(!file_ext.compare(".rln")){
            cout<<"\nDescomprimindo usando Run-Length..."<<endl;
            
            stringstream input_ss, output_ss;
            ifstream input_file;
            // passa do arquivo pra entrada em stringstream
            input_file.open(input_name.c_str(), ios::binary | ios::in);
            input_ss<<input_file.rdbuf();
            input_file.close();
            //----------------------------------
            RLdecompress(input_ss, output_ss);
            // passa da saida em stringstream para o arquivo
            ofstream output;
            output.open(output_name.c_str(), ios::binary | ios::out);
            output<<output_ss.rdbuf();
            output.close();
            
        } else {
            cout<<"\nPor favor insira um arquivo com extensão válida.\n"<<endl;
        }
    }
    cout<<"Fim do Processo.\n\n";
    return 0;
}