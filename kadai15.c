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

float height = 0.0;		/* ���� */
float y_max  = 0.0;		/* �����ʒu */
float gravt  = -5.81; 		/* �d�͉����x */
float dt   = 0.1;		/* ���Ԃ̍��� */
float vz   = 5.0;		/* �����x */

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* �g�U���ː����̔��ˋ��x*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* ���ʔ��ː����̔��ˋ��x */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* ���������̔��ˋ��x*/
float shininess = 128.0;
float light[] = {1.5, 1.5, 0.0, 0.0}; /* �����̈ʒu�Ǝ�� (���s����)*/
float emission[] = {1.0, 1.0, 0.0, 1.0}; /* ���ˌ��̑��� */

float head[] ={0.2706 ,0.9529 ,0.1882,1.0};
float nose[] ={0.9529 ,0.1882 ,0.7882,1.0};
float eye[] ={0.4706 ,0.4706 ,0.4706,1.0};
float ear[] ={0.9529 ,0.6902 ,0.1882,1.0};
float body[] ={0.9961 ,0.9647 ,0.1216,1.0};
float leg[] ={0.06275 ,0.2118 ,0.6941,1.0};
float hand[] ={0.000 ,0.7686 ,1.000,1.0};
float fly[] ={1.000 ,0.9569 ,0.000};

unsigned char image1[imageHeight][imageWidth][4];

unsigned char texture1[imageHeight][imageWidth]= /* texture1�̒�` */
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

void makeImage1(void)		/* texture1 ��image1�ɓo�^ */
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* z�o�b�t�@�������� */

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

  glEnable(GL_TEXTURE_2D);	/* �e�N�X�`����L���ɂ��� */
	
  glNormal3f(0.0,1.0,0.0);	
  glBegin(GL_QUADS);
    /* �e�N�X�`�����W�ƃ|���S�����W���蓮�Őݒ� */
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
    param = fmod(param+60.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC2�x������ */
  }
  if(flag == 2){
    param = fmod(param+2.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC2�x������ */
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
  if(state == GLUT_DOWN){     /* �}�E�X���N���b�N����� */
    switch(button){
    case GLUT_LEFT_BUTTON:    /*�N���b�N���ꂽ�̂����{�^���������� */
      flag = 1;               /* ���{�^�����N���b�N���ꂽ�Ƃ��ɍs������ */
      break;
    case GLUT_RIGHT_BUTTON:   /*�N���b�N���ꂽ�̂��E�{�^���������� */
      flag = 0;               /* �E�{�^�����N���b�N���ꂽ�Ƃ��ɍs������ */
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
  case 'q':                   /* q�����͂��ꂽ��C�v���O�������I������ */
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

void initTexture1()		/* �e�N�X�`���̏����ݒ� */
{
  makeImage1();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* �e�N�X�`����1�o�C�g���ǂݍ��� */
  /* �e�N�X�`���̌J��Ԃ����̐ݒ� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /* �e�N�X�`�����J��Ԃ� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

  /*�e�N�X�`���̊g��E�k���̐ݒ�  */  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* �ŋߖT�̉�f�����Ɋg�� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /* �ŋߖT�̉�f�����ɏk�� */

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, image1); /* �e�N�X�`���̊��蓖�� */
}

void initLighting()		/* �����̑����̐ݒ� */
{

  float diffuse_light[]  = {0.5, 0.5, 0.5, 1.0}; /* �����̊g�U���ː����̋��x */
  float specular_light[] = {0.5, 0.5, 0.5, 1.0}; /* �����̋��ʔ��ː����̋��x */
  float ambient_light[]  = {0.5, 0.5, 0.5, 1.0}; /* �����̊��������̋��x */

  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); /* �g�U���ː����̋��x */
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light); /* ���ʔ��ː����̋��x */
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);   /* ���������̋��x */
}

void init(char *winname)
{
  glutInitWindowPosition( XMIN, YMIN);
  glutInitWindowSize( XMAX-XMIN, YMAX-YMIN);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); /* z�o�b�t�@���p�̐錾 */
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* ���e�@�Ɋւ�����W�ϊ����J�n */
  glLoadIdentity();
  gluPerspective( 45.0, 1.0, 1.0, 50.0 );
  glMatrixMode(GL_MODELVIEW); /* ���_�̈ړ��⃂�f���̈ړ��ȂǓ��e�@
                                 �ȊO�̍��W�ϊ����J�n */
  gluLookAt( 3.0, 7.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  glShadeModel(GL_FLAT);     /* �V�F�[�f�B���O�̎�ނ��t���b�g�V�F�[�f�B���O�ɐݒ� */
  glEnable(GL_LIGHT0);       /* LIGHT0�̌�����L���ɂ��� */

  glEnable(GL_DEPTH_TEST);   /* �B�ʏ����̊J�n��錾 */

  initLighting( );
  initTexture1( );
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  init(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);  /* �}�E�X���͂̃R�[���o�b�N�֐�mouse�̎w�� */
  glutMotionFunc(mousedrag);		/* �}�E�X���{�^���������Ȃ���h���b�O����ꍇ */
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
