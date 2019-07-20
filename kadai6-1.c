/* sample6-1.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float param = 0.0;
int flag=0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();                         /* この時点での座標系（変換行列）を保存 */
  glRotatef(param, 0.0, 1.0, 0.0);        /* y軸を中心にparam度回転 */
  glBegin(GL_QUADS);
    if(flag==0){glColor3f(1.0,1.0,1.0);}
    if(flag==1){glColor3f(1.0,0.0,0.0);}
    if(flag==2){glColor3f(0.0,1.0,0.0);}
    if(flag==3){glColor3f(0.0,0.0,1.0);}
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
  glEnd();
  glPopMatrix();                          /* 9行目の変換系に戻る */
  glutSwapBuffers();
}

void idle(void)
{
  param = fmod(param, 360.0);  /* 回転角を0～360度まで，1.0度ずつ増加 */
  glutPostRedisplay();      /* ディスプレイコールバック関数(display)の実行 */
}

void keyboard(unsigned char key, int x, int y)
/*引数 key にはタイプされたキーの ASCII コードが，
x と y にはキーがタイプされたときのマウスの位置が渡される */
{
  switch (key) {
  case 'q':                   /* qが入力されたら，プログラムを終了する */
    exit(0);
  case 'r':
    param = fmod(param+30.0,360.0);
    break;
  case 'c':
    flag++;
    if(flag>3){flag=0;}
    break;
  default:
    break;
  }
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /* ダブルバッファの宣言 */

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
  glutInit(&argc, argv);
  init(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard); /* キーボード入力のコールバック関数keyboardの指定 */
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
