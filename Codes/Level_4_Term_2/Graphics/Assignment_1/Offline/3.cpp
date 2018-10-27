#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))


double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double bigArmFrontBack;
double bigArmSideWays;
double smallArmFrontBack;
double wrist;
double rotateFinger;
double frontBackFinger;

double cameraHeight;
double distance;

struct point
{
	double x,y,z;
};

struct point cameraPos;

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
		    if(bigArmFrontBack>-45)bigArmFrontBack-=3;
			break;

        case '2':
            if(bigArmFrontBack<45)bigArmFrontBack+=3;
			break;

        case '3':
            if(smallArmFrontBack>-90)smallArmFrontBack-=3;
			break;

        case '4':
            if(smallArmFrontBack<0)smallArmFrontBack+=3;
			break;

        case '5':
            if(wrist<45)wrist+=3;
			break;

        case '6':
            if(wrist>-45)wrist-=3;
			break;

        case '7':
            if(rotateFinger>-45)rotateFinger-=3;
			break;

        case '8':
            if(rotateFinger<45)rotateFinger+=3;
			break;

        case '9':
			if(frontBackFinger>-90)frontBackFinger-=3;
			break;

        case '0':
			if(frontBackFinger<0)frontBackFinger+=3;
			break;

        case 'q':
			if(bigArmSideWays>-90)bigArmSideWays-=3;
			break;

        case 'w':
			if(bigArmSideWays<0)bigArmSideWays+=3;
			break;


		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;


			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void drawWrist(){

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0,0,0);
        glVertex3f(0,10,-10);
        glVertex3f(0,-10,-10);
    }glEnd();
}

void myDrawFunction(){

    glRotatef(bigArmSideWays,1,0,0);


    //Long Arm
    glPushMatrix();
    {
        glRotatef(bigArmFrontBack,0,1,0);
        glTranslatef(0,0,-30);
        glScalef(1,1,3);
        glutWireSphere(10,10,10);
    }
    glPopMatrix();



    //Small Elbow
    glPushMatrix();
    {
        glRotatef(bigArmFrontBack,0,1,0);
        glTranslatef(0,0,-60);
        glRotatef(smallArmFrontBack,0,1,0);
        glTranslatef(0,0,-15);
        glScalef(1,1,3);
        glutWireSphere(5,10,10);
    }
    glPopMatrix();



    //Wrist
    glPushMatrix();
    {
        glRotatef(bigArmFrontBack,0,1,0);
        glTranslatef(0,0,-60);
        glRotatef(smallArmFrontBack,0,1,0);
        glTranslatef(0,0,-30);
        glRotatef(wrist,0,0,1);
        drawWrist();
    }
    glPopMatrix();







    //Rotate Finger
    glPushMatrix();
    {
        glRotatef(bigArmFrontBack,0,1,0);
        glTranslatef(0,0,-60);

        glRotatef(smallArmFrontBack,0,1,0);
        glTranslatef(0,0,-30);

        glRotatef(wrist,0,0,1);
        glTranslatef(0,-10,-10);

        glRotatef(rotateFinger,0,0,1);
        glTranslatef(0,0,-4);

        glScalef(1,1,3);
        glutWireSphere(2,5,5);
    }
    glPopMatrix();


    //Pointy Finger
    glPushMatrix();
    {
        glRotatef(bigArmFrontBack,0,1,0);
        glTranslatef(0,0,-60);

        glRotatef(smallArmFrontBack,0,1,0);
        glTranslatef(0,0,-30);

        glRotatef(wrist,0,0,1);
        glTranslatef(0,10,-10);

        glRotatef(frontBackFinger,0,1,0);
        glTranslatef(0,0,-4);

        glScalef(1,1,3);
        glutWireSphere(2,5,5);
    }
    glPopMatrix();










}

void myAnimationFunction(){
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(distance*cos(cameraAngle), distance*sin(cameraAngle), cameraHeight,		0,0,-50,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);
	//gluLookAt(cameraPos.x,cameraPos.y,cameraPos.z,0,0,-50,0,0,1);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);

	myDrawFunction();




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	myAnimationFunction();
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;

	cameraAngle=1.0;
	angle=0;
	bigArmFrontBack=0;
	bigArmSideWays=0;
	smallArmFrontBack=0;
	wrist=0;
	rotateFinger=0;
	frontBackFinger=0;

	cameraHeight=-50;
	distance = sqrt(100*100 + 100*100);

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
