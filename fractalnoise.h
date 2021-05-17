#ifndef FRACTALNOISE_H
#define FRACTALNOISE_H

#include <QByteArray>
#include <QObject>

class FractalNoise : public QObject
{
    Q_OBJECT

public:
    FractalNoise();

    /**
     * @brief generatePermutationTable
     * @param seed
     * this method should be called befor using noise to provide
     * gradient table
     */
    void generatePermutationTable(int seed = 1);

    Q_INVOKABLE float noise(float fx, float fy);
    Q_INVOKABLE float multiOctaveNoise(float fx, float fy, int octaves, float persistence = 0.5f);

private:
    /**
     * @brief lerp
     *  linear interpolation
     *
     * @param a - represents min coordinate
     * @param b - represents max coordinate
     * @param t - represents local coordinate
     * @return result of interpolation
     */
    float lerp(float a, float b, float t);

    /**
     * @brief quintic
     * @brief cosine
     * @brief cubic
     *
     *  can be passed as third parameter to lerp
     *  with local coordinate as its own parameter
     *  to increase curvature
     *
     * @param t - local coordinate
     * @return more curved result
     */

    float quintic(float t);
    float cosine(float t);
    float cubic(float t);
    float* getPseudoRandomGradientVector(int x, int y);     //add z coord later
    float dot(float a[], float b[]);

    uint m_permutationTable[1024];
};

#endif // FRACTALNOISE_H
