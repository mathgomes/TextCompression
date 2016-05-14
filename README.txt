--------------------------------------------------------------------------------
                          Projeto de Compressão de Texto
--------------------------------------------------------------------------------
Alunos:                             Nº USP:
- Bárbara Darques Barros            7243081
- Matheus Gomes

================================================================================
                                COMO USAR
================================================================================

1) Execute o arquivo "install.sh" na linha de comando da seguinte forma:

    . ./install.sh
    
        ------------------------------------------------------------------------
            (Atenção!)
            Não se esqueça do "." inicial, a execução somente de "./install.sh"
            não será autorizada pelo sistema.
        ------------------------------------------------------------------------
    
2) Comprima ou descomprima seus arquivos usando comandos nos seguintes formatos:
    
    - Para comprimir:
    
        encode -i aquivo_original.txt -o nome_do_arquivo_comprimido --bwt=true --txtblck=15 --huffman=false --runl=false
        
        ------------------------------------------------------------------------
            (Atenção!)
            Insira o nome do arquivo de saída sem extensão, a extensão corres-
            pondente aos métodos aplicados será adicionada automaticamente.
        ------------------------------------------------------------------------
    - Para descomprimir:
    
        decode -i arquivo_comprimido.bin -o arquivo_descomprimido_de_saida.txt
        
        ------------------------------------------------------------------------
            (Atenção!)
            Diferentemente da entrada pra compressão, aqui todos os arquivos de-
            verão ser acompanhados de suas extensões. O método de compressão a 
            ser utilizado será definido pela extensão do arquivo de entrada.
        ------------------------------------------------------------------------
        
================================================================================
                              GUIA DE EXTENSÕES
================================================================================

    Como já mencionado, ao codificar/compactar um arquivo de texto o programa
    adicionará automaticamente uma extensão correspondente ao(s) método(s) de
    codificação/compactação aplicado(s). Essas extensões são as seguintes:
    
                Extensões           Métodos utilizados:
                dos arquivos:
                
                .huf                Huffman
                .rln                Run-Length
                .bwt                Burrows-Wheeler Transform
                .hrl                Huffman e Run-Length
                .hbw                Huffman e Burrows-Wheeler Transform
                .rbw                Run-Length e Burrows-Wheeler Transform
                .bhr                Todos
