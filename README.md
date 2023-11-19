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
auto world = "world"_strc;
static_assert(std::is_same<
    decltype(world),
    cgx::strc<char, 'w', 'o', 'r', 'l', 'd'>
  >::value, "same type");
```
