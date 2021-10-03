#ifndef HELPER_H
#define HELPER_H

#include <QPointF>

namespace Helper
{
    static const int SCENE_X1 = -256;
    static const int SCENE_Y1 = -256;
    static const int SCENE_X2 = 512;
    static const int SCENE_Y2 = 512;

    static const int BORDER_MAX_X = 256;
    static const int BORDER_MIN_X = -256;
    static const int BORDER_MAX_Y = 256;
    static const int BORDER_MIN_Y = -256;

    static const int FIELD_SIZE_X = 31;
    static const int FIELD_SIZE_Y = 31;
    static const int FIELD_SIZE = 16;

    static const int SPEED_GAME = (int)(1000 / 5);
}

#endif // HELPER_H
