#include "libs/headers.h"

void drawToroid(GLdouble R,GLdouble H,GLuint rdiv,GLuint hdiv)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLuint i,j,cor;
  GLfloat delta, r, delta_, theta, theta_;
  r = H / 2;
  delta_ = 2*M_PI/rdiv;
	theta_ = 2*M_PI/hdiv;
	for (i = 0; i < rdiv; i++){
		delta = 2*M_PI*i/rdiv;
    for (j = 0; j < hdiv; j++){
      theta = 2*M_PI*j/hdiv;
      glBegin(GL_QUADS);
        if(i % 2 == 0){
          glColor3f(0.0, 0.0, 0.0);
        }else{
          glColor3f(0.0, 1.0, 1.0);
        }
        glVertex3f(R*cos(delta)-r*cos(theta)*cos(delta), r*sin(theta), R*sin(delta)-r*cos(theta)*sin(delta));
        glVertex3f(R*cos(delta+delta_)-r*cos(theta)*cos(delta+delta_), r*sin(theta), R*sin(delta+delta_)-r*cos(theta)*sin(delta+delta_));
        glVertex3f(R*cos(delta+delta_)-r*cos(theta+theta_)*cos(delta+delta_), r*sin(theta+theta_), R*sin(delta+delta_)-r*cos(theta+theta_)*sin(delta+delta_));
        glVertex3f(R*cos(delta)-r*cos(theta+theta_)*cos(delta), r*sin(theta+theta_), R*sin(delta)-r*cos(theta+theta_)*sin(delta));
      glEnd();
    }
	} 
}
