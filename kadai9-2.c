/* sample9-2.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define imageWidth 8
#define imageHeight 8

float param = 0.0;
int flag = 0;

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* �g�U���ː����̔��ˋ��x*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* ���ʔ��ː����̔��ˋ��x */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* ���������̔��ˋ��x*/
float shininess = 128.0;
float light[] = {1.5, 1.5, 0.0, 0.0}; /* �����̈ʒu�Ǝ�� (���s����)*/
float emission[] = {1.0, 1.0, 0.0, 1.0}; /* ���ˌ��̑��� */

unsigned char image1[imageHeight][imageWidth][4];
unsigned char image2[imageHeight][imageWidth][4];

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

void makeImage1(void)		/* texture1 ��image1�ɓo�^ */
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

void makeImage2(void)		/* texture2 ��image2�ɓo�^ */
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

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);     /* �g�U���˂̐ݒ� */
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);   /* ���ʔ��˂̐ݒ� */
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);     /* �����̐ݒ� */
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);  /* ���ʔ��˂̉s���̐ݒ� */

  glEnable(GL_LIGHTING);            /* �V�F�[�f�B���O�v�Z�̊J�n */
  glLightfv( GL_LIGHT0, GL_POSITION, light); /* ���s�����̐ݒ� */
  glEnable(GL_TEXTURE_2D);	/* �e�N�X�`����L���ɂ��� */

  glBindTexture(GL_TEXTURE_2D,2); /* 2�Ԃ̃e�N�X�`�����g�� */
  /* �e�N�X�`�����W�̎���������L���ɂ��� */
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  glutSolidSphere(1.0, 10, 10);	

  /* �e�N�X�`�����W�̎��������𖳌��ɂ��� */
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glPushMatrix();
  glTranslatef( light[0], light[1], light[2] ); /* �����̈ʒu�ɋ���u�� */
  glPushAttrib(GL_LIGHTING_BIT);		/* �V�F�[�f�B���O�ݒ���X�^�b�N�ɕۑ� */
  glMaterialfv(GL_FRONT, GL_EMISSION, emission); /* ���ˌ��̐ݒ� */
  glutSolidSphere(0.1, 10, 10);			 /* ����ݒu */
  glPopAttrib();
  glPopMatrix();
  
  glDisable(GL_LIGHTING);

  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,1); /* �P�Ԃ̃e�N�X�`���ɐ؂�ւ��� */
  glNormal3f(0.0,1.0,0.0);     
  glBegin(GL_QUADS);
  /* �e�N�X�`�����W�ƃ|���S�����W���蓮�Őݒ� */
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
    param = fmod(param+2.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC2�x������ */
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
  static float r[] = {1.0, 1.0, 0.0, 0.0};
  static float g[] = {1.0, 0.0, 1.0, 0.0};
  static float b[] = {1.0, 0.0, 0.0, 1.0};
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

void initTexture1()		/* 1�Ԗڂ̃e�N�X�`���̏����ݒ� */
{
  makeImage1();
  glBindTexture(GL_TEXTURE_2D,2);	 /* 1 �Ԗڂ̃e�N�X�`����ݒ肷�� */
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

void initTexture2()		/* 2�Ԗڂ̃e�N�X�`���̏����ݒ� */
{
  makeImage2();
  glBindTexture(GL_TEXTURE_2D,1);	 /* 1 �Ԗڂ̃e�N�X�`����ݒ肷�� */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* �e�N�X�`����1�o�C�g���ǂݍ��� */
  /* �e�N�X�`���̌J��Ԃ����̐ݒ� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /* �e�N�X�`�����J��Ԃ� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

  /*�e�N�X�`���̊g��E�k���̐ݒ�  */  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* �ŋߖT�̉�f�����Ɋg�� */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /* �ŋߖT�̉�f�����ɏk�� */

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, image2); /* �e�N�X�`���̊��蓖�� */

  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); /* �_�u���o�b�t�@�̐錾 */
  glutCreateWindow(winname);

  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* ���e�@�Ɋւ�����W�ϊ����J�n */
  glLoadIdentity();
  gluPerspective( 30.0, 1.0, 1.0, 10.0 );
  glMatrixMode(GL_MODELVIEW); /* ���_�̈ړ��⃂�f���̈ړ��ȂǓ��e�@
                                 �ȊO�̍��W�ϊ����J�n */
  gluLookAt( 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  glShadeModel(GL_FLAT);     /* �V�F�[�f�B���O�̎�ނ��t���b�g�V�F�[�f�B���O�ɐݒ� */
  glEnable(GL_LIGHT0);       /* LIGHT0�̌�����L���ɂ��� */
  glEnable(GL_DEPTH_TEST);   /* �B�ʏ����̊J�n��錾 */
  
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
