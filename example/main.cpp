#include <iostream>

#include "../strc.hpp"

int main() {
    auto hello = "hello "_strc;
    auto world = "world"_strc;
    static_assert(std::is_same<decltype(world),
                               cgx::strc<char, 'w', 'o', 'r', 'l', 'd'>>::value,
                  "same type");

    std::cout << "'hello ': " << hello.id() << std::endl;
    std::cout << "'world': " << world.id() << std::endl;

    auto hello_world = hello + world;
    std::cout << "'hello ' + 'world': " << hello_world.id() << std::endl;

    auto japanese = "日本語でも出来ます！"_strc;
    std::cout << "'日本語でも出来ます！': " << japanese.id() << std::endl;

    auto split = hello_world.split();
    static_assert(std::get<0>(split) == "h"_strc,
                  "Split should break down all the characters into independent "
                  "strc at compile time");
    std::cout << std::get<0>(split).id() << std::endl;
    std::cout << std::get<1>(split).id() << std::endl;

    auto filename = __FILE__ ""_strc;
    std::cout << "We can combine it with macros: " << filename.id()
              << std::endl;

    return 0;
}
