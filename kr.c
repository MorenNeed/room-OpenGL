#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// ініціалізація змінних кольору в 1.0
// вхідний трикутник – білий

unsigned int texture;
// AUX_RGBImageRec* image;

GLfloat red=1, blue=1, green=1;
GLfloat intensity0 = 0.0;
GLfloat intensity1 = 0.0;

GLfloat eyeX=2.3, eyeY=1.38, eyeZ=2.0, refX=0.0, refY=0.25, refZ=0.0; //2.3,1.38,2.0,0.0,0.25,0.0,0.0,1.0,0.0

static GLuint texName[4];

static int width, height;

void LoadTexture(char filename[], int iName)
{
    int channels;
    int desired_no_channels = 3;
    unsigned char *checkImage = stbi_load(filename, &width, &height, &channels, desired_no_channels);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName[iName]);
    glBindTexture(GL_TEXTURE_2D, texName[iName]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                    GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, 
                    height, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    checkImage);

}


void wall(double thickness)    // function to create the walls with given thickness
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}
void cube(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(1.0);
    glPopMatrix();
}
void sphere(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(1.0,10,10);
    glPopMatrix();
}
void torus(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidTorus(1.5,2.0,10,10);
    glPopMatrix();
}
void dode(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidDodecahedron();
    glPopMatrix();
}
void textured_cone(double scaleX, double scaleY, double scaleZ)
{
    GLUquadricObj *quadObj;
    glPushMatrix();
    LoadTexture("indexx.bmp",1);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glScaled(scaleX, scaleY, scaleZ);
    quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    glColor3d(1, 1, 1);
    gluCylinder(quadObj, 0.5, 0.5, 1, 100, 100);
    gluDeleteQuadric(quadObj);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void textured_cube(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    LoadTexture("wood.bmp",2);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glScaled(scaleX, scaleY, scaleZ);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-1.f, -1.f, -1.f);
        glTexCoord2f(0, 1); glVertex3f(-1.f,  1.f, -1.f);
        glTexCoord2f(1, 1); glVertex3f( 1.f,  1.f, -1.f);
        glTexCoord2f(1, 0); glVertex3f( 1.f, -1.f, -1.f);

        glTexCoord2f(0, 0); glVertex3f(-1.f, -1.f, 1.f);
        glTexCoord2f(0, 1); glVertex3f(-1.f,  1.f, 1.f);
        glTexCoord2f(1, 1); glVertex3f( 1.f,  1.f, 1.f);
        glTexCoord2f(1, 0); glVertex3f( 1.f, -1.f, 1.f);

        glTexCoord2f(0, 0); glVertex3f(-1.f, -1.f, -1.f);
        glTexCoord2f(0, 1); glVertex3f(-1.f,  1.f, -1.f);
        glTexCoord2f(1, 1); glVertex3f(-1.f,  1.f,  1.f);
        glTexCoord2f(1, 0); glVertex3f(-1.f, -1.f,  1.f);

        glTexCoord2f(0, 0); glVertex3f(1.f, -1.f, -1.f);
        glTexCoord2f(0, 1); glVertex3f(1.f,  1.f, -1.f);
        glTexCoord2f(1, 1); glVertex3f(1.f,  1.f,  1.f);
        glTexCoord2f(1, 0); glVertex3f(1.f, -1.f,  1.f);

        glTexCoord2f(0, 1); glVertex3f(-1.f, -1.f,  1.f);
        glTexCoord2f(0, 0); glVertex3f(-1.f, -1.f, -1.f);
        glTexCoord2f(1, 0); glVertex3f( 1.f, -1.f, -1.f);
        glTexCoord2f(1, 1); glVertex3f( 1.f, -1.f,  1.f);

        glTexCoord2f(0, 1); glVertex3f(-1.f, 1.f,  1.f);
        glTexCoord2f(0, 0); glVertex3f(-1.f, 1.f, -1.f);
        glTexCoord2f(1, 0); glVertex3f( 1.f, 1.f, -1.f);
        glTexCoord2f(1, 1); glVertex3f( 1.f, 1.f,  1.f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void textured(double scaleX, double scaleY, double scaleZ)
{
    glPushMatrix();
    LoadTexture("blue_screen.bmp",0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glScaled(scaleX, scaleY, scaleZ);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void material(GLfloat red, GLfloat green, GLfloat blue)
{
    GLfloat mat_ambient_diffuse[]={red,green,blue,0.1f};
    GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat mat_shininess[]={50.0f};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,mat_ambient_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}
void table()
{
    //left distal leg
    material(0.5,1.0,0.7);
    glPushMatrix();
    glTranslated(0.1,0.325,0.1);
    cube(0.015,0.175,0.015);
    glPopMatrix();

    //right distal leg
    material(0.5,1.0,0.6);
    glPushMatrix();
    glTranslated(0.35,0.325,0.1);
    cube(0.015,0.175,0.015);
    glPopMatrix();

    //left near leg
    material(0.2,1.0,0.6);
    glPushMatrix();
    glTranslated(0.1,0.325,0.25);
    cube(0.015,0.175,0.015);
    glPopMatrix();

    //right near leg
    material(0.5,1.0,0.6);
    glPushMatrix();
    glTranslated(0.35,0.325,0.25);
    cube(0.015,0.175,0.015);
    glPopMatrix();

    //table
    material(0.5,1.0,0.6);
    glPushMatrix();
    glTranslated(0.2105,0.4,0.1605);
    cube(0.3,0.015,0.2);
    glPopMatrix();
}
void cup()
{
    material(1,1,1);
    glPushMatrix();
    glTranslated(0.15,0.41,0.2);
    glRotated(-90, 1, 0, 0);
    textured_cone(0.025,0.025,0.05);
    glPopMatrix();
}
void tumb()
{
    material(1,1,1);
    glPushMatrix();
    glTranslated(1,0.3,0.3);
    textured_cube(0.025,0.01,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0.45,0.3);
    textured_cube(0.025,0.01,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0.6,0.3);
    textured_cube(0.025,0.01,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0.75,0.3);
    textured_cube(0.025,0.01,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0.9,0.3);
    textured_cube(0.025,0.01,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.025,0.6,0.3);
    textured_cube(0.005,0.31,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.00,0.6,0.4);
    glRotated(90,0,1,0);
    textured_cube(0.005,0.31,0.0275);
    glPopMatrix();
}
void screen()
{
    //screen image
    glPushMatrix();
    // glRotated(180, 0, 0 ,1);
    glTranslated(0.071,0.45,0.1705);
    if(intensity1 == 0.0)
    {

    }
    else
    {
        textured(0.29,0.2,0.3);
    }
    glPopMatrix();
    //screen
    material(0.1,0.1,intensity1 * 2);
    glPushMatrix();
    glTranslated(0.2105,0.55,0.1605);
    glRotated(90, 1, 0, 0);
    cube(0.3,0.015,0.2);
    glPopMatrix();

    //screen leg
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.2105,0.45,0.135);
    cube(0.015,0.125,0.015);
    glPopMatrix();
}
void chair()
{
    //seat
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.225,0.4,0.4);
    cube(0.15,0.015,0.15);
    glPopMatrix();
    //right near leg
    material(0.8,0.8,0.8);
    glPushMatrix();
    glTranslated(0.29,0.34,0.33);
    cube(0.015,0.1275,0.015);
    glPopMatrix();
    //left near leg
    material(0.8,0.8,0.8);
    glPushMatrix();
    glTranslated(0.16,0.34,0.33);
    cube(0.015,0.1275,0.015);
    glPopMatrix();
    //right distal leg
    material(0.8,0.8,0.8);
    glPushMatrix();
    glTranslated(0.29,0.34,0.47);
    cube(0.015,0.1275,0.015);
    glPopMatrix();
    //left distal leg
    material(0.8,0.8,0.8);
    glPushMatrix();
    glTranslated(0.16,0.34,0.47);
    cube(0.015,0.1275,0.015);
    glPopMatrix();
    //back
    material(0.7,0.7,0.7);
    glPushMatrix();
    glTranslated(0.225,0.5,0.5);
    glRotated(105,1,0,0);
    cube(0.15,0.015,0.2);
    glPopMatrix();
}
void window()
{
    //glass
    material(0.0,1.0,0.9);
    glPushMatrix();
    glTranslated(0.085,0.6,0.6);
    cube(0.005,0.3,0.2);
    glPopMatrix();
    //central verical frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.6,0.6);
    cube(0.015,0.3,0.015);
    glPopMatrix();
    //left vertical frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.6,0.695);
    cube(0.015,0.3,0.015);
    glPopMatrix();
    //right vertical frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.6,0.505);
    cube(0.015,0.3,0.015);
    glPopMatrix();
    //central horisontal frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.625,0.6);
    glRotated(90,1,0,0);
    cube(0.015,0.2,0.015);
    glPopMatrix();
    //lover horisontal frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.45,0.6);
    glRotated(90,1,0,0);
    cube(0.015,0.2,0.015);
    glPopMatrix();
    //upper horisontal frame
    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0.085,0.75,0.6);
    glRotated(90,1,0,0);
    cube(0.015,0.2,0.015);
    glPopMatrix();
}
void door()
{
    //basis
    material(0.5,0.3,0.4);
    glPushMatrix();
    glTranslated(1.08,0.575,0.9);
    cube(0.005,0.6,0.3);
    glPopMatrix();
    //left vertical frame
    material(0.5,0.3,0.6);
    glPushMatrix();
    glTranslated(1.08,0.575,1.05);
    cube(0.015,0.6,0.015);
    glPopMatrix();
    //right vertical frame
    material(0.5,0.3,0.6);
    glPushMatrix();
    glTranslated(1.08,0.575,0.75);
    cube(0.015,0.6,0.015);
    glPopMatrix();
    //upper horisontal frame
    material(0.5,0.3,0.6);
    glPushMatrix();
    glTranslated(1.08,0.87,0.9);
    glRotated(90,1,0,0);
    cube(0.015,0.3,0.015);
    glPopMatrix();
    //door knob
    material(0.8,0.5,0.6);
    glPushMatrix();
    glTranslated(1.0825,0.55,0.8);
    sphere(0.015,0.02,0.02);
    glPopMatrix();
}
void lamp()
{
    int R, G, B;
    if(intensity0 == 0)
    {
        R = 1;
        G = 1;
        B = 1;
    }
    else
    {
        R = 1;
        G = 1;
        B = 0;
    }
    // 0.98f, 1.5f, 0.9f
    //lamp
    material(R,G,B);
    glPushMatrix();
    glTranslated(0.6,1.1,0.6);
    sphere(0.03,0.05,0.03);
    glPopMatrix();
    //накриття
    material(0.5,1,1);
    glPushMatrix();
    glTranslated(0.6,1.15,0.6);
    glRotated(90,1,0,0);
    torus(0.02,0.02,0.001);
    glPopMatrix();
    //накриття
    material(1,0.5,1);
    glPushMatrix();
    glTranslated(0.6,1.15,0.6);
    dode(0.005,0.05,0.005);
    glPopMatrix();
}
void bed()
{
     //bed headboard
    //glTranslated(0.3,0.38,1.1);
    material(0.7,1.0,0.7);
    glPushMatrix();
    glTranslated(0.1,0.35,0.95);
    cube(0.05,0.175,0.2);
    glPopMatrix();
    
    //bed body
    material(0.5,0.3,0.7);
    glPushMatrix();
    glTranslated(0.325,0.3,0.95);
    cube(0.4, 0.1, 0.2);
    glPopMatrix();
    
    // //pillow
    material(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslated(0.15,0.38, 0.95);
    glRotated(35,0,0,1);
    cube(0.05,0.1,0.15);
    glPopMatrix();

    // //blanket
    material(0.32, 0.322, 0.176);
    glPushMatrix();
    glTranslated(0.38, 0.325, 0.95);
    cube(0.2, 0.08, 0.25);
    glPopMatrix();
}
void room()
{
    glPushMatrix();
    glTranslated(0.08,0.08,0.08);
    glPushMatrix();
    glTranslated(0.25,0.42,0.35);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.4,0,0.4);    
    glPopMatrix();
    material(1.0,0.3,0.3);
    wall(0.2);
    glPushMatrix();
    glRotated(-90.0,1.0,0.0,0.0);
    material(1,0.7,0.7);
    wall(0.02);
    glPopMatrix();
    glRotated(90.0,0.0,0.0,180.0);
    wall(0.02);
    glPopMatrix();
}

void light0(GLfloat intensity0)
{
    GLfloat ambientLight[] = { intensity0/4, intensity0/4, intensity0/2, 1.0f };
    GLfloat diffuseLight[] = { intensity0, intensity0, 0.0f, 1.0f };
    GLfloat specularLight[] = { intensity0/2, intensity0/2, intensity0/2, 1.0f };
    GLfloat position[] = { 0.6f, 1.1f, 0.6f, 1.0f };

    // Assign created components to GL_LIGHT0.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

}
void light1(GLfloat intensity1)
{
    // GLfloat ambientLight[] = { intensity1/4, intensity1/4, intensity1/2, 1.0f };
    GLfloat diffuseLight[] = { 0.0f, 0.0f, intensity1, 0.5f };
    // GLfloat specularLight[] = { intensity1/2, intensity1/2, intensity1/2, 1.0f };
    GLfloat position[] = { 0.2105f, 0.5f, 0.1725f, 0.95f };

    // Assign created components to GL_LIGHT0.
    // glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void renderScene(void)
{
    light0(intensity0);
    light1(intensity1);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // double winlet=1.0;
    //glOrtho(-winlet*64/48,winlet*64/48.0,-winlet*64/48,winlet*64/48,0.6,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,refX,refY,refZ,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    room();
    bed();
    table();
    cup();
    screen();
    chair();
    glPushMatrix();
    glTranslated(0,0,0.1);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,-0.15);
    window();
    glPopMatrix();
    door();
    tumb();
    lamp();
    glFlush();
}

void KeysBind(unsigned char key, int x, int y) {
 
    switch(key) {
        case 49:
            intensity0 = 0.8;
            break;
        case 50:
            intensity0 = 0.0;
            break;
        case 51:
            intensity1 = 0.8;
            break;
        case 52:
            intensity1 = 0.0;
            break;
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}
void changeSize(int w, int h) 
{
    float ratio;
    // запобігання поділу на нуль
    if (h == 0)
        h = 1;
    ratio =  w * 1.0 / h;
    // використовуємо матрицю проекції
    glMatrixMode(GL_PROJECTION);
    // обнуляємо матрицю
    glLoadIdentity();
    // встановити параметри вьюпорту
    glViewport(0, 0, w, h);
    // встановити коректну перспективу
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    // повернутися до матриці проекції
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv) {

    // ініціалізація
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280,720);
    glutCreateWindow("Roshchupkin Oleksii IT-02");
    // gluPerspective(60,1,1,100);

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(KeysBind);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0,1,1,0.0);

    // основний цикл
    glutMainLoop();
 
    return 1;
}
