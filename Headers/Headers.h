/*
 *
 *	Headers.h
 * 	Author: Behnam
 *
 */

#ifndef HEADERS_H_
#define HEADERS_H_

#include <iostream>
#include <utility>                  
#include <algorithm>               
#include <fstream>
#include <vector>
#include <stdio.h>      /* printf, fopen */
#include <stdlib.h>     /* exit, EXIT_FAILURE, system */
#include <sstream> //for double to string
#include <iomanip>

#include <time.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/ref.hpp>
#include <boost/graph/copy.hpp>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

#include <boost/algorithm/string.hpp> //For splitting strings boost::split()

//For make_vector
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>

//For parse_input
#include <cstring>
#include <ctype.h>
#include <cmath>
#include <string>
#include <map>
#include <set>
//For getline
#include <stddef.h>
#include <limits.h>
#include <errno.h>


using namespace std;
using namespace boost;

#endif
