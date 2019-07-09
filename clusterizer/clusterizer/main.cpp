#include <iostream>
#include <vector>
#include "CSV.h"
#include <list>

#include "DBSCAN.h"

#define M_SIZE 25

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






void printOut (std::vector <Obj> objects);

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
    
    for (int i = 0; i < M_SIZE; i++)
        objects.push_back (Obj (i, rand () % M_SIZE, i));


    printOut (objects);


    std::vector<std::vector <Obj>> clusters = DBSCAN (objects, 3, 2, distance);

    for (int i = 0; i < clusters.size (); i++)
        { 
        std::cout << "Cluster: " << i << std::endl;
        for (int j = 0; j < clusters[i].size (); j++)
            std::cout << "\t" << clusters [i][j].id << std::endl;
        }
    
    system ("pause");
    return 0;
    }





void printOut (std::vector <Obj> objects)
    {
    int matrix [M_SIZE] [M_SIZE] = { };

    for (auto i : objects)
        matrix [(int) i.x] [(int) i.y]++;

    printf ("\n\n");
    for (int i = 0; i < M_SIZE; i++)
        printf ("%d ", i%10);
    printf ("\n\n");
    for (int i = 0; i < M_SIZE; i++)
        {
        for (int j = 0; j < M_SIZE; j++)
            {
            printf ("%c ", (matrix [j] [i])? '0' : '.');
            }
        printf ("\n");
        }
    printf ("\n");
    }