/* sample3.c */
#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0); /* 描画する図形の色を白に指定 */
  glBegin(GL_QUADS);        /* 四角形を描画 */
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
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

  glLoadIdentity(); /* 変換行列の初期化 */
  //glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0); /* 平行投影の設定 */
  gluPerspective(30.0,1.0,1.0,10);
  gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glutの初期化 */
  init(argv[0]);
  glutDisplayFunc(display);        /* ディスプレイコールバック関数の指定 */
  glutMainLoop();                  /* イベント待ちの無限ループへ入る */
  return 0;                        /* ループが終わったら0を返して終了 */
}
