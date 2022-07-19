#include "tixtax.h"

TixTaxGame::TixTaxGame() {

}

void TixTaxGame::init() {
}

TixTaxGame::Room::Room() {
    red = blue = 0;
    status = Available;
}

bool TixTaxGame::Room::setColor(int row, int col, CellColor color) {
    if (status != Available)
        return false;
    int hand = 1 << (row*3+col);
    if (red & hand || blue & hand || color == None)
        return false;
    if (color == Red)
        red |= hand;
    else
        blue |= hand;
    if ((red & 0x7) == 0x7 || (red & 0x38) == 0x38 || (red & 0x1C0) == 0x1C0
      || (red & 0x49) == 0x49 || (red & 0x92) == 0x92 || (red & 0x124) == 0x124
      || (red & 0x111) == 0x111 || (red & 0x54) == 0x54)
        status = RedRoom;
    else if ((blue & 0x7) == 0x7 || (blue & 0x38) == 0x38 || (blue & 0x1C0) == 0x1C0
      || (blue & 0x49) == 0x49 || (blue & 0x92) == 0x92 || (blue & 0x124) == 0x124
      || (blue & 0x111) == 0x111 || (blue & 0x54) == 0x54)
        status = BlueRoom;
    else if ((blue | red) == 0x1ff)
        status = Full;
    return true;
}

TixTaxGame::RoomStatus TixTaxGame::Room::getStatus() {
    return status;
}