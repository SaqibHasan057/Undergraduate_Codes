#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double maxRadius;
double maxSide;

double radius;
double side;

struct point
{
	double x,y,z;
};

struct point pos;
struct point u;
struct point r;
struct point l;


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 0.6, 0.8);
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

void drawSquare(double a)
{
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}


void drawCircle(double radius,int segments,double height)
{
    int i;
    struct point points[100];
    //glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,height);
			glVertex3f(points[i+1].x,points[i+1].y,height);
        }
        glEnd();
    }
}



void drawCylinder(double radius,double height,int segments){
    struct point top[100];
    struct point bottom[100];
    int i;

     for(i=0;i<=segments;i++)
    {
        top[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        top[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        top[i].z=(double)height/(double)2;
    }

    for(i=0;i<=segments;i++)
    {
        bottom[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        bottom[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        bottom[i].z=-(double)height/(double)2;
    }


    //draw segments using generated points
    for(i=0;i<segments;i++)
    {

        /*
        glBegin(GL_LINES);
        {
			glVertex3f(top[i].x,top[i].y,top[i].z);
			glVertex3f(top[i+1].x,top[i+1].y,top[i+1].z);
        }
        glEnd();

        glBegin(GL_LINES);
        {
			glVertex3f(bottom[i].x,bottom[i].y,bottom[i].z);
			glVertex3f(bottom[i+1].x,bottom[i+1].y,bottom[i+1].z);
        }
        glEnd();
        */

        glColor3f((double)i/(double)segments,(double)i/(double)segments,(double)i/(double)segments);
        glBegin(GL_QUADS);{
                glVertex3d(top[i].x,top[i].y,top[i].z);
                glVertex3d(top[i+1].x,top[i+1].y,top[i+1].z);
                glVertex3d(bottom[i+1].x,bottom[i+1].y,bottom[i+1].z);
                glVertex3d(bottom[i].x,bottom[i].y,bottom[i].z);

        }glEnd();



    }
}



void drawOneFourthCylinder(double radius,double height,int segments){
    struct point top[100];
    struct point bottom[100];
    int i;

     for(i=0;i<=segments;i++)
    {
        top[i].x=radius*cos(((double)i/(double)segments)*((double)pi/(double)2));
        top[i].y=radius*sin(((double)i/(double)segments)*((double)pi/(double)2));
        top[i].z=(double)height/(double)2;
    }

    for(i=0;i<=segments;i++)
    {
        bottom[i].x=radius*cos(((double)i/(double)segments)*((double)pi/(double)2));
        bottom[i].y=radius*sin(((double)i/(double)segments)*((double)pi/(double)2));
        bottom[i].z=-(double)height/(double)2;
    }


    //draw segments using generated points
    for(i=0;i<segments;i++)
    {

        /*
        glBegin(GL_LINES);
        {
			glVertex3f(top[i].x,top[i].y,top[i].z);
			glVertex3f(top[i+1].x,top[i+1].y,top[i+1].z);
        }
        glEnd();

        glBegin(GL_LINES);
        {
			glVertex3f(bottom[i].x,bottom[i].y,bottom[i].z);
			glVertex3f(bottom[i+1].x,bottom[i+1].y,bottom[i+1].z);
        }
        glEnd();
        */

        //glColor3f((double)i/(double)segments,(double)i/(double)segments,(double)i/(double)segments);
        glColor3f(0,1,0);
        glBegin(GL_QUADS);{
                glVertex3d(top[i].x,top[i].y,top[i].z);
                glVertex3d(top[i+1].x,top[i+1].y,top[i+1].z);
                glVertex3d(bottom[i+1].x,bottom[i+1].y,bottom[i+1].z);
                glVertex3d(bottom[i].x,bottom[i].y,bottom[i].z);

        }glEnd();



    }
}


void drawOneEightSphere(double radius,int slices,int stacks){
    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<=stacks;i++)
	{
        glColor3f(1,0,0);
		for(j=0;j<=slices/4;j++)
		{

			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
				*/
			}glEnd();
		}
	}
}



struct point crossProduct(struct point a,struct point b){
    struct point c;

    c.x = a.y*b.z - b.y*a.z;
    c.y = -(a.x*b.z - b.x*a.z);
    c.z = a.x*b.y - b.x*a.y;

    return c;
}




void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			//drawgrid=1-drawgrid;
			{
			    double angle = -(double)3/(double)360 * 2 * pi;

               struct point lCrossu = crossProduct(l,u);
               l.x = l.x*cos(angle) + lCrossu.x*sin(angle);
               l.y = l.y*cos(angle) + lCrossu.y*sin(angle);
               l.z = l.z*cos(angle) + lCrossu.z*sin(angle);

               struct point rCrossu = crossProduct(r,u);
               r.x = r.x*cos(angle) + rCrossu.x*sin(angle);
               r.y = r.y*cos(angle) + rCrossu.y*sin(angle);
               r.z = r.z*cos(angle) + rCrossu.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");



               break;

			}





        case '2':
            {
                 double angle = (double)3/(double)360 * 2 * pi;

               struct point lCrossu = crossProduct(l,u);
               l.x = l.x*cos(angle) + lCrossu.x*sin(angle);
               l.y = l.y*cos(angle) + lCrossu.y*sin(angle);
               l.z = l.z*cos(angle) + lCrossu.z*sin(angle);

               struct point rCrossu = crossProduct(r,u);
               r.x = r.x*cos(angle) + rCrossu.x*sin(angle);
               r.y = r.y*cos(angle) + rCrossu.y*sin(angle);
               r.z = r.z*cos(angle) + rCrossu.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");

               break;


            }

        case '3':
            {
               double angle = -(double)3/(double)360 * 2 * pi;

               struct point lCrossr = crossProduct(l,r);
               l.x = l.x*cos(angle) + lCrossr.x*sin(angle);
               l.y = l.y*cos(angle) + lCrossr.y*sin(angle);
               l.z = l.z*cos(angle) + lCrossr.z*sin(angle);

               struct point uCrossr = crossProduct(u,r);
               u.x = u.x*cos(angle) + uCrossr.x*sin(angle);
               u.y = u.y*cos(angle) + uCrossr.y*sin(angle);
               u.z = u.z*cos(angle) + uCrossr.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");



               break;

            }

        case '4':
            {
                double angle = (double)3/(double)360 * 2 * pi;

               struct point lCrossr = crossProduct(l,r);
               l.x = l.x*cos(angle) + lCrossr.x*sin(angle);
               l.y = l.y*cos(angle) + lCrossr.y*sin(angle);
               l.z = l.z*cos(angle) + lCrossr.z*sin(angle);

               struct point uCrossr = crossProduct(u,r);
               u.x = u.x*cos(angle) + uCrossr.x*sin(angle);
               u.y = u.y*cos(angle) + uCrossr.y*sin(angle);
               u.z = u.z*cos(angle) + uCrossr.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");



               break;

            }

        case '5':
            {
                 double angle = -(double)3/(double)360 * 2 * pi;

               struct point rCrossl = crossProduct(r,l);
               struct point uCrossl = crossProduct(u,l);

               r.x = r.x*cos(angle) + rCrossl.x*sin(angle);
               r.y = r.y*cos(angle) + rCrossl.y*sin(angle);
               r.z = r.z*cos(angle) + rCrossl.z*sin(angle);

               u.x = u.x*cos(angle) + uCrossl.x*sin(angle);
               u.y = u.y*cos(angle) + uCrossl.y*sin(angle);
               u.z = u.z*cos(angle) + uCrossl.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");



               break;

            }

        case '6':
            {
                 double angle = (double)3/(double)360 * 2 * pi;

               struct point rCrossl = crossProduct(r,l);
               struct point uCrossl = crossProduct(u,l);

               r.x = r.x*cos(angle) + rCrossl.x*sin(angle);
               r.y = r.y*cos(angle) + rCrossl.y*sin(angle);
               r.z = r.z*cos(angle) + rCrossl.z*sin(angle);

               u.x = u.x*cos(angle) + uCrossl.x*sin(angle);
               u.y = u.y*cos(angle) + uCrossl.y*sin(angle);
               u.z = u.z*cos(angle) + uCrossl.z*sin(angle);

               printf("L: %f %f %f\n",l.x,l.y,l.z);
               printf("U: %f %f %f\n",u.x,u.y,u.z);
               printf("R: %f %f %f\n",r.x,r.y,r.z);
               printf("\n\n");


               break;

            }

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
		    pos.x -= l.x;
		    pos.y -= l.y;
		    pos.y -= l.z;
			//cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
            pos.x += l.x;
		    pos.y += l.y;
		    pos.y += l.z;
			//cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			pos.x += r.x;
			pos.y += r.y;
			pos.z += r.z;
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			pos.x -= r.x;
			pos.y -= r.y;
			pos.z -= r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x += 2*u.x;
		    pos.y += 2*u.y;
		    pos.z += 2*u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    pos.x -= u.x;
		    pos.y -= u.y;
		    pos.z -= u.z;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    if(side>0 && radius<maxRadius){
                radius+=1;
                side-=2;
		    }
			break;
		case GLUT_KEY_END:
		    if(side<maxSide && radius>0){
                radius-=1;
                side+=2;
		    }
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

void myDrawFunction(){

    /*
    glPushMatrix();
    glTranslatef(0,20,0);
    glRotatef(90,1,0,0);
    drawSquare(20);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-20,0);
    glRotatef(-90,1,0,0);
    drawSquare(20);
    glPopMatrix();
    */

    /*
    glPushMatrix();
    glRotatef(90,0,1,0);
    drawOneEightSphereUpper(40,60,60);
    glPopMatrix();
    drawOneEightSphereUpper(40,60,60);
    */


    //drawSphere(40,60,60);








    //draw all the six squares


    glPushMatrix();
    glTranslatef(0,side+radius,0);
    glRotatef(-90,1,0,0);
    drawSquare(side);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-side-radius,0);
    glRotatef(90,1,0,0);
    drawSquare(side);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(side+radius,0,0);
    glRotatef(-90,0,1,0);
    drawSquare(side);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side-radius,0,0);
    glRotatef(90,0,1,0);
    drawSquare(side);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,0,side+radius);
    drawSquare(side);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-side-radius);
    drawSquare(side);
    glPopMatrix();

    //finished drawing all squares








    //drawing all the spheres

    glPushMatrix();
    glTranslatef(side,side,side);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,side,-side);
    glRotatef(90,0,1,0);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-side,side,side);
    glRotatef(90,0,0,1);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side,side,-side);
    glRotatef(90,0,0,1);
    glRotatef(90,0,1,0);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-side,-side,side);
    glRotatef(180,0,0,1);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side,-side,-side);
    glRotatef(180,0,0,1);
    glRotatef(90,0,1,0);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(side,-side,side);
    glRotatef(270,0,0,1);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,-side,-side);
    glRotatef(270,0,0,1);
    glRotatef(90,0,1,0);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    //finished drawing all the spheres



    //draw vertical cylinders


    glPushMatrix();
    glTranslatef(side,side,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-side,side,0);
    glRotatef(90,0,0,1);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side,-side,0);
    glRotatef(180,0,0,1);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,-side,0);
    glRotatef(270,0,0,1);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();



    //finished drawing vertical cylinders





    //draw top cylinders

    glPushMatrix();
    glTranslatef(0,side,side);
    glRotatef(-90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side,0,side);
    glRotatef(90,0,0,1);
    glRotatef(-90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-side,side);
    glRotatef(180,0,0,1);
    glRotatef(-90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,0,side);
    glRotatef(270,0,0,1);
    glRotatef(-90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();


    //finished drawing top cylinders



    //draw bottom cylinders


    glPushMatrix();
    glTranslatef(0,side,-side);
    glRotatef(90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-side,0,-side);
    glRotatef(90,0,0,1);
    glRotatef(90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-side,-side);
    glRotatef(180,0,0,1);
    glRotatef(90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,0,-side);
    glRotatef(270,0,0,1);
    glRotatef(90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();


    //finished drawing bottom cylinders







    /*

    glPushMatrix();
    glTranslatef(side,side,side);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(side,side,-side);
    glRotatef(90,0,1,0);
    drawOneEightSphere(radius,3*radius,3*radius);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(side,side,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,side,side);
    glRotatef(-90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,side,-side);
    glRotatef(90,0,1,0);
    drawOneFourthCylinder(radius,2*side,3*radius);
    glPopMatrix();
    */





}

void myAnimation(){

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

	gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

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
	//angle+=0.005;
	//codes for any changes in Models, Camera
	myAnimation();
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	maxSide = 40 ;
	maxRadius = maxSide/2;

	radius = 5;
	side = 30;





	pos.x = 100;
	pos.y = 100;
	pos.z = 0;

	u.x = 0;
	u.y = 0;
	u.z = 1;

	r.x = -(double)1/(double)sqrt(2);
	r.y = (double)1/(double)sqrt(2);
	r.z = 0;

	l.x = -(double)1/(double)sqrt(2);
	l.y = -(double)1/(double)sqrt(2);
	l.z = 0;

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
