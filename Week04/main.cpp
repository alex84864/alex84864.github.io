#include <GL/glut.h>
#include <stdio.h>
float teapotX=0,teapotY=0; ///茶壺座標
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();  ///矩陣備份
        glTranslatef(teapotX,teapotY,0);  ///照著座標移動
        glutSolidTeapot(0.3);
    glPopMatrix();   ///矩陣還原
    glEnd();
    glutSwapBuffers();
}

void motion(int x,int y)   ///滑鼠移動的函式
{
    teapotX= (x-150)/150.0;  ///把茶壺的位置換算成座標
    teapotY=-(y-150)/150.0;
    display();   ///畫面更新
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH);
    glutCreateWindow("Week04 mouse");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMainLoop();
}
