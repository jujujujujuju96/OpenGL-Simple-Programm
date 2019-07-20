//-----------------------------------------------------------------------
//
//   plyファイル入力を行うプログラム
//      （但し，アスキーデータ，三角メッシュのみ対応）
//
//                    Written by Kyoko Hasegawa
//-----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ply.h"

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
	  float* vertMin, float *vertMax )
{
  FILE *fp;			/* ファイルポインタ */
  int nVert, nFace;		/* 頂点数とポリゴン数 */
  float *vertData;		/* 頂点座標 */
  int *faceData; 		/* 頂点の接続情報 */
  int *colorData;		/* 色情報 */
  float *vertNom;		/* 頂点法線 */
  int ifElem = 0, numData = 0, numNom = 0, numCol = 0;	/* 頂点データのproperty 順をカウント*/
  int i, j;			/* ループカウンタ */
  const int MAX_BUF = 500;	/* 1行の最大文字数 */
  char buf[ MAX_BUF ];		/* ファイル読み込みデータの一時保存 */
  char words[ 20 ][MAX_BUF];	/* トークン区切りした文字列 */
  char *p;	/* トークン区切りした文字列 */
  int numT; 			/* トークン数 */
      
  fprintf( stderr, "[%s] is not PLY file.\n", filename );
  //--- ファイルオープン
  if( (fp = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "Cannot open file [%s].\n", filename );
      exit(1);
  }

  //--- ヘッダファイルの読み込み
  fgets( buf, MAX_BUF, fp );

  //--- ply形式かどうかのチェック
  if( strncmp( buf, "ply", 3 ) != 0 ) {
    fprintf( stderr, "[%s] is not PLY file.\n", filename );
      exit(1);
  }
  
  numData = 0; 
  while( fgets( buf, MAX_BUF, fp ) != NULL ) {
    numT = 0;    
    p = buf;
    /* 空白またはTabで区切られた文字列を切り出し */
    while ( ( p=strtok(p," \t") ) != NULL ) {
      strcpy ( words[numT], p );
      numT++;      
      p = NULL;
    }
    //--- ASCII ファイルかどうかのチェック
    if( !strncmp( words[0], "format", 6 ) ) {
      if( strncmp( words[1], "ascii", 5 ) != 0 ) {
	fprintf( stderr, "[%s] is not ASCII file.\n", filename );
	exit(1);
      }
    }
    //--- 頂点数とポリゴン数の取得
    if( !strncmp( words[0], "element", 7 ) ) {
      if( !strncmp( words[1], "vertex", 6 ) ) /* 頂点数 */
	nVert = atoi( words[2] );
      else if( !strncmp( words[1], "face", 4 ) ) { /* 頂点数 */
	nFace = atoi( words[2] );
	ifElem = 1;
      }
    }
    //--- 頂点propertyのカウント 
    if( !strncmp( words[0], "property", 8 ) && ( ifElem == 0 ) ) {
      numData++;
      if( !strncmp( words[2], "nx", 2 ) ) numNom = numData -1 ;
      else if( !strncmp( words[2], "red", 3 ) ) numCol = numData -1;
    }
    //--- ヘッダの終了文字列がきたらループから脱出
    if( !strncmp( words[0], "end_header", 10 ) ){
      break;
    }
  } 
  
  printf( "Number of Vertices: %d, \t Number of polygons: %d\n", nVert, nFace );  

  vertData  = malloc( sizeof(float)*3*nVert );
  vertNom   = malloc( sizeof(float)*3*nVert );
  colorData = malloc( sizeof(  int)*3*nVert );
  faceData  = malloc( sizeof(  int)*3*nFace );
  vertMin[0] =  10000.0; vertMin[2] =  10000.0; vertMin[2] =  10000.0; 
  vertMax[0] = -10000.0; vertMax[2] = -10000.0; vertMax[2] = -10000.0; 

  //--- 頂点データの読み込み
  for( i=0; i<nVert; i++ ) {
    fgets( buf, MAX_BUF, fp );
    numT = 0;    
    p = buf;
    /* 空白またはTabで区切られた文字列を切り出し */
    while ( ( p=strtok(p," \t") ) != NULL ) {
      strcpy ( words[numT], p );
      numT++;      
      p = NULL;
    }
    if( numT < 3 ) {		/* データが存在しているかチェック */
      fprintf( stderr, "Error: [%s] is not a correct PLY file.\n", filename );
      exit(1);
    }
    vertData[ 3*i     ]  = atof( words[ 0 ] ); 
    vertData[ 3*i + 1 ]  = atof( words[ 1 ] );
    vertData[ 3*i + 2 ]  = atof( words[ 2 ] );
    //--- 最大値と最小値の検索
    if( vertMin[0] > vertData[3*i] ) vertMin[0] = vertData[3*i] ;
    if( vertMax[0] < vertData[3*i] ) vertMax[0] = vertData[3*i] ;
    if( vertMin[1] > vertData[3*i+1] ) vertMin[1] = vertData[3*i+1] ;
    if( vertMax[1] < vertData[3*i+1] ) vertMax[1] = vertData[3*i+1] ;
    if( vertMin[2] > vertData[3*i+2] ) vertMin[2] = vertData[3*i+2] ;
    if( vertMax[2] < vertData[3*i+2] ) vertMax[2] = vertData[3*i+2] ;
    
    if( numNom != 0 ) {
      vertNom [ 3*i     ]  = atof( words[ numNom     ] );
      vertNom [ 3*i + 1 ]  = atof( words[ numNom + 1 ] );
      vertNom [ 3*i + 2 ]  = atof( words[ numNom + 2 ] );
    }
    if( numCol != 0 ) {
      colorData[ 3*i     ] = atoi( words[ numCol      ] ); 
      colorData[ 3*i + 1 ] = atoi( words[ numCol + 1  ] );
      colorData[ 3*i + 2 ] = atoi( words[ numCol + 2  ] );
    }    
  } /* 頂点データ読み込み終了 */

  //--- 接続情報の読み込み
  for( i=0; i<nFace; i++ ) {
    fgets( buf, MAX_BUF, fp );
    numT = 0;    
    p = buf;
    /* 空白またはTabで区切られた文字列を切り出し */
    while ( ( p=strtok(p," \t") ) != NULL ) {
      strcpy ( words[numT], p );
      numT++;      
      p = NULL;
    }
    j = atoi( words[0] );
    if( j < 3 ) {
      fprintf( stderr, "Error: [%s] can not create a triangle mesh.\n", filename );
      exit(1);
    }
	
    faceData[ 3*i     ] = atoi( words[1] ) ;
    faceData[ 3*i + 1 ] = atoi( words[2] ) ;
    faceData[ 3*i + 2 ] = atoi( words[3] ) ;
  }    /* 接続情報の読み込み終了 */
  
  /* データのポインタを渡す */
  *vertnum = nVert;
  *facenum = nFace;
  *vert    = vertData;
  *face    = faceData;
  *color   = colorData;  
}
