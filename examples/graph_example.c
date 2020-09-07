#include <stdio.h>
#include "graph.h"

int main() {
	int edges[9][2] = {
		{0, 5},
		{0, 4},
		{0, 3},
		{0, 1},
		{1, 2},
		{2, 1},
		{3, 0},
		{3, 2},
		{4, 3}
	};
	vertex_ptr vertices[6];

	graph_ptr graph = graph_create(6);
	for(int i = 0; i < 6; i++)
		vertices[i] = graph_get_vertex(graph, i);

	printf("nvertice: %d | nedges: %d\n", graph_get_nvertices(graph), graph_get_nedges(graph));

	for(int i = 0; i < 9; i++)
		graph_add_edge(graph, vertices[edges[i][0]], vertices[edges[i][1]], 0.0);
	
	printf("nvertice: %d | nedges: %d\n", graph_get_nvertices(graph), graph_get_nedges(graph));

	graph_add_edge(graph, vertices[2], vertices[0], 0.0);

	printf("nvertice: %d | nedges: %d\n", graph_get_nvertices(graph), graph_get_nedges(graph));

	edge_ptr edge = graph_get_edge(graph, vertices[2], vertices[0]);
	vertex_ptr source = edge_get_source(edge);
	vertex_ptr destination = edge_get_destination(edge);
	printf("source: %d | destination: %d | weight: %f\n", vertex_get_id(source), vertex_get_id(destination), edge_get_weight(edge));

	graph_delete_edge(graph, vertices[2], vertices[0]);
	printf("nvertice: %d | nedges: %d\n", graph_get_nvertices(graph), graph_get_nedges(graph));
	edge = graph_get_edge(graph, vertices[2], vertices[0]);
	if(edge == NULL)
		printf("Edge not found\n");
	
	slist_ptr adj_list = graph_get_adj_vertices(graph, vertices[0]);
	slist_iter_ptr iter = slist_iter_forward(adj_list, NULL);
	while(slist_iter_has_next(iter)) {
		vertex_ptr vertex = slist_iter_next_element(iter);
		printf("%d ", vertex_get_id(vertex));
	}
	printf("\n");
	slist_iter_free(iter);
	slist_free(adj_list);

	slist_ptr edges_list = graph_get_edges(graph);
	iter = slist_iter_forward(edges_list, NULL);
	while(slist_iter_has_next(iter)) {
		edge_ptr edge = slist_iter_next_element(iter);
		vertex_ptr source = edge_get_source(edge);
		vertex_ptr destination = edge_get_destination(edge);
		printf("source: %d | destination: %d | weight: %f\n", vertex_get_id(source), vertex_get_id(destination), edge_get_weight(edge));
	}
	slist_iter_free(iter);
	slist_free(edges_list);

	graph_free(graph);

	return 0;
}