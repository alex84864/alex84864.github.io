#include <GL/glut.h>
#include <stdio.h>
float angle=0;
void hand()
{
    glPushMatrix();
        glScalef(0.5,0.1,0.1);
        glutSolidCube(1);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix(); ///左半邊
        glTranslatef(-0.25,0,0);///(3)把正確的手臂掛在肩關節
        glRotatef(angle,0,0,1); ///(2)轉動
        glTranslatef(-0.25,0,0); ///(1)旋轉中心
        hand();///上手臂
        glPushMatrix();
            glTranslatef(-0.25,0,0);///(3)把正確的手臂掛在肩上
            glRotatef(angle,0,0,1); ///(2)轉動
            glTranslatef(-0.25,0,0); ///(1)旋轉中心
            hand();///下手肘
        glPopMatrix();
    glPopMatrix();

     glPushMatrix(); ///右半邊
        glTranslatef(+0.25,0,0);///(3)把正確的手臂掛在肩關節
        glRotatef(-angle,0,0,1); ///(2)轉動
        glTranslatef(+0.25,0,0); ///(1)旋轉中心
        hand();///上手臂
        glPushMatrix();
            glTranslatef(+0.25,0,0);///(3)把正確的手臂掛在肩上
            glRotatef(-angle,0,0,1); ///(2)轉動
            glTranslatef(+0.25,0,0); ///(1)旋轉中心
            hand();///下手肘
        glPopMatrix();
    glPopMatrix();


    glutSwapBuffers();
    angle++;
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH);
    glutCreateWindow("Week06 08160971");

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
}
