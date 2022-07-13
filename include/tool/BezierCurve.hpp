#ifndef GOOLNN_HELPERCHESS_TOOL_BEZIERCURVE
#define GOOLNN_HELPERCHESS_TOOL_BEZIERCURVE

#include <QList>

class BezierCurve;
class Point;

class BezierCurve{
    private:
        QList<Point*> points;
    
    public:
        ~BezierCurve();

        void addPoint(double x,double y);

        Point calc(double t);

};

class Point{
    private:
        double x;
        double y;
    
    public:
        Point(double x,double y);
        Point();

        void addX(double x);
        void addY(double y);

        double getX();
        double getY();
    
};

#endif
