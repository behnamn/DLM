/*
 *
 *	MyGraph.cpp
 * 	Author: Behnam
 *
 */

#include "MyGraph.h"


MyGraph::MyGraph (Design* design_){
	design = design_;
	add_vertices();
	add_domains();
	num_bound_domains=0;
	num_bound_nucs=0;
	num_bound_H=0;
	num_bound_U=0;
	num_bound_S=0;
}

//Common Methods
void MyGraph::add_vertices(){
	for(int i=0; i<design->n_domains; i++){
		add_vertex(g);
	}
	reset_vertex_index();
}
void MyGraph::add_domains(){
	EdgeProperty EP; 
	EP.type = 's';
	EP.crossover.second = false;
	for (vector<Domain>::iterator d = design->domains.begin(); d != design->domains.end(); ++d) {	
		EP.id = distance(design->domains.begin(), d);
		EP.domain = make_pair(&*d,true);
		EP.weight = d->length * l_ss * lambda_ss;
		EP.length = d->length;
		d->edge = add_edge(d->vertices.first, d->vertices.second, EP, g).first;
	}
}
void MyGraph::bind_domain(Domain* domain){
	g[domain->edge].weight = domain->length * domain->length * ds_hack;
	num_bound_domains++;
	if(domain->staple->n_domains == 1){num_bound_H++;}
	if(domain->staple->n_domains == 2){num_bound_U++;}
	if(domain->staple->n_domains == 3){num_bound_S++;}
	num_bound_nucs += domain->length;
	//For drawing
	g[domain->edge].type = 'd';
}
void MyGraph::unbind_domain(Domain* domain){
	g[domain->edge].weight = domain->length * ss_hack;
	num_bound_domains--;
	if(domain->staple->n_domains == 1){num_bound_H--;}
	if(domain->staple->n_domains == 2){num_bound_U--;}
	if(domain->staple->n_domains == 3){num_bound_S--;}
	num_bound_nucs -= domain->length;
	//For drawing
	g[domain->edge].type = 's';
}
void MyGraph::reset_vertex_index() {
	Vertex_iter vi,vf;
	int i = 0;
	for(tie(vi,vf) = vertices(g); vi != vf; ++vi) {
		g[*vi].id = i;
		i++;
	}
}	
void MyGraph::reset_edge_index() {
	Edge_iter ei,ef;
	tie(ei,ef) = edges(g);
	int i = 0;
	for ( ; ei != ef ; ++ei){
		g[*ei].id = i;
		i++;
	}
}
void MyGraph::update_embedding() {
	emb.resize(num_vertices(g));
	if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding = &emb[0]))
		return;
	else
		cout << "input graph is not planar." << endl;
}
double MyGraph::total_weight(int a, int b) {
	typedef double Weight;
	typedef property_map <Graph,vertex_index_t>::type IndexMap;
	typedef iterator_property_map <Vertex_desc*,IndexMap,Vertex_desc,Vertex_desc&> PredecessorMap;
	typedef iterator_property_map <Weight*,IndexMap,Weight,Weight&> DistanceMap;
	vector<Vertex_desc> predecessors(num_vertices(g)); // To store parents
	vector<Weight> distances(num_vertices(g)); // To store distances
	IndexMap indexMap = get(vertex_index, g);
	PredecessorMap predecessorMap(&predecessors[0], indexMap);
	DistanceMap distanceMap(&distances[0], indexMap);
	dijkstra_shortest_paths(g, a, weight_map(get(&EdgeProperty::weight, g)).distance_map(distanceMap).predecessor_map(predecessorMap));
	//typedef vector<Edge_desc> Path;
	Path path;
	Vertex_desc v=b; // We want to start at the destination and work our way back to the source
	for(Vertex_desc u=predecessorMap[v]; u!=v; v=u, u=predecessorMap[v]) {
		pair<Edge_desc, bool> edgePair = edge(u, v, g);
		Edge_desc edge = edgePair.first;
		path.push_back(edge);
	}
	return distanceMap[b];
}

//Transition Methods
void MyGraph::add_crossover(Crossover* cross){
	EdgeProperty EP; 
	EP.domain.second = false;
   	EP.crossover = make_pair(cross,true);
	EP.type = cross->type;
	EP.length = default_crossover_size;
	EP.weight = cs_hack;
	cross->edge = add_edge(cross->vertices.first, cross->vertices.second, EP, g);
	reset_edge_index();
}
void MyGraph::remove_crossover(Crossover* cross){
	//Make sure this doesn't fuck up because of 5->3 / 3->5.
	remove_edge(cross->vertices.first, cross->vertices.second, g);
	cross->edge.second = false;
	reset_edge_index();
}


