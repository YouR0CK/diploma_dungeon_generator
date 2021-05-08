#include "basicentity.h"

BasicEntity::BasicEntity() :
    m_width(0),
    m_length(0),
    m_height(0),
    m_position(Position::kUndefined),
    m_coord{0, 0, 0}
{

}

BasicEntity::BasicEntity(double width,
                         double length,
                         double height,
                         Position position,
                         float coord[]) :
    m_width(width),
    m_length(length),
    m_height(height),
    m_position(position),
    m_coord{coord[0], coord[1], coord[2]}
{

}

double BasicEntity::getWidth()
{
    return m_width;
}

double BasicEntity::getLength()
{
    return m_length;
}

double BasicEntity::getHeight()
{
    return m_height;
}

Position BasicEntity::getPosition()
{
    return m_position;
}

float* BasicEntity::getCoordinates()
{
    return m_coord;
}

void BasicEntity::setWidth(double width)
{
    m_width = width;
}

void BasicEntity::setLength(double length)
{
    m_length = length;
}

void BasicEntity::setHeight(double heigth)
{
    m_height = heigth;
}

void BasicEntity::setPosition(Position position)
{
    m_position = position;
}

void BasicEntity::setCoordinates(float coord[])
{
    m_coord[0] = coord[0];
    m_coord[1] = coord[1];
    m_coord[2] = coord[2];
}

