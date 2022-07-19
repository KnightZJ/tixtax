#include "tixtax.h"

TixTaxGame::TixTaxGame() {

}

void TixTaxGame::start() {
    redroom = blueroom = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            rooms[i][j] = Room();
}

TixTaxGame::Room::Room() {
    red = blue = 0;
    status = Available;
}

RoomStatus check(int red, int blue) {
    if ((red & 0x7) == 0x7 || (red & 0x38) == 0x38 || (red & 0x1C0) == 0x1C0
      || (red & 0x49) == 0x49 || (red & 0x92) == 0x92 || (red & 0x124) == 0x124
      || (red & 0x111) == 0x111 || (red & 0x54) == 0x54)
        return RoomStatus::RedRoom;
    else if ((blue & 0x7) == 0x7 || (blue & 0x38) == 0x38 || (blue & 0x1C0) == 0x1C0
      || (blue & 0x49) == 0x49 || (blue & 0x92) == 0x92 || (blue & 0x124) == 0x124
      || (blue & 0x111) == 0x111 || (blue & 0x54) == 0x54)
        return RoomStatus::BlueRoom;
    else if ((blue | red) == 0x1ff)
        return RoomStatus::Full;
    return RoomStatus::Available;
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
    return true;
}

RoomStatus TixTaxGame::Room::getStatus() {
    return check(red, blue);
}