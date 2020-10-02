#pragma once

float inline lerp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

float inline clamp(float value, float min, float max) {
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}

#include <SFML/Graphics.hpp>

sf::Color inline RgbFromHsv(double h, double s, double v)
{
    // assuming hsv values in range 0-1
    h *= 6;    

    double fract = h - floor(h);
    double P = v * (1. - s);
    double Q = v * (1. - s * fract);
    double T = v * (1. - s * (1. - fract));
    
    if (0 <= h && h < 1)
        return sf::Color(v * 255, T * 255, P * 255);
    else if (1 <= h && h < 2)
        return sf::Color(Q * 255, v * 255, P * 255);
    else if (2 <= h && h < 3)
        return sf::Color(P * 255, v * 255, T * 255);
    else if (3 <= h && h < 4)
        return sf::Color(P * 255, Q * 255, v * 255);
    else if (4 <= h && h < 5)
        return sf::Color(T * 255, P * 255, v * 255);
    else if (5 <= h && h < 6)
        return sf::Color(v * 255, P * 255, Q * 255);
    else
        return sf::Color(0, 0, 0);
}