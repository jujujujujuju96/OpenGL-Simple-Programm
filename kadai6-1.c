/* sample6-1.c */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float param = 0.0;
int flag=0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();                         /* ���̎��_�ł̍��W�n�i�ϊ��s��j��ۑ� */
  glRotatef(param, 0.0, 1.0, 0.0);        /* y���𒆐S��param�x��] */
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
  glPopMatrix();                          /* 9�s�ڂ̕ϊ��n�ɖ߂� */
  glutSwapBuffers();
}

void idle(void)
{
  param = fmod(param, 360.0);  /* ��]�p��0�`360�x�܂ŁC1.0�x������ */
  glutPostRedisplay();      /* �f�B�X�v���C�R�[���o�b�N�֐�(display)�̎��s */
}

void keyboard(unsigned char key, int x, int y)
/*���� key �ɂ̓^�C�v���ꂽ�L�[�� ASCII �R�[�h���C
x �� y �ɂ̓L�[���^�C�v���ꂽ�Ƃ��̃}�E�X�̈ʒu���n����� */
{
  switch (key) {
  case 'q':                   /* q�����͂��ꂽ��C�v���O�������I������ */
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /* �_�u���o�b�t�@�̐錾 */

  glutCreateWindow(winname);


  glClearColor(0.2, 0.4, 0.4, 1.0);

  glMatrixMode(GL_PROJECTION); /* ���e�@�Ɋւ�����W�ϊ����J�n */
  glLoadIdentity();
  gluPerspective( 30.0, 1.0, 1.0, 10.0 );
  glMatrixMode(GL_MODELVIEW); /* ���_�̈ړ��⃂�f���̈ړ��ȂǓ��e�@
                                 �ȊO�̍��W�ϊ����J�n */
  gluLookAt( 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  init(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard); /* �L�[�{�[�h���͂̃R�[���o�b�N�֐�keyboard�̎w�� */
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
