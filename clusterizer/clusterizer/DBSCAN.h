#pragma once
#include <vector>

// ------------------------------------------------------------------
/// brief              DBSCAN clusterizer function
/// 
/// param obj          Clusterizeable objects vector
/// param d            Max. distance between neighbours
/// param n            Amount of neighbours  
/// param metrics      Ptr to the metrics function
/// param debug_output Activates output required for debug (Optional)
/// 
/// returns            std::vector of std::vectors containing the
///                    groups of the objects
// ------------------------------------------------------------------
template <typename T> 
std::vector <std::vector <T>> DBSCAN (std::vector <T> obj,
                                      double d,
                                      double n,
                                      double (*metrics) (T, T),
                                      bool debug_output = false);
