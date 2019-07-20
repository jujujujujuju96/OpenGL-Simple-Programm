/* sample3.c */
#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0); /* �`�悷��}�`�̐F�𔒂Ɏw�� */
  glBegin(GL_QUADS);        /* �l�p�`��`�� */
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
  glEnd();
  glFlush();                /* OpenGL �R�}���h�������I�Ɏ��s�i�`����s�j*/
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);    /* �E�B���h�E�̍���̈ʒu��(0,0)�Ƃ��� */
  glutInitWindowSize(500, 500);    /* �E�B���h�E�̃T�C�Y��500�~500�h�b�g�Ƃ��� */
  glutInitDisplayMode(GLUT_RGBA);  /* �F�̎w���RGBA���[�h��p���� */
  glutCreateWindow(winname);       /* winname�Ŏw�肳�ꂽ���O�ŃE�B���h�E���J�� */

  glClearColor(0.0, 0.0, 0.0, 1.0);/* �E�B���h�E�̔w�i�F�̎w�� */

  glLoadIdentity(); /* �ϊ��s��̏����� */
  //glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0); /* ���s���e�̐ݒ� */
  gluPerspective(30.0,1.0,1.0,10);
  gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glut�̏����� */
  init(argv[0]);
  glutDisplayFunc(display);        /* �f�B�X�v���C�R�[���o�b�N�֐��̎w�� */
  glutMainLoop();                  /* �C�x���g�҂��̖������[�v�֓��� */
  return 0;                        /* ���[�v���I�������0��Ԃ��ďI�� */
}
