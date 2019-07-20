/* sample5.c */
#include <GL/glut.h>
#include <math.h>

float param = 0.0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);        /* ���̎��_�ł̍��W�n�i�ϊ��s��j��ۑ� */
  glRotatef(param, 0.0, 0.0, 1.0);        /* z���𒆐S��param�x��] */
  glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
  glEnd();           /* 9�s�ڂ̕ϊ��n�ɖ߂� */
  glutSwapBuffers();
}

void idle(void)
{
  param = fmod(param+0.1, 360.0);  /* ��]�p��0�`360�x�܂ŁC2.0�x������ */
  glutPostRedisplay();      /* �f�B�X�v���C�R�[���o�b�N�֐�(display)�̎��s */
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
  glutIdleFunc(idle);              /* �A�C�h���R�[���o�b�N�֐��̎w�� */
  glutMainLoop();
  return 0;
}
