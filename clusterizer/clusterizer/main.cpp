#include <iostream>
#include <vector>


struct Obj
    {
    double x;
    double y;

    Obj ()
        { }
    Obj (double X, double Y):
        x (x),
        y (Y)
        { }
    };

template <typename T> void function (std::vector <T> obj);

int main ()
    { 
    int nObj = 10;

    std::vector <Obj> objects;
    for (int i = 0; i < nObj; i++)
        objects.push_back (Obj (rand() % 10, rand() % 10));
    

    system ("pause");
    return 0;
    }


double metrics (Obj obj0, Obj obj1)
    { 
    double dx = obj0.x - obj1.x;
    double dy = obj0.y - obj1.y;

    return sqrt (dx*dx + dy*dy);
    }

template<typename T>
void function (std::vector<T> obj)
    {
    }
