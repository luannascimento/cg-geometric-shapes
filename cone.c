#include "libs/headers.h"

void drawCone(GLdouble R,GLdouble H,GLuint rdiv,GLuint hdiv,GLuint texture)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLuint i,j;
  GLfloat delta, r_, r__, delta_h, H_, theta, theta_, H__;
  delta = (2 * M_PI) /(GLfloat) rdiv;
  delta_h = H/(GLfloat)hdiv;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  for(i=0;i<rdiv;i++)
  {
    theta = i*delta;
    theta_ = theta + delta;
    H_ = H - delta_h;
    r_ = R/(GLfloat)hdiv;
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,1.0);
      glVertex3f(0.0,H,0.0);
      glTexCoord2f(theta/(2*M_PI),H_/H);
      glVertex3f(r_ * cos(theta),  H_, r_ * sin(theta));
      glTexCoord2f(theta_/(2*M_PI),H_/H);
      glVertex3f(r_ * cos(theta_),  H_, r_ * sin(theta_));
    glEnd();
    for(j=0;j<hdiv-1;j++)
    {
      H_ = j*delta_h;
      H__ = H_ + delta_h;
      r_ = R*(H - H_)/(GLfloat)H;
      r__ = R*(H - H__)/(GLfloat)H;
      glBegin(GL_QUADS);
        glTexCoord2f(theta/(2*M_PI),H_/H);
        glVertex3f(r_ * cos(theta), H_, r_ * sin(theta));
        glTexCoord2f(theta/(2*M_PI),H__/H);
        glVertex3f(r__ * cos(theta), H__, r__ * sin(theta));
        glTexCoord2f(theta_/(2*M_PI),H__/H);
        glVertex3f(r__ * cos(theta_), H__, r__ * sin(theta_));
        glTexCoord2f(theta_/(2*M_PI),H_/H);
        glVertex3f(r_ * cos(theta_), H_, r_ * sin(theta_));
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