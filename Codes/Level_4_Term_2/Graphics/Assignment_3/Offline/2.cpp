#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include "bitmap_image.hpp"



#define INF 999999999
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

bitmap_image *image;




class Point{
public:
    double x;
    double y;
    double z;

    void printPoint(){
        cout<<endl;
        cout<<x<<" "<<y<<" "<<z<<endl;
        cout<<endl;
    }
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

class edgeNode{
public:
    double xAtYMin;
    double xAtYMax;
    double yMin;
    double yMax;
    double delX;
    double currentX;
    int ID;



    double findX(double yGiven){
        //cout<<"Changing X for y invalid: "<<yGiven<<endl;
        Point directionVector;
        directionVector.x = xAtYMax - xAtYMin;
        directionVector.y = yMax - yMin;
        directionVector.z = 0;


        double lambda = (double)(yGiven - yMin)/(double)(directionVector.y);
        double xFound = xAtYMin + lambda*directionVector.x;
        //cout<<"New x: "<<xFound<<endl;
        return xFound;
    }

    double findY(double xGiven){
        //cout<<"Changing Y for x invalid: "<<xGiven<<endl;
        Point directionVector;
        directionVector.x = xAtYMax - xAtYMin;
        directionVector.y = yMax - yMin;
        directionVector.z = 0;


        double lambda = (double)(xGiven - xAtYMin)/(double)(directionVector.x);
        double yFound = yMin + lambda*directionVector.y;
        //cout<<"New y: "<<yFound<<endl;
        return yFound;
    }
};


class polygonNode{
public:
    int ID;
    int color[3];
    double A;
    double B;
    double C;
    double D;
    int inOut=0;



    double calculateZ(double x,double y){
        double z = (double)(A*x + B*y +D)/(double)(-C);
        return z;
    }
};

vector <Triangle*> trianglesList;

vector <edgeNode*> *edgeTable;
vector <polygonNode*> polygonTable;

vector <edgeNode*> activeEdgeTable;
vector <polygonNode*> activePolygonTable;











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

    while(!stage3.eof()){
        Point* points = new Point[3];

        for(int i=0;i<3;i++){
           stage3>>points[i].x>>points[i].y>>points[i].z;
        }

        Triangle* triangle = new Triangle(points[0],points[1],points[2]);

        trianglesList.push_back(triangle);

    }
}


void initializeConfigAndImage(){

    dx = (double)(x_right_limit-x_left_limit)/(double)screenWidth;
    dy = (double)(y_top_limit-y_bottom_limit)/(double)screenHeight;

    Top_y = y_top_limit-(double)dy/(double)2;
    Left_x = x_left_limit + (double)dx/(double)2;

    z_max = z_rear;

    image = new bitmap_image(screenWidth,screenHeight);
    for(int i=0;i<screenWidth;i++){
        for(int j=0;j<screenHeight;j++){
            image->set_pixel(i,j,0,0,0);
        }
    }
}


Point calculatePlaneEquation(Point* p){
    Point directionVector1;
    directionVector1.x = p[0].x - p[1].x;
    directionVector1.y = p[0].y - p[1].y;
    directionVector1.z = p[0].z - p[1].z;

    //directionVector1.printPoint();


    Point directionVector2;
    directionVector2.x = p[2].x - p[1].x;
    directionVector2.y = p[2].y - p[1].y;
    directionVector2.z = p[2].z - p[1].z;

    //directionVector2.printPoint();

    Point planeEquation;
    planeEquation.x = directionVector1.y * directionVector2.z - directionVector1.z * directionVector2.y;
    planeEquation.y = -(directionVector1.x * directionVector2.z - directionVector1.z * directionVector2.x);
    planeEquation.z = directionVector1.x * directionVector2.y - directionVector2.x * directionVector1.y;

    return planeEquation;
}







void save(){
    image->save_image("2.bmp");
}

