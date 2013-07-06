#include "csa.h"
#include "board.h"

using namespace Shogi;


#define STR_PLAYER_CONVERT(str) \
    str == "+" ? Sente : \
    str == "-" ? Gote  : \
    NoPlayer;

#define STR_PIECE_TYPE_CONVERT(str) \
    str == "FU" ? PiecePawn : \
    str == "KY" ? PieceLance : \
    str == "KE" ? PieceKnight : \
    str == "GI" ? PieceSilver : \
    str == "KI" ? PieceGold : \
    str == "HI" ? PieceRook: \
    str == "KA" ? PieceBishop : \
    str == "OU" ? PieceKing : \
    str == "TO" ? PiecePawnPromotion : \
    str == "NY" ? PieceLancePromotion : \
    str == "NK" ? PieceKnightPromotion : \
    str == "NG" ? PieceSilverPromotion : \
    str == "RY" ? PieceRookPromotion : \
    str == "UM" ? PieceBishopPromotion : \
    PieceEmpty;


Csa::Csa(const String &csa_string) :
    m_csa_string(csa_string),
    m_valid(false)
{
    // 駒箱に標準的に使用される駒種別を追加する（歩18枚、飛2枚、角2枚、香4枚、桂4枚、銀4枚、金4枚、玉2枚
                // 先手分
    m_piece_box << PiecePawn  << PiecePawn   << PiecePawn   << PiecePawn << PiecePawn << PiecePawn << PiecePawn   << PiecePawn   << PiecePawn
                              << PieceRook                                                                        << PieceBishop
                << PieceLance << PieceKnight << PieceSilver << PieceGold << PieceKing << PieceGold << PieceSilver << PieceKnight << PieceLance
                // 後手分
                << PiecePawn  << PiecePawn   << PiecePawn   << PiecePawn << PiecePawn << PiecePawn << PiecePawn   << PiecePawn   << PiecePawn
                              << PieceBishop                                                                      << PieceRook
                << PieceLance << PieceKnight << PieceSilver << PieceGold << PieceKing << PieceGold << PieceSilver << PieceKnight << PieceLance;

    mainConvert();
}

Board Csa::toBoard() const
{
    return m_component.board();
}

Component Csa::toComponent() const
{
    return m_component;
}

void Csa::mainConvert()
{
    StringList lines = m_csa_string.split("\n");

    foreach (const String &line, lines) {
        // 空行なら読み飛ばし
        if (line.isEmpty())
            continue;

        Char key = line.at(0);
        String value = line.mid(1);

        switch (key.toAscii()) {
        case '\'':  // コメント
            break;
        case 'V':   // バージョン
            //
            break;
        case 'N':   // 対戦者名
            playerNameConvert(value);
            break;
        case '$':   // 各種棋譜情報
            gameInfoConvert(value);
            break;
        case 'P':   // 開始局面
            boardInitConvert(value);
            break;
        case '+':
        case '-':
            if (value.isEmpty()) {
                // 先手、後手
            } else {
                m_turn = STR_PLAYER_CONVERT(String(key));
                recordConvert(value);
            }
            break;
        case 'T':
            thinkTimeConvert(value);
            break;
        case '%':
            commandConvert(value);
            break;
        default:
            qDebug("Unknown CSA key: '%c'", key.toAscii());
            break;
        }
    }
}

void Csa::playerNameConvert(const String &text)
{
    switch (text.at(0).toAscii()) {
    case '+':
        m_component.setPlayerName(Sente, text.mid(1));
        break;
    case '-':
        m_component.setPlayerName(Gote, text.mid(1));
        break;
    }
}

void Csa::gameInfoConvert(const String &text)
{
    if (text.startsWith("EVENT:")) {
        // イベント名の設定 (何もしない)
    } else if (text.startsWith("SITE:")) {
        // 開催場所の設定 (何もしない)
    } else if (text.startsWith("START_TIME:")) {
        const DateTime &time = DateTime::fromString(text.mid(11), "yyyy/MM/dd hh:mm:ss");
        m_component.setStartDateTime(time);
    } else if (text.startsWith("END_TIME:")) {
        const DateTime &time = DateTime::fromString(text.mid(9), "yyyy/MM/dd hh:mm:ss");
        m_component.setEndDateTime(time);
    } else if (text.startsWith("TIME_LIMIT:")) {
        m_component.setTimeLimit(Time::fromString(text.mid(11), "hh:mm+00"));
        m_component.setTimeByouyomi(Time::fromString(text.mid(11), "00:00+ss"));
    } else if (text.startsWith("OPENING:")) {
        // (何もしない)
    }
}

