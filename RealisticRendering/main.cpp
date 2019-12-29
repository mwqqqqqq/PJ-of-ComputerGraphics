#include <GLUT/glut.h>
 
//1.设置光源、材质
void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);//参数：红绿蓝 AFA   清除颜色
    glShadeModel(GL_SMOOTH);//平滑过渡
 
    //设置光源
    GLfloat LightPosition[]= {2.0,3.0,6.0,0.0};
    GLfloat WhiteLight[] = { 1.0,1.0,1.0,1.0};
    
    glLightfv(GL_LIGHT0,GL_POSITION,LightPosition);//设置光源位置
    glLightfv(GL_LIGHT0,GL_DIFFUSE,WhiteLight);//漫反射光
    glLightfv(GL_LIGHT0,GL_SPECULAR,WhiteLight);//镜面光
    
    //设置材质
    GLfloat MaterialSpecular[]={ 1.0,1.0,1.0,1.0 };
    GLfloat MaterialShininess[] = { 50.0 };
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);//镜面光
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);//镜面指数

    //设置环境光照
       GLfloat LightModelAmbient[]={ 0.2,0.2,0.2,0.1}; glLightModelfv(GL_LIGHT_MODEL_AMBIENT,LightModelAmbient);//设置整个环境光照的RGBA值
    //开启光照
    glEnable(GL_LIGHTING);//总开关
    glEnable(GL_LIGHT0);//相应光的开关
    glEnable(GL_DEPTH_TEST);
}

//2.绘制立方体
void DrawCube(void)
{
    glBegin(GL_QUADS);
    //第一个面
    glNormal3f( 0.0F, 0.0F, 1.0F);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
    //第二个面
    glNormal3f( 0.0F, 0.0F,-1.0F);
    glVertex3f(-0.1f,-0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
    //第三个面
    glNormal3f( 0.0F, 1.0F, 0.0F);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    //第四个面
    glNormal3f( 0.0F,-1.0F, 0.0F);
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    //第五个面
    glNormal3f( 1.0F, 0.0F, 0.0F);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    //第六个面
    glNormal3f(-1.0F, 0.0F, 0.0F);
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glEnd();
}
 

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(30, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    glColor3f(0, 0, 1);
    DrawCube();
    glPopMatrix();
    glutSwapBuffers();
}

//3.调整宽高比例
void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);//调整位置、宽高
    glMatrixMode(GL_PROJECTION);//投影
    glLoadIdentity();
    if(w<=h) //调整宽高比例
        glOrtho(-1.5,1.5,-1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    else
        glOrtho(-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
int main(int argc,char** argv)
{
    //设置窗口属性
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    //设置光照和材质
    init();
    //显示图形
    glutDisplayFunc(display);
    //调整形状
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}


