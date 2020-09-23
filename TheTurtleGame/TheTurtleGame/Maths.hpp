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