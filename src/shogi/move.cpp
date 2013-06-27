#include "move.h"
#include "board.h"
#include "piece.h"

using namespace Shogi;


Move::Move(const Board &board) :
    m_board(board)
{
}

MovePointList Move::movePoints(const Piece &piece) const
{
    Q_ASSERT(piece.type() != PieceEmpty);

    if (piece.point() != Point(0, 0)) {
        return movePointsOfSquarePiece(piece);
    } else {
        return movePointsOfHandPiece(piece);
    }
}

PieceList Move::movablePieces(Player player) const
{
    Q_ASSERT(player != NoPlayer);

    PieceList pieces;

    // 盤上の駒の移動可能な駒を取得
    foreach (const Piece &piece, m_board.playerPieces(player)) {
        // 持駒だった場合は追加対象としない
        if (piece.point() == Point(0, 0))
            continue;

        if (!movePoints(piece).isEmpty())
            pieces.append(piece);
    }

    // 持駒の移動可能な駒を取得
    static const PieceType hand_piece_type[HAND_PIECE_TYPE_NUM] = {
        PiecePawn, PieceLance, PieceKnight, PieceSilver, PieceGold, PieceRook, PieceBishop,
    };
    for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
        foreach (const Piece &piece, m_board.handPieces(player, hand_piece_type[i])) {
            if (!movePoints(piece).isEmpty())
                pieces.append(piece);

            // 同じ種類の打ち駒をもう一度検索しても仕方ないのでループを抜ける
            break;
        }
    }

    return pieces;
}

bool Move::canMove(Player player, const Point &from, const Point &to, PieceType piece_type)
{
    Q_ASSERT(player != NoPlayer);
    Q_ASSERT(0 <= from.x() && from.x() <= 9);
    Q_ASSERT(0 <= from.y() && from.y() <= 9);
    Q_ASSERT(1 <= to.x() && to.x() <= 9);
    Q_ASSERT(1 <= to.y() && to.y() <= 9);
    Q_ASSERT(piece_type != PieceEmpty);

    // 移動元の駒を取得する
    const Piece &piece = m_board.piece(player, from, piece_type);

    // 移動元の駒がない場合は移動できない
    if (piece.type() == PieceEmpty)
        return false;

    // 移動先と一致した場合は移動できる
    foreach (const MovePoint &move_point, movePoints(piece)) {
        if (move_point.to == to)
            return true;
    }

    return false;
}

MovePromotion Move::movePromotionJudge(const Piece &piece, const Point &to) const
{
    Q_ASSERT(piece.type() != PieceEmpty);
    Q_ASSERT(piece.owner() != NoPlayer);
    Q_ASSERT(1 <= to.x() && to.x() <= 9);
    Q_ASSERT(1 <= to.y() && to.y() <= 9);

    // 駒が昇格可能か？
    if (!piece.canPromotion()) {
        return PromotionNone;
    }

    // 持駒からの移動は成れない
    if (piece.point() == Point(0 ,0)) {
        return PromotionNone;
    }

    // 歩、香や桂はそれ以上動くことのできない座標に移動する場合は強制的に昇格しなければならない
    if (!placeCheck(piece, to)) {
        return PromotionNeed;
    }

    // 昇格エリアに移動する場合、もしくは昇格エリア内からの移動する場合は成ることができる
    if (piece.owner() == Sente) {
        if (to.y() == 3)
            return PromotionAny;
        if (piece.point().y() == 3)
            return PromotionAny;
    } else if (piece.owner() == Gote) {
        if (to.y() == 7)
            return PromotionAny;
        if (piece.point().y() == 7)
            return PromotionAny;
    }

    // 上記処理に該当しない場合は成ることはできない
    return PromotionNone;
}

MovePointList Move::movePointsOfSquarePiece(const Piece &piece) const
{
    Q_ASSERT(piece.type() != PieceEmpty);
    Q_ASSERT(1 <= piece.point().x() && piece.point().x() <= 9);
    Q_ASSERT(1 <= piece.point().y() && piece.point().y() <= 9);

    const Point &from = piece.point();
    MovePointList move_points;

    foreach (const MovingRange &move_range, piece.moveRanges()) {
        Point search_point = from;
        for (int i = 0; i < move_range.range; ++i) {
            search_point += move_range.point;
            if ((search_point.x() < 1) || (search_point.x() > 9) || (search_point.y() < 1) || (search_point.y() > 9)) {
                break;
            }
            const Piece &search_piece = m_board.squarePiece(search_point);
            // 駒がない場合、駒が配置してあって自分の駒ではない場合
            if (search_piece.type() == PieceEmpty || (search_piece.owner() != piece.owner())) {
                // 移動した場合、自玉が王手状態になる場合は移動できない
                if (!kingDangerCheck(piece, search_point)) {
                    MovePoint  move_point;
                    move_point.from = from;         // 移動元座標
                    move_point.to = search_point;   // 移動先座標

                    // 駒種別の設定および移動可能座標の追加
                    // 移動時に成れる場合は2種駒種別で移動座標を追加する
                    switch (movePromotionJudge(piece, search_point)) {
                    case PromotionNone:
                        move_point.piece_type = piece.type();
                        move_points.append(move_point);
                        break;

                    case PromotionAny:
                        move_point.piece_type = piece.type();
                        move_points.append(move_point);
                        // PromotionNeed を継続
                        // break;
                    case PromotionNeed:
                        move_point.piece_type = reversePieceType(piece.type());
                        move_points.append(move_point);
                        break;

                    default:
                        Q_ASSERT_X(false, "movePointsOfSquarePiece", "Unknown move promotion.");
                        break;
                    }
                }
            } else {
                // 駒が配置してあった場合は移動先の検索を抜ける
                break;
            }
        }
    }

    return move_points;
}

