#include "libs/headers.h"

void drawCylinder(GLdouble R,GLdouble H,GLuint rdiv,GLuint hdiv)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLuint i,j,cor;
  GLfloat delta, delta_h, H_, theta, theta_, H__;
  delta = (2 * M_PI) /(GLfloat) rdiv;
  delta_h = H/hdiv;
  for(i=0;i<rdiv;i++)
  {
    theta = i*delta;
    theta_ = theta + delta;
    drawTriangle(R,H,(R*H),theta,theta_,i);
    for(j=0;j<hdiv;j++)
    {
      H_ = j*delta_h;
      H__ = H_ + delta_h;
      cor = (i%2 == 0) ? j : j+1;
      drawQuad(R,R,(R*H_),(R*H__),theta,theta_,cor);
    }
    drawTriangle(R,0.0,0.0,theta,theta_,i);
  }
}