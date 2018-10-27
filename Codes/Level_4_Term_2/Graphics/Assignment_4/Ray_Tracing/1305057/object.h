#include <vector>
#include <math.h>
#include <iostream>
#include "bitmap_image.hpp"
using namespace std;

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULAR 2
#define REFLECTION 3

extern int recursionLevel;





struct point
{
	double x,y,z;

	point(){
	    x=0;
	    y=0;
	    z=0;
	}

	point(double xN,double yN,double zN){
	    x=xN;
	    y=yN;
	    z=zN;
	}

	point operator+(point pt){
	    point temp(this->x+pt.x,this->y+pt.y,this->z+pt.z);
	    return temp;
	}

	point operator-(point pt){
	    point temp(this->x-pt.x,this->y-pt.y,this->z-pt.z);
	    return temp;
	}

	point operator*(point pt){
	    point temp(this->x*pt.x,this->y*pt.y,this->z*pt.z);
	    return temp;
	}

	point operator*(double pt){
	    point temp(this->x*pt,this->y*pt,this->z*pt);
	    return temp;
	}
};

struct vector3
{
    double x,y,z;

    vector3(){
	    x=0;
	    y=0;
	    z=0;
	}

    vector3(double xN,double yN,double zN){
	    x=xN;
	    y=yN;
	    z=zN;
	}

	vector3 operator+(vector3 v){
	    vector3 temp(this->x+v.x,this->y+v.y,this->z+v.z);
	    return temp;
	}

	vector3 operator-(vector3 v){
	    vector3 temp(this->x-v.x,this->y-v.y,this->z-v.z);
	    return temp;
	}

	vector3 operator*(vector3 v){
	    vector3 temp(this->x*v.x,this->y*v.y,this->z*v.z);
	    return temp;
	}

	vector3 operator*(double v){
	    vector3 temp(this->x*v,this->y*v,this->z*v);
	    return temp;
	}

	void normalize(){
	    double sum = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	    this->x = this->x/sum;
	    this->y = this->y/sum;
	    this->z = this->z/sum;
	}

	double dotProduct(vector3 v1,vector3 v2){
	    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	vector3 crossProduct(vector3 v1,vector3 v2){
	    vector3 temp(v1.y*v2.z-v2.y*v1.z,-(v1.x*v2.z-v2.x*v1.z),v1.x*v2.y-v2.x*v1.y);
	    return temp;
	}

	void printVector(){
	    cout<<x<<" "<<y<<" "<<z<<endl;
	}
};






class Ray{
public:
    vector3 start;
    vector3 dir;
    Ray(vector3 start,vector3 dir){
        this->start = start;
        this->dir = dir;
    }
};


class Object{
protected:
    vector3 reference_point;
    double height,width,length;
    int Shine;
    double color[3];
    double co_efficients[4];
    double source_factor = 1.0;
public:
    Object(){};

    virtual void draw(){};

    virtual double getIntersectingT(Ray *r){
        return -1;
    }

    virtual double intersect(Ray *r,double *current_color,int level){
        return -1;
    }

    void setColor(double color1,double color2,double color3){
        color[0]=color1;
        color[1]=color2;
        color[2]=color3;
    }

    void setShine(int shineValue){
        Shine = shineValue;
    }

    virtual void setRefractionParameters(double refIdx){
    }

    void setCoEfficients(double val1,double val2,double val3,double val4){
        co_efficients[0]=val1;
        co_efficients[1]=val2;
        co_efficients[2]=val3;
        co_efficients[3]=val4;
    }

    vector3 getReflection(Ray *ray,vector3 normal){
        vector3 temp = ray->dir - normal* normal.dotProduct(ray->dir, normal)*2.0;
        temp.normalize();
        return temp;
    }


};


extern vector <Object*> objects;
extern vector <vector3> lights;



class Sphere: public Object{
    double refractiveIndex = 4;
    bool doRefraction = false;
public:

    void setRefractionParameters(double refIdx){
        doRefraction = true;
        refractiveIndex = refIdx;
    }


    Sphere(vector3 center,double radius){
        reference_point = center;
        length = radius;
    }

    void draw(){
         glPushMatrix();
         glColor3f(color[0],color[1],color[2]);
         glTranslatef(reference_point.x,reference_point.y,reference_point.z);
         glutSolidSphere(length,200,200);
         glPopMatrix();
    }

