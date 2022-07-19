#include "tixtax.h"

TixTaxGame::TixTaxGame() {

}

void TixTaxGame::start() {
    redroom = blueroom = fullroom = 0;
    round = 1;
    status = Gaming;
    global = true;
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
        return RedRoom;
    else if ((blue & 0x7) == 0x7 || (blue & 0x38) == 0x38 || (blue & 0x1C0) == 0x1C0
      || (blue & 0x49) == 0x49 || (blue & 0x92) == 0x92 || (blue & 0x124) == 0x124
      || (blue & 0x111) == 0x111 || (blue & 0x54) == 0x54)
        return BlueRoom;
    else if ((blue | red) == 0x1ff)
        return Full;
    return Available;
}

bool TixTaxGame::Room::canMove(int row, int col, CellColor color) {
    if (status != Available)
        return false;
    int mask = 1 << (row*3+col);
    return !(red & mask || blue & mask || color == None);
}

bool TixTaxGame::Room::move(int row, int col, CellColor color) {
    if (canMove(row, col, color)) {
        int mask = 1 << (row*3+col);
        if (color == Red)
            red |= mask;
        else
            blue |= mask;
        updateStatus();
        return true;
    }
    return false;
}

void TixTaxGame::Room::updateStatus() {
    status = check(red, blue);
}

RoomStatus TixTaxGame::Room::getStatus() {
    return status;
}

string TixTaxGame::Room::print(int row) {
    if (status == RedRoom)
        switch (row) {
            case 0: return "   A   ";
            case 1: return "  AAA  ";
            case 2: return " AAAAA ";
        }
    else if (status == BlueRoom)
        switch (row) {
            case 0: return " BBBBB ";
            case 1: return " BBB   ";
            case 2: return " BBBBB ";
        }
    else if (status == Full)
        return " # # # ";
    int mask = 0x1 << (row * 3);
    string s = " ";
    for (int i = 0; i < 3; ++i) {
        if ((red & mask) == mask)
            s += "A ";
        else if ((blue & mask) == mask)
            s += "B ";
        else
            s += "  ";
        mask <<= 1;
    }
    return s;
}

string TixTaxGame::print() {
    string s = "  -------    -------    -------\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k)
                s += " |" + rooms[i][k].print(j) + "| ";
            s += "\n";
        }
        s += "  -------    -------    -------\n";
    }
    return s;
}

bool TixTaxGame::canMove(int cellRow, int cellCol, CellColor color) {
    return status == Gaming && (round % 2 == 1 ? color == Red : color == Blue) 
            && (global || lastRoomRow == cellRow/3 && lastRoomCol == cellCol/3) 
            && rooms[cellRow/3][cellCol/3].canMove(cellRow%3, cellCol%3, color);
}

bool TixTaxGame::move(int cellRow, int cellCol, CellColor color) {
    if (canMove(cellRow, cellCol, color)) {
        lastRoomRow = cellRow % 3;
        lastRoomCol = cellCol % 3;
        rooms[cellRow/3][cellCol/3].move(cellRow%3, cellCol%3, color);
        switch (rooms[cellRow/3][cellCol/3].getStatus()) {
            case RedRoom:
                redroom |= (1 << ((cellRow/3)*3 + cellCol/3));
                break;
            case BlueRoom:
                blueroom |= (1 << ((cellRow/3)*3 + cellCol/3));
                break;
            case Full:
                fullroom |= (1 << ((cellRow/3)*3 + cellCol/3));
                break;
        }
        updateStatus();
        global = (rooms[lastRoomRow][lastRoomCol].getStatus() != Available);
        ++round;
        return true;
    }
    return false;
}

void TixTaxGame::updateStatus() {
    RoomStatus roomStatus= check(redroom, blueroom);
    switch (roomStatus) {
        case RedRoom: status = RedWin; break;
        case BlueRoom: status = BlueWin; break;
        default:
            if ((redroom | blueroom | fullroom) == 0x1ff)
                status = Tie;
            else
                status = Gaming;
            break;
    }
}

GameStatus TixTaxGame::getStatus() {
    return status;
}