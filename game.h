#include <iostream>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
using namespace std;

enum Side { WHITE, BLACK };
enum Piece { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum P_type { HUMAN, ENGINE }; // player type

struct Point {
    int r, c;
    bool operator< (const Point& pt) const {
        return (r < pt.r) || ((!(pt.r < r)) && (c < pt.c));
    }

    bool operator== (const Point& pt) const {
        return (r == pt.r) && (c == pt.c);
    }
};

class PointHash {
public:
    size_t operator() (const Point& pt) const {
        return pt.r*8 + pt.c;
    }
};

class Game {
public:
    int board[8][8];
    P_type wp; // white player
    P_type bp; // black player
    Side curr_turn;
    bool moved[2][3]; // row 0 1 : white black, col 1 2 3: king l_rook r_rook

    long white_timer;
    long black_timer;

    Game(P_type wType, P_type bType);
    bool handle_command(Point src, Point dst); // return true on valid moves

protected:
    // array of set of positions for each pieces
    unordered_set<Point> *whitePiece;
    unordered_set<Point> *blackPiece;

private:
    void init_board();
    int check_first(Point src, int rd, int cd);
    bool not_blocked(Point src, Point dst, bool isCastling);
    bool is_check(Point src, Point dst, bool sameSide);
    bool is_valid_castling(Point src, Point dst);
    bool is_valid_move(Point src, Point dst, bool *isCastling);
    void make_move(Point src, Point dst, bool isCastling);
    void change_turn();
};