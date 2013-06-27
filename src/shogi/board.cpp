#include "board.h"
#include "piece.h"
#include "move.h"

using namespace Shogi;


Board::Board()
{
}

Board::~Board()
{
}

void Board::setPiece(Piece &piece)
{
    Q_ASSERT(piece.point().x() >= 0 && piece.point().x() <= 9);
    Q_ASSERT(piece.point().y() >= 0 && piece.point().y() <= 9);

    m_pieces.append(piece);
    player_pieces[piece.owner()].append(piece);

    // 盤面情報に駒を追加する。(0, 0)座標は持駒を表し駒所持者の持駒情報に追加する。
    if (piece.point() != Point(0, 0)) {
        square_piece[piece.point().x() - 1][piece.point().y() - 1] = piece;
    } else {
        hand_piece[piece.owner()][piece.type()].append(piece);
    }

    // 種別が玉の場合は情報を追加する
    if (piece.type() == PieceKing)
        king_piece[piece.owner()] = piece;

    /** @todo 駒情報リストをソートする */
    //
}

void Board::removePiece(Piece &piece)
{
    Piece empty_piece;
    empty_piece.setPoint(piece.point());

    m_pieces.removeOne(piece);
    player_pieces[piece.owner()].removeOne(piece);

    // 盤面情報に駒を追加する。(0, 0)座標は持駒を表し駒所持者の持駒情報に追加する。
    if (piece.point() != Point(0, 0)) {
        square_piece[empty_piece.point().x() - 1][empty_piece.point().y() - 1] = empty_piece;
    } else {
        hand_piece[piece.owner()][piece.type()].removeOne(piece);
    }

    // 種別が玉の場合は情報を削除
    if (piece.type() == PieceKing) king_piece[piece.owner()] = empty_piece;

    /** @todo 駒情報リストをソートする */
    //
}

void Board::movePiece(Piece piece, const Point &to)
{
    Q_ASSERT(piece.point().x() >= 0 && piece.point().x() <= 9);
    Q_ASSERT(piece.point().y() >= 0 && piece.point().y() <= 9);
    Q_ASSERT(to.x() >= 1 && to.x() <= 9);
    Q_ASSERT(to.y() >= 1 && to.y() <= 9);

    // 盤面/持駒情報から駒を削除する。
    if (piece.point() != Point(0, 0)) {
        Q_ASSERT_X(square_piece[piece.point().x() - 1][piece.point().y() - 1].type() != PieceEmpty, "movePiece", "from hand piece nothing.");
        square_piece[piece.point().x() - 1][piece.point().y() - 1] = Piece();
    } else {
        Q_ASSERT_X(!hand_piece[piece.owner()][piece.type()].isEmpty(), "movePiece", "from hand piece nothing.");
        hand_piece[piece.owner()][piece.type()].removeFirst();
    }

    // 移動先に駒がある場合は取る
    Piece to_piece = squarePiece(to);
    if (to_piece.type() != PieceEmpty) {
        Q_ASSERT_X(to_piece.owner() != piece.owner(), "movePiece", "my piece in place already.");   // 配置先に自分の駒がある場合は取ってはいけない
        Q_ASSERT_X(to_piece.type() != PieceKing, "movePiece", "not get king piece.");                    // 玉を取ってはいけない

        // 相手の所持駒リストから削除
        player_pieces[to_piece.owner()].removeOne(to_piece);

        // 自分の所持駒リストおよび持駒情報に追加
        Piece get_piece = Piece(piece.owner(), frontsidePieceType(to_piece.type()));
        get_piece.setPoint(Point(0, 0));
        player_pieces[piece.owner()].append(get_piece);
        hand_piece[piece.owner()][piece.type()].append(get_piece);
    }

    // 盤面移動先情報を反映する。
    piece.setPoint(to);
    square_piece[piece.point().x() - 1][piece.point().y() - 1] = piece;

    // 種別が玉の場合は情報を更新する
    if (piece.type() == PieceKing)
        king_piece[piece.owner()] = piece;
}

Move Board::move() const
{
    return Move(*this);
}

PieceList Board::pieces() const
{
    return m_pieces;
}

Piece Board::piece(Player player, const Point &from, PieceType piece_type) const
{
    Piece piece;

    if (from != Point(0, 0)) {
        // 座標の駒を取得する
        piece = squarePiece(from);

        // 指定した駒種別と違う場合は取得できない
        if (piece.type() != piece_type) {
            return Piece();
        }

        // 駒の所有者が自分ではなかった場合は取得できない
        if (piece.owner() != player) {
            return Piece();
        }
    } else {
        // 指定の持駒情報を取得する。持駒がなかった場合は移動できない
        if (!handPieces(player, piece_type).isEmpty())
            piece = handPieces(player, piece_type).first();
        else
            return Piece();
    }

    return piece;
}

PieceList Board::playerPieces(Player player) const
{
    Q_ASSERT(player == Sente || player == Gote);

    return player_pieces[player];
}

