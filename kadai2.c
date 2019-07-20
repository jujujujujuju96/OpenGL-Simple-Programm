/* sample2.c */
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926

void display(void)
{
  int n=10;
  int i=0;
  float x,y,z;
  float r=0.5;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0); /* 描画する図形の色を白に指定 */
  glBegin(GL_POLYGON);       
    for(i=0;i<n;i++){
       x = r*cos(2.0*PI*(float)i/(float)n);
       y = r*sin(2.0*PI*(float)i/(float)n);
       z = 0.0;
       glVertex3f(x,y,z);
     }
  glEnd();
  glFlush();                /* OpenGL コマンドを強制的に実行（描画実行）*/
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);    /* ウィンドウの左上の位置を(0,0)とする */
  glutInitWindowSize(500, 500);    /* ウィンドウのサイズを500×500ドットとする */
  glutInitDisplayMode(GLUT_RGBA);  /* 色の指定にRGBAモードを用いる */
  glutCreateWindow(winname);       /* winnameで指定された名前でウィンドウを開く */

  glClearColor(0.0, 0.0, 0.0, 1.0);/* ウィンドウの背景色の指定 */
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glutの初期化 */
  init(argv[0]);
  glutDisplayFunc(display);        /* ディスプレイコールバック関数の指定 */
  glutMainLoop();                  /* イベント待ちの無限ループへ入る */
  return 0;                        /* ループが終わったら0を返して終了 */
}
