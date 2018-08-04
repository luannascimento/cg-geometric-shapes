#include "libs/headers.h"

void drawTriangle(GLfloat R,GLfloat H,GLfloat H_,GLfloat theta,GLfloat theta_)
{
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0.0,H,0.0);
    glTexCoord2f(R * cos(theta),R * sin(theta));
    glVertex3f(R * cos(theta),  H_, R * sin(theta));
    glTexCoord2f(R * cos(theta_),R * sin(theta_));
    glVertex3f(R * cos(theta_),  H_, R * sin(theta_));
  glEnd();
}

void drawQuad(GLfloat r_,GLfloat r__,GLfloat H,GLfloat H_,GLfloat H__,GLfloat theta,GLfloat theta_)
{
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