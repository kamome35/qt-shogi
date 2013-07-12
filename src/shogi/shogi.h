#ifndef SHOGI_SHOGI_H
#define SHOGI_SHOGI_H

#include <QMap>
#include <QList>
#include <QPoint>
#include <QMetaType>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QDateTime>

/**
 * 将棋ゲーム処理関連
 */
namespace Shogi {

class Piece;
class Board;
class Move;
class Record;
class Component;
class Csa;

/**
 * 指手
 */
enum Player {
    Sente,            /**< 先手 */
    Gote,             /**< 後手 */
    NoPlayer
};

/**
 * 指し手の種別
 */
enum HumanType {
    HumanPlayer,
    HumanComputer,
    HumanNetwork
};

/**
 * 駒種別
 */
enum PieceType {
    PieceEmpty,             /**< 空 */
    PiecePawn,              /**< 歩 */
    PieceLance,             /**< 香 */
    PieceKnight,            /**< 桂 */
    PieceSilver,            /**< 銀 */
    PieceGold,              /**< 金 */
    PieceRook,              /**< 飛 */
    PieceBishop,            /**< 角 */
    PieceKing,              /**< 王 */
    PiecePawnPromotion,     /**< と */
    PieceLancePromotion,    /**< 杏 */
    PieceKnightPromotion,   /**< 圭 */
    PieceSilverPromotion,   /**< 全 */
    PieceRookPromotion,     /**< 竜 */
    PieceBishopPromotion,   /**< 馬 */
    PieceTail
};

/**
 * ゲーム種別
 */
enum GameType {
    Hirate                  /**< 平手 */
};

/**
 * ゲーム状態
 */
enum GameStatus {
    StatusStandBy,      /**< 開始待ち */
    StatusPlaying,      /**< 継続中 */
    StatusToryo,        /**< 投了 */
    StatusChudan,       /**< 中断 */
    StatusSennichite,   /**< 千日手 */
    StatusTimeUp,       /**< 手番側が時間切れで負け */
    StatusIllegalMove,  /**< 手番側の反則負け */
    StatusJishogi,      /**< 持将棋 */
    StatusKachi,        /**< (入玉で)勝ちの宣言 */
    StatusHikiwake,     /**< (入玉で)引き分けの宣言 */
    StatusTsumi,        /**< 詰み */
    StatusFuzumi,       /**< 不詰 */
    StatusError         /**< エラー */
};

/**
 * 移動時の成り判定結果
 */
enum MovePromotion
{
    PromotionNone,      /**< 成れない */
    PromotionAny,       /**< 成ることができる */
    PromotionNeed       /**< 成らないといけない */
};

typedef QPoint Point;                               ///< 座標
typedef QString String;                             ///< 文字列
typedef QChar Char;                                 ///< 文字
typedef QTime Time;                                 ///< 時間
typedef QDateTime DateTime;                         ///< 日時
typedef QList<QPoint> PointList;                    ///< 座標リスト
typedef QList<String> StringList;                   ///< 文字列リスト
typedef QList<PieceType> PieceTypeList;             ///< 駒種別リスト
typedef QList<Record> RecordList;                   ///< 棋譜
typedef QList<Piece> PieceList;                     ///< 駒リスト
typedef QMap<PieceType, PieceList> HandPieceMap;    ///< 持駒マップ
typedef QList<Board> BoardList;                     ///< 盤面情報リスト

/**
 * 駒移動情報
 */
struct MovePoint
{
    Point from;             /**< 移動元 */
    Point to;               /**< 移動先 */
    PieceType piece_type;   /**< 駒種別 */
};

typedef QList<MovePoint> MovePointList;             ///< 移動座標リスト

/**
 * 駒移動方向情報
 *
 * 駒の移動方向の情報を表し駒の移動範囲は MovingRangeList を用いる事
 * @see MovingRangeList
 */
struct MovingRange
{
    MovingRange() : point(0, 0), range(0) {}
    MovingRange(const Point &point, int range) : point(point), range(range) {}
    Point point;            /**< 移動方向 */
    int range;              /**< 移動量 */
};

typedef QList<MovingRange> MovingRangeList;         ///< 移動範囲

/**
 * 自陣からみた敵を取得する。
 *
 * @param player 自陣の種別
 * @return 先手なら後手を返却し、後手なら先手を返却する。
 */
inline Player enemy(Player player)
{
    return player == Sente ? Gote :
           player == Gote ? Sente :
           NoPlayer;
}

/**
 * 駒種別をCSA形式の文字列に変換する。
 *
 * @param piece_type 駒種別
 * @return 駒種別文字列
 */
extern String pieceTypeString(PieceType piece_type);


extern String gameStatusString(GameStatus status);

const int PLAYER_MAX = 2;               /**< プレイヤー数 */
const int BOARD_X_MAX = 9;              /**< 駒盤 X座標最大値 */
const int BOARD_Y_MAX = 9;              /**< 駒盤 Y座標最大値 */
const int HAND_PIECE_TYPE_NUM = 7;      /**< 持ち駒種別数 */

} // namespace Shogi

Q_DECLARE_METATYPE(Shogi::String)
Q_DECLARE_METATYPE(Shogi::Player)
QDataStream &operator <<(QDataStream &out, const Shogi::Player &data);
QDataStream &operator >>(QDataStream &in, Shogi::Player &data);
Q_DECLARE_METATYPE(Shogi::PieceType)
QDataStream &operator <<(QDataStream &out, const Shogi::PieceType &data);
QDataStream &operator >>(QDataStream &in, Shogi::PieceType &data);
Q_DECLARE_METATYPE(Shogi::GameType)
QDataStream &operator <<(QDataStream &out, const Shogi::GameType &data);
QDataStream &operator >>(QDataStream &in, Shogi::GameType &data);
Q_DECLARE_METATYPE(Shogi::MovePoint)
QDataStream &operator <<(QDataStream &out, const Shogi::MovePoint &data);
QDataStream &operator >>(QDataStream &in, Shogi::MovePoint &data);
Q_DECLARE_METATYPE(Shogi::MovePointList)
QDataStream &operator <<(QDataStream &out, const Shogi::MovePointList &data);
QDataStream &operator >>(QDataStream &in, Shogi::MovePointList &data);
Q_DECLARE_METATYPE(Shogi::MovingRange)
QDataStream &operator <<(QDataStream &out, const Shogi::MovingRange &data);
QDataStream &operator >>(QDataStream &in, Shogi::MovingRange &data);
Q_DECLARE_METATYPE(Shogi::MovingRangeList)
QDataStream &operator <<(QDataStream &out, const Shogi::MovingRangeList &data);
QDataStream &operator >>(QDataStream &in, Shogi::MovingRangeList &data);

#endif // SHOGI_SHOGI_H
