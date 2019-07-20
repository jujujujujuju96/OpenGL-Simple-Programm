/* sample2.c */
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926

void display(void)
{
  int n=10;
  int i=0;
  float x,y,z;
  float r=0.5;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0); /* �`�悷��}�`�̐F�𔒂Ɏw�� */
  glBegin(GL_POLYGON);       
    for(i=0;i<n;i++){
       x = r*cos(2.0*PI*(float)i/(float)n);
       y = r*sin(2.0*PI*(float)i/(float)n);
       z = 0.0;
       glVertex3f(x,y,z);
     }
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
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glut�̏����� */
  init(argv[0]);
  glutDisplayFunc(display);        /* �f�B�X�v���C�R�[���o�b�N�֐��̎w�� */
  glutMainLoop();                  /* �C�x���g�҂��̖������[�v�֓��� */
  return 0;                        /* ���[�v���I�������0��Ԃ��ďI�� */
}
