#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QFileDialog>


#define Linknum 7


struct stl3points
{
    double p[4][3];//һ����Ĳ�������ͷ�����
};

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

QList<stl3points> pp[Linknum];//����#Linknum ���ؽ�
//QList<stl3points> pp1;
//QList<stl3points> pp2;
//QList<stl3points> pp3;
//QList<stl3points> pp4;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);

private:
     GLfloat translate, xRot, yRot, zRot;//��ת�任�Ĳ����ľ���
     GLfloat  theta1,theta2,theta3,theta4,theta5,theta6;//�����ؽڵ���ת������


signals:

public slots:

};

#endif // MYGLWIDGET_H
