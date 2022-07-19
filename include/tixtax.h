#include <string>
using namespace std;

enum CellColor {
    None,
    Red,
    Blue
};

enum RoomStatus {
    Available,
    Full,
    RedRoom,
    BlueRoom
};

enum GameStatus {
    Gaming,
    RedWin,
    BlueWin,
    Tie
};

class TixTaxGame {
public:
    class Room {
    public:
        Room();
        bool move(int row, int col, CellColor color);
        bool canMove(int row, int col, CellColor color);
        RoomStatus getStatus();
        void updateStatus();
        string print(int row);
    private:
        int red, blue;
        RoomStatus status;
    };
public:
    TixTaxGame();
    void start();
    bool move(int cellRow, int CellCol, CellColor color);
    bool canMove(int cellRow, int CellCol, CellColor color);
    GameStatus getStatus();
    void updateStatus();
    string print();
private:
    Room rooms[3][3];
    int redroom, blueroom, fullroom;
    int round;
    int lastRoomRow, lastRoomCol;
    bool global;
    GameStatus status;
};