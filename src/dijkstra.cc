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

#include "dijkstra.h"
#include <float.h>

//
//  Edge
//
Edge::Edge()
{
	_vertex = 0;
	_weight = 0;
}

Edge::~Edge()
{
}

void Edge::show()
{
	printf("vertex: %-8d  weight: %-3f  \n", _vertex, _weight);
}

//
// Vertex
//
Vertex::Vertex()
{
	_edges = NULL;
	_edges_len = 0;
	_edges_size = 0;
	_dist = 0;
	_prev = 0;
	_visited = 0;
}

Vertex::~Vertex()
{
	if (NULL != _edges)
	{
		for (int i = 0; i < _edges_len; i++)
		{
			Edge* pEdge = _edges[i];
			free(pEdge);
		}
		free(_edges);
		_edges = NULL;
		return;
	}

}
void Vertex::addEdge(Edge *e)
{
	if (NULL == e)
	{
		return;
	}
	if (_edges_len >= _edges_size)
	{
		_edges_size = _edges_size ? _edges_size * 2 : 4;
		_edges = (Edge **) realloc(_edges, _edges_size * sizeof(Edge *));
		if (NULL == _edges)
		{
			_edges_size = 0;
			_edges_len = 0;
			_dist = 0;
			_prev = 0;
			_visited = 0;
			return;
		}
	}
	_edges[_edges_len++] = e;
}
Edge* Vertex::getEdge(int index)
{
	if ((index < 0) || (index >= _edges_len))
	{
		return NULL;
	}
	if (NULL == _edges)
	{
		return NULL;
	}
	return _edges[index];
}
int Vertex::edgeLength()
{
	return _edges_len;
}
void Vertex::Vertex::setDist(double value)
{
	_dist = value;
}
double Vertex::getDist()
{
	return _dist;
}
void Vertex::setPrev(int value)
{
	_prev = value;
}
int Vertex::getPrev()
{
	return _prev;
}
void Vertex::setVisited(int value)
{
	_visited = value;
}
int Vertex::getVisited()
{
	return _visited;
}
void Vertex::show()
{
	if (NULL == _edges)
	{
		return;
	}
	for (int i = 0; i < _edges_len; i++)
	{
		Edge* pEdge = _edges[i];
		pEdge->show();
	}
	printf("dist = %f \t", _dist);
	printf("prev = %d \t", _prev);
}

//
// Heap
//
Heap::Heap()
{
	_len = 0;
	_size = 0;
	_data = NULL;
	_prio = NULL;
	_index = NULL;

}

Heap::Heap(int n)
{
	_data = NULL;
	_prio = NULL;
	_index = NULL;
	_len = 0;
	_size = 0;
	if (n >= 0)
	{
		_data = (int*) calloc(n + 1, sizeof(int));
		_prio = (double*) calloc(n + 1, sizeof(double));
		_index = (int*) calloc(n, sizeof(int));
		if ((NULL == _data) || (NULL == _prio) || (NULL == _index))
		{
			clean();
			return;
		}
		for (int i = 0; i < n; i++)
		{
			_data[i] = 0;
			_prio[i] = 0;
			_index[i] = 0;
		}
		_data[n] = 0;
		_prio[n] = 0;
	}
	_size = n;
}

Heap::~Heap()
{
	if (NULL != _data)
	{
		free(_data);
		_data = 0;
	}
	if (NULL != _prio)
	{
		free(_prio);
		_prio = 0;
	}
	if (NULL != _index)
	{
		free(_index);
		_index = 0;
	}
}
int Heap::length()
{
	return _len;
}

void Heap::push(int v, double p)
{
	if (v < 0)
	{
		return;
	}
	if ((NULL == _data) || (NULL == _prio) || (NULL == _index))
	{
		printf("ERROR: Heap::push: _data is NULL. \n");
		return;
	}
	int i = _index[v] == 0 ? ++_len : _index[v];
	int j = i / 2;

	while (i > 1)
	{
		if (_prio[j] < p)
			break;
		_data[i] = _data[j];
		_prio[i] = _prio[j];
		_index[_data[i]] = i;
		i = j;
		j = j / 2;
	}

	_data[i] = v;
	_prio[i] = p;
	_index[v] = i;
	return;
}

int Heap::pop()
{
	if ((NULL == _data) || (NULL == _prio) || (NULL == _index))
	{
		printf("Heap::pop: data pointers invalid \n");
		return 0;
	}

	int v = _data[1];
	int i = 1;
	while (1)
	{
		int j = minimize(_len, 2 * i, 2 * i + 1);
		if (j == _len)
			break;
		_data[i] = _data[j];
		_prio[i] = _prio[j];
		_index[_data[i]] = i;
		i = j;
	}
	_data[i] = _data[_len];
	_prio[i] = _prio[_len];
	_index[_data[i]] = i;
	_len--;
	return v;
}

int Heap::minimize(int i, int j, int k)
{
	int m = i;
	if (j <= _len && _prio[j] < _prio[m])
		m = j;
	if (k <= _len && _prio[k] < _prio[m])
		m = k;
	return m;
}
void Heap::show()
{
	printf("Heap::show() \n");
	printf("    len = %d\n", _len);
	for (int i = 0; i < _len; i++)
	{
		printf("data[%d] = %d\n", i, _data[i]);
		printf("dist[%d] = %f\n", i, _prio[i]);
	}
}
//
// Graph
//
Graph::Graph()
{
	_vertices = NULL;
	_vertices_len = 0;
	_vertices_size = 0;
}
Graph::~Graph()
{
	if (NULL != _vertices)
	{
		for (int i = 0; i < _vertices_len; i++)
		{
			free(_vertices[i]);
		}
		free(_vertices);
		_vertices = 0;
	}
}