    void recurse(Ray *r,int level,double *current_color){
                int nearest = -1;
                double reflectedColor[3];
                double t_min = 999999999;

                for(int k=0;k<objects.size();k++){
                        double t = objects[k]->getIntersectingT(r);
                        if(t<=0)continue;

                        if(t<t_min){
                            t_min=t;
                            nearest=k;
                        }
                }

                if(nearest!=-1){
                    double t = objects[nearest]->intersect(r,reflectedColor,level+1);

                    if(t!=-1){
                        for(int a=0;a<3;a++){
                            current_color[a]+=reflectedColor[a]*co_efficients[REFLECTION];
                            if(current_color[a]<0)current_color[a]=0;
                            if(current_color[a]>1)current_color[a]=1;
                        }
                    }

                }
    }



    double getIntersectingT(Ray *r){
        vector3 origin;
        origin.x = r->start.x - reference_point.x;
        origin.y = r->start.y - reference_point.y;
        origin.z = r->start.z - reference_point.z;

        //r->start.printVector();
        //r->dir.printVector();
        //origin.printVector();


        double A = origin.dotProduct(r->dir,r->dir);
        double B = 2 * origin.dotProduct(r->dir,origin);
        double C = origin.dotProduct(origin,origin) - length*length;

        //cout<<"ABC:"<<A<<" "<<B<<" "<<C<<endl;

        double D = B*B - 4*A*C;

        //cout<<"D: "<<D<<endl;

        if(D<0)return -1;

        double d = sqrt(D);

        double t1 = (double)(-B+d)/(double)(2.0*A);
        double t2 = (double)(-B-d)/(double)(2.0*A);


        if(t1<t2)return t1;
        else return t2;
    }

    void setColorAt(double *current_color){
        for(int i=0;i<3;i++){
            current_color[i]=this->color[i]*co_efficients[AMBIENT];
            if(current_color[i]<0)current_color[i]=0;
            if(current_color[i]>1)current_color[i]=1;
        }
    }

    vector3 getNormal(vector3 intersectionPoint){
        vector3 temp = intersectionPoint - reference_point;
        temp.normalize();
        return temp;
    }


    vector3 getRefraction(Ray* ray, vector3 normal, double refractiveIndex)
    {
        double dotProduct = normal.dotProduct(normal, ray->dir);
        double k = 1.0 - refractiveIndex * refractiveIndex * (1.0 - dotProduct * dotProduct);
        if (k < 0.f)
        {
            vector3 temp(0,0,0);
            return temp;
        }
        else
        {
            vector3 out = ray->dir * refractiveIndex  - normal*(refractiveIndex * dotProduct + sqrt(k));
            out.normalize();
            return out;
        }
    }

    double intersect(Ray *r,double *current_color,int level){

        double t = getIntersectingT(r);

        if(t<=0)return -1;

        if(level==0)return t;


        setColorAt(current_color);


        vector3 intersectionPoint = r->start+ r->dir*t;



        vector3 normal = getNormal(intersectionPoint);
        vector3 reflection = getReflection(r,normal);
        vector3 refraction = getRefraction(r,normal,refractiveIndex);

        for(int i=0;i<lights.size();i++){
            vector3 direction = lights[i] - intersectionPoint;
            //cout<<"Normalized Correctly: ";
            //direction.printVector();
            double rayLength = sqrt(direction.dotProduct(direction,direction));
            direction.normalize();
            vector3 start = intersectionPoint + direction*1.0;

            Ray *tempRay = new Ray(start,direction);

            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double tempT = objects[j]->getIntersectingT(tempRay);
                if(tempT < 0 || tempT > rayLength) {
                    continue;
                }

                obscured = true;
                break;
            }

            if(!obscured){
                double lambertValue = normal.dotProduct(normal,tempRay->dir);
                double phongValue =  pow( reflection.dotProduct(reflection,r->dir),Shine);

                if(lambertValue<0)lambertValue=0;
                if(phongValue<0)phongValue=0;

                for(int k=0;k<3;k++){
                     current_color[k] += source_factor * lambertValue * co_efficients[DIFFUSE] * this->color[k];
                     current_color[k] += source_factor * phongValue * co_efficients[SPECULAR] * this->color[k];
                }

            }


            if(level<recursionLevel){
                start = intersectionPoint + reflection*1.0;

                Ray *reflectionRay = new Ray(start,reflection);
                recurse(reflectionRay,level,current_color);



                //Refraction

                if(doRefraction){

                start = intersectionPoint + refraction*1.0;

                Ray *refractionRay = new Ray(start,refraction);
                recurse(refractionRay,level,current_color);


                }
            }


        }



