#ifndef COLLAPSE_CORE_BASE_H_
#define COLLAPSE_CORE_BASE_H_

#include <array>

#define BOARD_MAX_X 8
#define BOARD_MAX_Y 8

namespace collapse {
namespace core {

enum class Status {
    TURN,       /// player's turn
    RANK,       /// player's pawn upgrade role choice
    FOLD,       /// player discarded the game
    CHECK,      /// player's king is threatened
    CHECKMATE,  /// player's king is threatened and is out of move
    STALEMATE   /// player is out of move and player's king is safe
};

/// player and piece type, aka color type
enum class Type {
    WHITE,
    BLACK
};

/// each role of pieces in chess and a relative value for them
enum class PieceRole {
    KING = 10000,  /// NOTE: This might change to 127
    QUEEN = 9,
    BISHOP = 7,
    ROOK = 5,
    KNIGHT = 3,
    PAWN = 1
};

/// a tile/block's coordinates in (x, y) form
class IPoint {
 public:
    IPoint(unsigned char x, unsigned char y);
    virtual unsigned char getX() = 0;
    virtual unsigned char getY() = 0;
};

/// a chess piece responsible for satisfying if a move
/// is valid or not, also its color type
class IPiece {
 public:
    explicit IPiece(Type type);
    virtual bool isValidMove(const IPoint &src, const IPoint &dst) = 0;
    virtual Type getType() = 0;
};

class IPlayer {
 public:
    IPlayer();
    explicit IPlayer(Type type);
    virtual Type getType() = 0;
    virtual PieceRole getRole() = 0;
};

class IMap {
 public:
    IMap();
    explicit IMap(std::array<std::array<IPiece, 8>, 8> &&init_table);
    IMap(std::initializer_list<std::array<PieceRole, 8>> init_table);
    virtual std::array<IPiece, 8> &operator[](std::size_t index) = 0;
};

class IBoard {
 public:
    explicit IBoard(IMap &map);
    virtual ~IBoard() = 0;
    virtual bool move(const IPoint &src, const IPoint &dst);
    virtual bool upgradeRankPawn(PieceRole role);
    virtual bool isValidMove(const IPoint &src, const IPoint &dst);
};

class IState {
 public:
    IPlayer &player;
    Status status;

    IState();
    IState(IPlayer &player, Status status);
    virtual ~IState() = 0;
};

class IChess {
 public:
    IChess(const IPlayer &white,
           const IPlayer &black,
           const IMap &map);

    const IState &move(const IPlayer &player,
                       const IPoint &src,
                       const IPoint &dst);
    const IState &rank(const IPlayer &player, PieceRole role);
    const IState &fold(const IPlayer &player);
    const IState &reset();

    const IState &getState();
};

}  // namespace core
}  // namespace collapse

#endif  // COLLAPSE_CORE_BASE_H_