#include <iostream>
#include <fstream>
#include <stack>
#include <math.h>
#include <iomanip>

#define PI (2*acos(0.0))

using namespace std;

class vec{
public:
    double x;
    double y;
    double z;

    vec(double x,double y,double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void display(){
        cout<<"Vector: "<<this->x<<" "<<this->y<<" "<<this->z<<endl;
    }

    void normalize(){
        double sum = this->x * this->x + this->y * this->y  + this->z * this->z;
        sum = sqrt(sum);
        this->x = this->x/sum;
        this->y = this->y/sum;
        this->z = this->z/sum;
    }

    void printVector(){
        cout<<"Vector: "<<this->x<<" "<<this->y<<" "<<this->z<<endl;
    }
};



double eyeX = 0;
double eyeY = 0;
double eyeZ = 0;

double lookX = 0;
double lookY = 0;
double lookZ = 0;

double upX = 0;
double upY = 0;
double upZ = 0;

double fovY = 0;
double aspectRatio = 0;
double near = 0;
double far  = 0;

vec l(0,0,0);
vec r(0,0,0);
vec u(0,0,0);

ifstream scene;
ofstream stage1;
ofstream stage2;
ofstream stage3;
string filePath = "scene.txt";

stack <double**> transformationStack;

double** transformationMatrix;
double** viewMatrix;
double** projectionMatrix;




void loadSceneFile(string filepath){
    scene.open(filepath.c_str());
}

void loadWriteFiles(){
    stage1.open("stage1.txt");
    stage2.open("stage2.txt");
    stage3.open("stage3.txt");
}


void initializeVariables(){
    scene>>eyeX;
    scene>>eyeY;
    scene>>eyeZ;

    scene>>lookX;
    scene>>lookY;
    scene>>lookZ;

    scene>>upX;
    scene>>upY;
    scene>>upZ;

    scene>>fovY;
    scene>>aspectRatio;
    scene>>near;
    scene>>far;

    transformationMatrix = new double*[4];

    for(int i=0;i<4;i++){
        transformationMatrix[i]=new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            transformationMatrix[i][j]=0;
        }
    }

    for(int i=0;i<4;i++){
        transformationMatrix[i][i]=1;
    }





    viewMatrix = new double*[4];

    for(int i=0;i<4;i++){
        viewMatrix[i]=new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            viewMatrix[i][j]=0;
        }
    }

    for(int i=0;i<4;i++){
        viewMatrix[i][i]=1;
    }


    projectionMatrix = new double*[4];

    for(int i=0;i<4;i++){
        projectionMatrix[i]=new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            projectionMatrix[i][j]=0;
        }
    }


}

void displayViewVariables(){
    cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<endl;
    cout<<lookX<<" "<<lookY<<" "<<lookZ<<endl;
    cout<<upX<<" "<<upY<<" "<<upZ<<endl;
    cout<<fovY<<" "<<aspectRatio<<" "<<near<<" "<<far<<endl;
}

double** createTranslationMatrix(double tx,double ty,double tz){
    double **matrix = new double*[4];

    for(int i=0;i<4;i++){
        matrix[i]= new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }

    for(int i=0;i<4;i++){
        matrix[i][i]=1;
    }

    matrix[0][3] = tx;
    matrix[1][3] = ty;
    matrix[2][3] = tz;

    return matrix;

}

double** createScaleMatrix(double sx,double sy,double sz){
    double **matrix = new double*[4];

    for(int i=0;i<4;i++){
        matrix[i]= new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }

    matrix[0][0]=sx;
    matrix[1][1]=sy;
    matrix[2][2]=sz;
    matrix[3][3]=1;

    return matrix;

}