        return t;

    }

};

class Floor:public Object{
public:
    bitmap_image floorTexture;
    double textUnitHeight,textUnitWidth;
    bool useTexture;


    Floor(double FloorWidth,double TileWidth,bool useTexture){
        reference_point = vector3(-FloorWidth/2.0,-FloorWidth/2,0);
        length = TileWidth;
        floorTexture = bitmap_image("texture.bmp");
        textUnitHeight = floorTexture.height()/(2.0*abs(reference_point.y));
        textUnitWidth = floorTexture.width()/(2.0*abs(reference_point.x));
        this->useTexture = useTexture;
    }

    void draw(){

        int numberOfTiles = abs(reference_point.y)*2.0/(double)length;
        vector3 q = reference_point;
        int seq = 0;

        for (int i=0; i<numberOfTiles; i++) {
            for (int j=0; j<numberOfTiles; j++) {

                if ((i+j)%2) {
                    glColor3f(0, 0, 0);
                } else {
                    glColor3f(1, 1, 1);
                }

                glBegin(GL_QUADS);
                {
                    glVertex3f(q.x+length*i, q.y+length*j, q.z);
                    glVertex3f(q.x+length*(i+1), q.y+length*j, q.z);
                    glVertex3f(q.x+length*(i+1), q.y+length*(j+1), q.z);
                    glVertex3f(q.x+length*i, q.y+length*(j+1), q.z);
                }
                glEnd();
            }
        }
    }


    void recurse(Ray *r,int level,double *current_color){
                int nearest = -1;
                double reflectedColor[3];
                double t_min = 999999999;

                for(int k=0;k<objects.size();k++){
                        double t = objects[k]->getIntersectingT(r);
                        if(t<=0)continue;

                        if(t<t_min){
                            t_min=t;
                            nearest=k;
                        }
                }

                if(nearest!=-1){
                    double t = objects[nearest]->intersect(r,reflectedColor,level+1);

                    if(t!=-1){
                        for(int a=0;a<3;a++){
                            current_color[a]+=reflectedColor[a]*co_efficients[REFLECTION];
                            if(current_color[a]<0)current_color[a]=0;
                            if(current_color[a]>1)current_color[a]=1;
                        }
                    }

                }
    }


    vector3 getNormal(){
        vector3 temp(0,0,1);
        temp.normalize();
        return temp;
    }



    double getIntersectingT(Ray *r){
        vector3 normal = getNormal();
        double t = (double)(-1.0 * normal.dotProduct(normal,r->start))/(double)normal.dotProduct(normal,r->dir);
        return t;
    }

    void setColorAt(double *current_color){
        current_color[0]=this->color[0]*co_efficients[AMBIENT];
        current_color[1]=this->color[1]*co_efficients[AMBIENT];
        current_color[2]=this->color[2]*co_efficients[AMBIENT];
    }







