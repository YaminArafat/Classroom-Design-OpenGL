#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "include/BmpLoader.h"
const int windowWidth = 800;
const int windowHeight = 800;

GLfloat eyeX = 23;
GLfloat eyeY = 15;
GLfloat eyeZ = 0;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

bool flagrotate =true;
float rot = 0;
float rotMin = 0;
float rotHour = 0;
GLfloat alpha = 0.0, theta = 0.0;
GLboolean bRotate = true, uRotate = true;

bool light1= true, light2 = true, light3 =true;
bool ambient =true, diffuse = true, specular = true;
unsigned int ID;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0}

};

static GLubyte quadIndices[6][4] =
{
    {0, 2, 6, 4},
    {1, 5, 7, 3},
    {0, 4, 5, 1},
    {2, 3, 7, 6},
    {0, 1, 3, 2},
    {4, 6, 7, 5}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void drawCube(float colorRed=1, float colorGreen=1, float colorBlue=1, bool on=false)
{
    GLfloat no_mat[] = { 0, 0, 0, 1.0 };
    GLfloat mat_ambient[] = { colorRed, colorGreen, colorBlue, 1.0 };
    GLfloat mat_diffuse[] = { colorRed,colorGreen, colorBlue, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {50};

    if(ambient)
    {
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);

    }
    else
    {
        glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    }

    if(diffuse)
    {
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);

    }
    else
    {
        glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    }

    if(specular)
    {
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    }
    else
    {
        glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    }



    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();

}
void table()
{
/// table base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glScalef(3, 0.5, 4);
    drawCube();//(0.502, 0.000, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// right paya back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glScalef(0.5, 3, 0.5);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// right paya front
    glPushMatrix();
    glTranslatef(2.5, 0, 0);
    glScalef(0.5, 3, 0.5);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// left paya back
    glPushMatrix();
    glTranslatef(0, 0, 3.5);
    glScalef(0.5, 3, 0.5);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// left paya front
    glPushMatrix();
    glTranslatef(2.5, 0, 3.5);
    glScalef(0.5, 3, 0.5);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void chair()
{
/// chair base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(4, 1.5, 1);
    glScalef(1.5, 0.5, 2);
    drawCube(0.824, 0.412, 0.118);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// chair paya right back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(4, 0, 1);
    glScalef(0.25, 1.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
/// chair paya right front
    glPushMatrix();
    glTranslatef(5.25, 0, 1);
    glScalef(0.25, 1.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
/// chair paya left back
    glPushMatrix();
    glTranslatef(4, 0, 2.75);
    glScalef(0.25, 1.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
/// chair paya left front
    glPushMatrix();
    glTranslatef(5.25, 0, 2.75);
    glScalef(0.25, 1.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// chair matha
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(5.25,2.5,1);
    glScalef(0.25, 1.5, 2);
    drawCube(1.000, 0.271, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// matha + base connector left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(5.25, 2, 1.25);
    glScalef(0.25, 0.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
/// matha + base connector right
    glPushMatrix();
    glTranslatef(5.25, 2, 2.5);
    glScalef(0.25, 0.5, 0.25);
    drawCube(0.502, 0.502, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void almari()
{
/// main almari
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(-18, 0, -14);
    glScalef(8.0, 10.0, 4.0);
    drawCube(1.000, 0.000, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// border left
    glPushMatrix();
    glTranslatef(-18, 0.5, -10);
    glScalef(0.25, 9.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// border right
    glPushMatrix();
    glTranslatef(-10.25, 0.5, -10);
    glScalef(0.25, 9.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
///border top
    glPushMatrix();
    glTranslatef(-18, 9.5, -10);
    glScalef(3.5, 0.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.75, 9.5, -10);
    glScalef(3.5, 0.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// border bottom
    glPushMatrix();
    glTranslatef(-18, 0.5, -10);
    glScalef(3.5, 0.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.75, 0.5, -10);
    glScalef(3.5, 0.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// door border left
    glPushMatrix();
    glTranslatef(-14.5, 0.5, -10);
    glScalef(0.25, 9.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// door border right
    glPushMatrix();
    glTranslatef(-13.75, 0.5, -10);
    glScalef(0.25, 9.25, 0.25);
    drawCube(0.627, 0.322, 0.176);
    glPopMatrix();
/// door handle left
    glPushMatrix();
    glTranslatef(-14.5, 4.5, -9.75);
    glScalef(0.20, 0.5, 0.20);
    drawCube(0.855, 0.647, 0.125);
    glPopMatrix();
/// door handle right
    glPushMatrix();
    glTranslatef(-13.8, 4.5, -9.75);
    glScalef(0.20, 0.5, 0.20);
    drawCube(0.855, 0.647, 0.125);
    glPopMatrix();
}
void light(float x=15)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 2.5,19,13.5, 1.0 };

    //glEnable( GL_LIGHT0);
    if(ambient)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);

    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    }

    if(diffuse)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    }
    else
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    }

    if(specular)
    {
         glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }
//    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    GLfloat light_ambient2[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse2[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position2[] = { 2.5,19,-14, 1.0 };

    //glEnable( GL_LIGHT1);
    if(ambient)
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient2);

    }
    else
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
    }

    if(diffuse)
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);

    }
    else
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    }

    if(specular)
    {
         glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular2);
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }
//    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient2);
//    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
//    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular2);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);

    GLfloat light_ambient3[]  = {0.5, 0.3, 0.7, 1.0};
    GLfloat light_diffuse3[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position3[] = { -0.5, x, -0.5, 1.0 };

    //glEnable( GL_LIGHT2);
    if(ambient)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient3);

    }
    else
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    }

    if(diffuse)
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);

    }
    else
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    }

    if(specular)
    {
          glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular3);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }
