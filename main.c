#include "libs/headers.h"

#define WIDTH 800
#define HEIGHT 600
#define TIMERMSECS 33

enum
{
  STOP = 0,
  SPHERE,
	CYLINDER,
	CONE,
  TOROID
} moveCamera;

GLfloat deltaT;
GLuint rdiv = 16,hdiv = 16;
GLfloat r = 0.0;
GLfloat rot = 0.0;
int bmp[5] = {1,2,3,4,5};
int img[4] = {0,1,2,3};
int mov = 0;
GLfloat graus = 90.0f;
GLfloat rx = 1.0,ry = 0.0,rz = 0.0;

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
  glClearColor(0.0,0.0,0.0,0.0);
  moveCamera = STOP;
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  textureInit(5);
  loadBitmap("bmp/t.bmp");
  loadBitmap("bmp/tt.bmp");
  loadBitmap("bmp/ttt.bmp");
  loadBitmap("bmp/tttt.bmp");
  loadBitmap("bmp/ttttt.bmp");
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  gluLookAt(	0.0, 1.0f, 10.0, 0.0, 1.0f,  9.0, 0.0f, 1.0f,  0.0f);
  glRotated(rot,0.0,1.0,0.0);

  glPushMatrix();
    glTranslated(0.0,0.0,-(12*(sqrt(3)/3)));
    glRotated(r,rx,ry,rz);
    glTranslated(0.0,-1,0.0);
      drawSphere(2,rdiv,hdiv,getTexture(bmp[img[0]]));
  glPopMatrix();

  glPushMatrix();
    glTranslated(6.0,0.0,0.0);
    glRotated(r,rx,ry,rz);
    glTranslated(0.0,-1,0.0);
    drawCone(1,2,rdiv,hdiv,getTexture(bmp[img[2]]));
  glPopMatrix();

  glPushMatrix();
    glTranslated(-6.0,0.0,0.0);
    glRotated(r,rx,ry,rz);
    glTranslated(0.0,-1,0.0);
    drawCylinder(1,2,rdiv,hdiv,getTexture(bmp[img[1]]));
  glPopMatrix();

  glPushMatrix();
    glTranslated(0.0,0.0,((12*sqrt(3))/3));
    glRotated(r,rx,ry,rz);
    drawToroid(0.7,0.7,rdiv,hdiv,getTexture(bmp[img[3]]));
  glPopMatrix();
  
  glFlush();
  glutSwapBuffers();
}

void timer(int value)
{
  GLfloat an = 0.0;
  static GLuint lastTime = 0;
  GLuint currentTime = glutGet(GLUT_ELAPSED_TIME);
  deltaT = (currentTime - lastTime)/100.0;

  r+= (1000/1000)*deltaT;

  if(mov == 1)
  {
    an = (1000/(GLfloat)100)*deltaT;
    if((rot+an) < graus)
      rot+=an;
    else{
      rot = graus;
      mov = 0;
      graus+=90.0;
    }
  }
    
  
  

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
    case 27:
      exit(EXIT_FAILURE);
      break;
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
    case 't':
      if(moveCamera == SPHERE)
        img[0] = (img[0] >= 4) ? 0 : img[0]+1;
      
      if(moveCamera == CYLINDER)
        img[1] = (img[1] >= 4) ? 0 : img[1]+1;

      if(moveCamera == CONE)
        img[2] = (img[2] >= 4) ? 0 : img[2]+1;
      
      if(moveCamera == TOROID)
        img[3] = (img[3] >= 4) ? 0 : img[3]+1;
      break;
    case 'w':
      mov = 1;
      break;
    case 'x':
      rx = 1.0;
      ry = 0.0;
      rz = 0.0;
      break;
    case 'y':
      rx = 0.0;
      ry = 1.0;
      rz = 0.0;
      break;
    case 'z':
      rx = 0.0;
      ry = 0.0;
      rz = 1.0;
      break;
    case 'b':
      rx = 1.0;
      break;
    case 'n':
      ry = 1.0;
      break;
    case 'm':
      rz = 1.0;
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
    case GLUT_KEY_F4 :
      moveCamera = TOROID;
      break;
	}
}