void printMatrix(double** matrix){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printPoint(double* point){
    for(int i=0;i<4;i++){
        cout<<point[i]<<endl;
    }
}

double dotProduct(vec a,vec x){
    double answer = x.x * a.x + x.y *a.y + x.z * a.z;
    return answer;
}

vec crossProduct(vec a,vec x){
    vec cross(0,0,0);

    cross.x = a.y * x.z - a.z * x.y;
    cross.y = -(a.x * x.z - a.z * x.x);
    cross.z = a.x * x.y - x.x * a.y;

    return cross;
}

vec RodriguesFormula(vec x,vec a,double theta){
    vec firstPortion(0,0,0);
    vec secondPortion(0,0,0);
    vec thirdPortion(0,0,0);
    vec finalVector (0,0,0);

    double cosineTheta = cos((double)theta/(double)360 * 2 * PI);
    double sineTheta = sin((double)theta/(double)360 * 2 * PI);

    //First portion
    firstPortion.x = cosineTheta * x.x;
    firstPortion.y = cosineTheta * x.y;
    firstPortion.z = cosineTheta * x.z;

    //Second Portion
    double dotax = dotProduct(a,x);

    secondPortion.x = (1-cosineTheta) * dotax * a.x;
    secondPortion.y = (1-cosineTheta) * dotax * a.y;
    secondPortion.z = (1-cosineTheta) * dotax * a.z;

    //Third Portion
    vec cross = crossProduct(a,x);

    thirdPortion.x = sineTheta * cross.x;
    thirdPortion.y = sineTheta * cross.y;
    thirdPortion.z = sineTheta * cross.z;


    //Final Portion
    finalVector.x = firstPortion.x + secondPortion.x + thirdPortion.x;
    finalVector.y = firstPortion.y + secondPortion.y + thirdPortion.y;
    finalVector.z = firstPortion.z + secondPortion.z + thirdPortion.z;

    return finalVector;
}


double** createRotationMatrix(double angle,double ax,double ay,double az){
    double **matrix = new double*[4];

    for(int i=0;i<4;i++){
        matrix[i]= new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }

    vec a(ax,ay,az);
    vec iUnitVector(1,0,0);
    vec jUnitVector(0,1,0);
    vec kUnitVector(0,0,1);

    a.normalize();

    vec c1 = RodriguesFormula(iUnitVector,a,angle);
    vec c2 = RodriguesFormula(jUnitVector,a,angle);
    vec c3 = RodriguesFormula(kUnitVector,a,angle);

    matrix[0][0] = c1.x;
    matrix[0][1] = c2.x;
    matrix[0][2] = c3.x;

    matrix[1][0] = c1.y;
    matrix[1][1] = c2.y;
    matrix[1][2] = c3.y;

    matrix[2][0] = c1.z;
    matrix[2][1] = c2.z;
    matrix[2][2] = c3.z;

    matrix[3][3] = 1;

    return matrix;
}

void pushMatrix(){
    double **tempMatrix = new double*[4];

    for(int i=0;i<4;i++){
        tempMatrix[i] = new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tempMatrix[i][j] = transformationMatrix[i][j];
        }
    }

    transformationStack.push(tempMatrix);
}

void popMatrix(){
    double **tempMatrix = transformationStack.top();

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            transformationMatrix[i][j]=tempMatrix[i][j];
        }
    }

    transformationStack.pop();
}

void multiplyTransformationMatrix(double** transformation){
    double **tempMatrix = new double*[4];

    for(int i=0;i<4;i++){
        tempMatrix[i]= new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tempMatrix[i][j]=0;
        }
    }





    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                tempMatrix[i][j] += transformationMatrix[i][k] * transformation[k][j];
            }
        }
    }


    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            transformationMatrix[i][j] = tempMatrix[i][j];
        }
    }

}

double* applyTransformationMatrix(double* position){
    double *tempMatrix = new double[4];

    for(int i=0;i<4;i++){
        tempMatrix[i]=0;
    }



    for(int i=0;i<4;i++){
            for(int k=0;k<4;k++){
                tempMatrix[i]+= transformationMatrix[i][k] * position[k];
            }
    }


    return tempMatrix;

}

double* applyViewMatrix(double* position){
    double *tempMatrix = new double[4];

    for(int i=0;i<4;i++){
        tempMatrix[i]=0;
    }



    for(int i=0;i<4;i++){
            for(int k=0;k<4;k++){
                tempMatrix[i]+= viewMatrix[i][k] * position[k];
            }
    }


    return tempMatrix;

}

void setuplru(){
    //Set up l
    l.x = lookX-eyeX;
    l.y = lookY-eyeY;
    l.z = lookZ-eyeZ;

    l.normalize();

    //Set up r
    vec up(upX,upY,upZ);
    r = crossProduct(l,up);

    r.normalize();

    //Set up u
    u = crossProduct(r,l);

    //l.printVector();
    //r.printVector();
    //u.printVector();


}

double **getViewTranslationMatrix(){
    double ** viewTranslation = new double*[4];

    for(int i=0;i<4;i++){
        viewTranslation[i] = new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            viewTranslation[i][j]=0;
        }
    }

    for(int i=0;i<4;i++){
        viewTranslation[i][i]=1;
    }

    viewTranslation[0][3] = -eyeX;
    viewTranslation[1][3] = -eyeY;
    viewTranslation[2][3] = -eyeZ;

    return viewTranslation;
}

double **getViewRotationMatrix(){
    double ** viewRotation = new double*[4];

    for(int i=0;i<4;i++){
        viewRotation[i] = new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            viewRotation[i][j]=0;
        }
    }

    viewRotation[3][3]=1;

    viewRotation[0][0] = r.x;
    viewRotation[0][1] = r.y;
    viewRotation[0][2] = r.z;

    viewRotation[1][0] = u.x;
    viewRotation[1][1] = u.y;
    viewRotation[1][2] = u.z;

    viewRotation[2][0] = -l.x;
    viewRotation[2][1] = -l.y;
    viewRotation[2][2] = -l.z;



    return viewRotation;
}


void setUpViewMatrix(double** viewRotation,double** viewTranslation){
    double **tempMatrix = new double*[4];

    for(int i=0;i<4;i++){
        tempMatrix[i]= new double[4];
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tempMatrix[i][j]=0;
        }
    }




    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                tempMatrix[i][j] += viewRotation[i][k] * viewTranslation[k][j];
            }
        }
    }


    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            viewMatrix[i][j] = tempMatrix[i][j];
        }
    }


}

