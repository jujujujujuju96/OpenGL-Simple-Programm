//-----------------------------------------------------------------------
//
//   plyファイル入力を行うプログラム
//      （但し，アスキーデータ，三角メッシュのみ対応）
//
//                    Written by Kyoko Hasegawa
//-----------------------------------------------------------------------
#ifndef _PLY_H_
#define _PLY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------------------------------------------------------------------
// ply( char* filename, int* vertnum, int* facenum, float** vert, int** face, int** color, 
//      float* vertMin, float *vertMax )
//
//  [引数]
//  filename    : (入力) PLYファイル名
//  vertnum     : (出力) ポリゴンデータの頂点数
//  facenum     : (出力) ポリゴンデータのポリゴン数
//  vert        : (出力) 頂点座標
//  face        : (出力) 頂点の接続情報
//  color       : (出力) 頂点の色情報
//  vertMin     : (出力) バウンディングボックスのの最小値 
//  vertMax     : (出力) バウンディングボックスのの最大値 
//-----------------------------------------------------------------------------------------
void ply( char* filename, int* vertnum, int* facenum, float** vert, int** face, int** color, 
	  float* vertMin, float *vertMax );
#endif
