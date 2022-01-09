#ifndef _INCLUDE_VGE_H
#define _INCLUDE_VGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *----------------------------------------------------------------------------
 * アプリケーション名
 *----------------------------------------------------------------------------
 */
#define APPNAME "VIDEO GAME SYSTEM"

/*
 *----------------------------------------------------------------------------
 * 画面サイズ：
 * ここを調整すればHVGA(320x480)等の画面サイズに対応できる.
 * ビデオゲームのデファクトスタンダード = QVGA(240x320又は320x240).
 * それは過去の話しだが、色々なハードへの移植に適しているメリットがある.
 *----------------------------------------------------------------------------
 */
#ifdef VGE_LANDSCAPE
#define XSIZE 320
#define YSIZE 240
#else
#define XSIZE 240
#define YSIZE 320
#endif

/*
 *----------------------------------------------------------------------------
 * データ型の宣言
 *----------------------------------------------------------------------------
 */

/* 8bit符号付き */
#ifndef INT8
#define INT8 char
#endif

/* 8bit符号なし */
#ifndef UINT8
#define UINT8
#endif

/* 16ビット符号付き */
#ifndef INT16
#define INT16 short
#endif

/* 16ビット符号なし */
#ifndef UINT16
#define UINT16 unsigned short
#endif

/* 32ビット符号付き */
#ifndef INT32
#define INT32 int
#endif

/* 32ビット符号なし */
#ifndef UINT32
#define UINT32 unsigned int
#endif

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_init: 初期化（ゲーム処理で実装する）
 *----------------------------------------------------------------------------
 * 戻り値: 成功は0、失敗時は非0を返すこと.
 *----------------------------------------------------------------------------
 */
int vge_init();

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_loop: フレーム間隔(60fps)毎の処理（ゲーム処理で実装する）
 *----------------------------------------------------------------------------
 * 戻り値: 成功は0、失敗時は非0を返すこと.
 *----------------------------------------------------------------------------
 */
int vge_loop();

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_gload: グラフィック(独自形式)をスロットにロードする
 *----------------------------------------------------------------------------
 */
int vge_gload(unsigned char n, const char *bin);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_putSP: スロットデータをスプライト領域へ転送する
 * 引数: vge_putBGと同じ
 * 解説: スプライトは、一度表示したら消える妖精のような存在
 *----------------------------------------------------------------------------
 */
void vge_putSP(unsigned char n, int sx, int sy, int xs, int ys, int dx, int dy);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_putSPM: スロットデータ(mask)をスプライト領域へ転送する
 * 引数: vge_putBGと同じ + maskカラー(c)
 * 解説: スプライトは、一度表示したら消える妖精のような存在
 *----------------------------------------------------------------------------
 */
void vge_putSPM(unsigned char n, int sx, int sy, int xs, int ys, int dx, int dy, unsigned char c);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_pixelSP: スプライト面にピクセルを描画する
 *----------------------------------------------------------------------------
 * 引数:
 * - x [I] X座標
 * - y [I] Y座標
 * - c [I] パレット番号
 *----------------------------------------------------------------------------
 */
void vge_pixelSP(int x, int y, unsigned char c);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_lineSP: スプライト面にラインを描画する
 *----------------------------------------------------------------------------
 * 引数:
 * - fx [I] X座標(基点)
 * - fy [I] Y座標(基点)
 * - tx [I] X座標(終点)
 * - ty [I] Y座標(終点)
 * - c [I] パレット番号
 *----------------------------------------------------------------------------
 */
void vge_lineSP(int fx, int fy, int tx, int ty, unsigned char c);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_boxSP: スプライト面にボックスを描画する
 *----------------------------------------------------------------------------
 * 引数:
 * - fx [I] X座標(基点)
 * - fy [I] Y座標(基点)
 * - tx [I] X座標(終点)
 * - ty [I] Y座標(終点)
 * - c [I] パレット番号
 *----------------------------------------------------------------------------
 */
void vge_boxSP(int fx, int fy, int tx, int ty, unsigned char c);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_boxfSP: スプライト面に塗りつぶしボックスを描画する
 *----------------------------------------------------------------------------
 * 引数:
 * - fx [I] X座標(基点)
 * - fy [I] Y座標(基点)
 * - tx [I] X座標(終点)
 * - ty [I] Y座標(終点)
 * - c [I] パレット番号
 *----------------------------------------------------------------------------
 */
void vge_boxfSP(int fx, int fy, int tx, int ty, unsigned char c);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] タッチパネルの状態を取得
 *----------------------------------------------------------------------------
 * 引数:
 * - s [O] タッチパネルを押した状態か否か（非タッチ0, タッチ中: フレーム数）
 * - cx [O] 現在のX座標（非タッチ中は不定）
 * - cy [O] 現在のY座標（非タッチ中は不定）
 * - dx [O] X方向の移動距離（非タッチ中は不定）
 * - dy [O] Y方向の移動距離（非タッチ中は不定）
 *----------------------------------------------------------------------------
 */
void vge_touch(int *s, int *cx, int *cy, int *dx, int *dy);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_getmute: 音を消す / 鳴らすの設定を取得
 *----------------------------------------------------------------------------
 * 戻り値: 非0=ミュート、0=発音
 *----------------------------------------------------------------------------
 */
unsigned char vge_getmute();

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_bplay: BGMを演奏する
 *----------------------------------------------------------------------------
 */
void vge_bplay(const char *mmlPath);

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_bstop: BGMの演奏を中断する
 *----------------------------------------------------------------------------
 */
void vge_bstop();

/*
 *----------------------------------------------------------------------------
 * [VGE-API] vge_bresume: BGMの演奏を中断したところから再開する
 *----------------------------------------------------------------------------
 */
void vge_bresume();

#ifdef __cplusplus
};
#endif

#endif
