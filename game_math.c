#include "game_math.h"

float int_power(float x, int y)
{
    float ret = 1;

    for (int i = y; i > 0; --i)
    {
        ret *= x;
    }

    return ret;
}

float taylor_sin(float theta)
{

    while (theta > 2 * M_PI)
    {
        theta -= 2 * M_PI;
    }

    while (theta < -2 * M_PI)
    {
        theta += 2 * M_PI;
    }

    float ret = 0;

    for (int n = 0; n <= 8; ++n)
    {
        float numerator = int_power(-1, n) * int_power(theta, 2 * n + 1);

        float denominator = 1;
        for (int i = 2 * n + 1; i > 0; --i)
        {
            denominator *= i;
        }

        ret += numerator / denominator;
    }

    return ret;
}

float taylor_cos(float theta)
{
    while (theta > 2 * M_PI)
    {
        theta -= 2 * M_PI;
    }

    while (theta < -2 * M_PI)
    {
        theta += 2 * M_PI;
    }


    float ret = 0;

    for (int n = 0; n <= 8; ++n)
    {
        float numerator = int_power(-1, n) * int_power(theta, 2 * n);

        float denominator = 1;
        for (int i = 2 * n; i > 0; --i)
        {
            denominator *= i;
        }

        ret += numerator / denominator;
    }

    return ret;
}

int round_to_int(float val)
{
    if (val < 0.0)
    {
        return (int)(val - 0.5);
    }
    else
    {
        return (int)(val + 0.5);
    }
}

// Thanks Stackoverflow
// https://stackoverflow.com/questions/3581528/how-is-the-square-root-function-implemented
float bin_search_sqrt(float n)
{
    float lo = 1 < n ? 1 : n;
    float hi = 1 > n ? 1 : n;
    float mid;

    while (100 * lo * lo < n)
    {
        lo *= 10;
    }

    while (0.01 * hi * hi > n)
    {
        hi *= 0.1;
    }

    for (int i = 0; i < 100; ++i)
    {
        mid = (lo + hi) / 2;
        
        if (mid * mid == n)
        {
            return mid;
        }

        if (mid * mid > n)
        {
            hi = mid;
        }
        else
        {
            lo = mid;
        }
    }

    return mid;
}