all:
	g++ -std=c++11 -g -o SigProc main.cpp -lmpg123 -lao -lpulse-simple -lpulse
