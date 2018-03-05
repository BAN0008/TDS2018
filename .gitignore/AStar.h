#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

class Path
{
protected:
	class Node //Should probably be public so that other objects can use lists of nodes to read generated paths : unless i decide to use Point
	{
	public:
		Node(unsigned x, unsigned y, unsigned endX, unsigned endY, Node* parent = nullptr);
		unsigned x, y, f, g, h;
		Node* parent;
		bool open = true;
		bool constant = false;
	};
public:
	Path(unsigned width, unsigned height);
	void addWall(unsigned x, unsigned y);
	int findPath(unsigned startX, unsigned startY, unsigned endX, unsigned endY);
	int generatePath(); //Merge into findPath()
	void print(int startX, int startY, int endX, int endY); //Debug
	class Point
	{
	public:
		//friend class Path;
		Point(Node* node, Point* prevPoint);
		int x, y;
		double vx, vy;
	};
	Point* operator[](unsigned i);
	unsigned size();
private:
	std::vector<Point*> path; //Change type to Node make Node public and delete Point?
	unsigned width, height;
	unsigned lastStartX, lastStartY, lastEndX, lastEndY;
	std::vector<std::vector<Node*>> nodeMap;
};

#endif //ASTAR_H