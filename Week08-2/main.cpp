#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
GLUquadric * quad;///TODO: Quad
void init()///copy 自 http://hackmd.io/@jsyeh/opengl
{
    IplImage * img = cvLoadImage("earth.jpg"); ///OpenCV讀圖
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
    quad = gluNewQuadric();///TODO: Quad
}   ///最後一行最難/最重要, 所貼圖影像的資料都設定好
float angle=0;///TODO:
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();///自動轉很帥///TODO:
        glRotatef(90, 1,0,0);///TODO:
        glRotatef(angle, 0,0,1);///自動轉很帥///TODO:
        gluQuadricTexture(quad, 1);///TODO:
        gluSphere(quad, 0.5, 30, 30);///glutSolidTeapot(0.3);///TODO:
    glPopMatrix();///自動轉很帥///TODO:
    ///glutSolidTeapot(0.3);
    glutSwapBuffers();
    angle++;///TODO:
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week08-2 texture");
    glutDisplayFunc(display);
    glutIdleFunc(display);///TODO:
    glEnable(GL_DEPTH_TEST);///TODO: 有3D的深度測試(前面會蓋掉後面)
    init();///上面把OpenGL都設好後, 才設定 OpenCV 的貼圖到 OpenGL上面
    glutMainLoop();
}