//Printers
void MyGraph::print_edges(){
	cout << "\n\n---------------------- Printing Edges -------------------------\n";
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		cout << g[*ei].id << "\t";
		cout << *ei << "\t";
		cout << "Type: " << g[*ei].type << "\t";
		cout << "Edge Length: " << g[*ei].length << "\t";
		if(g[*ei].domain.second == true)
			cout << "Domain Length: " << g[*ei].domain.first->length << "\t";
		if(g[*ei].crossover.second == true)
			cout << "Crossover Length: " << "not length" << "\t";
		cout << "\n";
	}	
}
void MyGraph::write_gv_circle(string filename) {
	double radius = 25;
	Vertex_iter vi,vf;
	int n_vertices = design->n_domains;
	double x, y, angle;
	angle = (2 * M_PI) / n_vertices;
	vector<double> X,Y;
	for (int i=0; i<n_vertices; i++){
		x = radius * cos(i*angle);
		y = radius * sin(i*angle);
		X.push_back(x);
		Y.push_back(y);
	}	
	int i=0;
	for(tie(vi,vf) = vertices(g); vi != vf; ++vi) {
		g[*vi].pos = std::to_string(X[i]);
		g[*vi].pos += ",";
		g[*vi].pos += std::to_string(Y[i]);
		g[*vi].pos += "!";
		g[*vi].height = 0.3;
		g[*vi].width = 0.3;
		g[*vi].other = "true";
		i++;
	}
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){g[*ei].colour = "black"; g[*ei].thickness = "6.0";}
		else if(g[*ei].type == 's'){g[*ei].colour = "black"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'i'){g[*ei].colour = "green"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'o'){g[*ei].colour = "blue"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'm'){g[*ei].colour = "red"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'l'){g[*ei].colour = "purple"; g[*ei].thickness = "2.0";}
		else {cout << "no domain type found for edge" << endl;}
	}
	boost::dynamic_properties dp;
	dp.property("len", get(&EdgeProperty::length, g));
	//dp.property("weight", get(&EdgeProperty::weight, g));
	//dp.property("label", get(&EdgeProperty::weight, g));
	dp.property("type", get(&EdgeProperty::type, g));
	dp.property("color", get(&EdgeProperty::colour, g));
	dp.property("penwidth", get(&EdgeProperty::thickness, g));
	//dp.property("label", get(&VertexProperty::name, g));
	dp.property("node_id", get(&VertexProperty::id, g)); //must have!
	dp.property("pos", get(&VertexProperty::pos, g)); //must have!
	dp.property("height", get(&VertexProperty::height, g)); //must have!
	dp.property("width", get(&VertexProperty::width, g)); //must have!
	dp.property("fixedsize", get(&VertexProperty::other, g)); //must have!
	ofstream outfile;
	outfile.open(filename+"_C.gv");
	write_graphviz_dp(outfile, g, dp);
	outfile.close();
}
void MyGraph::write_gv(string filename) {
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){g[*ei].colour = "black"; g[*ei].thickness = "6.0";}
		else if(g[*ei].type == 's'){g[*ei].colour = "black"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'i'){g[*ei].colour = "green"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'o'){g[*ei].colour = "blue"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'm'){g[*ei].colour = "red"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'l'){g[*ei].colour = "purple"; g[*ei].thickness = "2.0";}
		else {cout << "no domain type found for edge" << endl;}
	}
	boost::dynamic_properties dp;
	dp.property("len", get(&EdgeProperty::length, g));
	//dp.property("weight", get(&EdgeProperty::weight, g));
	//dp.property("label", get(&EdgeProperty::weight, g));
	dp.property("type", get(&EdgeProperty::type, g));
	dp.property("color", get(&EdgeProperty::colour, g));
	dp.property("penwidth", get(&EdgeProperty::thickness, g));
	//dp.property("label", get(&VertexProperty::name, g));
	dp.property("node_id", get(&VertexProperty::id, g)); //must have!
	ofstream outfile;
	outfile.open(filename+".gv");
	write_graphviz_dp(outfile, g, dp);
	outfile.close();
}
void MyGraph::print_embedding() {
	face_counter count_visitor;
	planar_face_traversal(g, &emb[0], count_visitor, get(&EdgeProperty::id, g));
	cout << "Traversing faces of planar embedding... the planar embedding of the graph has " << count_visitor.count << " faces." << endl;
	cout << endl << "Vertices on the faces: " << endl;
	vertex_output_visitor v_vis;
	planar_face_traversal(g, &emb[0], v_vis, get(&EdgeProperty::id, g));
	cout << endl << "Edges on the faces: " << endl;
	edge_output_visitor e_vis;
	planar_face_traversal(g, &emb[0], e_vis, get(&EdgeProperty::id, g));
}
/*
Edge_desc MyGraph::id_to_edge(int e){
	Edge_desc result;
	Edge_iter ei,ef;
	tie(ei,ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].id == e){result = *ei;}
	}
	return result;
}
*/
