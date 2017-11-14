@echo off

pushd src

cl /Fe..\compiler.exe *.cpp

del *.obj
pushd ..
