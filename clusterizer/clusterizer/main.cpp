#include <iostream>
#include <vector>
#include "CSV.h"


struct Obj
    {
    double x;
    double y;
    int id;

    Obj ()
        { }
    Obj (double X, double Y, int ID):
        x (X),
        y (Y),
        id (ID)
        { }
    };

template <typename T> std::vector<std::vector <T>> DBSCAN (std::vector <T> obj, double d, double n, double (*metrics) (T, T));

// Obj dist metric
double distance (Obj obj0, Obj obj1)
    {
    double dx = obj0.x - obj1.x;
    double dy = obj0.y - obj1.y;

    return sqrt (dx*dx + dy*dy);
    }

int main ()
    { 
    std::vector <Obj> objects;



    
    system ("pause");
    return 0;
    }




template<typename T>
std::vector<std::vector <T>> DBSCAN (std::vector<T> obj, double d, double n, double (*metrics)(T, T))
    {
    
    }
