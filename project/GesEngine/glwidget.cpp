#include "glwidget.h"
#include<GL/glu.h>

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
}

void GLWidget::resizeGL(int w, int h)
{

}
