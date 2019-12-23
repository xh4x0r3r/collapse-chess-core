#include "collapse/core.h"
#include "collapse/core/pieces.h"

namespace collapse {
namespace core {

bool
Bishop::isValidMove(const IMap &map, const IPoint &src, const IPoint &dst) override
{
	char delta_x = dst.getX() - src.getX();
    char delta_y = dst.getY() - src.getY();

    // check if diagonal linear
    if (delta_x != delta_y)
        return false;

    // check if nothing between
    char x_step = delta_x & 0x81, y_step = delta_y & 0x81;
    char x_end = dst.getX(), y_end = dst.getY();

    for (char x = src.getX() + x_step - 1, y = src.getY() + y_step - 1;
            x != x_end || y != y_end;
            (x += x_step) & (y += y_step))
    {
        if (map[y][x] != nullptr)
            return false;
    }
}

}  // namespace core
}  // namespace collapse
