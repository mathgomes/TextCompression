#include "burrowswheeler.h"
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
            
            // -----------> Matheus, pegue a string "bwt" e coloque como entrada do seu método
            
            // (CÓDIGO DO MATHEUS)
            
        } else if (b && h){
            cout<<"\nComprimindo usando BWT e Huffman..."<<endl;
            output_name+=".hbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            string bwt = output_ss.str(); // string que representa a saída do btw
            
            // ------------> Matheus, pegue a string "bwt" e coloque como entrada do seu método
            
            // (CÓDIGO DO MATHEUS)
            
        } else if(b && r){
            cout<<"\nComprimindo usando BWT e Run-Length..."<<endl;
            output_name+=".rbw";
            int block_size;
            stringstream sstr(txtblck);
            sstr>>block_size;
            stringstream output_ss;
            BWTencode(input_name, output_ss, block_size);
            string bwt = output_ss.str(); // string que representa a saída do btw
            
            // -------------> Matheus, pegue a string "bwt" e coloque como entrada do seu método
            
            // (CÓDIGO DO MATHEUS)
            
        } else if(h && r){
            cout<<"\nComprimindo usando Huffman e Run-Length..."<<endl;
            output_name+=".hrl";
            
            // (CÓDIGO DO MATHEUS)
            
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
            
            // (CÓDIGO DO MATHEUS)
            
        } else if(r){
            output_name+=".rln";
            cout<<"\nComprimindo usando Run-Length..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
        }
    } else if (!process.compare("decode")){
        string file_ext = input_name.substr(input_name.size()-4, 4); // extensão do arquivo
        if(!file_ext.compare(".bhr")){
            cout<<"\nDescomprimindo usando todos os métodos..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
            // ------------> Matheus, coloque a saída dos seus métodos na string result abaixo
            
            string result; // string resultado dos métodos anteriores
        
            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if (!file_ext.compare(".hbw")){
            cout<<"\nDescomprimindo usando BWT e Huffman..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
            // ------------> Matheus, coloque a saída dos seus métodos na string result abaixo
            
            string result; // string resultado dos métodos anteriores
        
            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if(!file_ext.compare(".rbw")){
            cout<<"\nDescomprimindo usando BWT e Run-Length..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
            // ------------> Matheus, coloque a saída dos seus métodos na string result abaixo
            
            string result; // string resultado dos métodos anteriores
        
            stringstream input_ss;
            input_ss.write(&result[0], result.size());
            BWTdecode(input_ss, output_name);
        } else if(!file_ext.compare(".hrl")){
            cout<<"\nDescomprimindo usando Huffman e Run-Length..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
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
            
            // (CÓDIGO DO MATHEUS)
            
        } else if(!file_ext.compare(".rln")){
            cout<<"\nDescomprimindo usando Run-Length..."<<endl;
            
            // (CÓDIGO DO MATHEUS)
            
        } else {
            cout<<"\nPor favor insira um arquivo com extensão válida.\n"<<endl;
        }
    }
    cout<<"Fim do Processo.\n\n";
    return 0;
}