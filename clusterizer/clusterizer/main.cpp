#include <iostream>
#include <vector>

#define M_SIZE 10

struct Obj
    {
    double x;
    double y;

    Obj ()
        { }
    Obj (double X, double Y):
        x (X),
        y (Y)
        { }
    };

template <typename T> void function (std::vector <T> obj, double d, double (*metrics) (T, T));


double distance (Obj obj0, Obj obj1)
    {
    double dx = obj0.x - obj1.x;
    double dy = obj0.y - obj1.y;

    return sqrt (dx*dx + dy*dy);
    }

void printOut (std::vector <Obj> objects);

int main ()
    { 
    int nObj = 10;

    std::vector <Obj> objects;
    for (int i = 0; i < nObj; i++)
        objects.push_back (Obj (rand() % M_SIZE, i));
    
    printOut (objects);

    function (objects, 3, distance);

    system ("pause");
    return 0;
    }


template<typename T>
void function (std::vector<T> obj, double d, double (*metrics)(T, T))
    {
    std::vector <int> nNeighb;

    for (int i = 0; i < obj.size (); i++)
        {
        nNeighb.push_back (0);

        for (int j = 0; j < obj.size(); j++)
            {
            if (i != j)
                { 
                double dist = metrics (obj [i], obj [j]);

                std::cout << dist << std::endl;

                if (dist < d)
                    nNeighb.back () += 1;
                }
            
            }
        std::cout << '\t' << nNeighb.back () << std::endl;
        }

    }

void printOut (std::vector <Obj> objects)
    { 
    int matrix [M_SIZE] [M_SIZE] = { };

    for (auto i : objects)
        matrix [(int) i.x] [(int) i.y]++;

    printf ("\n");
    for (int i = 0; i < 10; i++)
        {
        for (int j = 0; j < 10; j++)
            {
            printf ("%d ", matrix [i] [j]);
            }
        printf ("\n");
        }
    }