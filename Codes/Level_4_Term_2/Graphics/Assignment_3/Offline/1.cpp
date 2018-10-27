#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include "bitmap_image.hpp"
using namespace std;

ifstream config;
ifstream stage3;
ofstream bufferText;

double screenWidth = 0;
double screenHeight = 0;
double x_right_limit = 0;
double x_left_limit = 0;
double y_top_limit = 0;
double y_bottom_limit = 0;
double z_front = 0;
double z_rear = 0;


double dx = 0;
double dy = 0;
double Top_y = 0;
double Left_x = 0;
double z_max = 0;

double **zBuffer;
bitmap_image *image;




class Point{
public:
    double x;
    double y;
    double z;
};

class Triangle{
public:
    Point points[3];
    int color[3];

    Triangle(Point point1,Point point2,Point point3){
        points[0] = point1;
        points[1] = point2;
        points[2] = point3;

        color[0] = rand()%256;
        color[1] = rand()%256;
        color[2] = rand()%256;
    }

    void printTriangleData(){
        cout<<endl;
        cout<<"Points 1: "<<points[0].x<<" "<<points[0].y<<" "<<points[0].z<<endl;
        cout<<"Points 2: "<<points[1].x<<" "<<points[1].y<<" "<<points[1].z<<endl;
        cout<<"Points 3: "<<points[2].x<<" "<<points[2].y<<" "<<points[2].z<<endl;
        cout<<"Color: "<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
        cout<<endl;
    }
};



vector <Triangle*> trianglesList;






void readConfig(){
    config.open("config.txt");
    config>>screenWidth;
    config>>screenHeight;
    config>>x_left_limit;
    x_right_limit = -x_left_limit;
    config>>y_bottom_limit;
    y_top_limit = -y_bottom_limit;
    config>>z_front;
    config>>z_rear;
}


void readTriangle(){
    stage3.open("stage3.txt");
    cout<<"Reading triangles: "<<endl;

    while(!stage3.eof()){
        Point* points = new Point[3];

        for(int i=0;i<3;i++){
           stage3>>points[i].x>>points[i].y>>points[i].z;
           cout<<points[i].x<<" "<<points[i].y<<" "<<points[i].z<<endl;
        }


        Triangle* triangle = new Triangle(points[0],points[1],points[2]);
        cout<<"Okay"<<endl;

        trianglesList.push_back(triangle);
    }
}


void initializeBuffer(){

    dx = (double)(x_right_limit-x_left_limit)/(double)screenWidth;
    dy = (double)(y_top_limit-y_bottom_limit)/(double)screenHeight;

    Top_y = y_top_limit-(double)dy/(double)2;
    Left_x = x_left_limit + (double)dx/(double)2;

    z_max = z_rear;

    zBuffer = new double*[(int)screenHeight];
    for(int i=0;i<screenHeight;i++){
        zBuffer[i] = new double[(int)screenWidth];
    }

    for(int i=0;i<screenHeight;i++){
        for(int j=0;j<screenWidth;j++){
            zBuffer[i][j]=z_max;
        }
    }

    image = new bitmap_image(screenWidth,screenHeight);
    for(int i=0;i<screenWidth;i++){
        for(int j=0;j<screenHeight;j++){
            image->set_pixel(i,j,0,0,0);
        }
    }
}



void save(){
    image->save_image("1.bmp");

    bufferText.open("z_buffer.txt");

    bufferText<<std::fixed<<std::setprecision(6);
    for(int i=0;i<screenHeight;i++){
        for(int j=0;j<screenWidth;j++){
            if(zBuffer[i][j]<z_max){
                bufferText<<zBuffer[i][j]<<"\t";
            }
        }
        bufferText<<endl;
    }
}

void freeMemory(){
    delete zBuffer;
    delete image;

    for(int i=0;i<trianglesList.size();i++){
        delete trianglesList[i];
    }

    config.close();
    stage3.close();
    bufferText.close();
}

