#include <stdlib.h>
#include "slist.h"
#include "dlist.h"
#include "graph.h"

typedef struct vertex_t {
	int id;
	void *data;
	slist_ptr adj_list;
} vertex_t;

typedef struct edge_t {
	vertex_ptr source;
	vertex_ptr destination;
	double weight;
	void *data;
} edge_t;

typedef struct graph_t {
	size_t nvertices;
	size_t nedges;
	vertex_ptr *vertices;
	dlist_ptr edges;
} graph_t;

static vertex_ptr vertex_create(int id) {
	vertex_ptr vertex = malloc(sizeof(vertex_t));
	if(vertex != NULL) {
		vertex->id = id;
		vertex->data = NULL;
		vertex->adj_list = NULL;
	}
	return vertex;
}

int vertex_get_id(vertex_ptr vertex) {
	return vertex->id;
}

void vertex_set_data(vertex_ptr vertex, void *data) {
	vertex->data = data;
}

void *vertex_get_data(vertex_ptr vertex) {
	return vertex->data;
}

static void vertex_free(void *vertex) {
	free(vertex);
}

static edge_ptr edge_create(vertex_ptr source, vertex_ptr destination, double weight) {
	edge_ptr edge = malloc(sizeof(edge_t));
	if(edge != NULL) {
		edge->source = source;
		edge->destination = destination;
		edge->weight = weight;
		edge->data = NULL;
	}
	return edge;
}

vertex_ptr edge_get_source(edge_ptr edge) {
	return edge->source;
}

vertex_ptr edge_get_destination(edge_ptr edge) {
	return edge->destination;
}

double edge_get_weight(edge_ptr edge) {
	return edge->weight;
}

void edge_set_data(edge_ptr edge, void *data) {
	edge->data = data;
}

void *edge_get_data(edge_ptr edge) {
	return edge->data;
}

static void edge_free(void *edge) {
	free(edge);
}

graph_ptr graph_create(size_t nvertices) {
	graph_ptr graph = malloc(sizeof(graph_t));
	if(graph != NULL) {
		graph->nvertices = nvertices;
		graph->nedges = 0;
		graph->vertices = malloc(graph->nvertices * sizeof(vertex_ptr));
		for(int i = 0; i < graph->nvertices; i++) {
			graph->vertices[i] = vertex_create(i);
			graph->vertices[i]->adj_list = slist_create();
		}
		graph->edges = dlist_create();
	}
	return graph;
}

size_t graph_get_nvertices(graph_ptr graph) {
	return graph->nvertices;
}

size_t graph_get_nedges(graph_ptr graph) {
	return graph->nedges;
}

edge_ptr graph_add_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination, double weight) {
	edge_ptr edge = edge_create(source, destination, weight);
	dlist_node_ptr dlnode = dlist_insert_element_after(graph->edges, NULL, edge);
	slist_insert_element_after(source->adj_list, NULL, dlnode);
	(graph->nedges)++;
	return edge;
}

void graph_delete_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination) {
	slist_node_ptr previous_ptr = NULL;
	slist_iter_ptr iter = slist_iter_forward(source->adj_list, NULL);
	while(slist_iter_has_next(iter)) {
		slist_node_ptr node = slist_iter_next_node(iter);
		dlist_node_ptr dlnode = (dlist_node_ptr)slist_node_get_element(node);
		edge_ptr edge = (edge_ptr)dlist_node_get_element(dlnode);
		if(edge_get_destination(edge) == destination) {
			slist_delete_after(source->adj_list, previous_ptr);
			dlist_delete_current(graph->edges, dlnode);
			(graph->nedges)--;
			edge_free(edge);
			break;
		}
		previous_ptr = node;
	}
	slist_iter_free(iter);
}

edge_ptr graph_get_edge(graph_ptr graph, vertex_ptr source, vertex_ptr destination) {
	slist_iter_ptr iter = slist_iter_forward(source->adj_list, NULL);
	edge_ptr result = NULL;
	while(slist_iter_has_next(iter)) {
		dlist_node_ptr dlnode = (dlist_node_ptr)slist_iter_next_element(iter);
		edge_ptr edge = (edge_ptr)dlist_node_get_element(dlnode);
		if(edge_get_destination(edge) == destination) {
			result = edge;
			break;
		}
	}
	slist_iter_free(iter);
	return result;
}

slist_ptr graph_get_adj_vertices(graph_ptr graph, vertex_ptr vertex) {
	slist_ptr result = slist_create();
	slist_iter_ptr iter = slist_iter_forward(vertex->adj_list, NULL);
	while(slist_iter_has_next(iter)) {
		dlist_node_ptr dlnode = (dlist_node_ptr)slist_iter_next_element(iter);
		edge_ptr edge = (edge_ptr)dlist_node_get_element(dlnode);
		slist_insert_element_after(result, NULL, edge_get_destination(edge));
	}
	slist_iter_free(iter);
	return result;
}

vertex_ptr graph_get_vertex(graph_ptr graph, int id) {
	return graph->vertices[id];
}

slist_ptr graph_get_edges(graph_ptr graph) {
	slist_ptr result = slist_create();
	dlist_iter_ptr iter = dlist_iter_forward(graph->edges, NULL);
	while(dlist_iter_has_next(iter)) {
		edge_ptr edge = (edge_ptr)dlist_iter_next_element(iter);
		slist_insert_element_after(result, NULL, edge);
	}
	dlist_iter_free(iter);
	return result;
}

void graph_free(graph_ptr graph) {
	dlist_free_aux(graph->edges, edge_free);
	for(int i = 0; i < graph->nvertices; i++) {
		slist_free(graph->vertices[i]->adj_list);
		vertex_free(graph->vertices[i]);
	}
	free(graph->vertices);
	free(graph);
}