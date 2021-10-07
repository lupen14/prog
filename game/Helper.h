#ifndef HELPER_H
#define HELPER_H

#include <QPointF>

namespace Helper
{
    static const int GAME_VERSION   = 002;

    static const int SCENE_X1   = -256;
    static const int SCENE_Y1   = -256;
    static const int SCENE_X2   = 512;
    static const int SCENE_Y2   = 512;

    static const int BORDER_MAX_X   = 256;
    static const int BORDER_MIN_X   = -256;
    static const int BORDER_MAX_Y   = 256;
    static const int BORDER_MIN_Y   = -256;

    static const int FIELD_SIZE_X       = 31;
    static const int FIELD_SIZE_Y       = 31;
    static const int FIELD_SIZE         = 16;
    static const int FIELD_HALF_SIZE    = FIELD_SIZE/2;


    static const int SPEED_GAME     = (int)(1000 / 6);
    static const int SPEED_SNAKE    = SPEED_GAME;
}

namespace Angle
{
    static const int ANGLE_0    = 0;
    static const int ANGLE_90   = 90;
    static const int ANGLE_180  = 180;
    static const int ANGLE_270  = 270;
}

namespace Movement
{
    enum Direction
    {
        UP      = 0,
        DOWN    = 1,
        RIGHT   = 2,
        LEFT    = 3,
        ALL     = 4
    };
}

namespace AppleFlags
{
    enum Flags
    {
        NORMAL  = 0,
        MOVE
    };

}

#endif // HELPER_H
