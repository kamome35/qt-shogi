#ifndef SHOGI_COMPONENT_H
#define SHOGI_COMPONENT_H

#include "shogi.h"
#include "board.h"
#include "record.h"

namespace Shogi {

/**
 * 将棋のゲームを管理するクラス
 *
 * ゲームを実施する場合はこのクラスをメインに各クラスを利用する。
 */
class Component
{
public:
    Component();
    virtual ~Component();

    /**
     * ゲーム状態を取得する
     *
     * @return ゲーム状態
     * @see setGameStatus
     */
    inline GameStatus gameStatus() const { return m_status; }

    /**
     * ゲームの状態を設定する
     *
     * @param status ゲーム状態
     * @see gameStatus
     */
    void setGameStatus(GameStatus status);

    /**
     * ゲームを開始する。
     *
     * @param time_limit 持ち時間
     * @param time_byoyomi 秒読み
     */
    void gameStart(const Time &time_limit, const Time &time_byoyomi = Time());

    /**
     * ゲームを中断する
     */
    void gameSuspend();

    /**
     * ゲームを再開する
     */
    void gameRestart();

    /**
     * 手番を取得する
     *
     * @return 手番
     */
    inline Player turn() const { return m_turn; }

    /**
     * 盤情報取得
     *
     * @return 盤情報
     */
    inline Board board() const { return m_board; }

    /**
     * piece に指定した駒を盤に登録する。
     *
     * @param piece
     */
    inline void setPiece(Piece &piece) { m_board.setPiece(piece); }

    /**
     * piece に指定した駒を盤面から削除する。
     *
     * @param piece
     */
    inline void removePiece(Piece &piece) { m_board.removePiece(piece); }

    /**
     * 指手情報を追加する
     *
     * @param record
     */
    void addRecord(const Record &record);

    /**
     * 棋譜を取得する
     *
     * @return 棋譜情報
     */
    inline RecordList recordList() const { return m_record_list; }

    /**
     * 開始時間を取得する
     *
     * @return 開始時間
     */
    inline DateTime startDateTime() const { return m_start_date_time; }

    /**
     * 開始時間を設定する
     *
     * @param time_date
     */
    inline void setStartDateTime(const DateTime &time_date) { m_start_date_time = time_date; }

    /**
     * 終了時間を取得する
     *
     * @return 終了時間
     */
    inline DateTime endDateTime() const { return m_end_date_time; }

    /**
     * 終了時間を設定する
     *
     * @param time_date
     */
    inline void setEndDateTime(const DateTime &time_date) { m_end_date_time = time_date; }

    /**
     * 持ち時間を取得する
     *
     * @param player 手番
     * @return 持ち時間
     */
    inline Time timeLimit(Player player) const { return m_time_limit[player]; }

    /**
     * 持ち時間の設定
     *
     * @param time 持ち時間
     */
    inline void setTimeLimit(const Time &time) { m_time_limit_initial = m_time_limit[Sente] = m_time_limit[Gote]  = time; }

    /**
     * 秒読みを設定
     * 切れ負けの場合は0秒で設定する。
     *
     * @param time 秒読み時間
     */
    inline void setTimeByouyomi(const Time &time) { m_time_byouyomi = time; }

    /**
     * プレイヤー名取得する
     *
     * @param player 手番
     * @return プレイヤー名が返却される。 プレイヤー名が設定されていない場合は「No Name」が返却される。
     * @see setPlayerName
     */
    inline String playerName(Player player) const { return m_player_name[player]; }

    /**
     * プレイヤー名を設定する
     *
     * @param player 手番
     * @param name プレイヤー名
     * @see playerName
     */
    inline void setPlayerName(Player player, const String &name) { m_player_name[player] = name; }

    /**
     * 駒を移動する
     *
     * @param player 手番
     * @param from 移動元
     * @param to 移動先
     * @param piece_type 移動する駒種別
     * @return 駒を移動できた場合は true を返却する。 駒を移動できなかった場合は false を返却する。
     */
    bool movePiece(Player player, const Point &from, const Point &to, PieceType piece_type);

    /**
     * 棋譜上の次の手へ移動する。
     *
     * @note GameStatus が StatusPlaying の場合は移動することはできません。
     * @return 移動に成功すると棋譜のインデックス(手数)を返却します。 失敗すると -1 を返却します。
     * @see gameStatus
     * @see prevRecord
     * @see changeIndex
     */
    int nextRecord();

    /**
     * 棋譜上の前の手へ移動する。
     *
     * @note GameStatus が StatusPlaying の場合は移動することはできません。
     * @return 移動に成功すると棋譜のインデックス(手数)を返却します。 失敗すると -1 を返却します。
     * @see gameStatus
     * @see nextRecord
     * @see changeIndex
     */
    int prevRecord();

    /**
     * 棋譜上の指定の手数に移動する。
     *
     * @note GameStatus が StatusPlaying の場合は移動することはできません。
     * @param index 手数
     * @return 移動に成功すると棋譜のインデックス(手数)を返却します。 失敗すると -1 を返却します。
     * @see gameStatus
     * @see nextRecord
     * @see prevRecord
     */
    int changeIndex(unsigned int index);

    /**
     * 将棋情報をCSA標準棋譜ファイル形式に変換する
     *
     * @return CSA文字列
     */
    String toCsaString() const;

private:
    GameStatus m_status;                    ///< ゲーム状態
    Player m_turn;                          ///< 現在の指し手
    int m_index;                            ///< 手数
    RecordList m_record_list;               ///< 棋譜
    DateTime m_start_date_time;             ///< 開始時間
    DateTime m_end_date_time;               ///< 終了時間
    Time m_time_conter;                     ///< 指し手時間計測用
    Time m_time_byouyomi;                   ///< 秒読み時間
    Time m_time_limit_initial;              ///< 持ち時間
    Time m_time_limit[PLAYER_MAX];          ///< 指し手の現在の持ち時間
    String m_player_name[PLAYER_MAX];       ///< 指し手の名前
    Board m_board;                          ///< 現在の盤面情報
    Board m_board_initial;                  ///< 初期盤面情報
    BoardList m_board_list;                 ///< 盤面の情報リスト（棋譜と対応）
};

} // namespace Shogi

#endif // SHOGI_COMPONENT_H
