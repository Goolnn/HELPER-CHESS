#include "tool/BezierCurve.hpp"
#include "tool/Math.hpp"

#include <cmath>

using namespace std;

//贝塞尔曲线
BezierCurve::~BezierCurve(){
    for(int i=0;i<this->points.size();i++){
        delete this->points.at(i);

    }

}

void BezierCurve::addPoint(double x,double y){
    this->points.append(new Point(x,y));

}

Point BezierCurve::calc(double t){
    int n=this->points.size()-1;

    Point result=Point(0,0);

    for(int i=0;i<n+1;i++){
        result.addX(Math::combinatorialNumber(n,i)*this->points.at(i)->getX()*pow(1-t,n-i)*pow(t,i));
        result.addY(Math::combinatorialNumber(n,i)*this->points.at(i)->getY()*pow(1-t,n-i)*pow(t,i));

    }

    return result;

}

Point::Point(double x,double y){
    this->x=x;
    this->y=y;

}

Point::Point(){
    this->x=0;
    this->y=0;

}

void Point::addX(double x){
    this->x+=x;

}

void Point::addY(double y){
    this->y+=y;

}

double Point::getX(){
    return this->x;

}

double Point::getY(){
    return this->y;

}