MovePointList Move::movePointsOfHandPiece(const Piece &piece) const
{
    Q_ASSERT(piece.type() != PieceEmpty);
    Q_ASSERT(piece.point() == Point(0, 0));

    MovePointList move_points;

    for (int x = 1; x <= BOARD_X_MAX; ++x) {
        /* 2歩の場合は次のX座標へ */
        if (piece.type() == PiecePawn && doublePawnCheck(piece, x))
            continue;
        for (int y = 1; y <= BOARD_Y_MAX; ++y) {
            Point search_point = Point(x, y);
            Piece search_piece = m_board.squarePiece(search_point);
            /* 空き座標でなければ打てない */
            if (search_piece.type() != PieceEmpty)
                continue;
            /* 移動できない場所には打てない */
            if (!placeCheck(piece, search_point))
                continue;
            /* 動かした先が王手になる場合は配置できない */
            if (kingDangerCheck(piece, search_point))
                continue;
            /* 打ち歩詰めの場合は配置できない */
            if (checkmatePawnCheck(piece, search_point))
                continue;

            Shogi::MovePoint  move_point;
            move_point.from = piece.point();
            move_point.to = search_point;
            move_point.piece_type = piece.type();
            move_points.append(move_point);
        }
    }

    return move_points;
}

PieceType Move::reversePieceType(PieceType piece_type) const
{
    switch (piece_type) {
    case PiecePawn:
    case PiecePawnPromotion:
        return PiecePawnPromotion;
        break;

    case PieceLance:
    case PieceLancePromotion:
        return PieceLancePromotion;
        break;

    case PieceKnight:
    case PieceKnightPromotion:
        return PieceKnightPromotion;
        break;

    case PieceSilver:
    case PieceSilverPromotion:
        return PieceSilverPromotion;
        break;

    case PieceGold:
        return PieceEmpty;
        break;

    case PieceRook:
    case PieceRookPromotion:
        return PieceRookPromotion;
        break;

    case PieceBishop:
    case PieceBishopPromotion:
        return PieceBishopPromotion;
        break;

    case PieceKing:
        return PieceEmpty;
        break;

    default:
        Q_ASSERT_X(false, "reversePieceType", "Unknown piece type.");   // 未知の駒種別が指定されている
        break;
    }

    return PieceEmpty;
}

// memo: piece は移動させるので参照型にはしない
bool Move::kingDangerCheck(Piece piece, const Point &to) const
{
    Q_ASSERT(1 <= to.x() && to.x() <=9);
    Q_ASSERT(1 <= to.y() && to.y() <=9);

    // 盤面のコピーを作成して仮想的に動かしてから王手チェックを実施
    Board board_clone = m_board;
    board_clone.movePiece(piece, to);
    return board_clone.outeCheck(piece.owner());
}

bool Move::doublePawnCheck(const Piece &piece, int x) const
{
    Q_ASSERT(1 <= x && x <=9);

    // 駒種別が歩ではない場合は関係ない
    if (piece.type() != PiecePawn) {
        return false;
    }

    for (int y = 1; y < 9; ++y) {
        const Piece &search_piece = m_board.squarePiece(Point(x, y));
        if (search_piece.owner() == piece.owner() && search_piece.type() == PiecePawn) {
            return true;
        }
    }

    return false;
}

bool Move::checkmatePawnCheck(Piece piece, const Point &to) const
{
    Q_ASSERT(1 <= to.x() && to.x() <= 9);
    Q_ASSERT(1 <= to.y() && to.y() <= 9);

    // 歩でない場合は関係ない
    if (piece.type() != PiecePawn) {
        return false;
    }

    // 持駒ではない場合は打ち歩詰とはならないので関係ない
    if (piece.point() != Point(0, 0)) {
        return false;
    }

    // 盤面のコピーを作成して仮想的に動かしてから詰みックを実施する。
    Board board_clone = m_board;
    board_clone.movePiece(piece, to);
    return board_clone.checkmateCheck(piece.owner());
}

bool Move::placeCheck(const Piece &piece, const Point &to) const
{
    if (piece.owner() == Sente) {
        switch (piece.type()) {
        case PiecePawn:
        case PieceLance:
            if (to.y() == 1)
                return false;
            break;

        case PieceKnight:
            if (to.y() == 2)
                return false;
            break;

        default:
            break;
        }
    } else if (piece.owner() == Gote) {
        switch (piece.type()) {
        case PiecePawn:
        case PieceLance:
            if (to.y() == 9)
                return false;
            break;

        case PieceKnight:
            if (to.y() == 8)
                return false;
            break;

        default:
            break;
        }
    }

    return true;
}
