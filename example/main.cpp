#include <iostream>

#include "../strc.hpp"

int main() {
    auto hello = "Hello "_strc;
    auto world = "World"_strc;

    std::cout << "'Hello ': " << hello.id() << std::endl;
    std::cout << "'World': " << world.id() << std::endl;

    auto hello_world = hello + world;
    std::cout << "'Hello ' + 'World': " << hello_world.id() << std::endl;

    auto japanese = "日本語でも出来ます！"_strc;
    std::cout << "'日本語でも出来ます！': " << japanese.id() << std::endl;

    auto split = hello_world.split();
    static_assert(std::get<0>(split) == "H"_strc,
                  "Split should break down all the characters into independent "
                  "strc at compile time");
    std::cout << std::get<0>(split).id() << std::endl;
    std::cout << std::get<1>(split).id() << std::endl;

    auto filename = __FILE__ ""_strc;
    std::cout << "We can combine it with macros: " << filename.id()
              << std::endl;

    return 0;
}