//    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient3);
//    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
//    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular3);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position3);

    GLfloat spot_direction[] = { 0.0, -15.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
}

void fan()
{
/// fan base
    glPushMatrix();
    glTranslatef(0, 19.5, -0.375);
    glScalef(0.5,0.5,0.5);
    drawCube(0,0,0);
    glPopMatrix();
/// fan connector
    glPushMatrix();
    glTranslatef(0.10, 18.25, -0.25);
    glScalef(0.25,1.5,0.25);
    drawCube(0.663, 0.663, 0.663);
    glPopMatrix();

    glPushMatrix();
    glRotatef(theta,0, 1, 0);
    glTranslatef(-0.25, 0,0);
/// fan engine
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-0.25, 18, -0.5);
    glScalef(1,0.5,1);
    drawCube(1, 0.0, 0.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// fan blade 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(0, 18.2, -0.25);
    //glRotatef(rotFan,0,1,0);
    //glRotatef( alpha, 0, 1, 0.0 );
    glScalef(5,0.1,0.5);
    drawCube(0,0,0);//(1.000, 0.843, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// fan blade 2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(0.5, 18.2, 0.25);
    glRotatef(-120,0,1,0);
    //glRotatef(rotFan,0,1,0);
    //glRotatef( alpha, 0, 1, 0.0 );
    glScalef(5,0.1,0.5);
    drawCube(0,0,0);//(1.000, 0.843, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// fan blade 3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(0.1, 18.2, 0);
    glRotatef(-240,0,1,0);
    //glRotatef(rotFan,0,1,0);
    //glRotatef( alpha, 0, 1, 0.0 );
    glScalef(5,0.1,0.5);
    drawCube(0,0,0);//(1.000, 0.843, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void clock()
{
/// body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-19.25,14,-2.5);
    glScalef(0.5,4.0,5.0);
    drawCube(0.902, 0.902, 0.980);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// center
    glPushMatrix();
    glTranslatef(-18.75,16,-0.25);
    glScalef(0.5,0.5,0.5);
    drawCube(0,0,0);
    glPopMatrix();
/// hour
    glPushMatrix();
    glTranslatef(-18.75,16.25,0);
    glRotatef(-rotHour,1,0,0);
    glScalef(0.25,1.0,0.25);
    drawCube(0.502, 0.000, 0.000);
    glPopMatrix();
/// minute
    glPushMatrix();
    glTranslatef(-18.75,16.25,0);
    glRotatef(-rotMin,1,0,0);
    glScalef(0.25,1.5,0.25);
    drawCube(1.000, 0.271, 0.000);
    glPopMatrix();

}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 2.0, 100.0);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);
    glRotatef(rot,0,1,0);
