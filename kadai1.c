


/* sample1.c */
#include <GL/glut.h>               /* glutƒwƒbƒ_ƒtƒ@ƒCƒ‹‚ÌƒCƒ“ƒNƒ‹[ƒh */




void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);    /* ƒEƒBƒ“ƒhƒE‚Ì”wŒi‚ðŽw’è‚³‚ê‚½F‚Å“h‚è‚Â‚Ô‚· */
  glFlush();                       /* OpenGLƒRƒ}ƒ“ƒh‚ð‹­§“I‚ÉŽÀsi•`‰æŽÀsj */
}

void init(char *winname)
{
  glutInitWindowPosition(500, 500);    /* ƒEƒBƒ“ƒhƒE‚Ì¶ã‚ÌˆÊ’u‚ð(0,0)‚Æ‚·‚é */
  glutInitWindowSize(500, 200);    /* ƒEƒBƒ“ƒhƒE‚ÌƒTƒCƒY‚ð500~500ƒhƒbƒg‚Æ‚·‚é */
  glutInitDisplayMode(GLUT_RGBA);  /* F‚ÌŽw’è‚ÉRGBAƒ‚[ƒh‚ð—p‚¢‚é */
  glutCreateWindow(winname);       /* winname‚ÅŽw’è‚³‚ê‚½–¼‘O‚ÅƒEƒBƒ“ƒhƒE‚ðŠJ‚­ */

  glClearColor(0.0, 0.0, 1.0, 1.0);/* ƒEƒBƒ“ƒhƒE‚Ì”wŒiF‚ÌŽw’è */
                                   /* R(Ô),G(—Î),B(Â),A(“§–¾“x)‚Ì‡‚ÅŽw’è*/
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);           /* glut‚Ì‰Šú‰» */
  init(argv[0]);
  glutDisplayFunc(display);        /* ƒfƒBƒXƒvƒŒƒCƒR[ƒ‹ƒoƒbƒNŠÖ”‚ÌŽw’è */
  glutMainLoop();                  /* ƒCƒxƒ“ƒg‘Ò‚¿‚Ì–³ŒÀƒ‹[ƒv‚Ö“ü‚é */
  return 0;                        /* ƒ‹[ƒv‚ªI‚í‚Á‚½‚ç0‚ð•Ô‚µ‚ÄI—¹ */
}
