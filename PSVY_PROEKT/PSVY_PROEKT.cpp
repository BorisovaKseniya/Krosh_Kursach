#include<C:\Users\Ksenia\Documents\КГ курсач\Курсач\PSVY_PROEKT/glut.h>//Подключениебиблиотекиglut.h
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include <math.h>
#include <iostream>


const float light0_position[4] = { 0, 0, 1, 0 };
double rotate_y = 0;
double rotate_x = 0;
double rotate = 0;
bool deathStatus = 0;
bool helloStatus = 0;
//const float light0_position[4] = { 0, 0, 1, 0 };
float scale = 0.4f;
float vert[] = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0 };

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        rotate_y += 5;
    }
    else if (key == GLUT_KEY_LEFT) {
        rotate_y -= 5;
    }
    else if (key == GLUT_KEY_UP)
        rotate_x -= 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x += 5;
    else if (key == GLUT_KEY_F10)
        deathStatus = 1;
    else if (key == GLUT_KEY_F11)
        helloStatus = 1;

    glutPostRedisplay();
}

float movingDown = 0.0;
int timer = 0;
float flight = 0;

void DeathAnim() //Анимация мяча
{

    if (timer < 5)
    {//Первые 5 счетов движение вверх
        flight += 0.05;
        timer++;
    }
    if (timer == 5) {
        flight = 0.045;
    }

    if (timer >= 5 && timer < 15) {
        flight += 0.05;
        timer++;
    }
    if (timer == 15) {
        timer = 0;
    }
}

GLuint groundTex;




