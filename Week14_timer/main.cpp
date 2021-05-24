#include <GL/glut.h>
int angle=0;
void drawArm1(){
    glPushMatrix();
        glScalef(1,0.5,0.5);
        glColor3f(1,0,0);glutSolidCube(0.3); ///左手紅
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glColor3f(1,1,1);glutSolidCube(0.4); ///身體白
        glPushMatrix();
            glTranslatef(-0.2,+0.2,0); ///(3)掛到右上角
            glRotatef(angle,0,0,1); ///(2)轉動
            glTranslatef(-0.15,0,0); ///(1)把旋轉中心的關節軸放在中心
            drawArm1();
        glPopMatrix();

    glPopMatrix();
    glutSwapBuffers(); ///柳丁
}
int diff=2;
void timer(int t) ///鬧鐘響了，timer叫了
{
    glutTimerFunc(20,timer,t+1); ///馬上設定下一個鬧鐘，不要響太久
               ///倍速
    angle+=diff; ///上個廁所
    if(angle>180 || angle<0 ) diff=-diff;
    display(); ///喝個水
}///睡了
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH);
    glutCreateWindow("Week14 timer");

    glutDisplayFunc(display);
    glutTimerFunc(0  ,  timer  ,0);
                ///要等多久 叫誰 參數
    glutMainLoop();

}
