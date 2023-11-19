#include "../strc.hpp"

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

