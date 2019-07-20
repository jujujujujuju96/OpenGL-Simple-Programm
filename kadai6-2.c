/* sample6-2.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float param = 0.0;
float epsilon = 1.0e-4;
int flag = 0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();                         /* この時点での座標系（変換行列）を保存 */
  glRotatef(param, 0.0, 1.0, 0.0);        /* y軸を中心にparam度回転 */
  glBegin(GL_QUADS);
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
  if(flag == 1){
    param = fmod(param+2.0, 360.0);  /* 回転角を0～360度まで，2度ずつ増加 */
    //if(param < epsilon) flag = 0;  /* 一周したら，flagを0にして回転を止める */
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  if(state == GLUT_DOWN){     /* マウスがクリックされて */
    switch(button){
    case GLUT_LEFT_BUTTON:    /*クリックされたのが左ボタンだったら */
      flag = 1;               /* 左ボタンがクリックされたときに行う処理 */
      break;
    case GLUT_RIGHT_BUTTON:   /*クリックされたのが右ボタンだったら */
      /* 右ボタンがクリックされたときに行う処理 */
      flag = 0;
      break;
    }
  }
}

void keyboard(unsigned char key, int x, int y)
{
  static float r[] = {1.0, 1.0, 0.0, 0.0};
  static float g[] = {1.0, 0.0, 1.0, 0.0};
  static float b[] = {1.0, 0.0, 0.0, 1.0};
  static int index = 0;
  
  switch (key) {
  case 'q':                   /* qが入力されたら，プログラムを終了する */
    exit(0);
  case 'r':
    param += 30.;
    break;
  case 'c':
    index++;
    index %= 4;
    glColor3f( r[index], g[index], b[index] );
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
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);  /* マウス入力のコールバック関数mouseの指定 */
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
