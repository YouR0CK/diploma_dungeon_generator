#ifndef BASICENTITY_H
#define BASICENTITY_H

enum class Position {
    kUndefined = 0,
    kFloor,
    kWall,
    kCeiling
};

class BasicEntity
{
public:
    BasicEntity();
    BasicEntity(double width,
                double length,
                double height,
                Position position,
                float coord[]);

    double getWidth();
    double getLength();
    double getHeight();
    Position getPosition();
    float* getCoordinates();

    void setWidth(double width);
    void setLength(double length);
    void setHeight(double heigth);
    void setPosition(Position position);
    void setCoordinates(float coord[]);

private:
    /**
     * @param m_width
     * @param m_length
     * @param m_height
     * represents object's size
     */

    double m_width;
    double m_length;
    double m_height;

    /**
     * @param m_position
     * represents objects position in the room
     */

    Position m_position;

    /**
     * @param m_coord represents XYZ  coordinates
     * of top left angle of object
     * if it is a circle or ball - points to its center
     */
    float m_coord[3];

};

#endif // BASICENTITY_H
