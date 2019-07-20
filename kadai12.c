/* sample10.c */
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "myShape.h"

#define imageWidth 8
#define imageHeight 8

float param = 0.0;
float rot = 0.0;
int flag = 0;
float epsilon = 1.0e-4;

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

  glMaterialfv(GL_FRONT, GL_DIFFUSE, head);
  glPushMatrix();
  glRotatef(param, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  glutSolidCube(2.0);

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
  glTranslatef(0.3, -3.5, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  mySolidCylinder(0.2, 2.0, 30);
  glPopMatrix();//leg_right

  glMaterialfv(GL_FRONT, GL_DIFFUSE, leg);
  glPushMatrix();
  glTranslatef(-0.3, -3.5, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  mySolidCylinder(0.2, 2.0, 30);
  glPopMatrix();//leg_left
 
  //glPopMatrix();

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
  if(flag == 1){
    param = fmod(param+2.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC2�x������ */
  }
  if(flag == 2){
    param = fmod(param+2.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC2�x������ */
    if(param < epsilon){ flag = 0;}
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
  default:
    break;
  }
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
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); /* z�o�b�t�@���p�̐錾 */
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* ���e�@�Ɋւ�����W�ϊ����J�n */
  glLoadIdentity();
  gluPerspective( 45.0, 1.0, 1.0, 50.0 );
  glMatrixMode(GL_MODELVIEW); /* ���_�̈ړ��⃂�f���̈ړ��ȂǓ��e�@
                                 �ȊO�̍��W�ϊ����J�n */
  gluLookAt( 3.0, 4.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

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
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
