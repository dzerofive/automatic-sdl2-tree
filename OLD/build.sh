#!/bin/bash

g++ ./main.cpp ./core/game.cpp -L./lib/ -lGL -ldl -o ./application `sdl2-config --cflags --libs` && ./application