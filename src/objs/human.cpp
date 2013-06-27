#include "human.h"
#include <QMetaType>
#include <QMessageBox>

#include "shogi/board.h"
#include "shogi/piece.h"
#include "shogi/move.h"
#include "shogi/component.h"

using namespace Shogi;

Human::Human(Player player, QObject *parent) :
    QThread(parent)
{
}

Human::~Human()
{
}

void Human::setShogiComponent(ShogiComponent *shogi_component)
{
}

void Human::run()
{
    forever {
    }
}

void Human::selectionPoint(const Point &point)
{
    if (component->turn() != player) return;

    Piece piece;
    if (point.x() != 0) {
        piece = component->board().squarePiece(point);
    } else {
        PieceType piece_type = (PieceType)point.y();
        if (!component->board().handPieces(player, piece_type).isEmpty())
            piece = component->board().handPieces(player, piece_type).first();
    }

    if (select_piece != Piece()) {
        MovePointList move_points = Move(component->board()).movePoints(piece);
        foreach (const MovePoint &move_point, move_points) {
            if (move_point.to == point) {
                m_move_point.from = select_piece.point();
                m_move_point.to = point;
                if (Move(component->board()).movePromotionJudge(select_piece, point) == PromotionAny) {
                    if (QMessageBox::information(NULL, tr("確認"), tr("成りますか？"), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
                        m_move_point.piece_type = select_piece.type();
                    } else {
                        m_move_point.piece_type = reversePieceType(select_piece.type());
                    }
                }
                thinking = false;
                return;
            }
        }
        select_piece = Piece();
    }

    if (piece.type() != PieceEmpty && piece.owner() == player) {
        select_piece = piece;
        emit selectPiece(piece);
    }
}

PieceType Human::reversePieceType(PieceType piece_type) const
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
