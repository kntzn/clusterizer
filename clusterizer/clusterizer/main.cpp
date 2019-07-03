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
    // List of the neighbours for each object
    std::vector <std::vector <int>> neighb;
    
    // Collects ids of the neighbours for each object
    for (int i = 0; i < obj.size (); i++)
        {
        neighb.push_back (std::vector <int>);

        for (int j = 0; j < obj.size (); j++)
            if (i != j && metrics (obj [i], obj [j]) < d)
                neighb [i].push_back (j);
        }

    std::vector <int> cluster_ids (obj.size ()) = { };
    
    int n_clusters = 0;

    // This creates new clusters
    for (int i = 0; i < obj.size (); i++)
        {
        int nNeighb = neighb [i].size ();
        
        // In case this object has enough neighb.
        if (nNeighb >= n)
            { 
            // For each nieghbour
            for (int j = 0; j < nNeighb; j++)
                {
                // "object j" id
                int this_neighb_id = neighb [i][j];

                // if "object j" is already in cluster
                if (cluster_ids [obj [this_neighb_id]] != 0)
                    // Join "object i" to the same cluster
                    cluster_ids [i] = cluster_ids [obj [this_neighb_id]];
                // else 
                else
                    {
                    // if "object j" has no cluster
                    if (cluster_ids [i] == 0)
                        // Create new cluster with both objects
                        cluster_ids [i] = cluster_ids [obj [this_neighb_id]] = ++n_clusters;
                    else 
                        // Else (if "object i" was clusterized before) join "object j" to the same cluster
                        cluster_ids [obj [this_neighb_id]] = cluster_ids [i];
                    }


                }
            }
        }


    //// Joins to other clusters
    //else if (nNeighb == n - 1)
    //    { }
    //// Don't join
    //else
    //    { }

    // Convert clusters_ids to the clusters object

    std::vector <std::vector <T>> clusters;



    }
