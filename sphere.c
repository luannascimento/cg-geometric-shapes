#include "libs/headers.h"

void drawSphere(GLdouble D,GLint rdiv, GLint hdiv, GLuint texture)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLint i, j;
  GLfloat delta, delta_h, raio, r_, r__, H_, theta, theta_, H__;
  delta = (2 * M_PI) /(GLfloat) rdiv;
  raio = D / 2.0;
  delta_h = D /(GLfloat) hdiv;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  for (i = 0; i < rdiv; i++)
  {
    r_ = sqrt(raio * raio - (raio - (D - delta_h)) * (raio - (D - delta_h)));
    H_ = D - delta_h;
    theta = i * delta;
    theta_ = theta + delta;
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(theta/(2*M_PI),1.0);
      glVertex3f(0.0,D,0.0);
      glTexCoord2f(theta/(2*M_PI), H_/D);
      glVertex3f(r_ * cos(theta),  H_, r_ * sin(theta));
      glTexCoord2f(theta_/(2*M_PI), H_/D);
      glVertex3f(r_ * cos(theta_),  H_, r_ * sin(theta_));
    glEnd();
    
    for (j = 1; j < hdiv-1; j++)
    {
      H_ = j * delta_h;
      H__ = H_ + delta_h;
      r_ = sqrt((raio * raio) - (raio - H_) * (raio - H_));
      r__ = sqrt((raio * raio) - (raio - H__) * (raio - H__));
      glBegin(GL_QUADS);
        glTexCoord2f(theta/(2*M_PI), H_/D);
        glVertex3f(r_ * cos(theta), H_, r_ * sin(theta));
        glTexCoord2f(theta/(2*M_PI), H__/D);
        glVertex3f(r__ * cos(theta), H__, r__ * sin(theta));
        glTexCoord2f(theta_/(2*M_PI), H__/D);
        glVertex3f(r__ * cos(theta_), H__, r__ * sin(theta_));
        glTexCoord2f(theta_/(2*M_PI), H_/D);
        glVertex3f(r_ * cos(theta_), H_, r_ * sin(theta_));
      glEnd();
    }
    r_ = sqrt(raio * raio - (raio - (D - delta_h)) * (raio - (D - delta_h)));
    H_ = delta_h;
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(theta/(2*M_PI),0.0);
      glVertex3f(0.0,0.0,0.0);
      glTexCoord2f(theta/(2*M_PI), H_/D);
      glVertex3f(r_ * cos(theta),  H_, r_ * sin(theta));
      glTexCoord2f(theta_/(2*M_PI), H_/D);
      glVertex3f(r_ * cos(theta_),  H_, r_ * sin(theta_));
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}