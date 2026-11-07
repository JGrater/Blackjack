//
// Created by JGrater on 28/08/2026.
//

#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <chrono>
#include <random>

namespace ConsoleInput {

    template <typename T>
    T numericInput(const std::string_view prompt) {
        T input{};
        while (true) {
            std::cout << prompt;
            std::cin >> input;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        return input;
    }

    inline char charInput(const std::string_view prompt, const std::string_view validChars = "") {
        char input{};
        while (true) {
            std::cout << prompt;
            std::cin >> input;

            input = static_cast<char>(std::tolower(input));
            if (std::cin.fail() || (!validChars.empty() && validChars.find(input) == std::string_view::npos)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        return input;
    }

    inline std::string stringInput(const std::string_view prompt) {
        std::string input{};
        std::cout << prompt;
        std::getline(std::cin >> std::ws, input);
        return input;
    }

}


namespace Random {

    // Returns a seeded Mersenne Twister
    inline std::mt19937 generate() {
        std::random_device rd{};
        std::seed_seq ss{
            static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
            rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };
        return std::mt19937{ss};
    }

    inline std::mt19937 mt{generate()};

    // Generate a random int between [min, max] (inclusive)
    // * also handles cases where the two arguments have different types but can be converted to int
    inline int get(int min, int max) {
        return std::uniform_int_distribution{min, max}(mt);
    }

    // Generate a random value between [min, max] (inclusive)
    // * min and max must have the same type
    // * return value has same type as min and max
    // * Supported types:
    // *    short, int, long, long long
    // *    unsigned short, unsigned int, unsigned long, or unsigned long long
    // Sample call: Random::get(1L, 6L);             // returns long
    // Sample call: Random::get(1u, 6u);             // returns unsigned int
    template <typename T> T get(T min, T max) {
        return std::uniform_int_distribution<T>{min, max}(mt);
    }

    // Generate a random value between [min, max] (inclusive)
    // * min and max can have different types
    // * return type must be explicitly specified as a template argument
    // * min and max will be converted to the return type
    // Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
    // Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
    // Sample call: Random::get<std::int>(0, 6u);    // returns int
    template <typename R, typename S, typename T> R get(S min, T max) {
        return get<R>(static_cast<R>(min), static_cast<R>(max));
    }
}

#endif //COMMON_H
