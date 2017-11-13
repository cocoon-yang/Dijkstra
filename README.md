# Dijkstra
Node.js module of Dijkstra algorithm


Only header files and souse files of the Dijkstra algorighm are provided, the other foldes, such as /node, /lib, /Build/Release, are the same as in https://github.com/cocoon-yang/fann-node


Example:
```JavaScript
var Graph = require ("../Build/Release/dijkstra").YDijkstra;
var theGraph =  new Graph();

var Response  = [ 368.15, 1554.25, 378.33, 1535.03, 371.88,
		1549.879, 379.2, 1542.57, 381.61, 1531.18, 370.52, 1544.97,
		373.13, 1552.75, 381.28, 1542.18, 371.81, 1554.08, 367.52, 1552.81,
		369.27, 1559.198, 375.67, 1545.7, 367.79, 1552.17, 367.77,
		1564.72, 377.95, 1544.34, 382.58, 1537.07, 379.66,
		1537.639, 366.74, 1563.139, 375.73, 1537.82, 369.91,
		1560.4, 382.49, 1528.21, 371.1, 1547.09, 369.64,
		1552.61, 378.79, 1538.99, 376.95, 1540.72, 373.38, 1557.81,
		384.44, 1532.85, 375.26, 1544.899, 369.58, 1557.18,
		372.16, 1542.99, 368.37, 1561.82, 372.35, 1545.54, 370.07, 1552.03,
		369.45, 1553.06, 377.07, 1540.05, 381.37, 1541.94, 379.6,
		1536.418, 373.52, 1542.91, 380.81, 1536.92, 377.3,
		1548.149, 380.6, 1547.33, 372.21,
		1548.04, 370.67, 1548.38, 375.38, 1547.4, 370.39, 1559.03,
		374.37, 1541.11, 371.03, 1544.13, 370.46, 1544.71, 382.16, 1535.18,
		373.5, 1547.649, 379.39, 1529.8, 376.66, 1549.45, 388.47,
		1526.88, 373.08, 1548.74, 379.2, 1542.5, 374.95, 1551.22, 363.41,
		1560.55, 370.65, 1554.51, 366.84, 1563.35, 379.72, 1532.87,
		366.4, 1564.32, 377, 1546.32, 377, 1546.32, 369.48, 1548.3, 382.52,
		1527.649, 378.91, 1530.56, 382.18, 1529.07, 368.14, 1554.09,
		372.08, 1552.49, 372.63, 1546.73, 363.33, 1562.73, 377.78,
		1545.87, 381.2, 1539.75, 366.7, 1566.65, 379.27, 1536.14,
		377.38, 1539.5, 368.16, 1553.3, 371.06, 1552.58, 371.77,
		1549.57, 369.72, 1556.98, 374.04, 1543.409, 374.69, 1542.81,
		378.07, 1536.31, 379.01, 1541.86, 370.63, 1544.78, 371.82,
		1556.418, 371.94, 1542.688, 373.78, 1548.38, 373.33,
		1552.74, 376.59, 1538.31, 372.83, 1540.61, 371.52,
		1543.61, 372.87, 1542.14, 367.81, 1552.72, 367.81, 1552.72, 372.94,
		1545.48, 375.06, 1541.879, 378.56, 1536.35, 365.08,
		1559.06, 372.45, 1553.26 ];

var DIMENSION = 2;
var i;

function get( i,  j) {
	var N = DIMENSION;
	var index = i * N + j;
	var value = Response[index];
	return value;
}
 
function distance(  v1,   v2) {
	var sum = 0.0;
	for (var i = 0; i < DIMENSION; i++) {
		var x1 = get(v1, i);
		var x2 = get(v2, i);
		var dx = x1 - x2;
		sum += dx * dx;
	}
	return Math.sqrt(sum);
} 
 
function test() { 
	theGraph.addVertex(1);

	var setNumber = 200;
	for (var i = 0; i < setNumber-4; i++) {
		for (var j = i + 1; j < setNumber; j++) {
			var tmp = distance(i, j);
			//  prvarf( "i = %d, j = %d, %f \n", i, j, tmp );
			if (tmp <  5.5)
			{
				theGraph.addEdge( i,  j, tmp);
			}
		}
	}
	theGraph.distance( 25, 60);
	theGraph.path(60);
	theGraph.show();
} 
 
test();
``` 
 
