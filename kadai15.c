/* sample10.c */
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "myShape.h"

#define imageWidth 8
#define imageHeight 8

#define XMIN 32
#define YMIN 24
#define XMAX 1000
#define YMAX 1000

float param = 0.0;
float rot = 0.0;
int flag = 0;
int flag2 = 0;
int flag_fly1 = 0,flag_fly2=1,flag_down=0;
float fly_h = 0.0;
float epsilon = 1.0e-4;
float r_leg = 0;
float A,B;
float xx=0.0,yy=0.0;

float height = 0.0;		/* 高さ */
float y_max  = 0.0;		/* 初期位置 */
float gravt  = -5.81; 		/* 重力加速度 */
float dt   = 0.1;		/* 時間の刻み */
float vz   = 5.0;		/* 初速度 */

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* 拡散反射成分の反射強度*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* 鏡面反射成分の反射強度 */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* 環境光成分の反射強度*/
float shininess = 128.0;
float light[] = {1.5, 1.5, 0.0, 0.0}; /* 光源の位置と種類 (平行光源)*/
float emission[] = {1.0, 1.0, 0.0, 1.0}; /* 放射光の属性 */

float head[] ={0.2706 ,0.9529 ,0.1882,1.0};
float nose[] ={0.9529 ,0.1882 ,0.7882,1.0};
float eye[] ={0.4706 ,0.4706 ,0.4706,1.0};
float ear[] ={0.9529 ,0.6902 ,0.1882,1.0};
float body[] ={0.9961 ,0.9647 ,0.1216,1.0};
float leg[] ={0.06275 ,0.2118 ,0.6941,1.0};
float hand[] ={0.000 ,0.7686 ,1.000,1.0};
float fly[] ={1.000 ,0.9569 ,0.000};

unsigned char image1[imageHeight][imageWidth][4];

unsigned char texture1[imageHeight][imageWidth]= /* texture1の定義 */
{
  {255, 255, 255, 255,   0,   0,   0,   0},
  {255, 255, 255, 255,   0,   0,   0,   0},
  {255, 255, 255, 255,   0,   0,   0,   0},
  {255, 255, 255, 255,   0,   0,   0,   0},
  {  0,   0,   0,   0, 255, 255, 255, 255},
  {  0,   0,   0,   0, 255, 255, 255, 255},
  {  0,   0,   0,   0, 255, 255, 255, 255},
  {  0,   0,   0,   0, 255, 255, 255, 255}
};

