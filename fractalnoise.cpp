#include "fractalnoise.h"
#include "math.h"

#include <QRandomGenerator>

FractalNoise::FractalNoise()
{
    QRandomGenerator gen(1488);
    m_baPermutationTable.resize(1024);
    gen.fillRange(reinterpret_cast<uint *>(m_baPermutationTable.data()), m_baPermutationTable.size());
}

float FractalNoise::noise(float fx, float fy)
{
    //top left apex of square
    int left = static_cast<int>(floor(fx));
    int top = static_cast<int>(floor(fy));

    // local dot coordinates inside of square
    float pointInQuadX = fx - left;
    float pointInQuadY = fy - top;

    float *topLeftGradient = getPseudoRandomGradientVector(left, top);
    float *topRightGradient = getPseudoRandomGradientVector(left + 1, top);
    float *bottomLeftGradient = getPseudoRandomGradientVector(left, top + 1);
    float *bottomRightGradient = getPseudoRandomGradientVector(left + 1, top +1);

    float distanceToTopLeft[2] = {pointInQuadX, pointInQuadY};
    float distanceToTopRight[2] = {pointInQuadX - 1, pointInQuadY};
    float distanceToBottomLeft[2] = {pointInQuadX, pointInQuadY - 1};
    float distanceToBottomRight[2] = {pointInQuadX - 1, pointInQuadY - 1};

    //counting scalar product of vectors to be interpolated
    float tx1 = dot(distanceToTopLeft, topLeftGradient);
    float tx2 = dot(distanceToTopRight, topRightGradient);
    float bx1 = dot(distanceToBottomLeft, bottomLeftGradient);
    float bx2 = dot(distanceToBottomRight, bottomRightGradient);

    //preparing interpolation parameters to make it unlinear
    pointInQuadX = quintic(pointInQuadX);
    pointInQuadX = quintic(pointInQuadY);

    //innterpolation
    float tx = lerp(tx1, tx2, pointInQuadX);
    float bx = lerp(bx1, bx2, pointInQuadX);
    float tb = lerp(tx, bx, pointInQuadY);

    return tb;
}

float FractalNoise::multiOctaveNoise(float fx, float fy, int octaves, float persistence)
{
    float amplitude = 1;
    float max = 0;
    float result = 0;

    while (octaves -- > 0) {
        max += amplitude;
        result += noise(fx, fy) * amplitude;
                amplitude *= persistence;
                fx *= 2;
                fy *= 2;
    }
    return result/max;
}

float FractalNoise::lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

float FractalNoise::quintic(float t)
{
    return pow(t, 3) * (t * (t * 6 - 15) + 10);
}

float FractalNoise::cosine(float t)
{
    return (1 - cos(t * M_PI)) / 2;
}

float FractalNoise::cubic(float t)
{
    return -2 * pow(t, 3) + 3 * pow(t, 2);
}

float *FractalNoise::getPseudoRandomGradientVector(int x, int y)
{
    int v = static_cast<int>(((((x * 1055910892) ^ (y * 1556193525)) + 7782501394) & 1023));

    v = m_baPermutationTable[v] & 3;

    switch (v) {
    case 0:
        static float res[2] = {1, 0};
        return res;
    case 1:
        static float res1[2] = {-1, 0};
        return res1;
    case 2:
        static float res2[2] = {0, 1};
        return res2;
    default:
        static float res3[2] = {0, -1};
        return res3;
    }
}

float FractalNoise::dot(float a[], float b[])
{
    return a[0] * b[0] + a[1] * b[1];
}
