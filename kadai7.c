/* sample7.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float param = 0.0;
int flag = 0;

float diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* �g�U���ː����̔��ˋ��x*/
float specular[] = {1.0, 1.0, 1.0, 1.0}; /* ���ʔ��ː����̔��ˋ��x */
float ambient[] = {0.2, 0.2, 0.2, 1.0};  /* ���������̔��ˋ��x*/
float shininess = 128.0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(param, 0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);     /* �g�U���˂̐ݒ� */
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);   /* ���ʔ��˂̐ݒ� */
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);     /* �����̐ݒ� */
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);  /* ���ʔ��˂̉s���̐ݒ� */

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);            /* �V�F�[�f�B���O�v�Z�̊J�n */
  glutSolidSphere(1.0, 10, 10);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
  glutSwapBuffers();
}

void idle(void)
{
  if(flag == 1){
    param = fmod(param+1.0, 360.0);  /* ��]�p��0�`360�x�܂ŁC1�x������ */
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
  static int flag = 0;

  switch (key) {
  case 'q':                   /* q�����͂��ꂽ��C�v���O�������I������ */
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
  glEnable(GL_DEPTH_TEST);
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
