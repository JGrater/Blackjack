cmake_minimum_required(VERSION 3.31)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Blackjack main.cpp
        Deck.cpp
        Deck.h
        Blackjack.cpp
        Blackjack.h
        Player.h
        Player.cpp
        Renderer.h
        Settings.h
        Hand.h)