void printConfigData(){
    double screenWidth = 0;
    double screenHeight = 0;
    double x_right_limit = 0;
    double x_left_limit = 0;
    double y_top_limit = 0;
    double y_bottom_limit = 0;
    double z_front = 0;
    double z_rear = 0;

    cout<<"Config Data"<<endl;

    cout<<endl;
    cout<<"Screen Width,Height: "<<screenWidth<<" "<<screenHeight<<endl;
    cout<<"X left,right limit : "<<x_left_limit<<" "<<x_right_limit<<endl;
    cout<<"Y bottom,top limit : "<<y_bottom_limit<<" "<<y_top_limit<<endl;
    cout<<"Z front,rear : "<<z_front<<" "<<z_rear<<endl;
    cout<<endl;


}

void printTriangleData(){
    cout<<"Triangle Data"<<endl;
    for(int i=0;i<trianglesList.size();i++){
        trianglesList[i]->printTriangleData();
    }
    cout<<endl;
}


void printBufferData(){
    cout<<"Buffer Data: "<<endl;
    cout<<endl;
    cout<<"dx "<<dx<<endl;
    cout<<"dy "<<dy<<endl;
    cout<<"Top y: "<<Top_y<<endl;
    cout<<"Left x: "<<Left_x<<endl;
    cout<<"Z Max: "<<z_max<<endl;
    cout<<endl;
}

void readData(){
    readConfig();
    readTriangle();
}

double rowToY(int r){
    return Top_y- r*dy;
}

double colToX(int c){
    return Left_x+c*dx;
}

int yToRow(double y){
    double ret = (double)(Top_y-y)/(double)dy;
    ret = round(ret);
    int retInt = (int)ret;
    return retInt;
}

int xToCol(double x){
    double ret = (double)(x-Left_x)/(double)dx;
    ret = round(ret);
    int retInt = (int)ret;
    return retInt;
}

