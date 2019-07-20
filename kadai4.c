/* sample4.c */
#include <GL/glut.h>

double vertex[][3] = {   /* 頂点を配列で宣言する方法 */
  {-0.5,-0.5, 0.0},
  { 0.5,-0.5, 0.0},
  { 0.5, 0.5, 0.0},
  {-0.5, 0.5, 0.0},
};

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  //glTranslatef(-1.0, 0.0, 0.0);    /* 物体をx方向に-1.0平行移動する */
  glTranslatef(0.0,0.0,-1.0);
  glRotatef(30,0.0,1.0,0.0);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  for( i=0; i<4; i++)
    glVertex3f(vertex[i][0],vertex[i][1],vertex[i][2]);
  glEnd();
  glFlush();
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* 投影法に関する座標変換を開始 */
  glLoadIdentity();
  gluPerspective( 30.0, 1.0, 1.0, 10.0 );
  glMatrixMode(GL_MODELVIEW); /* 視点の移動やモデルの移動など投影法
                                 以外の座標変換を開始 */
  gluLookAt( 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glutの初期化 */
  init(argv[0]);
  glutDisplayFunc(display);        /* ディスプレイコールバック関数の指定 */
  glutMainLoop();                  /* イベント待ちの無限ループへ入る */
  return 0;                        /* ループが終わったら0を返して終了 */
}