void makeImage1(void)		/* texture1 をimage1に登録 */
{
  int i,j;
  for (i = 0; i < imageHeight; i++) {
    for (j = 0; j < imageWidth; j++) {
      image1[i][j][0] = (unsigned char) texture1[i][j];
      image1[i][j][1] = (unsigned char) texture1[i][j];
      image1[i][j][2] = (unsigned char) texture1[i][j];
      image1[i][j][3] = (unsigned char) 100;
    }
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* zバッファを初期化 */

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
  glEnable(GL_LIGHTING);

  glPushMatrix();//jump_push
  glTranslatef(0.0, fly_h, 0.0);
  glTranslatef(0.0, height, 0.0);
  glTranslatef(xx/100,0.0,-yy/100);//walking

  glMaterialfv(GL_FRONT, GL_DIFFUSE, head);
  glPushMatrix();
  //glRotatef(param, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  glutSolidCube(2.0);//head

  glMaterialfv(GL_FRONT, GL_DIFFUSE, fly);
  glPushMatrix();
  glTranslatef(0.0, 1.30, 0.0);
  glRotatef(param, 0.0, 1.0, 0.0);
  glRotatef(90,1.0,0.0,0.0);  
  mySolidCylinder(0.08,2.0,50);                                                                                                             
  glPopMatrix();//fly_1

  glMaterialfv(GL_FRONT, GL_DIFFUSE, leg);
  glPushMatrix();
  glTranslatef(0.0, 0.88, 0.0);
  mySolidCylinder(0.09,1.0,50);                                                                                                             
  glPopMatrix();//fly_2

  glMaterialfv(GL_FRONT, GL_DIFFUSE, eye);
  glPushMatrix();
  glTranslatef(-0.5, 0.5, 1.0);
  glutSolidSphere(0.2, 10, 10);
  glPopMatrix();//eye_right

  glMaterialfv(GL_FRONT, GL_DIFFUSE, eye);
  glPushMatrix();
  glTranslatef(0.5, 0.5, 1.0);
  glutSolidSphere(0.2, 10, 10);
  glPopMatrix();//eye_left

  glMaterialfv(GL_FRONT, GL_DIFFUSE, nose);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 1.1);
  glutSolidCube(0.2);
  glPopMatrix();//nose

  glMaterialfv(GL_FRONT, GL_DIFFUSE, ear);
  glPushMatrix();
  glTranslatef(1.0, 0.0, 0.0);
  glutWireTorus(0.1, 0.2, 50, 50);
  glutSolidTorus(0.1, 0.2, 50, 50);
  glPopMatrix();//ears_right

  glMaterialfv(GL_FRONT, GL_DIFFUSE, ear);
  glPushMatrix();
  glTranslatef(-1.0, 0.0, 0.0);
  glutWireTorus(0.1, 0.2, 50, 50);
  glutSolidTorus(0.1, 0.2, 50, 50);
  glPopMatrix();//ears_left
  
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_DIFFUSE, body);
  glPushMatrix();
  glTranslatef(0.0, -2.0, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  mySolidCylinder(0.5, 1.5, 30);
  glPopMatrix();//body 

  glMaterialfv(GL_FRONT, GL_DIFFUSE, hand);
  glPushMatrix();
  glTranslatef(0.8, -1.8, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  mySolidCylinder(0.2, 1, 30);
  glPopMatrix();//hand_left

  glMaterialfv(GL_FRONT, GL_DIFFUSE, hand);
  glPushMatrix();
  glTranslatef(-0.8, -1.8, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  mySolidCylinder(0.2, 1, 30);
  glPopMatrix();//hand_right

  glMaterialfv(GL_FRONT, GL_DIFFUSE, leg);
  glPushMatrix();
  //glRotatef(-r_leg,1.0,0.0,0.0);//leg_rotate
  glTranslatef(0.3, -3.5, 0.0);
  glTranslatef(0.0, 2.8, 0.0);
  mySolidCylinder(0.2, 1.7, 27);
  glPopMatrix();//leg_right

  glMaterialfv(GL_FRONT, GL_DIFFUSE, leg);
  glPushMatrix();
  //glRotatef(r_leg,1.0,0.0,0.0);//leg_rotate
  glTranslatef(-0.3, -3.5, 0.0);
  glTranslatef(0.0, 2.8, 0.0);
  mySolidCylinder(0.2, 1.7, 27);
  glPopMatrix();//leg_left
 
  glPopMatrix();//jump_pop

  glDisable(GL_LIGHTING);

  glEnable(GL_TEXTURE_2D);	/* テクスチャを有効にする */
	
  glNormal3f(0.0,1.0,0.0);	
  glBegin(GL_QUADS);
    /* テクスチャ座標とポリゴン座標を手動で設定 */
    glTexCoord2f(0.0,0.0); glVertex3f(-5.5, -1.5, -5.5);
    glTexCoord2f(0.0,20.0); glVertex3f(-5.5, -1.5,  5.5);
    glTexCoord2f(20.0,20.0); glVertex3f( 5.5, -1.5,  5.5);
    glTexCoord2f(20.0,0.0); glVertex3f( 5.5, -1.5, -5.5);
  glEnd();

  glDisable(GL_TEXTURE_2D);

  glutSwapBuffers();
}

void idle(void)
{
  if(flag_fly1 == 1 && flag_down == 0){
    param = fmod(param+60.0, 360.0);  /* 回転角を0～360度まで，2度ずつ増加 */
  }
  if(flag == 2){
    param = fmod(param+2.0, 360.0);  /* 回転角を0～360度まで，2度ずつ増加 */
    if(param < epsilon){ flag = 0;}
  }

  if(flag_fly1 == 1 && flag_fly2 == 1){//fly
    fly_h = fly_h + 0.15*dt;
    if(fly_h > 1.5){
      flag_fly2 = 0;
    }
  }
 
  if(flag_down == 1){
    fly_h = fly_h -0.7 * dt;
    if(fly_h < 0.01){
      flag_down = 0;
    }
  }

  if (flag2 == 1 ) {//jump
    height = height + vz*dt;
    vz= vz+ gravt*dt;
  if( height < 0.0 ) {
      flag2 = 0;
      height = 0;
      vz   = 5.0;
    }
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
  static float col[4][4] =
    {{1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0}};
  static int index = 0;
  static int smooth = 0;
  switch (key) {
  case 'q':                   /* qが入力されたら，プログラムを終了する */
    exit(0);
  case 'r':
    param += 30.;
    break;
  case 'c':
    index++;
    index %= 4;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col[index] );
    break;
  case 's':
    if( smooth )
      glShadeModel(GL_SMOOTH);
    else
      glShadeModel(GL_FLAT);
    smooth = !smooth;
    break;
  case 'h':
    flag = 2;
    break;
  case 'j':
    flag2 = 1;
    height = y_max;
    flag = 1;
    break;
  case 'f':
    flag_fly1 = 1;
    flag_down = 0;
    break;
  case 'd':
    flag_down = 1;
    flag_fly1 = 0;
    break;
  default:
    break;
  }
}

void mousedrag( int x, int y )
{
  xx = x - XMAX/2 ; 
  yy = YMAX/2 - y;
}

void initTexture1()		/* テクスチャの初期設定 */
{
  makeImage1();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* テクスチャを1バイトずつ読み込み */
  /* テクスチャの繰り返し方の設定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /* テクスチャを繰り返す */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

  /*テクスチャの拡大・縮小の設定  */  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* 最近傍の画素を元に拡大 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /* 最近傍の画素を元に縮小 */

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, image1); /* テクスチャの割り当て */
}

void initLighting()		/* 光源の属性の設定 */
{

  float diffuse_light[]  = {0.5, 0.5, 0.5, 1.0}; /* 光源の拡散反射成分の強度 */
  float specular_light[] = {0.5, 0.5, 0.5, 1.0}; /* 光源の鏡面反射成分の強度 */
  float ambient_light[]  = {0.5, 0.5, 0.5, 1.0}; /* 光源の環境光成分の強度 */

  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); /* 拡散反射成分の強度 */
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light); /* 鏡面反射成分の強度 */
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);   /* 環境光成分の強度 */
}

void init(char *winname)
{
  glutInitWindowPosition( XMIN, YMIN);
  glutInitWindowSize( XMAX-XMIN, YMAX-YMIN);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); /* zバッファ利用の宣言 */
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* 投影法に関する座標変換を開始 */
  glLoadIdentity();
  gluPerspective( 45.0, 1.0, 1.0, 50.0 );
  glMatrixMode(GL_MODELVIEW); /* 視点の移動やモデルの移動など投影法
                                 以外の座標変換を開始 */
  gluLookAt( 3.0, 7.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  glShadeModel(GL_FLAT);     /* シェーディングの種類をフラットシェーディングに設定 */
  glEnable(GL_LIGHT0);       /* LIGHT0の光源を有効にする */

  glEnable(GL_DEPTH_TEST);   /* 隠面処理の開始を宣言 */

  initLighting( );
  initTexture1( );
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  init(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);  /* マウス入力のコールバック関数mouseの指定 */
  glutMotionFunc(mousedrag);		/* マウス左ボタンを押しながらドラッグする場合 */
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
