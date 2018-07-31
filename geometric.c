#include "libs/headers.h"
#define cor(i) i%2 == 0 ? 1 : 0
static float c[][3] = {{0.0,0.0,0.8},
                    {0.0,0.39,0.0}};

void drawTriangle(GLfloat R,GLfloat H,GLfloat H_,GLfloat theta,GLfloat theta_,GLuint i)
{
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(0.0,H,0.0);
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R * cos(theta), H_, R * sin(theta));
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R * cos(theta_), H_, R * sin(theta_));
  glEnd();
}

void drawQuad(GLfloat R,GLfloat R_,GLfloat H,GLfloat H_,GLfloat theta,GLfloat theta_,GLuint i)
{
  glBegin(GL_QUADS);
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R * cos(theta), H, R * sin(theta));
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R_ * cos(theta),  H_, R_ * sin(theta));
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R_ * cos(theta_),  H_, R_ * sin(theta_));
    glColor3f(c[cor(i)][0],c[cor(i)][1],c[cor(i)][2]);
    glVertex3f(R * cos(theta_),  H, R * sin(theta_));
  glEnd();
}