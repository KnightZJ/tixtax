
enum RoomStatus {
    Available,
    Full,
    RedRoom,
    BlueRoom
};
class TixTaxGame {
public:
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
    void start();
private:
    Room rooms[3][3];
    int redroom, blueroom;
    int round;
};