@echo off
g++ -O2 -s -Wall -std=c++17 .\main.cpp -I SFML\include\ -L SFML\lib\ -lsfml-main -lsfml-graphics -lsfml-system -lsfml-window -o bin\run