    double intersect(Ray *r,double *current_color,int level){

        double t = getIntersectingT(r);

        vector3 intersectionPoint = r->start+ r->dir*t;

        double minimumX = reference_point.x;
        double maximumX = minimumX * (-1.0);

        double minimumY = reference_point.y;
        double maximumY = minimumY * (-1.0);


        if (intersectionPoint.x<minimumX || intersectionPoint.x > maximumX || intersectionPoint.y<minimumY || intersectionPoint.y > maximumY){
            return -1;
        }

        int xCord = (intersectionPoint.x-reference_point.x) / length;
        int yCord = (intersectionPoint.y-reference_point.y) / length;

        if ((xCord+yCord)%2) {
            color[0] = color[1] = color[2] = 0;
        } else {
            color[0] = color[1] = color[2] = 1;
        }


        //setColorAt(current_color);


        if(useTexture){
            int xValue = (intersectionPoint.x - reference_point.x)*textUnitWidth;
            int yValue = (intersectionPoint.y - reference_point.y)*textUnitHeight;

            unsigned char red,green,blue;

            floorTexture.get_pixel(xValue,yValue,red,green,blue);

            current_color[0]=this->color[0]*co_efficients[AMBIENT]*(double)red;
            current_color[1]=this->color[1]*co_efficients[AMBIENT]*(double)blue;
            current_color[2]=this->color[2]*co_efficients[AMBIENT]*(double)green;
        }
        else{
            setColorAt(current_color);
        }






        vector3 normal = getNormal();
        vector3 reflection = getReflection(r,normal);

        for(int i=0;i<lights.size();i++){
            vector3 direction = lights[i] - intersectionPoint;
            //cout<<"Normalized Correctly: ";
            //direction.printVector();
            double rayLength = sqrt(direction.dotProduct(direction,direction));
            direction.normalize();
            vector3 start = intersectionPoint + direction*1.0;

            Ray *tempRay = new Ray(start,direction);

            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double tempT = objects[j]->getIntersectingT(tempRay);
                if(tempT < 0 || tempT > rayLength) {
                    continue;
                }

                obscured = true;
                break;
            }

            if(!obscured){
                double lambertValue = normal.dotProduct(normal,tempRay->dir);
                double phongValue =  pow( reflection.dotProduct(reflection,r->dir),Shine);

                if(lambertValue<0)lambertValue=0;
                if(phongValue<0)phongValue=0;

                for(int k=0;k<3;k++){
                     current_color[k] += source_factor * lambertValue * co_efficients[DIFFUSE] * this->color[k];
                     current_color[k] += source_factor * phongValue * co_efficients[SPECULAR] * this->color[k];
                }

            }


            if(level<recursionLevel){
                start = intersectionPoint + reflection*1.0;

                Ray *reflectionRay = new Ray(start,reflection);

                //cout<<"Recursion Enter "<<level<<endl;

                recurse(reflectionRay,level,current_color);
            }



        }




        return t;

    }


};

class Triangle:public Object{
    vector3 a,b,c;
public:


    Triangle(vector3 a,vector3 b,vector3 c){
        this->a=a;
        this->b=b;
        this->c=c;
    }

    void draw(){
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_TRIANGLES);{
            glVertex3f(a.x,a.y,a.z);
            glVertex3f(b.x,b.y,b.z);
            glVertex3f(c.x,c.y,c.z);
		}glEnd();

    }


    vector3 getNormal(){
        vector3 one = b-a;
        vector3 two = c-a;
        vector3 temp = one.crossProduct(one,two);
        temp.normalize();
        return temp;

    }

    void recurse(Ray *r,int level,double *current_color){
                int nearest = -1;
                double reflectedColor[3];
                double t_min = 999999999;

                for(int k=0;k<objects.size();k++){
                        double t = objects[k]->getIntersectingT(r);
                        if(t<=0)continue;

                        if(t<t_min){
                            t_min=t;
                            nearest=k;
                        }
                }

                if(nearest!=-1){
                    double t = objects[nearest]->intersect(r,reflectedColor,level+1);

                    if(t!=-1){
                        for(int a=0;a<3;a++){
                            current_color[a]+=reflectedColor[a]*co_efficients[REFLECTION];
                            if(current_color[a]<0)current_color[a]=0;
                            if(current_color[a]>1)current_color[a]=1;
                        }
                    }

                }
    }



    double getIntersectingT(Ray *r){
        double EPSILON = 0.0000001;
        vector3 edge1, edge2, h, s, q;
        double aS,f,u,v;
        edge1 = b - a;
        edge2 = c - a;
        h = r->dir.crossProduct(r->dir,edge2);
        aS = edge1.dotProduct(edge1,h);
        if (aS > -EPSILON && aS < EPSILON)
            return -1;
        f = 1.0/aS;
        s = r->start - a;
        u = s.dotProduct(s,h)*f;
        if (u < 0.0 || u > 1.0)
            return -1;
        q = s.crossProduct(s,edge1);
        v = r->dir.dotProduct(r->dir,q)*f;
        if (v < 0.0 || u + v > 1.0)
            return -1;
    // At this stage we can compute t to find out where the intersection point is on the line.
        double t = edge2.dotProduct(edge2,q)*f;
        if (t > EPSILON) // ray intersection
        {
            return t;
        }
        else return -1;
    }

    void setColorAt(double *current_color){
        current_color[0]=this->color[0]*co_efficients[AMBIENT];
        current_color[1]=this->color[1]*co_efficients[AMBIENT];
        current_color[2]=this->color[2]*co_efficients[AMBIENT];
    }

    double intersect(Ray *r,double *current_color,int level){

        double t = getIntersectingT(r);

        if(t<=0)return -1;
        if(level==0)return t;


        vector3 intersectionPoint = r->start+ r->dir*t;

        setColorAt(current_color);



        for(int i=0;i<lights.size();i++){
            vector3 normal = getNormal();

            vector3 direction = lights[i] - intersectionPoint;
            //cout<<"Normalized Correctly: ";
            //direction.printVector();
            double rayLength = sqrt(direction.dotProduct(direction,direction));
            direction.normalize();

            vector3 reflection = getReflection(r,normal);

            vector3 start = intersectionPoint + direction*1.0;

            Ray *tempRay = new Ray(start,direction);

            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double tempT = objects[j]->getIntersectingT(tempRay);
                if(tempT < 0 || tempT > rayLength) {
                    continue;
                }

                obscured = true;
                break;
            }

            if(!obscured){
                double lambertValue = normal.dotProduct(normal,tempRay->dir);
                double phongValue =  pow( reflection.dotProduct(reflection,r->dir),Shine);

                if(lambertValue<0)lambertValue=0;
                if(phongValue<0)phongValue=0;

                for(int k=0;k<3;k++){
                     current_color[k] += source_factor * lambertValue * co_efficients[DIFFUSE] * this->color[k];
                     current_color[k] += source_factor * phongValue * co_efficients[SPECULAR] * this->color[k];
                }

            }


            if(level<recursionLevel){
                start = intersectionPoint + reflection*1.0;

                Ray *reflectionRay = new Ray(start,reflection);
                recurse(reflectionRay,level,current_color);
            }


        }



        return t;

    }


};




