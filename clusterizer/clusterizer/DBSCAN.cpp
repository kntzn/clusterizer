#include "DBSCAN.h"

template<typename T> 
std::vector<std::vector <T>> DBSCAN (std::vector<T> obj,
                                     double d,
                                     double n,
                                     double (*metrics)(T, T),
                                     bool debug_output)
    {
    // List of the neighbours for each object
    std::vector <std::vector <int>> neighb;

    if (debug_output)
        std::cout << "\nNeighbour id collector: " << std::endl;

    // Collects ids of the neighbours for each object
    for (int i = 0; i < obj.size (); i++)
        {
        std::vector <int> newVec;

        // For each object
        for (int j = 0; j < obj.size (); j++)
            // That is not "object i" and close enough to it
            if (i != j && metrics (obj [i], obj [j]) <= d)
                // Add it to the table
                newVec.push_back (j);

        if (debug_output)
            std::cout << "\tid:" << i << "-" << newVec.size () << " neighb." << std::endl;

        neighb.push_back (newVec);
        }

    // List that contains id of each object's cluster
    std::vector <int> cluster_ids (obj.size ());
    // Cluster id
    int n_clusters = 0;

    if (debug_output)
        std::cout << "\nCluster id collector: " << std::endl;

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
                int this_neighb_id = neighb [i] [j];

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

            if (debug_output)
                std::cout << "\tid:" << i << "-" << cluster_ids [i] << std::endl;
            }
        else if (debug_output)
            std::cout << "\tid:" << i << "-Not enough neighbours" << std::endl;
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

    // Object to return
    std::vector <std::vector <T>> clusters (n_clusters + 1);

    // Convert clusters_ids to the clusters object
    for (int i = 0; i < obj.size (); i++)
        //if (cluster_ids [i] != 0) 
        clusters [cluster_ids [i]].push_back (obj [i]);

    return clusters;
    }
