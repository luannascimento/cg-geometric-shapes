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
    drawTriangle(r_,H,H_,theta,theta_);
    
    for(j=0;j<hdiv-1;j++)
    {
      H_ = j*delta_h;
      H__ = H_ + delta_h;
      r_ = R*(H - H_)/(GLfloat)H;
      r__ = R*(H - H__)/(GLfloat)H;
      drawQuad(r_,r__,H,H_,H__,theta,theta_);
    }
    drawTriangle(R,0.0,0.0,theta,theta_);
  }
  glDisable(GL_TEXTURE_2D);
}