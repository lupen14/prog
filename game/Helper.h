#ifndef HELPER_H
#define HELPER_H

// c с++ 11 typedef не использовтаь, лучше type alias (using name = type)
using itemType = int;

namespace Helper
{
    using snakeSpeed = int;

    static const int SPEED_GAME     = (int)(1000 / 6);
    static const int SPEED_SNAKE    = SPEED_GAME;

    enum ItemType
    {
        SNAKE   = 0,
        DOT     = 1,
        APPLE   = 2,
        PORTAl  = 3,
    };

    enum ItemZValue
    {
        Z_BACKGROUND,
        Z_SNAKE,
        Z_PORTAL
    };

    enum Mutagen
    {
        NONE = 1,
        SPEED = 2,
        ALL
    };

}

namespace Base
{
    static const int GAME_VERSION   = 002;

    static const int SCENE_X1   = -256;
    static const int SCENE_Y1   = -256;
    static const int SCENE_X2   = 512;
    static const int SCENE_Y2   = 512;

    static const int BORDER_MAX_X   = 240;
    static const int BORDER_MIN_X   = -240;
    static const int BORDER_MAX_Y   = 240;
    static const int BORDER_MIN_Y   = -240;

    static const int FIELD_SIZE_X       = 31;
    static const int FIELD_SIZE_Y       = 31;
    static const int FIELD_SIZE         = 16;
    static const int FIELD_HALF_SIZE    = FIELD_SIZE/2;
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
        NONE    = -1,
        UP,
        DOWN,
        RIGHT,
        LEFT
    };
}

#endif // HELPER_H
