#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))
#define LEFT 0
#define RIGHT 1

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;





struct point
{
	double x,y,z;
};


int drawframe;
double framelength;

struct point pos;
struct point v;
struct point head;
struct point trianglePoint1;
struct point trianglePoint2;


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

void drawFrame()
{
	int i;
	if(drawframe==1)
	{
		glColor3f(1, 1, 1);	//grey
		glBegin(GL_LINES);{
			glVertex3f(framelength, framelength, 0);
            glVertex3f(-framelength,  framelength, 0);

            glVertex3f(framelength, framelength, 0);
            glVertex3f(framelength, -framelength, 0);

            glVertex3f(framelength, -framelength, 0);
            glVertex3f(-framelength,  -framelength, 0);

            glVertex3f(-framelength,  -framelength, 0);
            glVertex3f(-framelength,  framelength, 0);
		}glEnd();
	}
}


struct point normalVector(struct point a){
    struct point ret;
    ret.x = -a.y;
    ret.y = a.x;
    return ret;
};


void rotateArrow(int direction){
    double angle;

    if(direction==LEFT){
        angle = (double)3/(double)360 * 2 * pi;
    }
    else{
        angle = -(double)3/(double)360 * 2 * pi;
    }


    double rotationVector[2][2] = {{cos(angle),-sin(angle)},{sin(angle),cos(angle)}};

    //printf("Rotation Values: %f %f %f %f %f\n",rotationVector[0][0],rotationVector[0][1],rotationVector[1][0],rotationVector[1][1],cos(angle));

    //printf("Old Values:\n");
    //printf("%f %f %f\n",head.x,trianglePoint1.x,trianglePoint2.x);
    //printf("%f %f %f\n",head.y,trianglePoint1.y,trianglePoint2.y);

    head.x -= pos.x;
    head.y -= pos.y;
    struct point headNormal = normalVector(head);
    head.x = head.x * cos(angle) + headNormal.x * sin(angle);
    head.y = head.y * cos(angle) + headNormal.y * sin(angle);
    head.x += pos.x;
    head.y += pos.y;


    trianglePoint1.x -=pos.x;
    trianglePoint1.y -=pos.y;
    struct point trianglePoint1Normal = normalVector(trianglePoint1);
    trianglePoint1.x = trianglePoint1.x * cos(angle) + trianglePoint1Normal.x * sin(angle);
    trianglePoint1.y = trianglePoint1.y * cos(angle) + trianglePoint1Normal.y * sin(angle);
    trianglePoint1.x +=pos.x;
    trianglePoint1.y +=pos.y;


    trianglePoint2.x -=pos.x;
    trianglePoint2.y -=pos.y;
    struct point trianglePoint2Normal = normalVector(trianglePoint2);
    trianglePoint2.x = trianglePoint2.x * cos(angle) + trianglePoint2Normal.x * sin(angle);
    trianglePoint2.y = trianglePoint2.y * cos(angle) + trianglePoint2Normal.y * sin(angle);
    trianglePoint2.x +=pos.x;
    trianglePoint2.y +=pos.y;

    struct point vNormal = normalVector(v);
    v.x = v.x * cos(angle) + vNormal.x * sin(angle);
    v.y = v.y * cos(angle) + vNormal.y * sin(angle);

    //printf("New Values:\n");
    //printf("%f %f %f\n",head.x,trianglePoint1.x,trianglePoint2.x);
    //printf("%f %f %f\n",head.y,trianglePoint1.y,trianglePoint2.y);


}





void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			rotateArrow(RIGHT);
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			rotateArrow(LEFT);
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
				drawframe = 1 - drawframe;
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


void drawArrow(){




    glColor3f(1,1,1);
    glBegin(GL_LINES);
    {
        glVertex3f(pos.x,pos.y,0);
        glVertex3f(head.x,head.y,0);
    }glEnd();


    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(head.x,head.y,0);
        glVertex3f(trianglePoint1.x,trianglePoint1.y,0);
        glVertex3f(trianglePoint2.x,trianglePoint2.y,0);
    }glEnd();




}

void myDrawFunction(){
    drawArrow();
}

void myAnimationFunction(){

    pos.x += v.x;
    pos.y += v.y;
    head.x += v.x;
    head.y += v.y;
    trianglePoint1.x += v.x;
    trianglePoint1.y += v.y;
    trianglePoint2.x +=v.x;
    trianglePoint2.y += v.y;


    if(head.x<=-framelength || head.x>=framelength){

        v.x=-v.x;
        head.x-= 2*(head.x-pos.x);
        trianglePoint1.x -= 2*(trianglePoint1.x-pos.x);
        trianglePoint2.x -= 2*(trianglePoint2.x-pos.x);
        printf("X: %f %f %f\n",head.x,trianglePoint1.x,trianglePoint2.x);
        printf("Y: %f %f %f\n",head.y,trianglePoint1.y,trianglePoint2.y);

    }

    if(head.y<=-framelength || head.y>=framelength){
        //printf("Y: %f %f %f\n",head.y,trianglePoint1.y,trianglePoint2.y);
        v.y=-v.y;
        head.y-= 2*(head.y-pos.y);
        trianglePoint1.y -= 2*(trianglePoint1.y-pos.y);
        trianglePoint2.y -= 2*(trianglePoint2.y-pos.y);
        printf("X: %f %f %f\n",head.x,trianglePoint1.x,trianglePoint2.x);
        printf("Y: %f %f %f\n",head.y,trianglePoint1.y,trianglePoint2.y);

    }




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
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,100,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	drawFrame();

	myDrawFunction();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




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
	drawaxes=0;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;




	//initialization for arrow

	drawframe = 1;
	framelength = 60;

	pos.x = 0;//-framelength;
	pos.y = 0;//-framelength;

	v.x = 0.025;
	v.y = 0.025;


	head.x = pos.x+10;
	head.y = pos.y+10;

	trianglePoint1.x = head.x -1.55;
	trianglePoint1.y = head.y -5.8;

	trianglePoint2.x = head.x -5.8;
	trianglePoint2.y = head.y -1.55;





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