void Csa::boardInitConvert(const String &text)
{
    Char key = text.at(0);
    String value = text.mid(1);
    switch (key.toAscii()) {
    case 'I':   // 平手
    {
        // 駒落ち情報を取得
        PointList point_list;
        while (!value.isEmpty()) {
            const int x = value.at(0).digitValue();
            const int y = value.at(1).digitValue();
            point_list.append(Point(x, y));
            value = value.mid(4);
        }

        struct PieceInitList {
            Player owner;
            PieceType piece_type;
            Point point;
        };

        // 平手の駒配置
        const PieceInitList piece_init_type[] = {
            { Sente, PiecePawn,   Point(1, 7) },
            { Sente, PiecePawn,   Point(2, 7) },
            { Sente, PiecePawn,   Point(3, 7) },
            { Sente, PiecePawn,   Point(4, 7) },
            { Sente, PiecePawn,   Point(5, 7) },
            { Sente, PiecePawn,   Point(6, 7) },
            { Sente, PiecePawn,   Point(7, 7) },
            { Sente, PiecePawn,   Point(8, 7) },
            { Sente, PiecePawn,   Point(9, 7) },
            { Sente, PieceRook,   Point(2, 8) },
            { Sente, PieceBishop, Point(8, 8) },
            { Sente, PieceLance,  Point(1, 9) },
            { Sente, PieceKnight, Point(2, 9) },
            { Sente, PieceSilver, Point(3, 9) },
            { Sente, PieceGold,   Point(4, 9) },
            { Sente, PieceKing,   Point(5, 9) },
            { Sente, PieceGold,   Point(6, 9) },
            { Sente, PieceSilver, Point(7, 9) },
            { Sente, PieceKnight, Point(8, 9) },
            { Sente, PieceLance,  Point(9, 9) },
            { Gote,  PiecePawn,   Point(1, 3) },
            { Gote,  PiecePawn,   Point(2, 3) },
            { Gote,  PiecePawn,   Point(3, 3) },
            { Gote,  PiecePawn,   Point(4, 3) },
            { Gote,  PiecePawn,   Point(5, 3) },
            { Gote,  PiecePawn,   Point(6, 3) },
            { Gote,  PiecePawn,   Point(7, 3) },
            { Gote,  PiecePawn,   Point(8, 3) },
            { Gote,  PiecePawn,   Point(9, 3) },
            { Gote,  PieceRook,   Point(8, 2) },
            { Gote,  PieceBishop, Point(2, 2) },
            { Gote,  PieceLance,  Point(1, 1) },
            { Gote,  PieceKnight, Point(2, 1) },
            { Gote,  PieceSilver, Point(3, 1) },
            { Gote,  PieceGold,   Point(4, 1) },
            { Gote,  PieceKing,   Point(5, 1) },
            { Gote,  PieceGold,   Point(6, 1) },
            { Gote,  PieceSilver, Point(7, 1) },
            { Gote,  PieceKnight, Point(8, 1) },
            { Gote,  PieceLance,  Point(9, 1) },
        };

        // 駒を配置する
        const int count = sizeof(piece_init_type) / sizeof(piece_init_type[0]);
        for (int i = 0; i < count; ++i) {
            // 駒落ち情報リストに登録されている座標の駒は登録しない。
            if (point_list.contains(piece_init_type[i].point))
                continue;

            Piece piece(piece_init_type[i].owner, piece_init_type[i].piece_type);
            piece.setPoint(piece_init_type[i].point);
            m_component.setPiece(piece);
        }
    }
        break;
    case '1':   // 一括表現
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        const int y = key.digitValue();
        for (int x = 9; x > 0; --x) {
            const String &player_text = value.at(0);
            if (!player_text.isEmpty()) {
                // 手番を取得
                Player owner = STR_PLAYER_CONVERT(player_text);

                // 駒種別を取得
                const String &piece_type_text = value.mid(1, 2);
                PieceType piece_type = STR_PIECE_TYPE_CONVERT(piece_type_text);

                // 手番と駒種別が正しく取得できていれば駒を盤面情報に設定する
                if (owner != NoPlayer && piece_type != PieceEmpty) {
                    Piece piece(owner, piece_type);
                    piece.setPoint(Point(x, y));
                    m_component.setPiece(piece);
                }
            }
            value = value.mid(3);
            if (value.isEmpty())
                break;
        }
    }
        break;
    case '+':   // 駒別単独表現
    case '-':
    {
        // 手番を取得
        Player owner = STR_PLAYER_CONVERT(String(key));

        while (!value.isEmpty()) {
            // 座標の取得
            const int x = value.at(0).digitValue();
            const int y = value.at(1).digitValue();
            Point point(x, y);

            // 駒種別を取得
            const String &piece_type_text = value.mid(2, 2);
            PieceType piece_type = STR_PIECE_TYPE_CONVERT(piece_type_text);

            // 手番と駒種別が正しく取得できていれば駒を盤面情報に設定する
            if (owner != NoPlayer && piece_type != PieceEmpty) {
                Piece piece(owner, piece_type);
                piece.setPoint(point);
                m_component.setPiece(piece);

                // 駒箱から取り除く
                m_piece_box.removeOne(piece_type);
            }

            // 座標(0, 0)の時に駒種別"AL"が指定されると残りの駒を全て配置する
            if (point == Point(0, 0) && piece_type_text == "AL") {
                while (!m_piece_box.isEmpty()) {
                    PieceType piece_type = m_piece_box.first();
                    Piece piece(owner, piece_type);
                    piece.setPoint(point);
                    m_component.setPiece(piece);

                    // 駒箱から取り除く
                    m_piece_box.removeOne(piece_type);
                }
            }

            value = value.mid(4);
        }
    }
        break;
    default:
        qDebug("Unknown Board key: '%c'", key.toAscii());
        break;
    }
}

