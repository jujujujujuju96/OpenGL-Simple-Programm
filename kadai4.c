/* sample4.c */
#include <GL/glut.h>

double vertex[][3] = {   /* ���_��z��Ő錾������@ */
  {-0.5,-0.5, 0.0},
  { 0.5,-0.5, 0.0},
  { 0.5, 0.5, 0.0},
  {-0.5, 0.5, 0.0},
};

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  //glTranslatef(-1.0, 0.0, 0.0);    /* ���̂�x������-1.0���s�ړ����� */
  glTranslatef(0.0,0.0,-1.0);
  glRotatef(30,0.0,1.0,0.0);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  for( i=0; i<4; i++)
    glVertex3f(vertex[i][0],vertex[i][1],vertex[i][2]);
  glEnd();
  glFlush();
}

void init(char *winname)
{
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_RGBA);
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
  glutInit(&argc, argv);           /* glut�̏����� */
  init(argv[0]);
  glutDisplayFunc(display);        /* �f�B�X�v���C�R�[���o�b�N�֐��̎w�� */
  glutMainLoop();                  /* �C�x���g�҂��̖������[�v�֓��� */
  return 0;                        /* ���[�v���I�������0��Ԃ��ďI�� */
}
