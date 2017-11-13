#ifndef YANG_A_GRAPH_DIJK_H_
#define YANG_A_GRAPH_DIJK_H_
/*
 * dijkstra.h
 *
 *  Created on:
 *      Author:
 *  Based on:
 *  https://rosettacode.org/wiki/Dijkstra%27s_algorithm
 *
 *  Copyright @ 2017. CHUNFENG YANG. All Rights Reserved.
 *  Permission to use, copy, modify, and distribute this software
 *  and its documentation for educational, research, and
 *  not-for-profit purposes, without fee and without a signed
 *  above copyright notice, this paragraph and the following two
 *  distributions.
 *  IN NO EVENT SHALL CHUNFENG YANG BE LIABLE TO ANY PARTY FOR
 *  DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 *  DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS
 *  SOFTWARE AND ITS DOCUMENTATION, EVEN IF CHUNFENG YANG HAS BEEN
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  CHUNFENG YANG SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 *  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *  AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE AND
 *  ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
 *  PROVIDED "AS IS". CHUNFENG YANG HAS NO OBLIGATION TO PROVIDE
 *  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

class Edge
{
public:
	Edge();
	virtual ~Edge();

public:
	void show();

public:
	int _vertex;
	double _weight;
};

class Vertex
{
public:
	Vertex();
	virtual ~Vertex();
public:
	void addEdge(Edge*);
	void setDist(double);
	double getDist();
	void setPrev(int);
	int getPrev();
	void setVisited(int);
	int getVisited();
	int edgeLength();
	Edge* getEdge(int);

	void show();
public:
	Edge **_edges;
	int _edges_len;
	int _edges_size;
	double _dist;
	int _prev;
	int _visited;
};

class Graph
{
public:
	Graph();
	virtual ~Graph();

public:
	void addVertex(int i);
	void addEdge(int a, int b, double w);
	void dijkstra(int a, int b);
	double distance(int i, int j);	
	void print_path(int);
	void show();
	int length();
public:
	Vertex **_vertices;
	int _vertices_len;
	int _vertices_size;
};

class Heap
{
public:
	Heap();
	Heap(int n);
	virtual ~Heap();

public:
	void push(int v, double p);
	int pop();
	int minimize(int i, int j, int k);
	int length();
	void show();
	void clean();
public:
	int *_data;
	double *_prio;
	int *_index;
	int _len;
	int _size;
};

#endif // YANG_A_GRAPH_DIJK_H_
