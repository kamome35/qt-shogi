#ifndef SHOGI_CSA_H
#define SHOGI_CSA_H

#include "shogi.h"
#include "component.h"
#include "record.h"

namespace Shogi {

/**
 * CSA棋譜形式ク解析クラス
 *
 * CSA V2.2に対応したCSA棋譜を読み込みComponetクラスに変換するためのクラス
 * @see Component
 * @todo 改行「,」が行末に含まれる場合は複数行として扱わなければならない。（未対応）
 */
class Csa
{
public:
    /**
     * Csaコンストラクタ
     *
     * @param csa_string CSA形式の文字列
     */
    Csa(const String &csa_string);

    /**
     * 盤面情報に変換
     *
     * CSAに棋譜が含まれている場合は、棋譜の最終局面の盤面情報に返却する。
     *
     * @return 盤面情報
     */
    Board toBoard() const;

    /**
     * 将棋ゲーム情報に変換
     *
     * @return 将棋ゲーム管理情報
     */
    Component toComponent() const;

    /**
     * CSA形式の有効有無判定
     *
     * @return 入力されたCSA形式が有効であれば true が返却されるが無効な場合は false が返却される。
     */
    bool isValid() const { return m_valid; }

protected:

    /**
     * CSA形式文字列変換処理
     */
    void mainConvert();

    /**
     * 対戦者名を変換する
     *
     * @param text 文字列
     */
    void playerNameConvert(const String &text);

    /**
     * ゲーム情報変換
     *
     * @param text 文字列
     */
    void gameInfoConvert(const String &text);

    /**
     * 盤面情報変換
     *
     * @param text 文字列
     */
    void boardInitConvert(const String &text);

    /**
     * 指手情報変換
     *
     * 指手情報を変換するのみで、実際のデータ1手としては反映されない。
     * この情報を反映させるには続けて thinkTimeConvert を呼ぶ必要がある。
     *
     * @param text 文字列
     * @see thinkTimeConvert
     */
    void recordConvert(const String &text);

    /**
     * 考慮時間の変換
     *
     * 事前に呼ばれた recordConvert 内で変換された指手情報に考慮時間を付与して
     * 将棋ゲーム情報に反映させる。
     *
     * @param text 文字列
     * @see recordConvert
     */
    void thinkTimeConvert(const String &text);

    /**
     * コマンド情報の変換
     *
     * @param text 文字列
     */
    void commandConvert(const String &text);
private:
    String m_csa_string;        ///< 入力されたCSA形式文字列（オリジナルまま）
    PieceTypeList m_piece_box;  ///< 駒箱
    Component m_component;      ///< ゲーム
    bool m_valid;               ///< 有効状態
    Player m_turn;              ///< 指手情報保持用
    Record m_record;            ///< 指手情報保持用
};

} // namespace Shogi

#endif // SHOGI_CSA_H
