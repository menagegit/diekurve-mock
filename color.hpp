#ifndef COLOR_HPP
#define COLOR_HPP

struct color_t
{
    int r, g, b, a;
};

const color_t red = { 255, 0, 0, 255 };
const color_t green = { 0, 255, 0, 255 };
const color_t blue = { 0, 0, 255, 255 };
const color_t pink = { 255, 0, 255, 255 };
const color_t purple = { 127, 0, 255, 255 };
const color_t cyan = { 0, 255, 255, 255 };
const color_t yellow = { 255, 255, 0, 255 };
const color_t orange = { 255, 128, 0, 255 };

#endif /* COLOR_HPP */
