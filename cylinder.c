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
    drawTriangle(R,H,(R*H),theta,theta_);
    
    for(j=0;j<hdiv;j++)
    {
      H_ = j*delta_h;
      H__ = H_ + delta_h;
      drawQuad(R,R,H,(R*H_),(R*H__),theta,theta_);
    }
    drawTriangle(R,0.0,0.0,theta,theta_);
  }
  glDisable(GL_TEXTURE_2D);
}