void Csa::recordConvert(const String &text)
{
    // 手番を取得
    Player turn = m_turn;

    // 移動元座標を取得
    Point from(text.mid(0, 1).toInt(), text.mid(1, 1).toInt());

    // 移動先座標を取得
    Point to(text.mid(2, 1).toInt(), text.mid(3, 1).toInt());

    // 駒種別を取得
    PieceType piece_type = STR_PIECE_TYPE_CONVERT(text.mid(4, 2));
    Record record(turn, from, to, piece_type);
    m_record = record;
}

void Csa::thinkTimeConvert(const String &text)
{
    m_record.setSec(text.toInt());
    m_component.addRecord(m_record);
}

void Csa::commandConvert(const String &text)
{
    if (text.startsWith("TORYO")) {                 // 投了
        Record record(NoPlayer, StatusToryo);
        m_component.addRecord(record);
    } else if (text.startsWith("CHUDAN")) {         // 中断
        Record record(NoPlayer, StatusChudan);
        m_component.addRecord(record);
    } else if (text.startsWith("SENNICHITE")) {     // 千日手
        Record record(NoPlayer, StatusSennichite);
        m_component.addRecord(record);
    } else if (text.startsWith("TIME_UP")) {        // 手番側が時間切れで負け
        Record record(NoPlayer, StatusTimeUp);
        m_component.addRecord(record);
    } else if (text.startsWith("ILLEGAL_MOVE")) {   // 手番側の反則負け、反則の内容はコメントで記録する
        Record record(NoPlayer, StatusIllegalMove);
        m_component.addRecord(record);
    } else if (text.startsWith("+ILLEGAL_ACTION")) {    // 先手(下手)の反則行為により、後手(上手)の勝ち
        Record record(Sente, StatusIllegalMove);
        m_component.addRecord(record);
    } else if (text.startsWith("-ILLEGAL_ACTION")) {    // 後手(上手)の反則行為により、先手(下手)の勝ち
        Record record(Gote, StatusIllegalMove);
        m_component.addRecord(record);
    } else if (text.startsWith("JISHOGI")) {        // 持将棋
        Record record(NoPlayer, StatusJishogi);
        m_component.addRecord(record);
    } else if (text.startsWith("KACHI")) {          // (入玉で)勝ちの宣言
        Record record(NoPlayer, StatusKachi);
        m_component.addRecord(record);
    } else if (text.startsWith("HIKIWAKE")) {       // (入玉で)引き分けの宣言
        Record record(NoPlayer, StatusHikiwake);
        m_component.addRecord(record);
#if 0
    } else if (info.startsWith("MATTA")) {          // 待った
        Record record(NoPlayer, StatusMATTA);
        m_component.addRecord(record);
#endif
    } else if (text.startsWith("TSUMI")) {          // 詰み
        Record record(NoPlayer, StatusTsumi);
        m_component.addRecord(record);
    } else if (text.startsWith("FUZUMI")) {         // 不詰
        Record record(NoPlayer, StatusFuzumi);
        m_component.addRecord(record);
    } else if (text.startsWith("ERROR")) {          // エラー
        Record record(NoPlayer, StatusError);
        m_component.addRecord(record);
    }
}
