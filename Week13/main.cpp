#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h" ///使用外掛
GLMmodel * pmodel = NULL; ///glm模型的指標
GLMmodel * body = NULL;
GLMmodel * arm1 = NULL;
GLMmodel * arm2 = NULL;
///GLMmodel * hand1 = NULL;
///GLMmodel * hand2 = NULL;
void drawmodel(void)
{
    if (!pmodel) {
	pmodel = glmReadOBJ("gundam.obj");
	if (!pmodel) exit(0);
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    }

    glmDraw(pmodel, GLM_SMOOTH | GLM_TEXTURE);
}

GLuint id1, id2; ///TODO:增加2個 貼圖ID
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, id1);

    glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(angle,0,1,0);
        ///drawmodel();
        glmDraw(body,GLM_SMOOTH | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(-0.35,+0.68+1,0);
            glRotatef(angle,0,0,1);
            glTranslatef(+0.35,-0.68-1,0);
            glmDraw(arm1,GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id2);
    glBegin(GL_POLYGON);
        glTexCoord2f( 0, 0 ); glVertex3f( -1, -1,0.8 );
        glTexCoord2f( 0, 1 ); glVertex3f( -1, +1 ,0.8 );
        glTexCoord2f( 1, 1 ); glVertex3f( +1, +1 ,0.8);
        glTexCoord2f( 1, 0 ); glVertex3f( +1, -1 ,0.8);
    glEnd();
    glutSwapBuffers();
    angle+=0.1;
}
int main(int argc, char** argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow(" Week13 ");
    glutDisplayFunc(display);
    glutIdleFunc(display);

    id1 = myTexture("Diffuse.jpg");
    id2 = myTexture("bg.jpg");
    body = glmReadOBJ("body.obj");
    arm1 = glmReadOBJ("arm1.obj");
    arm2 = glmReadOBJ("arm2.obj"); ///因為會被調掉

    pmodel=glmReadOBJ("gundam.obj");///完整的大模型
    float dimensions[3];
    glmDimensions( pmodel,dimensions);
    glmScale(pmodel,2.0/dimensions[1]);
    glmScale(body,  2.0/dimensions[1]);
    glmScale(arm1,  2.0/dimensions[1]);
    glmScale(arm2,  2.0/dimensions[1]);


    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
