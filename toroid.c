#include "libs/headers.h"

void drawToroid(GLdouble R,GLdouble H,GLuint rdiv,GLuint hdiv,GLuint texture)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLuint i,j;
  GLfloat delta, r, delta_, theta, theta_;
  r = H / 2;
  delta_ = 2*M_PI/rdiv;
	theta_ = 2*M_PI/hdiv;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
	for (i = 0; i < rdiv; i++){
		delta = 2*M_PI*i/rdiv;
    for (j = 0; j < hdiv; j++){
      theta = 2*M_PI*j/hdiv;
      glBegin(GL_QUADS);
        glTexCoord2f((delta)/(2*M_PI), (theta)/(2*M_PI));
        glVertex3f(R*cos(delta)-r*cos(theta)*cos(delta), r*sin(theta), R*sin(delta)-r*cos(theta)*sin(delta));
        glTexCoord2f((delta+delta_)/(2*M_PI),(theta)/(2*M_PI));
        glVertex3f(R*cos(delta+delta_)-r*cos(theta)*cos(delta+delta_), r*sin(theta), R*sin(delta+delta_)-r*cos(theta)*sin(delta+delta_));
        glTexCoord2f((delta+delta_)/(2*M_PI), (theta+theta_)/(2*M_PI));
        glVertex3f(R*cos(delta+delta_)-r*cos(theta+theta_)*cos(delta+delta_), r*sin(theta+theta_), R*sin(delta+delta_)-r*cos(theta+theta_)*sin(delta+delta_));
        glTexCoord2f((delta)/(2*M_PI), (theta+theta_)/(2*M_PI));
        glVertex3f(R*cos(delta)-r*cos(theta+theta_)*cos(delta), r*sin(theta+theta_), R*sin(delta)-r*cos(theta+theta_)*sin(delta));
      glEnd();
    }
	}
  glDisable(GL_TEXTURE_2D);
}
