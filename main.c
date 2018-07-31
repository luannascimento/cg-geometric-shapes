#include "libs/headers.h"

#define WIDTH 800
#define HEIGHT 600
#define TIMERMSECS 33

enum
{
  STOP = 0,
  SPHERE,
	CYLINDER,
	CONE
} moveCamera;

GLfloat x = 0.0f, z = 12.0f, lx = 0.0f, lz = -1.0f, angle = 0.0f;
GLfloat deltaT;
GLuint rdiv = 16,hdiv = 16;
GLfloat r = 0.0;
GLfloat rot = 0.0;

void init();
void display();
void keyboard(unsigned char,int,int);
void keyboard2(int,int,int);
void reshape(GLsizei,GLsizei);
void timer(int);

int main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(50,50);
  glutCreateWindow("CG-Formas");
  glutReshapeFunc( reshape );
  glutTimerFunc( TIMERMSECS, timer, 0 );
  glutDisplayFunc( display );
  glutKeyboardFunc( keyboard );
  glutSpecialFunc( keyboard2 );
  init();
  glutMainLoop();
  return 0;
}

void init()
{
  glClearColor(1.0,1.0,1.0,1.0);
  moveCamera = STOP;
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  gluLookAt(	x, 1.0f, z, x+lx, 1.0f,  z+lz, 0.0f, 1.0f,  0.0f);
  

  glPushMatrix();
    glTranslated(6.0,0.0,-(12*(sqrt(3)/6)));
    glRotated(r,1.0,0.0,0.0);
    glTranslated(0.0,-1,0.0);
    if(moveCamera == CYLINDER)
      drawCone(1,2,rdiv,hdiv);
    else if(moveCamera == CONE)
      drawSphere(2,rdiv,hdiv);
    else
      drawCylinder(1,2,rdiv,hdiv);
  glPopMatrix();

  glPushMatrix();
    glTranslated(-6.0,0.0,-(12*(sqrt(3)/6)));
    glRotated(r,1.0,0.0,0.0);
    glTranslated(0.0,-1,0.0);
    if(moveCamera == CYLINDER)
      drawSphere(2,rdiv,hdiv);
    else if(moveCamera == CONE)
      drawCylinder(1,2,rdiv,hdiv);
    else
      drawCone(1,2,rdiv,hdiv);
      
  glPopMatrix();

  glPushMatrix();
    glTranslated(0.0,0.0,((12*sqrt(3))/3));
    glRotated(r,1.0,0.0,0.0);
    glTranslated(0.0,-1,0.0);
    if(moveCamera == CYLINDER)
      drawCylinder(1,2,rdiv,hdiv);
    else if(moveCamera == CONE)
      drawCone(1,2,rdiv,hdiv);
    else
      drawSphere(2,rdiv,hdiv);
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

void timer(int value)
{
  static GLuint lastTime = 0;
  GLuint currentTime = glutGet(GLUT_ELAPSED_TIME);
  deltaT = (currentTime - lastTime)/100.0;

  r+= (1000/1000)*deltaT;

  glutPostRedisplay();
  lastTime = currentTime;
  glutTimerFunc( TIMERMSECS, timer, 0 );
}

void reshape(GLsizei w,GLsizei h)
{
  if(h == 0) h = 1;
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,(GLfloat)w / (GLfloat)h,0.1,100.0);
  glTranslated(0.0,1.0,0.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key,int x,int y)
{
  switch(key)
  {
    case 'q':
        r+=10;
      break;
    case 'R':
        rdiv++;
      break;
    case 'r':
        rdiv--;
      break;
    case 'H':
        hdiv++;
      break;
    case 'h':
        hdiv--;
      break;
  }
}

void keyboard2(int key,int mouse_x,int mouse_y)
{
  switch (key) {
		case GLUT_KEY_F1 :
      moveCamera = SPHERE;
			break;
		case GLUT_KEY_F2 :
      moveCamera = CYLINDER;
			break;
		case GLUT_KEY_F3 :
      moveCamera = CONE;
			break;
	}
}