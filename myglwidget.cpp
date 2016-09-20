#include "myglwidget.h"
#include <QKeyEvent>
# include <QDebug>




MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{

//旋转等操作的参数初始化
    translate = -6.0;
    xRot = yRot = zRot = 0.0;

//文件获取对话框
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("文件对话框"),
    "F:/2016-8-13/src/12/12-1/myOpenGL",tr("模型文件(*stl)"));          //获取模型文件
    qDebug()<< "fileNames:" << fileNames;
    fileNames.sort();
//
    qDebug()<< "fileNames:" << fileNames;
    qDebug()<< "index:" << fileNames[1];

//读取stl文件,共有Linknum个
    //QFile f("aaa.stl");
    for(int n =0;n<Linknum;n++)
    {
            QFile f(fileNames[n]);
            if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
            {
            qDebug() << "Open failed." << endl;
            //return -1;
            }
        else
        {
            QTextStream txtInput(&f);
            QString lineStr;
            stl3points p;
            while(!txtInput.atEnd())
            {
                lineStr = txtInput.readLine();
                lineStr  =  lineStr.simplified();
                if(lineStr.startsWith("facet"))
                {
                QStringList list=lineStr.split(" ");
                p.p[3][0]= QString(list[2]).toDouble();
                p.p[3][1]= QString(list[3]).toDouble();
                p.p[3][2]= QString(list[4]).toDouble();

                 lineStr = txtInput.readLine();
                lineStr  =  lineStr.simplified();
                list=lineStr.split(" ");
                 lineStr = txtInput.readLine();
                lineStr  =  lineStr.simplified();
                list=lineStr.split(" ");

                p.p[0][0]= QString(list[1]).toDouble();
                p.p[0][1]= QString(list[2]).toDouble();
                p.p[0][2]= QString(list[3]).toDouble();

                lineStr = txtInput.readLine();
                lineStr  =  lineStr.simplified();
                list=lineStr.split(" ");
                p.p[1][0]= QString(list[1]).toDouble();
                p.p[1][1]= QString(list[2]).toDouble();
                p.p[1][2]= QString(list[3]).toDouble();

                lineStr = txtInput.readLine();
                lineStr  =  lineStr.simplified();
                list=lineStr.split(" ");
                p.p[2][0]= QString(list[1]).toDouble();
                p.p[2][1]= QString(list[2]).toDouble();
                p.p[2][2]= QString(list[3]).toDouble();

                pp[n]<<p;
                }
            }
            //qDebug()<<"size:  "<<pp.size();
            //qDebug()<<"  "<<pp[2].p[1][1];
            f.close();
        }
    }
}

// 初始化环境
void MyGLWidget::initializeGL()
{
    //光照材质参数初始化
    //glClearColor (0.51, 0.512, 0.512, 0.0);
    GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 0.10 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat no_mat[] = { 0.8, 0.4, 0.2,1.0 };

    GLfloat mat_shininess[] = { 0.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0};

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// 调整视口大小
void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w/(GLfloat)h, 0.1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     //glTranslatef(0, 0.0, -300);
}

// 渲染场景///////////////////////////////////////////////////
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt (200, 100, 1200, 0.0, 0, 0.0, 0.0, 1.0, 0.0);
    //绘制背景
    glColor3f(0.2,0.2,0.46);
    glTranslatef(0,0,-800);
    glRectf(-4000,-4000,4000,4000);
    glTranslatef(0,0,500);

    //旋转变换操作
    glTranslatef(200,-200,0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    //glTranslatef(0, 0.0, -1000);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    //颜色
   // glColor3f(0.8,0.4,0.2);

    // 旋转、平移变换的参数、
     double Trans[7][4] =
     {
         {0,0,0,0},{0,0,0,290},{-90,0,-90,0},
         {0,270,0,0},{-90,70,0,302},{90,0,0,0},
         {-90,0,180,72}
     };

    //绘制图形
    glBegin(GL_TRIANGLES);//开始绘制三角形
   // glColor3f(0.8,0.4,0.2);//颜色
     GLfloat mm []={0.910,0.443,0.031,1.0};
      GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat no_shininess[] = { 0.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT,mm);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mm);
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    for(int n =0;n<Linknum;n++)//绘制LInknum个关节
    {    //按照D_H参数进行变换操作
        glRotatef(Trans[n][0], 1.0, 0.0, 0.0);
        glTranslatef(Trans[n][1] , 0.0, 0);
        glRotatef(Trans[n][2], 0.0, 0.0, 1.0);
        glTranslatef( 0.0, 0.0, Trans[n][3]);

        //绘制第n个零件
        for(int i =0;i< pp[n].size();i++)
        {
            //绘制第i个面
            for(int j=0;j<3;j++)
            {//绘制第j个点，每个面三个点
            glNormal3f(pp[n][i].p[3][0], pp[n][i].p[3][1],pp[n][i].p[3][2]);//法向量
            glVertex3f(pp[n][i].p[j][0], pp[n][i].p[j][1],pp[n][i].p[j][2]);
            }
//        glNormal3f(pp[i].p[3][0], pp[i].p[3][1],pp[i].p[3][2]);
//        glVertex3f(pp[i].p[0][0], pp[i].p[0][1],pp[i].p[0][2]);
//        glNormal3f(pp[i].p[3][0], pp[i].p[3][1],pp[i].p[3][2]);
//        glVertex3f(pp[i].p[1][0], pp[i].p[1][1],pp[i].p[1][2]);
//        glNormal3f(pp[i].p[3][0], pp[i].p[3][1],pp[i].p[3][2]);
//        glVertex3f(pp[i].p[2][0], pp[i].p[2][1],pp[i].p[2][2]);
        }
    }
    glEnd();//结束绘制三角形

    glFlush ();


}
//按键处理函数
void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        translate -= 1;
        if (translate <= -20)
            translate = -1;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}
