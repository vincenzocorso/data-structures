#ifndef GRAPH_H
#define GRAPH_H

#include "slist.h"

typedef struct vertex_t *vertex_ptr;

int vertex_get_id(vertex_ptr vertex);
void vertex_set_data(vertex_ptr vertex, void *data);
void *vertex_get_data(vertex_ptr vertex);

typedef struct edge_t *edge_ptr;

vertex_ptr edge_get_source(edge_ptr edge);
vertex_ptr edge_get_destination(edge_ptr edge);
double edge_get_weight(edge_ptr edge);
void edge_set_data(edge_ptr edge, void *data);
void *edge_get_data(edge_ptr edge);

typedef struct graph_t *graph_ptr;

graph_ptr graph_create(size_t nvertices);
size_t graph_get_nvertices(graph_ptr graph);
size_t graph_get_nedges(graph_ptr graph);
edge_ptr graph_add_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination, double weight);
void graph_delete_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination);
edge_ptr graph_get_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination);
slist_ptr graph_get_adj_vertices(graph_ptr graph, vertex_ptr vertex);
vertex_ptr graph_get_vertex(graph_ptr graph, int id);
slist_ptr graph_get_edges(graph_ptr graph);
void graph_free(graph_ptr graph);

#endif