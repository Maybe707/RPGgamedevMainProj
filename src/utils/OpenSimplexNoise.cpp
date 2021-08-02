#include "OpenSimplexNoise.h"
#include <cmath>

#define STRETCH_2D -0.211324865405187 
#define SQUISH_2D 0.366025403784439

OpenSimplexNoise::OpenSimplexNoise(u64 seed) : m_gradients2D{ 5,  2,  2,  5,
                                                             -5,  2, -2,  5,
                                                              5, -2,  2, -5,
                                                             -5, -2, -2, -5}
{
    i16 source[PSIZE];
    for (i16 i = 0; i < PSIZE; i++)
    {
        source[i] = i;
    }

    for (i32 i = PSIZE; i >= 0; i--)
    {
        seed = seed * 6364136223846793005L + 1442695040888963407L;
        i32 r = static_cast<i32>((seed + 31) % (i + 1));
        if (r < 0)
        {
            r += (i + 1);
        }
        m_perm[i] = source[r];
        m_permGradIndex2d[i] = m_gradients2D[m_perm[i]];
        source[r] = source[i];
    }
    
}

double OpenSimplexNoise::eval(double x, double y) const
{
    double stretchOffset = (x + y) * STRETCH_2D;
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;

    int xsb = static_cast<int>(floor(xs));
    int ysb = static_cast<int>(floor(ys));

    double squishOffset = (xsb + ysb) * SQUISH_2D;
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;

    double xins = xs - xsb;
    double yins = ys - ysb;

    double inSum = xins + yins;

    double dx0 = x - xb;
    double dy0 = y - yb;
    
    double dx_ext, dy_ext;
    int xsv_ext, ysv_ext;

    double value = 0;

    double dx1 = dx0 - 1 - SQUISH_2D;
    double dy1 = dy0 - 0 - SQUISH_2D;
    double attn1 = 2 - dx1 * dx1 - dy1 * dy1;
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += attn1 * attn1 * extrapolate(xsb + 1, ysb + 0, dx1, dy1);
    }

    double dx2 = dx0 - 0 - SQUISH_2D;
    double dy2 = dy0 - 1 - SQUISH_2D;
    double attn2 = 2 - dx2 * dx2 - dy2 * dy2;
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += attn2 * attn2 * extrapolate(xsb + 0, ysb + 1, dx2, dy2);
    }

    if (inSum <= 1)
    {
      double zins = 1 - inSum;
      if (zins > xins || zins > yins)
      {
        if (xins > yins)
        {
          xsv_ext = xsb + 1;
          ysv_ext = ysb - 1;
          dx_ext = dx0 - 1;
          dy_ext = dy0 + 1;
        }
        else
        {
          xsv_ext = xsb - 1;
          ysv_ext = ysb + 1;
          dx_ext = dx0 + 1;
          dy_ext = dy0 - 1;
        }
      }
      else
      { //(1,0) and (0,1) are the closest two vertices.
        xsv_ext = xsb + 1;
        ysv_ext = ysb + 1;
        dx_ext = dx0 - 1 - 2 * SQUISH_2D;
        dy_ext = dy0 - 1 - 2 * SQUISH_2D;
      }
    }
    else
    {
      double zins = 2 - inSum;
      if (zins < xins || zins < yins)
      {
        if (xins > yins)
        {
          xsv_ext = xsb + 2;
          ysv_ext = ysb + 0;
          dx_ext = dx0 - 2 - 2 * SQUISH_2D;
          dy_ext = dy0 + 0 - 2 * SQUISH_2D;
        }
        else
        {
            xsv_ext = xsb + 0;
          ysv_ext = ysb + 2;
          dx_ext = dx0 + 0 - 2 * SQUISH_2D;
          dy_ext = dy0 - 2 - 2 * SQUISH_2D;
        }
      }
      else
      {
        dx_ext = dx0;
        dy_ext = dy0;
        xsv_ext = xsb;
        ysv_ext = ysb;
      }
      xsb += 1;
      ysb += 1;
      dx0 = dx0 - 1 - 2 * SQUISH_2D;
      dy0 = dy0 - 1 - 2 * SQUISH_2D;
    }

    double attn0 = 2 - dx0 * dx0 - dy0 * dy0;
    if (attn0 > 0)
    {
      attn0 *= attn0;
      value += attn0 * attn0 * extrapolate(xsb, ysb, dx0, dy0);
    }

    double attn_ext = 2 - dx_ext * dx_ext - dy_ext * dy_ext;
    if (attn_ext > 0)
    {
      attn_ext *= attn_ext;
      value += attn_ext * attn_ext * extrapolate(xsv_ext, ysv_ext, dx_ext, dy_ext);
    }

    return value * (1.0 / 47.0);
}

double OpenSimplexNoise::extrapolate(i32 xsb, i32 ysb, double dx, double dy) const
{
  i32 index = m_perm[(m_perm[xsb & PMASK] + ysb) & PMASK] & 0x0E;
  return m_gradients2D[index] * dx * m_gradients2D[index + 1] * dy;
}
