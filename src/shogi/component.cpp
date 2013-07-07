#include "component.h"
#include "move.h"

using namespace Shogi;


Component::Component()
{
    m_status = StatusStandBy;
    m_turn = NoPlayer;
    m_index = 0;
    m_player_name[Sente] = "No Name";
    m_player_name[Gote] = "No Name";
}

Shogi::Component::~Component()
{
}

void Component::setGameStatus(GameStatus status)
{
    m_status = status;
}

void Component::gameStartInit(const Time &time_limit, const Time &time_byoyomi)
{
    m_status = StatusPlaying;
    m_turn = Sente;
    m_index = 0;
    m_start_date_time = DateTime::currentDateTime();
    m_time_byouyomi = time_byoyomi;
    m_time_limit_initial = m_time_limit[Sente] = m_time_limit[Gote] = time_limit;
    m_time_conter.start();
    m_board_initial = m_board;
}

void Component::gameSuspend()
{
    m_status = StatusChudan;
    m_time_conter = Time();
}

void Component::gameRestart()
{
    // 棋譜インデックスが移動している場合はリストから巻き戻している分を削除する
    for (int i = 0; m_index < m_record_list.count(); ++i ) {
        m_record_list.removeLast();
    }
    // 棋譜インデックスが移動している場合はリストから巻き戻している分を削除する
    for (int i = 0; m_index < m_board_list.count(); ++i ) {
        m_board_list.removeLast();
    }
    m_status = StatusPlaying;
    m_time_conter.start();
}

void Component::addRecord(const Record &record)
{
    // 棋譜情報がゲーム中の情報であれば
    if (record.status() == StatusPlaying) {
        /** @todo 棋譜の直接追加時は m_status != StatusPlaying じゃなくても動かせるようにきちんと考慮しないといけない */

        // 元のゲームの状態を保持して、駒を動かすために状態を一時的にゲーム中にする
        GameStatus old_status = m_status;
        m_status = StatusPlaying;

        // 指手情報を元に駒を移動する
        movePiece(record.turn(), record.from(), record.to(), record.pieceType());

        // プレイ中じゃなくなっていた場合は戻さない
        if (m_status == StatusPlaying)
            m_status = old_status; // ゲームの状態を元に戻す。
    } else {
        // コマンド系の情報なら状態を変更する
        m_status = record.status();

        // 指手情報を追加する。
        m_record_list.append(record);
    }

}

bool Component::movePiece(Player player, const Point &from, const Point &to, PieceType piece_type)
{
    Q_ASSERT(player != NoPlayer);
    Q_ASSERT(piece_type != PieceEmpty);
    Q_ASSERT(0 <= from.x() && from.x() <= 9);
    Q_ASSERT(0 <= from.y() && from.y() <= 9);
    Q_ASSERT(1 <= to.x() && to.x() <= 9);
    Q_ASSERT(1 <= to.y() && to.y() <= 9);

    // プレイ中以外は移動できない
    if (m_status != StatusPlaying)
        return false;
/*
    // 自分の手番ではない場合は移動できない
    if (m_turn != player) {
        m_status = StatusIllegalMove;
        m_record_list << Record(player, m_status);
        return false;
    }
*/

    // 持ち時間を更新して、持ち時間が無くなった場合は、ゲームを終了する
    const int sec = m_time_conter.restart();
    m_time_limit[player].addSecs(-sec);
    if (Time().secsTo(m_time_limit[player]) < 0) {
        m_status = StatusTimeUp;
        m_record_list << Record(player, m_status);
        return false;
    }

    // 移動可能な座標か調べる
    if (!m_board.move().canMove(player, from, to, piece_type)) {
        m_status = StatusIllegalMove;
        m_record_list << Record(player, m_status);
        return false;
    }

    // 駒を移動する
    Piece piece = m_board.piece(player, from, piece_type);
    piece.setType(piece_type);
    m_board.movePiece(piece, to);
    m_board_list.append(m_board);

    // 棋譜に記録する
    m_record_list << Record(player, from, to, piece_type, sec);

    // 手番を変える
    m_turn = enemy(player);

    // 詰みチェック
    if (m_board.checkmateCheck(m_turn)) {
        m_status = StatusTsumi;
        m_record_list << Record(m_turn, m_status);
    }

    // 手数を増やす
    ++m_index;

    return true;
}

