# strc
String constant type for C++

This is a simple library that takes inspiration from [intel's compile-time-init-build](https://github.com/intel/compile-time-init-build) to create string constants that can be mapped to a unique identifier. Each string and its identifier is saved on a `strc.json` database that can be used later to parse the identifier.

This is useful when verbose logging is required, but size and runtime constraints prohibit extensive use of strings (e.g. embedded systems). All processing is done at compile time, and the device just needs to communicate the unique identifier.

By default, the size of the identifier is 32-bits, which should be more than enough for most projects. If you would like to use a different number of unique strings in you project, you can define its size with the following compiler flags:

- `CGX_STRC_8BIT`: for 8 bit size
- `CGX_STRC_16BIT`: for 16 bit size
- `CGX_STRC_32BIT`: for 32 bit size
- `CGX_STRC_64BIT`: for 64 bit size

Minimum requirement: `C++14`

See an example at: [example](./example)

## Usage

```cpp
#include "strc.hpp"

...

auto text = "A really long text"_strc;
std::uint32_t id = text.id();

```

Make sure to add `strc.cpp` into your target sources (this file is generated automatically by `./tools/make_strc.py` with the correct identifiers).

## How does it work?

This library exploits how a user-defined literal behaves when using it with string literals. When using templates, it is possible to unpack each character into a template parameter. Then, an external script gets the signature of each defined literal, and creates a unique id, which is dumped into `strc.cpp`. The project is recompiled with this new source and a link is established between the unique identifier and the string literal. Because everything happens at compile time, there is no runtime cost and assertions can be made statically when compiling.

```cpp
// ./example/main.cpp
#include <iostream>

#include "../format.hpp"
#include "../strc.hpp"

void output(const char* str, std::uint64_t id) {
    std::cout << str << ": " << std::hex << id << std::endl;
}

int main() {
    output("current size of strc", sizeof(cgx::strc_id_t));

    auto hello = "hello "_strc;
    auto world = "world"_strc;
    static_assert(
        std::is_same<
            decltype(world),
            cgx::strc<char, 'w', 'o', 'r', 'l', 'd'>
        >::value, "same type");

    std::cout << "Each word has a unique id: " << std::endl;
    output("'hello '", hello.id());
    output("'world'", world.id());

    std::cout << "We can combine them into a new word: " << std::endl;
    auto hello_world = hello + world;
    output("'hello ' + 'world'", hello_world.id());

    std::cout << "Any UTF-8 characters is supported: " << std::endl;
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

    return 0;
}
```