void Graph::addVertex(int i)
{
	if (i < 0)
	{
		return;
	}

	if (_vertices_size < i + 1)
	{
		int size = _vertices_size * 2 > i ? _vertices_size * 2 : i + 4;
		_vertices = (Vertex **) realloc(_vertices, size * sizeof(Vertex *));
		if (NULL == _vertices)
		{
			_vertices_len = 0;
			_vertices_size = 0;
			return;
		}
		for (int j = _vertices_size; j < size; j++)
			_vertices[j] = NULL;
		_vertices_size = size;
	}
	if (!_vertices[i])
	{
		_vertices[i] = (Vertex *) calloc(1, sizeof(Vertex));
		_vertices_len++;
	}
	return;
}

void Graph::addEdge(int a, int b, double w)
{
	if (NULL == _vertices)
	{
		printf("ERROR: Graph::addEdge: vertices pointer is NULL. \n");
		return;
	}
	a = a - 0;
	b = b - 0;
	addVertex(a);
	addVertex(b);
	Vertex *v = _vertices[a];
	if (v->_edges_len >= v->_edges_size)
	{
		v->_edges_size = v->_edges_size ? v->_edges_size * 2 : 4;
		v->_edges = (Edge **) realloc(v->_edges,
				v->_edges_size * sizeof(Edge *));
	}
	Edge *e = (Edge *) calloc(1, sizeof(Edge));
	if (NULL == e)
	{
		_vertices[a] = NULL;
		return;
	}
	e->_vertex = b;
	e->_weight = w;
	v->_edges[v->_edges_len++] = e;
}
void Graph::dijkstra(int a, int b)
{
	if (_vertices_len <= 0)
	{
		return;
	}
	int i, j;
	a = a - 0;
	b = b - 0;
	for (i = 0; i < _vertices_len; i++)
	{
		Vertex *v = _vertices[i];
		v->setDist(FLT_MAX);
		v->setPrev(0);
		v->setVisited(0);
	}
	Vertex *v = _vertices[a];
	v->setDist(0);
	Heap *h = new Heap(_vertices_len);
	if (NULL == h)
	{
		return;
	}
	h->push(a, v->getDist());
	int len = h->length();
	while (len)
	{
		i = h->pop();
		if (i == b)
			break;
		v = _vertices[i];
		v->setVisited(1);
		for (j = 0; j < v->edgeLength(); j++)
		{
			Edge *e = v->getEdge(j);
			Vertex *u = _vertices[e->_vertex];
			if (!u->getVisited() && v->getDist() + e->_weight <= u->getDist())
			{
				u->setPrev(i);
				u->setDist(v->getDist() + e->_weight);
				h->push(e->_vertex, u->getDist());
			}
		}
	}
}

void Heap::clean()
{
	free(_data);
	free(_prio);
	free(_index);
	_data = NULL;
	_prio = NULL;
	_index = NULL;
	_len = 0;
	_size = 0;
}
int Graph::length()
{
	return _vertices_len;
}
double Graph::distance(int i, int j)
{
	dijkstra(i, j);
	Vertex *v = _vertices[j];

	if (v->_dist == FLT_MAX)
	{
		printf("Vertex reached Maxium. \n no path\n");
		return 0.0;
	}

	double len = v->_dist;
	return len;
}
void Graph::show()
{
	printf("Graph::show()");
	printf(" len = %d\n", _vertices_len);

	if (NULL == _vertices)
	{
		printf("ERROR: Graph::show: vertices pointer is NULL. \n");
		return;
	}
	for (int i = 0; i < _vertices_len; i++)
	{
		Vertex* pVertex = _vertices[i];
		printf("Vertex -- %d \n", i);
		pVertex->show();
		printf("\n");
	}
}

void Graph::print_path(int i)
{

	printf("Path:  \n");

	int n, j;
	Vertex *v, *u;
	i = i - 0;
	v = _vertices[i];

	if (v->_dist == FLT_MAX)
	{
		printf("Vertex reached Maxium. \n no path\n");
		return;
	}

	double len = v->_dist;

	for (n = 1, u = v; u->_dist; u = _vertices[u->_prev], n++)
		;

	char *path = (char*) malloc(n + 1);
	if (NULL == path)
	{
		return;
	}
	path[n] = '\0';
	path[n - 1] = 0 + i;

	for (j = 0, u = v; u->_dist; u = _vertices[u->_prev], j++)
	{
		if (NULL == u)
		{
			break;
		}
		path[n - j - 2] = 0 + u->_prev;
	}
	printf("Length: %f  \n Route: %s \n", len, path);

//	i = i + 0;
	printf("%d", i);
	for (j = 0, u = v; u->_dist; u = _vertices[u->_prev], j++)
	{
		if (NULL == u)
		{
			break;
		}
		path[n - j - 2] = 0 + u->_prev;
		printf(" => %d", u->_prev);
	}
	printf(" \n", i);
	free(path);
}

