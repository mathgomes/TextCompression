#!/bin/bash
alias encode='function func(){
                make all
                ./build/projeto encode $@
            };
            func'
alias decode='function func(){
                make all
                ./build/projeto decode $@ --bwt=bool --txtblck=0 --huffman=bool --runl=bool
            };
            func'
