@echo off

set SRC=..\src\

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl /ZI %SRC%main.cpp %SRC%Lexer.cpp %SRC%Token.cpp
