#include <iostream>
#include <vector>

#define M_SIZE 10

template<typename T>
struct Cluster
    {
    std::vector <T> objects;
    };

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
        objects.push_back (Obj (i, rand() % M_SIZE, i));
    
    printOut (objects);

    function (objects, 3, distance);

    system ("pause");
    return 0;
    }




template<typename T>
void function (std::vector<T> obj, double d, double (*metrics)(T, T))
    {
    std::vector <std::vector <T>> neighb;

    for (int i = 0; i < obj.size (); i++)
        {
        std::vector <T> this_id_neighb;

        neighb.push_back (this_id_neighb);

        for (int j = 0; j < obj.size (); j++)
            {
            if (i != j)
                {
                double dist = metrics (obj [i], obj [j]);

                if (dist < d)
                    neighb.back ().push_back (obj [j]);
                }

            }
        std::cout << i << ' ';
        for (auto j : neighb.back ())
            { 
            std::cout << j.id << ' ';
            }
        std::cout << std::endl;
        }


    }

void printOut (std::vector <Obj> objects)
    { 
    int matrix [M_SIZE] [M_SIZE] = { };

    for (auto i : objects)
        matrix [(int) i.x] [(int) i.y]++;

    printf ("\n\n");
    for (int i = 0; i < 10; i++)
        printf ("%d ", i);
    printf ("\n\n");
    for (int i = 0; i < 10; i++)
        {
        for (int j = 0; j < 10; j++)
            {
            printf ("%d ", matrix [j] [i]);
            }
        printf ("\n");
        }
    printf ("\n");
    }