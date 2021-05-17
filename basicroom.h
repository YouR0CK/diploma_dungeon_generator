#ifndef BASICROOM_H
#define BASICROOM_H

#include <QObject>

struct Door
{
    float _doorHingesCoord[2];
    float width;
};

class BasicRoom
{
public:
    BasicRoom(float x, float y, float width, float length);
    void addDoor(Door newDoor);

private:

    float m_topLeftCoordinates[2];
    float m_width;
    float m_length;

    QList<Door> m_doors;

};

#endif // BASICROOM_H