/// Floor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-20, -1, -15);
    glScalef(50.0, 1.0, 30.0);
    drawCube(0.878, 1.000, 1.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// Front Wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(-20.0,0, -15);
    glScalef(1.0, 20.0, 30.0);
    drawCube(0.000, 0.392, 0.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// Right Wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-20, 0, -15);
    glScalef(50.0, 7.0, 1.0);
    drawCube(0.780, 0.082, 0.522);
    glPopMatrix();
/// middle
    glPushMatrix();
    glTranslatef(-20, 7, -15);
    glScalef(14.0, 6.0, 1.0);
    drawCube(0.780, 0.082, 0.522);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 7, -15);
    glScalef(24.0, 6.0, 1.0);
    drawCube(0.780, 0.082, 0.522);
    glPopMatrix();
/// top
    glPushMatrix();
    glTranslatef(-20, 13, -15);
    glScalef(50.0, 7.0, 1.0);
    drawCube(0.780, 0.082, 0.522);
    glPopMatrix();
/// barrier
    glPushMatrix();
    glTranslatef(-0.25, 7,-15);
    glScalef(0.5,6,0.5);
    drawCube(0.502, 0.000, 0.000);
    glPopMatrix();
/// cyan
    glPushMatrix();
    glTranslatef(0.25, 7,-14.5);
    //glRotatef(180,1,0,0);
    glRotatef(alpha,0, 1, 0);
    glScalef(5.5,6,-0.5);
    drawCube(0.000, 1.000, 1.000);
    glPopMatrix();
/// white
    glPushMatrix();
    glTranslatef(-5.75, 7,-14.5);
    glRotatef(alpha,0, 1, 0);
    glScalef(5.5,6,-0.5);
    drawCube(1.000, 1.000, 1.000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// Left Wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-20, 0, 14);
    glScalef(50.0, 20.0, 1.0);
    drawCube(0.000, 0.000, 0.502);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// Top Wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-20, 20, -15);
    glScalef(50.0, 1.0, 30.0);
    drawCube(0.502, 0.502, 0.502);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
/// blackboard
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-19.5,5, -7.5);
    glScalef(1.0, 8.0, 15.0);
    drawCube();//(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,0,-2);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-9);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-2);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-9);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5,0,-2);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,0,-9);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,0,5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5,0,-2);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,0,-9);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,0,5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5,0,-2);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,0,-9);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,0,5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5,0,-2);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,0,-9);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,0,5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,-2);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15,0,-9);
    table();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15,0,5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,-2);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15,0,-9);
    chair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15,0,5);
    chair();
    glPopMatrix();

    almari();

    glPushMatrix();
    glTranslatef(8,0,0);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,0,0);
    fan();
    glPopMatrix();
    clock();

/// light left
    glPushMatrix();
    glTranslatef(0,19,13.5);
    glScalef(6,0.5,0.5);
    drawCube(1, 1.000, 1.000);
    glPopMatrix();
/// light right
    glPushMatrix();
    glTranslatef(0,19,-14);
    glScalef(6,0.5,0.5);
    drawCube(1, 1.000, 1.000);
    glPopMatrix();
/// central light
/// base
    glPushMatrix();
    glTranslatef(-0.1, 19.5, -0.1);
    glScalef(0.5,0.5,0.5);
    drawCube(0,0,0);
    glPopMatrix();
