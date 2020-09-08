#ifndef GRAPH_H
#define GRAPH_H

#include "slist.h"

typedef struct vertex_t *vertex_ptr;

/*	Get the id of the given vertex.
	vertex: a pointer to the given vertex.
	return: the id of the given vertex.
*/
int vertex_get_id(vertex_ptr vertex);

/*	Set the data of the given vertex.
	vertex: a pointer to the given vertex.
	data: a pointer to data.
*/
void vertex_set_data(vertex_ptr vertex, void *data);

/*	Get the data of the given vertex.
	vertex: a pointer to the given vertex.
	return: a pointer to the data of the given vertex.
*/
void *vertex_get_data(vertex_ptr vertex);



typedef struct edge_t *edge_ptr;

/*	Get the source of the given edge.
	edge: a pointer to the given edge.
	return: the source vertex of the given edge.
*/
vertex_ptr edge_get_source(edge_ptr edge);

/*	Get the destination of the given edge.
	edge: a pointer to the given edge.
	return: the destination vertex of the given edge.
*/
vertex_ptr edge_get_destination(edge_ptr edge);

/*	Get the weight of the given edge.
	edge: a pointer to the given edge.
	return: the weight of the given edge.
*/
double edge_get_weight(edge_ptr edge);

/*	Set the data of the given edge.
	edge: a pointer to the given edge.
	data: a pointer to the data of the given edge.
*/
void edge_set_data(edge_ptr edge, void *data);

/*	Get the data of the given edge.
	edge: a pointer to the given edge.
	return: a pointer to the data of the given edge.
*/
void *edge_get_data(edge_ptr edge);



typedef struct graph_t *graph_ptr;

/*	Create a graph with some vertices (without edges).
	nvertices: the number of vertices.
	return: a pointer to the graph.
*/
graph_ptr graph_create(size_t nvertices);

/*	Get the number of vertices.
	graph: a pointer to the graph.
	return: the number of vertices.
*/
size_t graph_get_nvertices(graph_ptr graph);

/*	Get the number of edges.
	graph: a pointer to the graph.
	return: the number of edges.
*/
size_t graph_get_nedges(graph_ptr graph);

/*	Add a new edge in the graph.
	graph: a pointer to the graph.
	source: a pointer to the source vertex.
	destination: a pointer to the destination vertex.
	weight: the weight of the new edge.
	return: a pointer to the new edge.
*/
edge_ptr graph_add_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination, double weight);

/*	Delete an edge from the graph.
	graph: a pointer to the graph.
	source: a pointer to the source vertex.
	destination: a pointer to the destination vertex.
*/
void graph_delete_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination);

/*	Get an edge in the graph.
	graph: a pointer to the graph.
	source: a pointer to the source vertex.
	destination: a pointer to the destination vertex.
	return: a pointer to the given edge if it's exists, NULL otherwise.
*/
edge_ptr graph_get_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination);

/*	Get the vertices adjacent to a given vertex.
	graph: a pointer to the graph.
	vertex: a pointer to the given vertex.
	return: a single linked list of adjacent vertices.
*/
slist_ptr graph_get_adj_vertices(graph_ptr graph, vertex_ptr vertex);

/*	Get a specific vertex in the graph.
	graph: a pointer to the graph.
	id: the id of the vertex.
	return: a pointer to the vertex.
*/
vertex_ptr graph_get_vertex(graph_ptr graph, int id);

/*	Get the edges in the graph.
	graph: a pointer to the graph.
	return: a single linked list of edges.
*/
slist_ptr graph_get_edges(graph_ptr graph);

/*	Free the memory allocated for the graph, vertices and edges.
	graph: a pointer to the graph.
*/
void graph_free(graph_ptr graph);

#endif