int main(){
    readData();

    printConfigData();
    printTriangleData();

    initializeBuffer();

    printBufferData();


    cout<<"Algorithm starts!!"<<endl;
    for(int t=0;t<trianglesList.size();t++){
        Triangle* tri = trianglesList[t];
        //cout<<"Triangle "<<t+1<<endl;
        //cout<<"Step 1"<<endl;

        double top_scanline = 0;
        double bottom_scanline = 0;

        top_scanline = max(tri->points[0].y,max(tri->points[1].y,tri->points[2].y));
        if(top_scanline>y_top_limit)top_scanline = y_top_limit;
        bottom_scanline = min(tri->points[0].y,min(tri->points[1].y,tri->points[2].y));
        if(bottom_scanline<y_bottom_limit)bottom_scanline = y_bottom_limit;


        //cout<<"Scanlines: "<<top_scanline<<" "<<bottom_scanline<<endl;
        int top_row = yToRow(top_scanline);
        int bottom_row = yToRow(bottom_scanline);

        //cout<<top_scanline<<" "<<bottom_scanline<<" "<<top_row<<" "<<bottom_row<<endl;
        for(int i=top_row;i<=bottom_row;i++){
            //cout<<"Step 2"<<endl;
            double scanline = rowToY(i);


            if(i==top_row && scanline>=top_scanline){
                scanline = top_scanline;
            }

            if(i==bottom_row && scanline<=bottom_scanline){
                scanline = bottom_scanline;
            }


            double x1,z1,x2,z2,x3,z3;
            //cout<<"Y scanned "<<scanline<<endl;

            //Finding out which intersect
            bool pointIntersect[] = {false,false,false};


            //AB or 01

            if(scanline>=tri->points[0].y && scanline<=tri->points[1].y)pointIntersect[0]=true;
            if(scanline<=tri->points[0].y && scanline>=tri->points[1].y)pointIntersect[0]=true;

            //AC or 02

            if(scanline>=tri->points[0].y && scanline<=tri->points[2].y)pointIntersect[1]=true;
            if(scanline<=tri->points[0].y && scanline>=tri->points[2].y)pointIntersect[1]=true;


            //BC or 12

            if(scanline>=tri->points[1].y && scanline<=tri->points[2].y)pointIntersect[2]=true;
            if(scanline<=tri->points[1].y && scanline>=tri->points[2].y)pointIntersect[2]=true;


            //cout<<pointIntersect[0]<<" "<<pointIntersect[1]<<" "<<pointIntersect[2]<<endl;




            double xFound[] = {-1,-1,-1};
            double zFound[] = {-1,-1,-1};

            vector <double> xLimits;
            vector <double> zLimits;



            if(pointIntersect[0]){
                Point directionVector;
                directionVector.x = tri->points[1].x - tri->points[0].x;
                directionVector.y = tri->points[1].y - tri->points[0].y;
                directionVector.z = tri->points[1].z - tri->points[0].z;


                double lambda = (double)(scanline-tri->points[0].y)/(double)(directionVector.y);
                xFound[0] = tri->points[0].x + lambda*directionVector.x;
                zFound[0] = tri->points[0].z + lambda*directionVector.z;

                xLimits.push_back(xFound[0]);
                zLimits.push_back(zFound[0]);
            }

            if(pointIntersect[1]){
                Point directionVector;
                directionVector.x = tri->points[2].x - tri->points[0].x;
                directionVector.y = tri->points[2].y - tri->points[0].y;
                directionVector.z = tri->points[2].z - tri->points[0].z;


                double lambda = (double)(scanline-tri->points[0].y)/(double)(directionVector.y);
                xFound[1] = tri->points[0].x + lambda*directionVector.x;
                zFound[1] = tri->points[0].z + lambda*directionVector.z;

                xLimits.push_back(xFound[1]);
                zLimits.push_back(zFound[1]);
            }

            if(pointIntersect[2]){
                Point directionVector;
                directionVector.x = tri->points[2].x - tri->points[1].x;
                directionVector.y = tri->points[2].y - tri->points[1].y;
                directionVector.z = tri->points[2].z - tri->points[1].z;


                double lambda = (double)(scanline-tri->points[1].y)/(double)(directionVector.y);
                xFound[2] = tri->points[1].x + lambda*directionVector.x;
                zFound[2] = tri->points[1].z + lambda*directionVector.z;

                xLimits.push_back(xFound[2]);
                zLimits.push_back(zFound[2]);
            }


            //cout<<"x array:"<<endl;
            //for(int h=0;h<xLimits.size();h++)cout<<xLimits[h]<<" ";
            //cout<<endl;
            //cout<<"z array:"<<endl;
            //for(int h=0;h<zLimits.size();h++)cout<<zLimits[h]<<" ";
            //cout<<endl;






            double left_intersecting_column = 0;
            double right_intersecting_column = 0;



            double maxX = -999999999;
            double maxXerZ = -999999999;

            double minX = 999999999;
            double minXerZ = 999999999;


            for(int a=0;a<xLimits.size();a++){
                if(xLimits[a]>maxX){
                    maxX = xLimits[a];
                    maxXerZ = zLimits[a];
                }

                if(xLimits[a]<minX){
                    minX = xLimits[a];
                    minXerZ = zLimits[a];
                }
            }




            left_intersecting_column = minX;
            if(left_intersecting_column<x_left_limit)left_intersecting_column = x_left_limit;
            right_intersecting_column = maxX;
            if(right_intersecting_column>x_right_limit)right_intersecting_column = x_right_limit;


            int Left_column = xToCol(left_intersecting_column);
            int Right_column = xToCol(right_intersecting_column);

            if(Left_column<0)Left_column = 0;
            if(Right_column>screenWidth)Right_column=screenWidth;


            Point directionVectorForBuffer;
            directionVectorForBuffer.x = right_intersecting_column - left_intersecting_column;
            directionVectorForBuffer.y = -699;
            directionVectorForBuffer.z = maxXerZ - minXerZ;

            //cout<<left_intersecting_column<<" "<<right_intersecting_column<<" "<<Left_column<<" "<<Right_column<<endl;
            //break;
            for(int j=Left_column;j<=Right_column;j++){
                //cout<<"Hello"<<endl;
                double corresponding_x = colToX(j);

                double lambda = (double)(corresponding_x-left_intersecting_column)/(double)directionVectorForBuffer.x;
                double zNew = minXerZ + lambda*directionVectorForBuffer.z;

                if(zNew<zBuffer[i][j]){
                    //cout<<zBuffer[i][j]<<" "<<zNew;
                    zBuffer[i][j] = zNew;
                    image->set_pixel(j,i,tri->color[0],tri->color[1],tri->color[2]);
                }

            }


        }
        //cout<<endl<<endl;
    }
    cout<<"Algorithm ends!!"<<endl;




    save();
    freeMemory();




}