Piece Board::squarePiece(const Point &point) const
{
    Q_ASSERT(point.x() >= 1 && point.x() <= 9);
    Q_ASSERT(point.y() >= 1 && point.y() <= 9);

    return square_piece[point.x() - 1][point.y() - 1];
}

PieceList Board::handPieces(Player player, PieceType piece_type) const
{
    Q_ASSERT(player == Sente || player == Gote);
    Q_ASSERT(piece_type == PiecePawn ||
             piece_type == PieceLance ||
             piece_type == PieceKnight ||
             piece_type == PieceSilver ||
             piece_type == PieceGold ||
             piece_type == PieceRook ||
             piece_type == PieceBishop);

    return hand_piece[player][piece_type];
}

Piece Board::kingPiece(Player player) const
{
    Q_ASSERT(player == Sente || player == Gote);

    return king_piece[player];
}

bool Board::outeCheck(Player player) const
{
    // 自分の玉の位置を取得
    const Point &king_point = kingPiece(player).point();

    // 相手の盤上(相手の手駒を除く)の駒の移動先が自玉と同じ位置なら王手
    foreach (const Piece &piece, playerPieces(enemy(player))) {
        // 持駒は検索対象外
        if (piece.point() == Point(0, 0)) {
            continue;
        }

        foreach (const MovingRange &move_range, piece.moveRanges()) {
            Point search_point = piece.point();
            for (int i = 0; i < move_range.range; ++i) {
                search_point += move_range.point;
                if ((search_point.x() < 1) || (search_point.x() > 9) || (search_point.y() < 1) || (search_point.y() > 9)) {
                    break;
                }
                const Piece &search_piece = squarePiece(search_point);
                /* 既に駒があり, 王でなければ王手ではない */
                if (search_piece.type() != PieceEmpty && search_piece.type() != PieceKing) {
                    break;
                }

                /* 王と同じ位置であれば王手 */
                if (search_point == king_point)
                    return true; // 王手
            }
        }
    }

    return false;   // 王手ではない
}

bool Board::checkmateCheck(Player player) const
{
    // 詰みチェックは重たいので王手の場合の詰みチェックを行う
    if (outeCheck(player)) {
        // 動かせる駒がない場合は詰み
        if (Move(*this).movablePieces(player).isEmpty()) {
            return true;    // 詰み
        }
    }

    return false; // 詰みではない
}

String Board::toCsaString() const
{
    QString text;

    // 盤面情報変換
    for (int y = 1; y <= BOARD_Y_MAX; ++y) {
        text += "P" + String::number(y);
        for (int x = 9; x > 0; --x) {
            const Piece &piece = squarePiece(Point(x, y));
            text += piece.type() == PieceEmpty ? " * " :
                    piece.owner() == Sente ? "+" + pieceTypeString(piece.type()) :
                    piece.owner() == Gote  ? "-" + pieceTypeString(piece.type()) :
                    " * ";

        }
        text += "\n";
    }

    // 取得する持駒種別を定義
    static const PieceType hand_piece_type[HAND_PIECE_TYPE_NUM] = {
        PiecePawn, PieceLance, PieceKnight, PieceSilver, PieceGold, PieceRook, PieceBishop,
    };

    // 先手持駒を変換
    if (!hand_piece[Sente].isEmpty()) {
        text += "P+";
        for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
            foreach (const Piece &piece, handPieces(Sente, hand_piece_type[i])) {
                text += "00" + pieceTypeString(piece.type());
            }
        }
        text += "\n";
    }

    // 後手持駒を変換
    if (!hand_piece[Gote].isEmpty()) {
        text += "P-";
        for (int i = 0; i < HAND_PIECE_TYPE_NUM; ++i) {
            foreach (const Piece &piece, handPieces(Gote, hand_piece_type[i])) {
                text += "00" + pieceTypeString(piece.type());
            }
        }
        text += "\n";
    }

    return text;
}

PieceType Board::frontsidePieceType(PieceType piece_type)
{
    switch (piece_type) {
    case PiecePawn:
    case PiecePawnPromotion:
        return PiecePawn;
        break;

    case PieceLance:
    case PieceLancePromotion:
        return PieceLance;
        break;

    case PieceKnight:
    case PieceKnightPromotion:
        return PieceKnight;
        break;

    case PieceSilver:
    case PieceSilverPromotion:
        return PieceSilver;
        break;

    case PieceGold:
        return PieceGold;
        break;

    case PieceRook:
    case PieceRookPromotion:
        return PieceRook;
        break;

    case PieceBishop:
    case PieceBishopPromotion:
        return PieceBishop;
        break;

    case PieceKing:
        return PieceKing;
        break;

    default:
        Q_ASSERT_X(false, "frontsidePieceType", "Unknown piece type.");   // 未知の駒種別が指定されている
        break;
    }

    return PieceEmpty;
}
