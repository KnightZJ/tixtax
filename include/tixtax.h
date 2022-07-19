
class TixTaxGame {
public:
    enum RoomStatus {
        Available,
        Full,
        RedRoom,
        BlueRoom
    };
    class Room {
    public:
        enum CellColor {
            None,
            Red,
            Blue
        };
    public:
        Room();
        bool setColor(int row, int col, CellColor color);
        RoomStatus getStatus();
    private:
        int red, blue;
        RoomStatus status;
    };
public:
    TixTaxGame();
    void init();
private:
    Room rooms[3][3];
    RoomStatus roomStatus[3][3];
    int round;
};