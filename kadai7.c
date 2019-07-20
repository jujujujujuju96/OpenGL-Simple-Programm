/* sample7.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float param = 0.0;
int flag = 0;

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* 拡散反射成分の反射強度*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* 鏡面反射成分の反射強度 */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* 環境光成分の反射強度*/
float shininess = 128.0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(param, 0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);     /* 拡散反射の設定 */
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);   /* 鏡面反射の設定 */
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);     /* 環境光の設定 */
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);  /* 鏡面反射の鋭さの設定 */

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);            /* シェーディング計算の開始 */
  glutSolidSphere(1.0, 10, 10);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
  glutSwapBuffers();
}

void idle(void)
{
  if(flag == 1){
    param = fmod(param+1.0, 360.0);  /* 回転角を0～360度まで，1度ずつ増加 */
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
      flag = 0;               /* 右ボタンがクリックされたときに行う処理 */
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
  static int flag = 0;

  switch (key) {
  case 'q':                   /* qが入力されたら，プログラムを終了する */
    exit(0);
  case 'r':
    param += 30.0;
    break;
  case 'c':
    index++;
    index %= 4;
    diffuse[0] = r[index];
    diffuse[1] = g[index];
    diffuse[2] = b[index];
    break;
  case 's':
    if(flag==0){
      glShadeModel(GL_SMOOTH);
      flag=1;
    }else{
      glShadeModel(GL_FLAT);
      flag=0;
    }
    break;
  default:
    break;
  }
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); /* ダブルバッファの宣言 */
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* 投影法に関する座標変換を開始 */
  glLoadIdentity();
  gluPerspective( 30.0, 1.0, 1.0, 10.0 );
  glMatrixMode(GL_MODELVIEW); /* 視点の移動やモデルの移動など投影法
                                 以外の座標変換を開始 */
  gluLookAt( 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  glShadeModel(GL_FLAT);     /* シェーディングの種類をフラットシェーディングに設定 */
  glEnable(GL_LIGHT0);       /* LIGHT0の光源を有効にする */
  glEnable(GL_DEPTH_TEST);
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