class GeneralQuadric:public Object{
    double A,B,C,D,E,F,G,H,I,J;

public:

    GeneralQuadric(double values[10],vector3 ref,double length,double width,double height){
        A=values[0];
        B=values[1];
        C=values[2];
        D=values[3];
        E=values[4];
        F=values[5];
        G=values[6];
        H=values[7];
        I=values[8];
        J=values[9];
        this->reference_point = ref;
        this->length = length;
        this->width = width;
        this->height = height;
    }

    void draw(){

    }


    void recurse(Ray *r,int level,double *current_color){
                int nearest = -1;
                double reflectedColor[3];
                double t_min = 999999999;

                for(int k=0;k<objects.size();k++){
                        double t = objects[k]->getIntersectingT(r);
                        if(t<=0)continue;

                        if(t<t_min){
                            t_min=t;
                            nearest=k;
                        }
                }

                if(nearest!=-1){
                    double t = objects[nearest]->intersect(r,reflectedColor,level+1);

                    if(t!=-1){
                        for(int a=0;a<3;a++){
                            current_color[a]+=reflectedColor[a]*co_efficients[REFLECTION];
                            if(current_color[a]<0)current_color[a]=0;
                            if(current_color[a]>1)current_color[a]=1;
                        }
                    }

                }
    }


    vector3 getNormal(vector3 intersectionPoint){
        double x = 2*A*intersectionPoint.x + D*intersectionPoint.y + E*intersectionPoint.z + G;
        double y = 2*B*intersectionPoint.y + D*intersectionPoint.x + F*intersectionPoint.z + H;
        double z = 2*C*intersectionPoint.z + E*intersectionPoint.x + F*intersectionPoint.y + I;

        vector3 temp(x,y,z);
        temp.normalize();

        return temp;
    }



