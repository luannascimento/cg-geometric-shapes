#include "libs/headers.h"

void drawCylinder(GLdouble R,GLdouble H,GLuint rdiv,GLuint hdiv, GLuint texture)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLuint i,j;
  GLfloat delta, delta_h, H_, theta, theta_, H__;
  delta = (2 * M_PI) /(GLfloat) rdiv;
  delta_h = H/hdiv;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  for(i=0;i<rdiv;i++)
  {
    theta = i*delta;
    theta_ = theta + delta;
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5);
      glVertex3f(0.0,H,0.0);
      glTexCoord2f(theta/(2*M_PI),(R*H)/H);
      glVertex3f(R * cos(theta),  (R*H), R * sin(theta));
      glTexCoord2f(theta_/(2*M_PI),(R*H)/H);
      glVertex3f(R * cos(theta_),  (R*H), R * sin(theta_));
    glEnd();
    
    for(j=0;j<hdiv;j++)
    {
      H_ = j*delta_h;
      H__ = H_ + delta_h;
      glBegin(GL_QUADS);
        glTexCoord2f(theta/(2*M_PI), (R * H_)/H);
        glVertex3f(R * cos(theta), (R * H_), R * sin(theta));
        glTexCoord2f(theta/(2*M_PI), (R * H__)/H);
        glVertex3f(R * cos(theta), (R * H__), R * sin(theta));
        glTexCoord2f(theta_/(2*M_PI), (R * H__)/H);
        glVertex3f(R * cos(theta_), (R * H__), R * sin(theta_));
        glTexCoord2f(theta_/(2*M_PI), (R * H_)/H);
        glVertex3f(R * cos(theta_), (R * H_), R * sin(theta_));
      glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5);
      glVertex3f(0.0,0.0,0.0);
      glTexCoord2f(theta/(2*M_PI),0.0);
      glVertex3f(R * cos(theta),  0.0, R * sin(theta));
      glTexCoord2f(theta_/(2*M_PI),0.0);
      glVertex3f(R * cos(theta_),  0.0, R * sin(theta_));
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}