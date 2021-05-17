#include "basicroom.h"

BasicRoom::BasicRoom(float x, float y, float width, float length) : m_topLeftCoordinates{x, y}, m_width(width), m_length(length) {}

void BasicRoom::addDoor(Door newDoor)
{
    m_doors.append(newDoor);
}