    double getIntersectingT(Ray *r){
        double a = this->A * r->dir.x * r->dir.x + this->B * r->dir.y * r->dir.y + this->C * r->dir.z * r->dir.z;
        double b = 2.0 * (this->A * r->start.x * r->dir.x + this->B * r->start.y * r->dir.y + this->C * r->start.z * r->dir.z);
        double c = this->A * r->start.x * r->start.x + this->B * r->start.y * r->start.y + this->C * r->start.z * r->start.z;

        a += this->D * r->dir.x * r->dir.y + this->F * r->dir.y * r->dir.z + this->E * r->dir.z * r->dir.x;
        b += this->D * (r->start.x * r->dir.y + r->dir.x * r->start.y)+ this->F * (r->start.y * r->dir.z + r->dir.y * r->start.z)+ this->E * (r->start.z * r->dir.x + r->dir.z * r->start.x);
        c += this->D * r->start.x * r->start.y + this->F * r->start.y * r->start.z + this->E * r->start.z * r->start.x;

        b += this->G * r->dir.x + this->H * r->dir.y + this->I * r->dir.z;
        c += this->G * r->start.x + this->H * r->start.y + this->I * r->start.z + J;


        double d = b*b - 4*a*c;


        if (d < 0) {
            return -1;
        }

        d = sqrt(d);

        double t1 = (- b + d) / (2.0*a);
        double t2 = (- b - d) / (2.0*a);


        vector3 intersectionPoint1 = r->start + r->dir * t1;
        vector3 intersectionPoint2 = r->start + r->dir * t2;

        double minimumX = reference_point.x;
        double maximumX = minimumX + length;

        double minimumY = reference_point.y;
        double maximumY = minimumY + width;

        double minimumZ = reference_point.z;
        double maximumZ = minimumZ + height;

        bool condition1x = length > 0 && (intersectionPoint1.x<minimumX || intersectionPoint1.x > maximumX);
        bool condition1y = width > 0 && (intersectionPoint1.y<minimumY || intersectionPoint1.y > maximumY);
        bool condition1z = height > 0 && (intersectionPoint1.z<minimumZ || intersectionPoint1.z > maximumZ);

        bool condition2x = length > 0 && (intersectionPoint2.x<minimumX || intersectionPoint2.x > maximumX);
        bool condition2y = width > 0 && (intersectionPoint2.y<minimumY || intersectionPoint2.y > maximumY);
        bool condition2z = height > 0 && (intersectionPoint2.z<minimumZ || intersectionPoint2.z > maximumZ);


        bool condition1 = condition1x || condition1y || condition1z;
        bool condition2 = condition2x || condition2y || condition2z;

        if (condition1 && condition2) {
            return -1;
        } else if (condition1) {
            return t2;
        } else if (condition2) {
            return t1;
        } else {
            if(t1<t2)return t1;
            else return t2;
        }

    }

    void setColorAt(double *current_color){
        current_color[0]=this->color[0]*co_efficients[AMBIENT];
        current_color[1]=this->color[1]*co_efficients[AMBIENT];
        current_color[2]=this->color[2]*co_efficients[AMBIENT];
    }

    double intersect(Ray *r,double *current_color,int level){

        double t = getIntersectingT(r);

        if(t<=0)return -1;

        if(level==0)return t;


        setColorAt(current_color);


        vector3 intersectionPoint = r->start+ r->dir*t;



        vector3 normal = getNormal(intersectionPoint);
        vector3 reflection = getReflection(r,normal);

        for(int i=0;i<lights.size();i++){
            vector3 direction = lights[i] - intersectionPoint;
            //cout<<"Normalized Correctly: ";
            //direction.printVector();
            double rayLength = sqrt(direction.dotProduct(direction,direction));
            direction.normalize();
            vector3 start = intersectionPoint + direction*1.0;

            Ray *tempRay = new Ray(start,direction);

            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double tempT = objects[j]->getIntersectingT(tempRay);
                if(tempT < 0 || tempT > rayLength) {
                    continue;
                }

                obscured = true;
                break;
            }

            if(!obscured){
                double lambertValue = normal.dotProduct(normal,tempRay->dir);
                double phongValue =  pow( reflection.dotProduct(reflection,r->dir),Shine);

                if(lambertValue<0)lambertValue=0;
                if(phongValue<0)phongValue=0;

                for(int k=0;k<3;k++){
                     current_color[k] += source_factor * lambertValue * co_efficients[DIFFUSE] * this->color[k];
                     current_color[k] += source_factor * phongValue * co_efficients[SPECULAR] * this->color[k];
                }

            }


            if(level<recursionLevel){
                start = intersectionPoint + reflection*1.0;

                Ray *reflectionRay = new Ray(start,reflection);
                recurse(reflectionRay,level,current_color);
            }


        }

        return t;

    }


};









