# Chess Class

Chess class represents a chess game, requiring 2 players and a map for board initialization.

this class supports 2 main actions for player's prespective:
*   `move`: move a piece from a point to another point.
            player must own the piece.
*   `rank`: rank up the last pawn which made to the top of board, 
            8th rank/tile/block in Y-axis, to one of four roles: 
            queen, bishop, rook, knight.
*   `fold`: a player might fold, winner will be the opposite player.

and also an action that's not about the game:
*   `reset`: game is reset to where it started. same players and init map.

## Properties

Each property is described in format "\<name\> : \<type\>" under its access attribute.

*   private:
    *   board : Board
    *   state : State

*   public:
    *   map\_init : Map

        > the change of this property will be useful for `reset` action.

    *   player\_black : Player

        > it's possible to change this player during game,  
        > but be careful what you pass to functions as player.

    *   player\_white : Player

        > it's possible to change this player during game,  
        > but be careful what you pass to functions as player.

## Methods

Each method is described in simple C++ method prototype form.

**NOTE**: it's **simplified**! meaning type notations are not _exact_ but from same class. being *const* or *pointer* or etc.. will be decided later.

*   constructor(s):  
    *   Chess(Player player\_white, Player player\_black, Map init\_map)

*   public:
    *   State move(Player cur, Point src, Point dst)

        > checks if `cur` is the current player \(same player's turn\),
        > then checks if move `src` to `dst` is valid in
        > `board`, then updates `state` and returns it.

    *   State fold(Player cur)

        > updates the `state` and returns it.  
        > after this, the game won't be playable, but it can be reset.

    *   State rank(Player cur, PieceRole role)

        > checks if `cur` is the current player, and this action 
        > matches the `state` (same player, status must be RANK), so 
        > then upgrades last rank pawn through `board`.  
        > if it fail, the state remains, otherwise it will become 
        > the TURN of opposite player.  
        > (last rank pawn is a Pawn piece that reaches 8th 
        > tile/block of Y-axis in board.)

    *   State reset()

        > reconstructs the game using `map_init`,
        > `player_black` and `player_white`, so
        > updates `board` and `state`, then
        > returns `state`. it'll be just like making
        > new Chess but way more efficient.

    *   State getState()

        > returns `state`.

*   private:
    *   bool isCurrentPlayer(Player player)

        > checks if this `player` is the same player as 
        > specified in `state`.
