#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>


//Ray Tracing
#include "object.h"
#include <vector>
#include "bitmap_image.hpp"
#include <fstream>
using namespace std;

#define pi (2*acos(0.0))
#define VIEW_ANGLE 80

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double maxRadius;
double maxSide;

double radius;
double side;







//Ray Tracing
struct point pos;
struct point u;
struct point r;
struct point l;

double windowWidth=500;
double windowHeight=500;

int imageWidth;

vector <Object*> objects;
vector <vector3> lights;

int recursionLevel;

int noOfSphereToRefract = 2;
int refractingSpheres = 0;
double refIndexToBeSet = 1.5;
bool useTexture = true;



//Ray Tracing


void Capture(){
    cout<<"Capturing started!!"<<endl;
    bitmap_image image(imageWidth,imageWidth);
    double plane_distance = (double)((double)windowHeight/(double)2.0)/(double)tan((double)(VIEW_ANGLE*pi)/(double)360.0);

    struct vector3 topleft;
    topleft.x = pos.x + l.x*plane_distance - r.x*windowWidth/2.0 + u.x*windowHeight/2.0;
    topleft.y = pos.y + l.y*plane_distance - r.y*windowWidth/2.0 + u.y*windowHeight/2.0;
    topleft.z = pos.z + l.z*plane_distance - r.z*windowWidth/2.0 + u.z*windowHeight/2.0;

    struct vector3 eye(pos.x,pos.y,pos.z);


    double du = (double)windowWidth/(double)imageWidth;
    double dv = (double)windowHeight/(double)imageWidth;


    for(int i=0;i<imageWidth;i++){
        for(int j=0;j<imageWidth;j++){
            //cout<<"IJ "<<i<<" "<<j<<endl;
            struct vector3 corner;
            corner.x = topleft.x + r.x*j*du - u.x*i*dv;
            corner.y = topleft.y + r.y*j*du - u.y*i*dv;
            corner.z = topleft.z + r.z*j*du - u.z*i*dv;

            //corner.printVector();

            struct vector3 cornerMinusPos;
            cornerMinusPos.x = corner.x - pos.x;
            cornerMinusPos.y = corner.y - pos.y;
            cornerMinusPos.z = corner.z - pos.z;

            cornerMinusPos.normalize();

            Ray *ray = new Ray(eye,cornerMinusPos);

            int nearest = -1;
            double dummyColorAt[3];
            double t_min = 999999999;

            for(int k=0;k<objects.size();k++){
                double t = objects[k]->intersect(ray,dummyColorAt,0);
                //cout<<"t "<<t<<endl;

                if(t<=0)continue;

                if(t<t_min){
                    t_min=t;
                    nearest=k;
                }
            }

            //cout<<"Nearest t_min"<<nearest<<" "<<t_min<<endl;

            if(nearest!=-1){
                double t = objects[nearest]->intersect(ray,dummyColorAt,1);
                //cout<<"Setting colors: "<<dummyColorAt[0]<<" "<<dummyColorAt[1]<<" "<<dummyColorAt[2]<<endl;
                //cout<<"Pixels at: "<<j<<" "<<i<<endl;
                image.set_pixel(j,i,dummyColorAt[0]*255,dummyColorAt[1]*255,dummyColorAt[2]*255);
            }
        }
    }

    image.save_image("rayTracing.bmp");
    cout<<"It works!!"<<endl;
}


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 0, 0);
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
        case '0':
            {
                Capture();
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


    //Ray Tracing

    for(int i=0;i<objects.size();i++){
        objects[i]->draw();
    }

    glColor3f(0.5, 1, 0.5);
    glBegin (GL_POINTS);
    for(int i=0;i<lights.size();i++){
        glVertex3f (lights[i].x,lights[i].y,lights[i].z);
    }
    glEnd ();





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

	//gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);

	//Ray Tracing
	gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

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
	//angle+=0.005;
	//codes for any changes in Models, Camera
	myAnimation();
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	maxSide = 40 ;
	maxRadius = maxSide/2;

	radius = 5;
	side = 30;




	//Ray Tracing
	pos.x = 0;
	pos.y = -80;
	pos.z = 10;

	u.x = 0;
	u.y = 0;
	u.z = 1;

	r.x = 1;
	r.y = 0;
	r.z = 0;

	l.x = 0;
	l.y = 1;
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


//Ray Tracing
void loadTestData(){
    recursionLevel = 3;


    Object *temp;
/*
    vector3 Center(0.0,0.0,10.0);
    double Radius = 10;
    temp=new Sphere(Center, Radius); // Center(0,0,10), Radius 10
    temp->setColor(1,0,0);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);
*/

    double values[10] = {0.0625,0.04,0.04,0,0,0,0,0,0,-36};
    vector3 centerQ(0,0,0);
    double length = 0;
    double width = 0;
    double height = 15;
    temp = new GeneralQuadric(values,centerQ,length,width,height);
    temp->setColor(1,0,0);
    temp->setCoEfficients(0.4,0.2,0.1,0.3);
    temp->setShine(10);
    objects.push_back(temp);





    vector3 a(50.0,30.0,0.0);
    vector3 b(70.0,60.0,0.0);
    vector3 c(50.0,45.0,50.0);
    temp=new Triangle(a,b,c); // Center(0,0,10), Radius 10
    temp->setColor(1,0,0);
    temp->setCoEfficients(0.4,0.2,0.1,0.3);
    temp->setShine(5);
    objects.push_back(temp);

    vector3 a2(70.0,60.0,0.0);
    vector3 b2(30.0,60.0,0.0);
    vector3 c2(50.0,45.0,50.0);
    temp=new Triangle(a2,b2,c2); // Center(0,0,10), Radius 10
    temp->setColor(1,0,0);
    temp->setCoEfficients(0.4,0.2,0.1,0.3);
    temp->setShine(5);
    objects.push_back(temp);

    vector3 a3(30.0,60.0,0.0);
    vector3 b3(50.0,30.0,0.0);
    vector3 c3(50.0,45.0,50.0);
    temp=new Triangle(a3,b3,c3); // Center(0,0,10), Radius 10
    temp->setColor(1,0,0);
    temp->setCoEfficients(0.4,0.2,0.1,0.3);
    temp->setShine(5);
    objects.push_back(temp);



/*
    vector3 Center2(20.0,10.0,40.0);
    double Radius2 = 5;
    temp=new Sphere(Center2, Radius2); // Center(0,0,10), Radius 10
    temp->setColor(0,1,0);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);

    vector3 Center3(20.0,-50.0,0.0);
    double Radius3 = 3;
    temp=new Sphere(Center3, Radius3); // Center(0,0,10), Radius 10
    temp->setColor(0,0,1);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);


    vector3 Center4(30.0,-20.0,5.0);
    double Radius4 = 7;
    temp=new Sphere(Center4, Radius4); // Center(0,0,10), Radius 10
    temp->setColor(0,0,1);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);

    vector3 Center5(20.0,-50.0,0.0);
    double Radius5 = 8;
    temp=new Sphere(Center5, Radius5); // Center(0,0,10), Radius 10
    temp->setColor(1,0,1);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);

    vector3 Center6(4.0,-16.0,4.0);
    double Radius6 = 4;
    temp=new Sphere(Center6, Radius6); // Center(0,0,10), Radius 10
    temp->setColor(1,1,0);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);

    vector3 Center7(50.0,40.0,50.0);
    double Radius7 = 15;
    temp=new Sphere(Center7, Radius7); // Center(0,0,10), Radius 10
    temp->setColor(0,1,1);
    temp->setCoEfficients(0.4,0.2,0.2,0.2);
    temp->setShine(1);
    objects.push_back(temp);

*/



    vector3 light1(-50,50,50);
    lights.push_back(light1);


    Object *floorTemp = new Floor(1000,20,useTexture);
    floorTemp->setCoEfficients(0.4,0.2,0.2,0.2);
    floorTemp->setShine(1);
    objects.push_back(floorTemp);


    imageWidth=768;
}

void loadActualData(){
    ifstream readScene;
    readScene.open("scene.txt");

    readScene>>recursionLevel;
    readScene>>imageWidth;

    int numberOfObjects;

    readScene>>numberOfObjects;

    cout<<"Initial:"<<endl;
    cout<<recursionLevel<<endl;
    cout<<imageWidth<<endl;
    cout<<numberOfObjects<<endl<<endl;

    for(int i=0;i<numberOfObjects;i++){
        string typeOfObject;
        readScene>>typeOfObject;
        cout<<typeOfObject<<endl;

        if(typeOfObject=="sphere"){
            Object *temp;
            double center[3];
            double radius;
            double color[3];
            double coefficients[4];
            int shine;

            readScene>>center[0]>>center[1]>>center[2];
            readScene>>radius;
            readScene>>color[0]>>color[1]>>color[2];
            readScene>>coefficients[0]>>coefficients[1]>>coefficients[2]>>coefficients[3];
            readScene>>shine;

            //cout<<"Sphere:"<<endl;
            cout<<center[0]<<" "<<center[1]<<" "<<center[2]<<endl;
            cout<<radius<<endl;
            cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<" "<<endl;
            cout<<coefficients[0]<<" "<<coefficients[1]<<" "<<coefficients[2]<<" "<<coefficients[3]<<endl;
            cout<<shine<<endl<<endl;

            vector3 Center(center[0],center[1],center[2]);
            temp=new Sphere(Center, radius);
            temp->setColor(color[0],color[1],color[2]);
            temp->setCoEfficients(coefficients[0],coefficients[1],coefficients[2],coefficients[3]);
            temp->setShine(shine);

            if(refractingSpheres<noOfSphereToRefract){
                temp->setRefractionParameters(refIndexToBeSet);
                refractingSpheres++;
            }

            objects.push_back(temp);
        }
        else if(typeOfObject=="triangle"){
            Object *temp;
            vector3 a;
            vector3 b;
            vector3 c;
            double color[3];
            double coefficients[4];
            int shine;

            readScene>>a.x>>a.y>>a.z;
            readScene>>b.x>>b.y>>b.z;
            readScene>>c.x>>c.y>>c.z;
            //cout<<"Triangle"<<endl;
            a.printVector();
            b.printVector();
            c.printVector();
            readScene>>color[0]>>color[1]>>color[2];
            readScene>>coefficients[0]>>coefficients[1]>>coefficients[2]>>coefficients[3];
            readScene>>shine;

            cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<" "<<endl;
            cout<<coefficients[0]<<" "<<coefficients[1]<<" "<<coefficients[2]<<" "<<coefficients[3]<<endl;
            cout<<shine<<endl<<endl;


            temp=new Triangle(a,b,c); // Center(0,0,10), Radius 10
            temp->setColor(color[0],color[1],color[2]);
            temp->setCoEfficients(coefficients[0],coefficients[1],coefficients[2],coefficients[3]);
            temp->setShine(shine);
            objects.push_back(temp);
        }
        else{
            Object *temp;
            double values[10];
            vector3 centerQ;
            double length;
            double width;
            double height;
            double color[3];
            double coefficients[4];
            int shine;

            for(int j=0;j<10;j++)readScene>>values[j];
            readScene>>centerQ.x>>centerQ.y>>centerQ.z;
            readScene>>length>>width>>height;
            readScene>>color[0]>>color[1]>>color[2];
            readScene>>coefficients[0]>>coefficients[1]>>coefficients[2]>>coefficients[3];
            readScene>>shine;

            //cout<<"General"<<endl;
            for(int j=0;j<10;j++)cout<<values[j]<<" ";
            cout<<endl;
            cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<" "<<endl;
            cout<<coefficients[0]<<" "<<coefficients[1]<<" "<<coefficients[2]<<" "<<coefficients[3]<<endl;
            cout<<shine<<endl<<endl;

            temp = new GeneralQuadric(values,centerQ,length,width,height);
            temp->setColor(color[0],color[1],color[2]);
            temp->setCoEfficients(coefficients[0],coefficients[1],coefficients[2],coefficients[3]);
            temp->setShine(shine);
            objects.push_back(temp);
        }
    }

    int numberOfLightSources;
    readScene>>numberOfLightSources;

    cout<<"Light:"<<endl;
    cout<<numberOfLightSources<<endl;

    for(int i=0;i<numberOfLightSources;i++){
        vector3 light;
        readScene>>light.x>>light.y>>light.z;
        light.printVector();
        lights.push_back(light);
    }

    Object *floorTemp = new Floor(1000,20,useTexture);
    floorTemp->setCoEfficients(0.4,0.2,0.2,0.2);
    floorTemp->setShine(1);
    objects.push_back(floorTemp);

    readScene.close();
}

void freeMemory(){
    for(int i=0;i<objects.size();i++){
        delete objects[i];
    }

    cout<<"Memory Freed!!"<<endl;

}




int main(int argc, char **argv){
    //Ray Tracing
    //loadTestData();
    loadActualData();

	glutInit(&argc,argv);
	glutInitWindowSize(windowWidth, windowHeight);
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

	freeMemory();
	return 0;

}

