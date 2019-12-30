#ifndef COLLAPSE_CORE_H_
#define COLLAPSE_CORE_H_

#include <array>

#include "collapse/core/base.h"

namespace collapse {
namespace core {

class Point : public IPoint {
    char x;
    char y;

 public:
    Point(char x, char y);
    virtual char getX() const; // override;
    virtual char getY() const; // override;
};

class Player : public IPlayer {
    Type type;

 public:
    explicit Player(Type type) : type(type) {};
    Type getType() const { return type; };
};

template<typename T>
class Map : public IMap<T> {
    std::array<std::array<T*, 8>, 8> *table;

 public:
    Map();
    explicit Map(const std::array<std::array<T*, 8>, 8> &init_table);
    Map(const Map<T> &other);
    Map<T> &operator=(const Map<T> &other);
    ~Map();

    T *get(std::size_t x, std::size_t y) const override;
    T *set(std::size_t x, std::size_t y, T *ptr) override;
    T *delete_at(std::size_t x, std::size_t y) override;
    T *operator()(std::size_t x, std::size_t y) const override;
};

class Board : public IBoard {
    Map<IPiece> map;
    Status status;
    Point last_rank_pawn;
    bool has_last_rank_pawn;

 public:
    Board(Map<IPiece> &map);
    bool move(const IPoint &src, const IPoint &dst) override;
    bool upgradeRankPawn(PieceRole role) override;
    bool isValidMove(const IPoint &src, const IPoint &dst) const override;
    IPoint *getLastRankPawn() const override;

 private:
    Status check_map(const IMap<IPiece> &map, Type self_type) const;
};

class State : public IState {
 public:
    IPlayer &player;
    Status status;

    State(IPlayer &player, Status status)
        : player(player)
        , status(status)
    {}
};

class Chess : public IChess {
    Board board;
    State state;

 public:
    IPlayer &player_black;
    IPlayer &player_white;
    IMap<IPiece> &map_init;

    Chess(IPlayer &white, IPlayer &black, Map<IPiece> &map);

    const IState &move(const IPlayer &player,
                       const IPoint &src,
                       const IPoint &dst) override;
    const IState &rank(const IPlayer &player, PieceRole role) override;
    const IState &fold(const IPlayer &player) override;
    const IState &reset();

    bool isValidMove(const IPlayer &player,
                     const IPoint &src,
                     const IPoint &dst) const;
    const IState &getState() const;
};

// explicit instantiation of necessary template types
template class Map<IPiece>;

}  // namespace core
}  // namespace collapse

#endif  // COLLAPSE_CORE_H_