void freeMemory(){
    delete image;

    for(int i=0;i<trianglesList.size();i++){
        delete trianglesList[i];
    }
    config.close();
    stage3.close();
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
    cout<<"Parameter Data: "<<endl;
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

void putIntoEdgeTable(edgeNode* tempNode){
    int yMin = tempNode->yMin;
    int xAtYMin = tempNode->xAtYMin;

    if(edgeTable[yMin].size()==0){
        edgeTable[yMin].push_back(tempNode);
    }
    else{
        int insertPoint = 0;
        for(int i=0;i<edgeTable[yMin].size();i++){
            if(xAtYMin<(int)edgeTable[yMin][i]->xAtYMin){
                break;
            }
            insertPoint++;
        }

        if(insertPoint==edgeTable[yMin].size()){
            edgeTable[yMin].push_back(tempNode);
        }
        else{
            edgeTable[yMin].insert(edgeTable[yMin].begin() + insertPoint, tempNode);
        }
    }
}


void initializeEdgePolygonTable(){

    edgeTable = new vector <edgeNode*> [(int)screenHeight];
    for(int t=0;t<trianglesList.size();t++){
        Triangle* tri = trianglesList[t];

        polygonNode *tempPolygonNode = new polygonNode;
        tempPolygonNode->ID = t;
        tempPolygonNode->color[0] = tri->color[0];
        tempPolygonNode->color[1] = tri->color[1];
        tempPolygonNode->color[2] = tri->color[2];

        Point planeEquation = calculatePlaneEquation(tri->points);
        tempPolygonNode->A = planeEquation.x;
        tempPolygonNode->B = planeEquation.y;
        tempPolygonNode->C = planeEquation.z;
        tempPolygonNode->D = tri->points[0].x * tempPolygonNode->A + tri->points[0].y * tempPolygonNode->B + tri->points[0].z * tempPolygonNode->C;
        tempPolygonNode->D = -tempPolygonNode->D;

        tempPolygonNode->inOut = 0;

        polygonTable.push_back(tempPolygonNode);



        //Edge 01
    {
        double x1 = xToCol(tri->points[0].x);
        double y1 = yToRow(tri->points[0].y);
        double x2 = xToCol(tri->points[1].x);
        double y2 = yToRow(tri->points[1].y);

        edgeNode *tempEdgeNode = new edgeNode;

        if(y1<y2){
            tempEdgeNode->xAtYMin = x1;
            tempEdgeNode->yMin = y1;
            tempEdgeNode->xAtYMax = x2;
            tempEdgeNode->yMax = y2;
        }
        else{
            tempEdgeNode->xAtYMin = x2;
            tempEdgeNode->yMin = y2;
            tempEdgeNode->xAtYMax = x1;
            tempEdgeNode->yMax = y1;

        }

        tempEdgeNode->ID = t;





        double m = (double)(y2-y1)/(double)(x2-x1);
        tempEdgeNode->delX = (double)1/(double)m;
        tempEdgeNode->currentX = tempEdgeNode->xAtYMin;

        bool invalid = (tempEdgeNode->yMax<0) || (tempEdgeNode->yMin>screenHeight) || (max(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)<0) || (min(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)>screenWidth) || (isinf(tempEdgeNode->delX ));
        if(!invalid){

            if(tempEdgeNode->yMin<0){
                double xNew = tempEdgeNode->findX(0);
                tempEdgeNode->yMin = 0;
                tempEdgeNode->xAtYMin = xNew;
                tempEdgeNode->currentX = xNew;
                //cout<<" We have new values: "<<tempEdgeNode->xAtYMin<<" "<<tempEdgeNode->yMin<<endl;
            }

            if(tempEdgeNode->yMax>screenHeight){
                double xNew = tempEdgeNode->findX(screenHeight);
                tempEdgeNode->yMax = screenHeight;
                tempEdgeNode->xAtYMax = xNew;
            }



            putIntoEdgeTable(tempEdgeNode);
        }
    }




        //Edge 02
    {
        double x1 = xToCol(tri->points[0].x);
        double y1 = yToRow(tri->points[0].y);
        double x2 = xToCol(tri->points[2].x);
        double y2 = yToRow(tri->points[2].y);

        edgeNode *tempEdgeNode = new edgeNode;

        if(y1<y2){
            tempEdgeNode->xAtYMin = x1;
            tempEdgeNode->yMin = y1;
            tempEdgeNode->xAtYMax = x2;
            tempEdgeNode->yMax = y2;
        }
        else{
            tempEdgeNode->xAtYMin = x2;
            tempEdgeNode->yMin = y2;
            tempEdgeNode->xAtYMax = x1;
            tempEdgeNode->yMax = y1;
        }

        tempEdgeNode->ID = t;

        double m = (double)(y2-y1)/(double)(x2-x1);
        tempEdgeNode->delX = (double)1/(double)m;
        tempEdgeNode->currentX = tempEdgeNode->xAtYMin;
        bool invalid = (tempEdgeNode->yMax<0) || (tempEdgeNode->yMin>screenHeight) || (max(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)<0) || (min(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)>screenWidth) || (isinf(tempEdgeNode->delX ));
        if(!invalid){

            if(tempEdgeNode->yMin<0){
                double xNew = tempEdgeNode->findX(0);
                tempEdgeNode->yMin = 0;
                tempEdgeNode->xAtYMin = xNew;
                tempEdgeNode->currentX = xNew;
                //cout<<" We have new values: "<<tempEdgeNode->xAtYMin<<" "<<tempEdgeNode->yMin<<endl;
            }

            if(tempEdgeNode->yMax>screenHeight){
                double xNew = tempEdgeNode->findX(screenHeight);
                tempEdgeNode->yMax = screenHeight;
                tempEdgeNode->xAtYMax = xNew;
            }




            putIntoEdgeTable(tempEdgeNode);
        }
    }



        //Edge 03
    {
        double x1 = xToCol(tri->points[1].x);
        double y1 = yToRow(tri->points[1].y);
        double x2 = xToCol(tri->points[2].x);
        double y2 = yToRow(tri->points[2].y);

        edgeNode *tempEdgeNode = new edgeNode;

        if(y1<y2){
            tempEdgeNode->xAtYMin = x1;
            tempEdgeNode->yMin = y1;
            tempEdgeNode->xAtYMax = x2;
            tempEdgeNode->yMax = y2;
        }
        else{
            tempEdgeNode->xAtYMin = x2;
            tempEdgeNode->yMin = y2;
            tempEdgeNode->xAtYMax = x1;
            tempEdgeNode->yMax = y1;
        }

        tempEdgeNode->ID = t;

        double m = (double)(y2-y1)/(double)(x2-x1);
        tempEdgeNode->delX = (double)1/(double)m;
        tempEdgeNode->currentX = tempEdgeNode->xAtYMin;
        bool invalid = (tempEdgeNode->yMax<0) || (tempEdgeNode->yMin>screenHeight) || (max(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)<0) || (min(tempEdgeNode->xAtYMin,tempEdgeNode->xAtYMax)>screenWidth) || (isinf(tempEdgeNode->delX ));
        if(!invalid){

            if(tempEdgeNode->yMin<0){
                double xNew = tempEdgeNode->findX(0);
                tempEdgeNode->yMin = 0;
                tempEdgeNode->xAtYMin = xNew;
                tempEdgeNode->currentX = xNew;
                //cout<<" We have new values: "<<tempEdgeNode->xAtYMin<<" "<<tempEdgeNode->yMin<<endl;
            }

            if(tempEdgeNode->yMax>screenHeight){
                double xNew = tempEdgeNode->findX(screenHeight);
                tempEdgeNode->yMax = screenHeight;
                tempEdgeNode->xAtYMax = xNew;
            }



            putIntoEdgeTable(tempEdgeNode);
        }


    }



    }
}



void printEdgeAndPolygonTable(){
    cout<<endl<<endl;
    cout<<"Polygon Table:"<<endl;
    for(int i=0;i<polygonTable.size();i++){
        polygonNode *tempPolygonNode = polygonTable[i];
        cout<<"Id: "<<tempPolygonNode->ID<<endl;
        cout<<"Colors: "<<tempPolygonNode->color[0]<<" "<<tempPolygonNode->color[1]<<" "<<tempPolygonNode->color[2]<<endl;
        cout<<"A B C D: "<<tempPolygonNode->A<<" "<<tempPolygonNode->B<<" "<<tempPolygonNode->C<<" "<<tempPolygonNode->D<<endl;
        cout<<"InOut: "<<tempPolygonNode->inOut<<endl;
    }

    cout<<endl<<"Edge Table:"<<endl;
    for(int i=0;i<screenHeight;i++){
        for(int j=0;j<edgeTable[i].size();j++){
            cout<<i<<":"<<endl;
            cout<<"X at Ymin: "<<edgeTable[i][j]->xAtYMin<<" "<<"Ymin: "<<edgeTable[i][j]->yMin<<" "<<"X at Ymax: "<<edgeTable[i][j]->xAtYMax<<" "<<"Y max: "<<edgeTable[i][j]->yMax<<" "<<"DelX: "<<edgeTable[i][j]->delX<<" "<<"Current X: "<<edgeTable[i][j]->currentX<<" "<<"ID: "<<edgeTable[i][j]->ID<<endl;
        }
    }
    cout<<endl<<endl;
}

void printAEL(){
    cout<<"Printing AEL"<<endl<<endl;
    for(int i=0;i<activeEdgeTable.size();i++){
        cout<<"X at Ymin: "<<activeEdgeTable[i]->xAtYMin<<" "<<"Ymin: "<<activeEdgeTable[i]->yMin<<" "<<"X at Ymax: "<<activeEdgeTable[i]->xAtYMax<<" "<<"Y max: "<<activeEdgeTable[i]->yMax<<" "<<"DelX: "<<activeEdgeTable[i]->delX<<" "<<"Current X: "<<activeEdgeTable[i]->currentX<<" "<<"ID: "<<activeEdgeTable[i]->ID<<endl;
    }
    cout<<endl<<endl;
}

void printAPL(){
    cout<<"Printing APL"<<endl<<endl;
    for(int i=0;i<activePolygonTable.size();i++){
        polygonNode *tempPolygonNode = activePolygonTable[i];
        cout<<"Id: "<<tempPolygonNode->ID<<endl;
        cout<<"Colors: "<<tempPolygonNode->color[0]<<" "<<tempPolygonNode->color[1]<<" "<<tempPolygonNode->color[2]<<endl;
        cout<<"A B C D: "<<tempPolygonNode->A<<" "<<tempPolygonNode->B<<" "<<tempPolygonNode->C<<" "<<tempPolygonNode->D<<endl;
        cout<<"InOut: "<<tempPolygonNode->inOut<<endl;
    }
    cout<<endl<<endl;
}


void sortAEL(){
    for(int i=0;i<activeEdgeTable.size();i++){
        int minimumIndex = i;
        for(int j=i+1;j<activeEdgeTable.size();j++){
            if(activeEdgeTable[j]->currentX<activeEdgeTable[minimumIndex]->currentX){
                minimumIndex = j;
            }
        }
        edgeNode* temp = activeEdgeTable[i];
        activeEdgeTable[i] = activeEdgeTable[minimumIndex];
        activeEdgeTable[minimumIndex] = temp;
    }
}


void updateAPL(polygonNode* node){
    bool alreadyExists = false;
    for(int i=0;i<activePolygonTable.size();i++){
        if(activePolygonTable[i]->ID==node->ID){
            alreadyExists=true;
            break;
        }
    }

    if(!alreadyExists){
        activePolygonTable.push_back(node);
    }
}

int smallestPolygon(double pixelX,double pixelY){
    double actualX = colToX((int)pixelX);
    double actualY = rowToY((int)pixelY);


    double minimumZ = 9999999999;
    int minimumIndex = -1;
    //cout<<endl<<endl;

    for(int i=0;i<activePolygonTable.size();i++){
        double zCalculated = activePolygonTable[i]->calculateZ(actualX,actualY);
        //cout<<"XY of matching: "<<pixelX<<" "<<pixelY<<endl;
        //cout<<"At polygon ID "<<activePolygonTable[i]->ID<<"z found: "<<zCalculated<<endl;
        if(zCalculated<minimumZ && activePolygonTable[i]->inOut==1){
            minimumZ = zCalculated;
            minimumIndex = i;
            //cout<<"New minimum: "<<minimumZ<<" "<<minimumIndex<<endl;
        }
    }
    //cout<<endl<<endl;
    return minimumIndex;
}

void resetAPL(){
    for(int i=0;i<activePolygonTable.size();i++){
        activePolygonTable[i]->inOut = 0;
    }
    activePolygonTable.clear();
}


int main(){
    readData();

    printConfigData();
    printTriangleData();

    initializeConfigAndImage();

    printBufferData();

    initializeEdgePolygonTable();
    printEdgeAndPolygonTable();




    /*
    updateAPL(polygonTable[edgeTable[0][0]->ID]);
    updateAPL(polygonTable[edgeTable[83][0]->ID]);
    printAPL();

    int i = smallestPolygon(20.0,250.0);
    cout<<i<<endl;
    */







    //Main Algorithm
    cout<<"Scan line algorithm started: "<<endl;
    for(int scanline=0;scanline<screenHeight;scanline++){
        //cout<<"Starting "<<scanline<<endl;
        for(int i=0;i<edgeTable[scanline].size();i++){
            activeEdgeTable.push_back(edgeTable[scanline][i]);
        }
        sortAEL();
        //printAEL();
        //break;
        //cout<<"Ol"<<(int)activeEdgeTable.size()-1<<endl;
        for(int i=0;i<(int)activeEdgeTable.size()-1;i++){
            //cout<<"Ozo"<<endl;
            polygonTable[activeEdgeTable[i]->ID]->inOut = 1-polygonTable[activeEdgeTable[i]->ID]->inOut;
            updateAPL(polygonTable[activeEdgeTable[i]->ID]);
            //cout<<"Ola1"<<endl;

            //Determine polygon P
            if(activePolygonTable.size()==0)continue;
            int polygonNumber = smallestPolygon(activeEdgeTable[i]->currentX,scanline);
            if(polygonNumber==-1)continue;
            //cout<<"Ola2"<<endl;


            //Color pixels
            int leftLimit = (int)activeEdgeTable[i]->currentX;
            int rightLimit = (int)activeEdgeTable[i+1]->currentX;
            //cout<<"Draw from "<<leftLimit<<" to "<<rightLimit<<" using color of "<<polygonNumber<<endl;
            if(leftLimit<0)leftLimit = 0;
            if(rightLimit>screenWidth)rightLimit = screenWidth;
            //cout<<"Ola3"<<endl;

            for(int j=leftLimit;j<rightLimit;j++){
                image->set_pixel(j,scanline,activePolygonTable[polygonNumber]->color[0],activePolygonTable[polygonNumber]->color[1],activePolygonTable[polygonNumber]->color[2]);
            }
        }



        for(int i=0;i<activeEdgeTable.size();i++){
            int temp = (int)round(activeEdgeTable[i]->yMax);
            if(scanline+1 >= temp ){
                //cout<<"Leaving ID: "<<i<<" "<<activeEdgeTable[i]->ID<<" "<<activeEdgeTable[i]->xAtYMax<<" "<<activeEdgeTable[i]->yMax<<endl;
                activeEdgeTable[i] = 0;
            }
        }
        vector <edgeNode*> tempEdgeTable;
        for(int i=0;i<activeEdgeTable.size();i++){
            if(activeEdgeTable[i]!=0){
                tempEdgeTable.push_back(activeEdgeTable[i]);
            }
        }
        activeEdgeTable.clear();
        for(int i=0;i<tempEdgeTable.size();i++){
            activeEdgeTable.push_back(tempEdgeTable[i]);
        }






        for(int i=0;i<activeEdgeTable.size();i++){
            activeEdgeTable[i]->currentX+=activeEdgeTable[i]->delX;
        }
        resetAPL();
        sortAEL();
        //cout<<endl<<endl;
    }
    cout<<"Scan-line algorithm ended."<<endl;






    save();
    freeMemory();




}
