/* sample9-2.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define imageWidth 8
#define imageHeight 8

float param = 0.0;
int flag = 0;

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* 拡散反射成分の反射強度*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* 鏡面反射成分の反射強度 */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* 環境光成分の反射強度*/
float shininess = 128.0;
float light[] = {1.5, 1.5, 0.0, 0.0}; /* 光源の位置と種類 (平行光源)*/
float emission[] = {1.0, 1.0, 0.0, 1.0}; /* 放射光の属性 */

unsigned char image1[imageHeight][imageWidth][4];
unsigned char image2[imageHeight][imageWidth][4];

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

unsigned char texture2[imageHeight][imageWidth]=
{
  {255, 255, 255, 255, 255, 255, 255, 255},
  {255,   0,   0,   0,   0,   0,   0, 255},
  {255,   0, 255, 255, 255, 255,   0, 255},
  {255,   0, 255,   0,   0, 255,   0, 255},
  {255,   0, 255,   0,   0, 255,   0, 255},
  {255,   0, 255, 255, 255, 255,   0, 255},
  {255,   0,   0,   0,   0,   0,   0, 255},
  {255, 255, 255, 255, 255, 255, 255, 255}
};

void makeImage1(void)		/* texture1 をimage1に登録 */
{
  int i,j;
  for (i = 0; i < imageHeight; i++) {
    for (j = 0; j < imageWidth; j++) {
      image1[i][j][0] = (unsigned char) texture1[i][j];
      image1[i][j][1] = (unsigned char) texture1[i][j];
      image1[i][j][2] = (unsigned char) texture1[i][j];
      image1[i][j][3] = (unsigned char) texture1[i][j];
    }
  }
}

void makeImage2(void)		/* texture2 をimage2に登録 */
{
  int i,j;
  for (i = 0; i < imageHeight; i++) {
    for (j = 0; j < imageWidth; j++) {
      image2[i][j][0] = (unsigned char) texture2[i][j];
      image2[i][j][1] = (unsigned char) texture2[i][j];
      image2[i][j][2] = (unsigned char) texture2[i][j];
      image2[i][j][3] = (unsigned char) texture2[i][j];
    }
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glPushMatrix();
  glRotatef(param, 0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);     /* 拡散反射の設定 */
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);   /* 鏡面反射の設定 */
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);     /* 環境光の設定 */
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);  /* 鏡面反射の鋭さの設定 */

  glEnable(GL_LIGHTING);            /* シェーディング計算の開始 */
  glLightfv( GL_LIGHT0, GL_POSITION, light); /* 平行光源の設定 */
  glEnable(GL_TEXTURE_2D);	/* テクスチャを有効にする */

  glBindTexture(GL_TEXTURE_2D,2); /* 2番のテクスチャを使う */
  /* テクスチャ座標の自動生成を有効にする */
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  glutSolidSphere(1.0, 10, 10);	

  /* テクスチャ座標の自動生成を無効にする */
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glPushMatrix();
  glTranslatef( light[0], light[1], light[2] ); /* 光源の位置に球を置く */
  glPushAttrib(GL_LIGHTING_BIT);		/* シェーディング設定をスタックに保存 */
  glMaterialfv(GL_FRONT, GL_EMISSION, emission); /* 放射光の設定 */
  glutSolidSphere(0.1, 10, 10);			 /* 球を設置 */
  glPopAttrib();
  glPopMatrix();
  
  glDisable(GL_LIGHTING);

  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,1); /* １番のテクスチャに切り替える */
  glNormal3f(0.0,1.0,0.0);     
  glBegin(GL_QUADS);
  /* テクスチャ座標とポリゴン座標を手動で設定 */
  glTexCoord2f(0.0,0.0); glVertex3f(-1.5, -1.5, -1.5);
  glTexCoord2f(0.0,5.0); glVertex3f(-1.5, -1.5,  1.5);
  glTexCoord2f(5.0,5.0); glVertex3f( 1.5, -1.5,  1.5);
  glTexCoord2f(5.0,0.0); glVertex3f( 1.5, -1.5, -1.5);
  glEnd();

  glDisable(GL_TEXTURE_2D);

  glutSwapBuffers();
}

void idle(void)
{
  if(flag == 1){
    param = fmod(param+2.0, 360.0);  /* 回転角を0～360度まで，2度ずつ増加 */
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
    diffuse[0] = r[index];
    diffuse[1] = g[index];
    diffuse[2] = b[index];
    break;
  case 's':
    if( smooth )
      glShadeModel(GL_SMOOTH);
    else
      glShadeModel(GL_FLAT);
    smooth = !smooth;
    break;
  default:
    break;
  }
}

void initTexture1()		/* 1番目のテクスチャの初期設定 */
{
  makeImage1();
  glBindTexture(GL_TEXTURE_2D,2);	 /* 1 番目のテクスチャを設定する */
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

void initTexture2()		/* 2番目のテクスチャの初期設定 */
{
  makeImage2();
  glBindTexture(GL_TEXTURE_2D,1);	 /* 1 番目のテクスチャを設定する */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* テクスチャを1バイトずつ読み込み */
  /* テクスチャの繰り返し方の設定 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /* テクスチャを繰り返す */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

  /*テクスチャの拡大・縮小の設定  */  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* 最近傍の画素を元に拡大 */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /* 最近傍の画素を元に縮小 */

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, image2); /* テクスチャの割り当て */

  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

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
  glEnable(GL_DEPTH_TEST);   /* 隠面処理の開始を宣言 */
  
  initLighting( );
  initTexture1( );
  initTexture2( );
  
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  init(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
