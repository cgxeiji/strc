#include <iostream>

#include "../strc.hpp"

void output(const char* str, std::uint64_t id) {
    std::cout << str << ": " << std::hex << id << std::endl;
}

enum class Enumerator {
    ItCanBeVerbose,
};

int main() {
    output("current size of strc", sizeof(cgx::strc_id_t));

    auto hello = "hello "_strc;
    auto world = "world"_strc;
    static_assert(std::is_same<decltype(world),
                               cgx::strc<char, 'w', 'o', 'r', 'l', 'd'>>::value,
                  "same type");

    std::cout << "Each word has a unique id: " << std::endl;
    output("'hello '", hello.id());
    output("'world'", world.id());

    std::cout << "We can combine them into a new word: " << std::endl;
    auto hello_world = hello + world;
    output("'hello ' + 'world'", hello_world.id());

    std::cout << "Any UTF-8 character is supported: " << std::endl;
    auto japanese = "日本語でも出来ます！"_strc;
    output("'日本語でも出来ます！'", japanese.id());

    std::cout << "If we reuse the same string, the unique id is reused:"
              << std::endl;
    auto hello_world2 = "hello world"_strc;
    output("'hello world'", hello_world2.id());

    std::cout << "We can split them into individual characters, each with a "
                 "unique id: "
              << std::endl;
    auto split = hello_world.split();
    static_assert(std::get<0>(split) == "h"_strc,
                  "Split should break down all the characters into independent "
                  "strc at compile time");
    output("h", std::get<0>(split).id());
    output("e", std::get<1>(split).id());

    std::cout << "We can combine it with macros:" << std::endl;
    auto filename = __FILE__ ""_strc;
    output("__FILE__: " __FILE__, filename.id());

    std::cout
        << "And format it with variables that are passed as a byte array: "
        << std::endl;
    auto data = cgx::format(
        "int: %d, char: %d, float: %f, double: "
        "%f, short: %d, long: %d"_strc,
        1, char(2), 3.14f, 2.223, uint16_t(1024), 100000);
    std::cout << "'int: %d, char: %d, float: %f, double: "
                 "%f, short: %d, long: %d'"
              << std::endl
              << "becomes:" << std::endl;
    for (auto& i : data) {
        std::cout << std::hex << static_cast<int>(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "The size of each parameter is calculated at compile time: "
              << std::endl;
    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "char: " << sizeof(char) << std::endl;
    std::cout << "float: " << sizeof(float) << std::endl;
    std::cout << "double: " << sizeof(double) << std::endl;
    std::cout << "short: " << sizeof(uint16_t) << std::endl;
    std::cout << "long: " << sizeof(uint32_t) << std::endl;

    std::cout << "We can also use it with enums: " << std::endl;
    auto enumerator = Enumerator::ItCanBeVerbose;
    auto enum_data = cgx::format("Enumerator: %d"_strc, cgx::enum_arg(enumerator));
    for (auto& i : enum_data) {
        std::cout << std::hex << static_cast<int>(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
