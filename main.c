#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
//#include "myShape.h"

#include "ply.h"

float param = 0.0;
int flag = 0,flag1=0;
float epsilon=1.0e-4;

int vertnum, facenum;		/* 頂点数， ポリゴン数*/
float* vert;			/* 頂点座標 */
int *face;			/* 頂点の接続情報 */
int *color;			/* 頂点色 */
float vertMin[3], vertMax[3];  /* 読み込んだオブジェクトのバウンディングボックス */
float vertCenter[3];		/* 読み込んだオブジェクトの中心 */

void display(void)
{
  int i;
  int e0, e1, e2;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glPushMatrix();
  glRotatef(param, 0.0, 1.0, 0.0);//全部回転

  //---- ポリゴンデータを描画
  glBegin(GL_TRIANGLES);
  for( i=0; i<facenum; i++ ) {
    e0 = face[3*i];		/* 三角ポリゴンの頂点番号 0 */
    e1 = face[3*i+1];		/* 三角ポリゴンの頂点番号 1 */
    e2 = face[3*i+2];		/* 三角ポリゴンの頂点番号 2 */
    /* 頂点色が0 ~ 255 の数字になっているので，0 ~ 1に正規化 */
    glColor3f( (float)color[ 3*e0 ]/255.0, (float)color[ 3*e0 + 1 ]/255.0, (float)color[ 3*e0 + 2 ]/255.0 ); 
    glVertex3f( vert[ 3*e0 ], vert[ 3*e0 + 1 ], vert[ 3*e0 + 2 ] );
    glColor3f( (float)color[ 3*e1 ]/255.0, (float)color[ 3*e1 + 1 ]/255.0, (float)color[ 3*e1 + 2 ]/255.0 );
    glVertex3f( vert[ 3*e1 ], vert[ 3*e1 + 1 ], vert[ 3*e1 + 2 ] );
    glColor3f( (float)color[ 3*e2 ]/255.0, (float)color[ 3*e2 + 1 ]/255.0, (float)color[ 3*e2 + 2 ]/255.0 );
    glVertex3f( vert[ 3*e2 ], vert[ 3*e2 + 1 ], vert[ 3*e2 + 2 ] );
  }
  glEnd();

  //---- ワイヤーフレーム表示
  glColor3f(0.0, 0.0, 0.0);    //--- 線の色は黒で描画
  for( i=0; i<facenum; i++ ) {
    e0 = face[3*i];
    e1 = face[3*i+1];
    e2 = face[3*i+2];
    glBegin(GL_LINE_STRIP);    
      glVertex3f( vert[ 3*e0 ], vert[ 3*e0 + 1 ], vert[ 3*e0 + 2 ] );
      glVertex3f( vert[ 3*e1 ], vert[ 3*e1 + 1 ], vert[ 3*e1 + 2 ] );
      glVertex3f( vert[ 3*e2 ], vert[ 3*e2 + 1 ], vert[ 3*e2 + 2 ] );
    glEnd();
  }
  glEnd();
  
  glPopMatrix();

  glFlush();
  glutSwapBuffers();

}

void idle(void)
{
  if(flag==1){
    param = fmod(param+2.0,360.0);
    if(param<epsilon){
       flag=0;
      }  
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    exit(0);
  case 'r':
    flag=1;
    break;
  case 's':
    flag1=1;
    break;
  default:
    break;
  }
}
 
void init(char *winname)
{
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(winname);       /* winnameで指定された名前でウィンドウを開く */
  glClearColor(0.0, 0.0, 0.0, 1.0);/* ウィンドウの背景色の指定 */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); /* 変換行列の初期化 */
  gluPerspective( 45.0, 1.0, 1.0, 2000.0 ); /* Setting Perspective Viewing*/
  gluLookAt(  vertCenter[0]-300, vertCenter[1]+500, vertCenter[2] + 700, vertCenter[0], vertCenter[1], vertCenter[2], 0.0, 1.0, 0.0 );
}

int main(int argc, char**argv)
{

  //--- plyファイルからポリゴンデータを読み込む
  ply( argv[1], &vertnum, &facenum, &vert, &face, &color, vertMin, vertMax );
  vertCenter[0] = vertMin[0] + (vertMax[0] - vertMin[0])/2.0;
  vertCenter[1] = vertMin[1] + (vertMax[1] - vertMin[1])/2.0;
  vertCenter[2] = vertMin[2] + (vertMax[2] - vertMin[2])/2.0;

  printf( "vertnum: %d, facenum: %d\n", vertnum, facenum );
  printf( "Min: %g %g %g\n", vertMin[0], vertMin[1], vertMin[2] );
  printf( "Max: %g %g %g\n", vertMax[0], vertMax[1], vertMax[2] );
  printf( "Center: %g %g %g\n", vertCenter[0], vertCenter[1], vertCenter[2] );

  glutInit(&argc, argv);           /* glutの初期化 */
  init(argv[0]);
  glutDisplayFunc(display);        /* ディスプレイコールバック関数の指定 */
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutIdleFunc(idle);
  glutMainLoop();                  /* イベント待ちの無限ループへ入る */

  free( vert );
  free( face );
  free( color );
  return 0;
}
