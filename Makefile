build:
	g++ -std=c++17 main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app
