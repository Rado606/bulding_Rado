cd compile

g++ -c ../SourceCode/main.cpp 
g++ -c ../SourceCode/budynek.cpp 


cd ..

g++ -o main compile/main.o compile/budynek.o

main.exe