/// connector
    glPushMatrix();
    glTranslatef(0, 16, 0);
    glScalef(0.25,3.5,0.25);
    drawCube(0.663, 0.663, 0.663);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,15,-0.5);
    //glScalef(6,0.5,0.5);
    drawCube(1, 1.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,15,-0.25);
    glScalef(0.5,0.5,0.5);
    drawCube(0, 1.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0,15,-0.25);
    glScalef(0.5,0.5,0.5);
    drawCube(0, 1.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25,15,-1.5);
    glScalef(0.5,0.5,0.5);
    drawCube(1, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25,15,1.0);
    glScalef(0.5,0.5,0.5);
    drawCube(1, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.125,15.25,-1.25);
    glScalef(0.25,0.25,2.5);
    drawCube(0, 0.000, 0000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25,15.25,-0.125);
    glScalef(2.5,0.25,0.25);
    drawCube(0, 0.000, 0000);
    glPopMatrix();
/// stage
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(-18.5, 0, -9.0);
    glScalef(7,0.3,20);
    drawCube(0.184, 0.310, 0.310);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glFlush();
    glutSwapBuffers();
}

static void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case '+':
        rot++;
        break;
    case '-':
        rot--;
        break;
    case 'w':
        eyeY += 0.5;
        break;
    case 's':
        eyeY -= 0.5;
        break;
    case 'a':
        eyeX += 0.5;
        break;
    case 'd':
        eyeX -= 0.5;
        break;
    case 'e':
        eyeZ += 0.5;
        break;
    case 'r':
        eyeZ -= 0.5;
        break;

    case 'f':
    case 'F':
        bRotate = !bRotate;
        //uRotate = false;
        break;
    case 'g':
    case 'G':
        if(!uRotate)
        {
            alpha=0;
            uRotate=true;
        }
        else
        {
            alpha=70;
            uRotate=false;
        }
        break;
    case '1':
        if(light1)
        {
            glEnable(GL_LIGHT0);
            light1 = false;
        }

        else
        {
            glDisable(GL_LIGHT0);
            light1 = true;
        }
        break;
    case '2':
        if(light2)
        {
            glEnable(GL_LIGHT1);
            light2 = false;
        }

        else
        {
            glDisable(GL_LIGHT1);
            light2 = true;
        }
        break;
    case '3':
        if(light3)
        {
            glEnable(GL_LIGHT2);
            light3 = false;
        }

        else
        {
            glDisable(GL_LIGHT2);
            light3 = true;
        }
        break;
    case 'z':
        ambient = !ambient;
        break;
    case 'x':
        diffuse = !diffuse;
        break;
    case 'c':
        specular = !specular;
        break;
//    case '+':
//        Tzval+=0.2;
//        break;
//
//    case '-':
//        Tzval-=0.2;
//        break;
//        case 'W':
//    case 's':
//        Tyval+=0.2;
//        break;
//    case 'w':
//        Tyval-=0.2;
//        break;
    }
    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}
void animate()
{
    if (flagrotate == true)
    {
        rotMin+= 0.02;
        rotHour+=0.002;

    }
    if (bRotate == true)
    {
        theta += 0.5;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

//    if (uRotate == true)
//    {
//        alpha += 0.2;
////        if(alpha > 360.0)
////            alpha -= 360.0*floor(alpha/360.0);
//    }
    glutPostRedisplay();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("ClassRoom Design OpenGL");

    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\wall7.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\wall2.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\wall4.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\wall8.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\bb3.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\test2.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\leg1.bmp");
    //LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\test.bmp");
    LoadTexture("F:\\Study\\4.2\\lab\\lab 02 assignment\\Lab03Assignment\\BMP\\leg3.bmp");


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutIdleFunc(animate);
    light(15);
    //light();
    //light(5);
    printf("\n\n\n\t\tClassRoom Design OpenGL\n\n\n");
    printf("1. Use 'w' to look up, 's' to look down, 'd' to look right, and 'a' to look left, 'e'/'r' to zoom\n\n");
    printf("2. Use '+'/'-' to rotate.\n\n\n");
    printf("3. Use 'f' to on/off fan.\n\n\n");
    printf("4. Use 'g' to on/off window.\n\n\n");
    printf("5. Use '1'/'2'/'3' to on/off light.\n\n\n");
    printf("5. Use 'z'/'x'/'c' to on/off ambient, diffuse, specular.\n\n\n");
    glutMainLoop();
    return EXIT_SUCCESS;
}