void initializeViewMatrix(){
    setuplru();

    double** viewTranslation = getViewTranslationMatrix();
    double** viewRotation = getViewRotationMatrix();

    /*
    cout<<"Translation Matrix:"<<endl;
    printMatrix(viewTranslation);
    cout<<endl<<endl;
    cout<<"Rotation Matrix:"<<endl;
    printMatrix(viewRotation);
    cout<<endl<<endl;
    */



    setUpViewMatrix(viewRotation,viewTranslation);
    //cout<<"View Matrix:"<<endl;
    //printMatrix(viewMatrix);


}

void initializeProjectionMatrix(){
    fovY = 2 * PI * (double)fovY/(double)360;
    double fovX = fovY * aspectRatio;
    double t = near * tan((double)fovY/(double)2);
    double r = near * tan((double)fovX/(double)2);

    projectionMatrix[0][0] = (double)near/(double)r;
    projectionMatrix[1][1] = (double)near/(double)t;
    projectionMatrix[2][2] = -(double)(far+near)/((double)far-near);
    projectionMatrix[2][3] = -((double)2*far*near)/(double)(far-near);
    projectionMatrix[3][2] = -1;

    //cout<<"Projection Matrix: "<<endl;
    //printMatrix(projectionMatrix);
}



double* applyProjectionMatrix(double* position){
    double *tempMatrix = new double[4];

    for(int i=0;i<4;i++){
        tempMatrix[i]=0;
    }



    for(int i=0;i<4;i++){
            for(int k=0;k<4;k++){
                tempMatrix[i]+= projectionMatrix[i][k] * position[k];
            }
    }

    double w = tempMatrix[3];

    for(int i=0;i<4;i++){
        tempMatrix[i]=(double)tempMatrix[i]/(double)w;
        //cout<<tempMatrix[i]<<endl;
    }


    return tempMatrix;

}







int main(){

    cout<<"Starting Graphics API..."<<endl;

    loadSceneFile(filePath);
    loadWriteFiles();



    initializeVariables();
    //cout<<"Here are the view variables"<<endl<<endl;
    //displayViewVariables();
    //cout<<"End of view variables"<<endl<<endl;
    initializeViewMatrix();
    initializeProjectionMatrix();
    cout<<endl<<endl;
    while(true){
        string command;
        scene>>command;

        if(command=="triangle"){
            //cout<<"Went In!!"<<endl<<endl;
            for(int i=0;i<3;i++){
                double* point = new double[4];

                for(int j=0;j<3;j++){
                    scene>>point[j];
                    //cout<<point[j]<<endl;
                }

                //cout<<endl<<endl;

                point[3]=1;

                double* transformationPoint = applyTransformationMatrix(point);
                double* viewPoint = applyViewMatrix(transformationPoint);
                double* projectionPoint = applyProjectionMatrix(viewPoint);

                //printPoint(point);
                //cout<<endl<<endl;

                stage1<<std::fixed<<std::setprecision(7);
                stage1<<transformationPoint[0]<<" "<<transformationPoint[1]<<" "<<transformationPoint[2]<<endl;

                stage2<<std::fixed<<std::setprecision(7);
                stage2<<viewPoint[0]<<" "<<viewPoint[1]<<" "<<viewPoint[2]<<endl;

                stage3<<std::fixed<<std::setprecision(7);
                stage3<<projectionPoint[0]<<" "<<projectionPoint[1]<<" "<<projectionPoint[2]<<endl;
            }
            stage1<<endl;
            stage2<<endl;
            stage3<<endl;

        }
        else if(command=="translate"){
            double *translationAmounts = new double[3];
            scene>>translationAmounts[0]>>translationAmounts[1]>>translationAmounts[2];

            double **tempMatrix = createTranslationMatrix(translationAmounts[0],translationAmounts[1],translationAmounts[2]);
            multiplyTransformationMatrix(tempMatrix);

        }
        else if(command=="scale"){
            double *translationAmounts = new double[3];
            scene>>translationAmounts[0]>>translationAmounts[1]>>translationAmounts[2];

            double **tempMatrix = createScaleMatrix(translationAmounts[0],translationAmounts[1],translationAmounts[2]);
            multiplyTransformationMatrix(tempMatrix);
        }
        else if(command=="rotate"){
            double *translationAmounts = new double[4];
            scene>>translationAmounts[0]>>translationAmounts[1]>>translationAmounts[2]>>translationAmounts[3];

            double **tempMatrix = createRotationMatrix(translationAmounts[0],translationAmounts[1],translationAmounts[2],translationAmounts[3]);
            multiplyTransformationMatrix(tempMatrix);
        }
        else if(command=="push"){
            //printMatrix(transformationMatrix);
            pushMatrix();
        }
        else if(command=="pop"){
            popMatrix();
            //printMatrix(transformationMatrix);
        }
        else if(command=="end"){
            break;
        }
    }

    cout<<"The Graphics API has ended!!"<<endl;









}
