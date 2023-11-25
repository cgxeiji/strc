#include "../strc.hpp"
#include "../format.hpp"

template</*
    hello 
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 104, 101, 108, 108, 111, 32>>() { return 0; }

template</*
    world
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 119, 111, 114, 108, 100>>() { return 1; }

template</*
    hello world
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 104, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100>>() { return 2; }

template</*
    日本語でも出来ます！
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 230, 151, 165, 230, 156, 172, 232, 170, 158, 227, 129, 167, 227, 130, 130, 229, 135, 186, 230, 157, 165, 227, 129, 190, 227, 129, 153, 239, 188, 129>>() { return 3; }

template</*
    h
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 104>>() { return 4; }

template</*
    e
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 101>>() { return 5; }

template</*
    /main.cpp
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 47, 109, 97, 105, 110, 46, 99, 112, 112>>() { return 6; }

template</*
    int: %d, char: %d, float: %f, double: %f, short: %d, long: %d
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 105, 110, 116, 58, 32, 37, 100, 44, 32, 99, 104, 97, 114, 58, 32, 37, 100, 44, 32, 102, 108, 111, 97, 116, 58, 32, 37, 102, 44, 32, 100, 111, 117, 98, 108, 101, 58, 32, 37, 102, 44, 32, 115, 104, 111, 114, 116, 58, 32, 37, 100, 44, 32, 108, 111, 110, 103, 58, 32, 37, 100>>() { return 7; }

template</*
    int: %d, char: %d, float: %f, double: %f, short: %d, long: %d
*/>
cgx::strc_id_t cgx::get_fmt_strc_id<cgx::strc<char, 105, 110, 116, 58, 32, 37, 100, 44, 32, 99, 104, 97, 114, 58, 32, 37, 100, 44, 32, 102, 108, 111, 97, 116, 58, 32, 37, 102, 44, 32, 100, 111, 117, 98, 108, 101, 58, 32, 37, 102, 44, 32, 115, 104, 111, 114, 116, 58, 32, 37, 100, 44, 32, 108, 111, 110, 103, 58, 32, 37, 100>, int, char, float, double, unsigned short, int>() { return 7; }

template</*
    Enumerator: %d
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 69, 110, 117, 109, 101, 114, 97, 116, 111, 114, 58, 32, 37, 100>>() { return 8; }

template</*
    Enumerator: %d
*/>
cgx::strc_id_t cgx::get_fmt_strc_id<cgx::strc<char, 69, 110, 117, 109, 101, 114, 97, 116, 111, 114, 58, 32, 37, 100>, unsigned int>() { return 8; }

template</*
    Enumerator::ItCanBeVerbose
*/>
cgx::strc_id_t cgx::get_strc_id<cgx::strc<char, 69, 110, 117, 109, 101, 114, 97, 116, 111, 114, 58, 58, 73, 116, 67, 97, 110, 66, 101, 86, 101, 114, 98, 111, 115, 101>>() { return 9; }

