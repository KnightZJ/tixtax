#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tixtax.h"

using namespace std;

int main() {
    TixTaxGame game;
    srand(time(0));
    int maxRound = 1;
    int maxMatch = 1000000, blueWin = 0, redWin = 0, tie = 0;
    for(int i = 0; i < maxMatch; ++i) {
        game.start();
        CellColor color = Red;
        int round = 1;
        while(game.getStatus() == Gaming) {
            int row = rand()%9, col = rand()%9;
            if (game.move(row, col, color)) {
                color = color == Red ? Blue : Red;
                ++round;
            }
        }
        maxRound = round > maxRound ? round : maxRound;
        switch (game.getStatus()) {
            case RedWin:
                redWin++;
                break;
            case BlueWin:
                blueWin++;
                break;
            case Tie:
                tie++;
                break;
        }
    }
    cout << "RedWin :  " << redWin*100.0/maxMatch << "% (" << redWin << "/" << maxMatch << ")" << endl;
    cout << "BlueWin: " << blueWin*100.0/maxMatch << "% (" << blueWin << "/" << maxMatch << ")" << endl;
    cout << "Tie    : " << tie*100.0/maxMatch << "% (" << tie << "/" << maxMatch << ")" << endl;
    return 0;
}