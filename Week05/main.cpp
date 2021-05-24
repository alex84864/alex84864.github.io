#include <GL/glut.h>
#include <stdio.h>
float vx[2000],vy[2000];  ///準備一堆頂點，等一下要畫!!! 座標介於-1 ~1之間
int N=0; //有N個頂點
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP); //畫線
    for(int i=0;i<N;i++){
        glVertex2f(vx[i],vy[i]);
    }
    glEnd();
    glutSwapBuffers();
}
void motion(int x,int y)   ///mouse
{
    printf("%d %d\n",x,y); //頂點
    vx[N]= (x-150)/150.0;
    vy[N]=-(y-150)/150.0;
    N++;
    display(); //更新畫面
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH);
    glutCreateWindow("Week05 drawing");
    glutDisplayFunc(display);
    glutMotionFunc(motion); //在動(拖曳)/在畫
    glutMainLoop();
}
