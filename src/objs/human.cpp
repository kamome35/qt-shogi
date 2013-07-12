#include "human.h"
#include <QMessageBox>

#include <QThread>
#include <shogi/shogi.h>
#include <shogi/move.h>

using namespace Shogi;

Human::Human(Player player, QObject *parent) :
    QThread(parent),
    component(NULL),
    player(player),
    thinking(true)
{
}

Human::~Human()
{
}

void Human::setShogiComponent(ShogiComponent *shogi_component)
{
    component = shogi_component;
}

void Human::run()
{
    // 思考ルーチンを開始する
    forever {
        // 思考が終了しており、自分の手番であれば駒を移動させる
        if (!thinking && component->turn() == player) {
            // 駒を移動する
            component->movePiece(player, m_move_point.from, m_move_point.to, m_move_point.piece_type);

            // 思考フラグを有効にする
            thinking = true;
        }

        msleep(100);
    }
}

void Human::selectionPoint(const Point &point)
{
    // 自分の手番ではない場合は処理しない
    if (component->turn() != player) return;

    // 選択した駒を取得する
    Piece piece;
    if (point.x() != 0) {
        piece = component->board().squarePiece(point);
    } else {
        // X座標が0の場合は持駒から取得する
        PieceType piece_type = (PieceType)(point.y());
        if (!component->board().handPieces(player, piece_type).isEmpty())
            piece = component->board().handPieces(player, piece_type).first();
    }

    // 選択中の駒が存在する場合は移動処理を実施する
    if (select_piece != Piece()) {
        // 駒の移動先リストを取得する
        MovePointList move_points = Move(component->board()).movePoints(select_piece);
        foreach (const MovePoint &move_point, move_points) {
            // 選択した座標が駒の移動先リストに含まれているか判定する
            if (move_point.to == point) {
                // 移動情報を生成する
                m_move_point.from = select_piece.point();
                m_move_point.to = point;

                switch (Move(component->board()).movePromotionJudge(select_piece, point)) {
                // 駒が成れる場合は、成り確認を行う
                case PromotionAny:
                    if (QMessageBox::information(NULL, tr("確認"), tr("成りますか？"), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
                        m_move_point.piece_type = select_piece.type();
                    } else {
                        m_move_point.piece_type = reversePieceType(select_piece.type());
                    }
                    break;

                // 成れないといけない場合は、問い合わせせずに成る
                case PromotionNeed:
                    m_move_point.piece_type = reversePieceType(select_piece.type());
                    break;

                // 成れない場合はそのままの駒種別で設定する
                case PromotionNone:
                    m_move_point.piece_type = select_piece.type();
                    break;

                }
                select_piece = Piece();
                thinking = false;
                return;
            }
        }
        select_piece = Piece();
    }

    // 取得した駒は自分所有の駒の場合、選択中の駒に設定する
    if (piece.type() != PieceEmpty && piece.owner() == player) {
        select_piece = piece;

        // 駒を選択したことを通知する
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
