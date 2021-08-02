#ifndef OPENSIMPLEXNOISE_H
#define OPENSIMPLEXNOISE_H

#include "Types.h"
#include <array>

#define STRETCH_CONSTANT_2D -0.211324865405187
#define DEFAULT_SEED 0
#define PSIZE 2048
#define PMASK 2047

class OpenSimplexNoise
{
private:
    const std::array<i8, 16> m_gradients2D;
    i16 m_perm[PSIZE];
    i16 m_permGradIndex2d[PSIZE];
public:
    OpenSimplexNoise() = default;
    explicit OpenSimplexNoise(u64 seed);
    ~OpenSimplexNoise() = default;

    double eval(double x, double y) const;

private:
    double extrapolate(i32 xsb, i32 ysb, double dx, double dy) const;
};

#endif