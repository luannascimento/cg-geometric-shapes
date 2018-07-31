#include "libs/headers.h"

void drawSphere(GLdouble D,GLint rdiv, GLint hdiv)
{
  if(hdiv < 1 || rdiv < 1) return;
  GLint i, j,cor;
  GLfloat delta, delta_h, raio, r_, r__, H_, theta, theta_, H__;
  delta = (2 * M_PI) /(GLfloat) rdiv;
  raio = D / 2.0;
  delta_h = D /(GLfloat) hdiv;

  for (i = 0; i < rdiv; i++)
  {
    r_ = sqrt(raio * raio - (raio - (D - delta_h)) * (raio - (D - delta_h)));
    H_ = D - delta_h;
    theta = i * delta;
    theta_ = theta + delta;
    drawTriangle(r_,D,H_,theta,theta_,i);

    for (j = 1; j < hdiv-1; j++)
    {
      H_ = j * delta_h;
      H__ = H_ + delta_h;
      r_ = sqrt((raio * raio) - (raio - H_) * (raio - H_));
      r__ = sqrt((raio * raio) - (raio - H__) * (raio - H__));
      cor = (i%2 == 0) ? j : j+1;
      drawQuad(r_,r__,H_,H__,theta,theta_,cor);
    }
    r_ = sqrt(raio * raio - (raio - (D - delta_h)) * (raio - (D - delta_h)));
    H_ = delta_h;
    drawTriangle(r_,0.0,H_,theta,theta_,i);
  }
}