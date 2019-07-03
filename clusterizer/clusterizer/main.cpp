#include <iostream>
#include <vector>
#include "CSV.h"

#define M_SIZE 20

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
    printf ("\n");


    system ("pause");
    return 0;
    }




template<typename T>
std::vector<std::vector <T>> DBSCAN (std::vector<T> obj, double d, double n, double (*metrics)(T, T))
    {
    // List of the neighbours for each object
    std::vector <std::vector <int>> neighb;
    
    // Collects ids of the neighbours for each object
    for (int i = 0; i < obj.size (); i++)
        {
        std::vector <int> newVec;
        
        // For each object
        for (int j = 0; j < obj.size (); j++)
            // That is not "object i" and close enough to it
            if (i != j && metrics (obj [i], obj [j]) < d)
                // Add it to the table
                newVec.push_back (j);

        neighb.push_back (newVec);
        }

    // List that contains id of each object's cluster
    std::vector <int> cluster_ids (obj.size ());
    // Cluster id
    int n_clusters = 0;

    // Cluster collector
    for (int i = 0; i < obj.size (); i++)
        {
        int nNeighb = neighb [i].size ();
        
        // In case "object i" has enough neighb.
        if (nNeighb >= n)
            { 
            // For each nieghbour
            for (int j = 0; j < nNeighb; j++)
                {
                // "object j" id
                int this_neighb_id = neighb [i][j];
                
                // In case "object j" has enough neighb. too
                if (neighb [this_neighb_id].size () >= n)
                    { 
                    // if "object j" is already in cluster
                    if (cluster_ids [this_neighb_id] != 0)
                        // Join "object i" to the same cluster
                        cluster_ids [i] = cluster_ids [this_neighb_id];
                    // else 
                    else
                        {
                        // if "object j" has no cluster
                        if (cluster_ids [i] == 0)
                            // Create new cluster with both objects
                            cluster_ids [i] = cluster_ids [this_neighb_id] = ++n_clusters;
                        else
                            // Else (if "object i" was clusterized before) join "object j" to the same cluster
                            cluster_ids [this_neighb_id] = cluster_ids [i];
                        }
                    }
                }
            }
        }

    // Cluster joiner
    for (int i = 0; i < obj.size (); i++)
        {
        int nNeighb = neighb [i].size ();

        // if "object i" does not have enough neighbours
        //     but it is still clusterizeable
        if (nNeighb == n - 1) // This is adjustable
            {
            // Then start searching the closest neighbour
            double min_distance = INFINITY;
            double closest_neighb_id = -1;

            // For each nieghbour
            for (int j = 0; j < nNeighb; j++)
                {
                // "object j" id
                int this_neighb_id = neighb [i] [j];

                // Saves the closest neighbour
                double current_distance = distance (obj [i], obj [this_neighb_id]);
                if (min_distance > current_distance)
                    {
                    min_distance = current_distance;
                    closest_neighb_id = this_neighb_id;
                    }

                }

            // Joins "object i" to the closest "object j"'s cluster
            cluster_ids [i] = cluster_ids [closest_neighb_id];
            }
        }

    //// Don't join
    //else
    //    { }


    // Object to return
    std::vector <std::vector <T>> clusters (n_clusters);

    // Convert clusters_ids to the clusters object
    for (int i = 0; i < obj.size (); i++)
        if (cluster_ids [i] != 0)
        clusters [cluster_ids [i]-1].push_back (obj [i]);

    return clusters;
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
            printf ("%d ", matrix [j] [i]);
            }
        printf ("\n");
        }
    printf ("\n");
    }