int Component::nextRecord()
{
//    // ゲームプレイ中は棋譜の移動はできない。
//    if (m_status == StatusPlaying)
//        return -1;

    // 次の棋譜は存在しない
    const int next_index = m_index + 1;
    if (next_index >= m_board_list.count())
        return -1;

    // 次の盤面情報を取得する
    const Board &board = m_board_list.value(next_index);

    // 盤面を上書きする
    m_board = board;

    // 持時間を更新
    m_time_limit[Sente] = m_time_limit[Gote] = m_time_limit_initial;
    for (int i = 0; i < next_index; ++i) {
        const Record &record = m_record_list.value(i);
        if (record.status() == StatusPlaying)
            m_time_limit[record.turn()].addSecs(-record.sec());
    }

    // インデックスを移動して値を返却する
    return (m_index = next_index);
}

int Component::prevRecord()
{
//    // ゲームプレイ中は棋譜の移動はできない。
//    if (m_status == StatusPlaying)
//        return -1;

    // 前の棋譜は存在しない
    const int prev_index = m_index - 1;
    if (prev_index < 0)
        return -1;

    // 前の盤面情報を取得する
    const Board &board = m_board_list.value(prev_index);

    // 盤面を上書きする
    m_board = board;

    // 持時間を更新
    m_time_limit[Sente] = m_time_limit[Gote] = m_time_limit_initial;
    for (int i = 0; i < prev_index; ++i) {
        const Record &record = m_record_list.value(i);
        if (record.status() == StatusPlaying)
            m_time_limit[record.turn()].addSecs(-record.sec());
    }

    // インデックスを移動して値を返却する
    return (m_index = prev_index);
}

int Component::changeIndex(unsigned int index)
{
    // ゲームプレイ中は棋譜の移動はできない。
    if (m_status == StatusPlaying)
        return -1;

    // 前の棋譜は存在しない
    if (index >= (unsigned int)m_board_list.count())
        return -1;

    // 前の盤面情報を取得する
    const Board &board = m_board_list.value(index);

    // 盤面を上書きする
    m_board = board;

    // 持時間を更新
    m_time_limit[Sente] = m_time_limit[Gote] = m_time_limit_initial;
    for (unsigned int i = 0; i < index; ++i) {
        const Record &record = m_record_list.value(i);
        if (record.status() == StatusPlaying)
            m_time_limit[record.turn()].addSecs(-record.sec());
    }

    // インデックスを移動して値を返却する
    return (m_index = index);
}

String Component::toCsaString() const
{
    String text;

    // CSAバージョン
    text += "V2.2\n";

    // プレイヤー名変換
    if (!playerName(Sente).isEmpty()) text += "N+" + playerName(Sente) + "\n";
    if (!playerName(Gote).isEmpty())  text += "N+" + playerName(Gote) + "\n";

    // 開始時間変換
    if (startDateTime() != DateTime()) text += "$START_TIME:" + startDateTime().toString("yyyy/MM/dd hh:mm:ss") + "\n";

    // 終了時間変換
    if (endDateTime() != DateTime()) text += "$END_TIME:" + endDateTime().toString("yyyy/MM/dd hh:mm:ss") + "\n";

    // 持ち時間変換
    text += "$TIME_LIMIT:" + m_time_limit_initial.toString("hh:mm") + "+" + m_time_byouyomi.toString("ss") + "\n";

    // 初期盤面情報変換
    text += m_board_initial.toCsaString();

    // 手番変換
    text += "+\n";

    // 棋譜変換
    foreach (const Record &record, m_record_list) {
        if (record.status() == StatusPlaying) {
            // 指し手変換
            text += String::number(record.from().x()) + String::number(record.from().y()) +
                    String::number(record.to().x()) + String::number(record.to().y()) +
                    pieceTypeString(record.pieceType()) + "\n";
            // 考慮時間変換
            text += "T" + String::number(record.sec()) + "\n";
        } else {
            // 特殊コマンド変換
            text += "%" + gameStatusString(record.status()) + "\n";
        }
    }

    return text;
}