GLuint LoadTexture(const char* filename)
{//Функция считывания текстуры из файла
    GLuint texture;
    int width, height;
    unsigned char* data;
    FILE* file;
    file = fopen(filename, "rb");
    if (file == NULL) return 0; //Не считывать несуществующий файл
    width = 256; //Размер изображения в пикселях
    height = 256;
    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB,
        GL_UNSIGNED_BYTE, data);
    free(data);
    return texture;
}
void Ground() {//Отображение поверхности с текстурой
    groundTex = LoadTexture("m_g_grass04.bmp");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.8f, -0.3f, -0.8f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.8f, -0.3f, -0.8f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.8f, -0.3f, 0.8f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.8f, -0.3, 0.8f);
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
float scaleChange = 1.0;
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    glLoadIdentity();
    if (deathStatus == 1)
        DeathAnim();
  /*  else if (helloStatus == 1)
        HelloAnim();*/

    glRotatef(rotate_x, 1.0, 0.0, 0.0); // поворот сцены
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    Ground();
    glScalef(scaleChange, scaleChange, scaleChange);

    // Туловище кроша
    glPushMatrix();
    glColor3f(0.5, 1.0, 1.0); // синий цвет
    glutSolidSphere(0.2, 50, 50); // сфера для туловища кроша
    glPopMatrix();

    
 


    // Морда кроша
        // уши
    glPushMatrix();
    glTranslatef(0.05, 0.25, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(-15, 0, 0, 1);
    glScalef(1.0, 3.9, 1.0);
    glutSolidSphere(0.065, 50, 50); //сфера 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.05, 0.25, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(15, 0, 0, 1);
    glScalef(1.0, 3.9, 1.0);
    glutSolidSphere(0.065, 50, 50); //сфера 
    glPopMatrix();

    //глаза
    glPushMatrix();
    glTranslatef(-0.06, 0.03, -0.17); // смещаем относительно туловища
    glColor3f(1.0, 1.0, 1.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.04, 50, 50); //сфера 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.06, 0.03, -0.205); // смещаем относительно туловища
    glColor3f(0.0, 0.0, 0.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.015, 50, 50); //сфера 
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.06, 0.03, -0.17); // смещаем относительно туловища
    glColor3f(1.0, 1.0, 1.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.04, 50, 50); //сфера 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06, 0.03, -0.205); // смещаем относительно туловища
    glColor3f(0.0, 0.0, 0.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.015, 50, 50); //сфера 
    glPopMatrix();

    //нос
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.205); // смещаем относительно туловища
    glColor3f(1.0, 0.5, 0.0); // белый цвет
    glutSolidSphere(0.025, 50, 50); //сфера 
    glPopMatrix();

    //зубы
    glPushMatrix();
    glTranslatef(0.015, -0.065, -0.185); // смещаем относительно туловища
    glColor3f(1.0, 1.0, 1.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.015, 50, 50); //сфера
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.015, -0.065, -0.185); // смещаем относительно туловища
    glColor3f(1.0, 1.0, 1.0); // белый цвет
    glScalef(1.2, 1.6, 1.0);
    glutSolidSphere(0.015, 50, 50); //сфера 
    glPopMatrix();


    //лапы
    //нижние
    glPushMatrix();
    glTranslatef(0.07, -0.23, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(90, 0, 0, 1);
    glScalef(1.0, 1.8, 1.0);
    glutSolidSphere(0.05, 50, 50); // сфера 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.07, -0.23, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(90, 0, 0, 1);
    glScalef(1.0, 1.8, 1.0);
    glutSolidSphere(0.05, 50, 50); // сфера 
    glPopMatrix();

    //верхние
    glPushMatrix();
    glTranslatef(0.18, 0.015, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(45, 0, 0, 1);
    glScalef(1.0, 2.2, 1.0);
    glutSolidSphere(0.05, 50, 50); // сфера 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.18, 0.015, 0.0); // смещаем относительно туловища
    glColor3f(0.5, 1.0, 1.0); // Синий цвет
    glRotatef(-45, 0, 0, 1);
    glScalef(1.0, 2.2, 1.0);
    glutSolidSphere(0.05, 50, 50); // сфера 
    glPopMatrix();


    //glPushMatrix();
    //glTranslatef(0.0, -0.5 * flight, 0.0);
    //
    //glPushMatrix();
    //glTranslatef(-0.5, -0.25, -0.05); // смещаем относительно туловища
    //glColor3f(1.0, 0.5, 0.0);
    //glScalef(3.0, 3.0, 3.0);
    //glutSolidSphere(0.05, 50, 50); //сфера глаза
    //glPopMatrix();


    //сковородка
    //ручка
    glPushMatrix();
    glTranslatef(0.33, -0.05, -0.09); // смещаем относительно туловища
    glColor3f(0.0, 0.0, 0.0); // черный цвет
    glRotatef(45, 0, 1, 0);
    glScalef(5.0, 1.0, 1.0);
    glutSolidSphere(0.02, 50, 50); // сфера 
    glPopMatrix();
    //емкость
    glPushMatrix();
    glTranslatef(0.5, -0.05, -0.3); // смещаем относительно туловища
    glColor3f(0.0, 0.0, 0.0); // черный цвет
    glScalef(5.0, 1.0, 5.0);
    glutSolidSphere(0.04, 50, 50); // сфера 
    glPopMatrix();

    //яишница
    glPushMatrix();
    glTranslatef(0.0, 0.5 * flight, 0.0);

    glPushMatrix();
    glTranslatef(0.5, -0.01, -0.3); // смещаем относительно туловища
    glColor3f(1.0, 1.0, 1.0); // черный цвет
    glScalef(6.0, 1.0, 6.0);
    glutSolidSphere(0.02, 50, 50); // сфера 
    glPopMatrix();
  

    glPushMatrix();
    glTranslatef(0.5, 0.0, -0.27); // смещаем относительно туловища
    glColor3f(1.0, 0.5, 0.0); // оранжевый цвет
    glScalef(3.0, 1.0, 3.0);
    glutSolidSphere(0.02, 50, 50); // сфера 
    glPopMatrix();
    DeathAnim();
    glPopMatrix();

    //апельсин

    //glPushMatrix();
    //glTranslatef(0.0, -0.5 * flight, 0.0);
    //
    //glPushMatrix();
    //glTranslatef(-0.25, -0.25, -0.05); // смещаем относительно туловища
    //glColor3f(1.0, 0.5, 0.0);
    //glScalef(1.0, 1.0, 1.0);
    //glutSolidSphere(0.05, 50, 50); //сфера глаза
    //glPopMatrix();

  

    glScalef(1 / scaleChange, 1 / scaleChange, 1 / scaleChange);
    glTranslatef(x, y + movingDown, z); //перенос объекта
    glRotatef(90, 1, 0, 0);
    glTranslatef(x, y - 0.065, z + 0.05);
    GLUquadric* obj = gluNewQuadric();
    gluCylinder(obj, 0.04, 0.03, 0.09, 100, 100);
    glTranslatef(x, y, z + 0.09);
    gluDisk(obj, 0, 0.03, 100, 100);
    glFlush();
    Sleep(50);
    glutSwapBuffers();
    glutPostRedisplay();
}
void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("3D. Ukusi menya pchela");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    float ambient[4] = { 0.5, 0.5, 0.7, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glutDisplayFunc(Display);
    glutSpecialFunc(specialKeys);
    Initialize();
    glutMainLoop();
    return 0;
}