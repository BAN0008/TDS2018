/********************************************
*	TODO:									*
*		Add 4 more directions so the path	*
*		can be diagonal. In Progress(test)	*
*											*
*		Ensure functionality with non 1:1	*
*		map aspect ratio. Done				*
*											*
*		Define nodeMap properly with		*
*		variable dimensions	and a class		*
*		wide scope. Done					*
*											*
*		Make sure findPath cleans up		*
*		nodeMap with no memory leaks.		*
*											*
*		Extensively test.					*
*											*
*		Ensure that	checking for			*
*		obstructions when moving diagonally	*
*		uses || instead of &&. Done			*
*											*
*		Ensure that the algorithm behaves	*
*		sanely when there is no possible	*
*		path. Done							*
*											*
*		Fix issue with edges. Done			*
*											*
*		Change Path::print() so it doesn't	*
*		take arguments						*
********************************************/

#include <iostream>
#include "AStar.h"
#include <cmath>

Path::Path(unsigned width, unsigned height) : width(width), height(height)
{
	for (int i = 0; i < width; i++)
	{
		nodeMap.emplace_back(std::vector<Node*>());
		for (int j = 0; j < height; j++)
		{
			nodeMap[i].push_back(nullptr);
			//nodeMap[i][j] = nullptr;
		}
	}
	path = std::vector<Point*>();
}

void Path::addWall(unsigned x, unsigned y)
{
	if (nodeMap[x][y] == nullptr)
	{
		nodeMap[x][y] = new Node(x, y, 0, 0);
		nodeMap[x][y]->constant = true;
		nodeMap[x][y]->open = false;
	}
}

int Path::findPath(unsigned startX, unsigned startY, unsigned endX, unsigned endY)
{
	lastStartX = startX;
	lastStartY = startY;
	lastEndX = endX;
	lastEndY = endY;
	//Node* nodeMap[width][height];

	//Set all nodes to nullptr
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (nodeMap[i][j] != nullptr && !nodeMap[i][j]->constant)
			{
				nodeMap[i][j] = nullptr;
			}
		}
	}
	
	nodeMap[startX][startY] = new Node(startX, startY, endX, endY);
	//std::vector<Node> nodeList

	while (nodeMap[endX][endY] == nullptr)
	{
		//* Find the node with the lowest f that is open. This node will be called N
		Node* lowest = nullptr;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (nodeMap[i][j] != nullptr)
				{
					if (lowest != nullptr)
					{
						if (nodeMap[i][j]->open == true && nodeMap[i][j]->f < lowest->f)
						{
							lowest = nodeMap[i][j];
						}
					}
					else
					{
						if (nodeMap[i][j]->open) //Unsure
						{
							lowest = nodeMap[i][j];
						}
					}
				}
			}
		}
		
		//Check to see if there is no possible path
		if (lowest == nullptr)
		{
			return 1;
		}

		//* Change N to closed
		lowest->open = false;
		
		//* For each direction that the path can take relative to N
		int adjacentX, adjacentY;
		for (int i = 0; i < 4; i++)
		{
			bool skip = false;
			switch(i)
			{
				//Right
				case 0:
					adjacentX = lowest->x + 1;
					adjacentY = lowest->y;
					skip = (adjacentX > width - 1);
					break;
				//Left
				case 1:
					adjacentX = lowest->x - 1;
					adjacentY = lowest->y;
					skip = (adjacentX < 0);
					break;
				//Up
				case 2:
					adjacentX = lowest->x;
					adjacentY = lowest->y - 1;
					skip = (adjacentY < 0);
					break;
				//Down
				case 3:
					adjacentX = lowest->x;
					adjacentY = lowest->y + 1;
					skip = (adjacentY > height - 1);
					break;
				//Right-Up	
				case 4:
					adjacentX = lowest->x + 1;
					adjacentY = lowest->y - 1;
					//Should the below line check that nodes adjacent to the position adjacentX/Y are open rather than that their not constant?
					skip = (adjacentX > width - 1 || adjacentY < 0 || (nodeMap[adjacentX - 1][adjacentY] != nullptr && nodeMap[adjacentX - 1][adjacentY]->constant) || (nodeMap[adjacentX][adjacentY + 1] != nullptr && nodeMap[adjacentX][adjacentY + 1]->constant));
					break;
				//Right-Down	
				case 5:
					adjacentX = lowest->x + 1;
					adjacentY = lowest->y + 1;
					//Should the below line check that nodes adjacent to the position adjacentX/Y are open rather than that their not constant?
					skip = (adjacentX > width - 1 || adjacentY > height - 1 || (nodeMap[adjacentX - 1][adjacentY] != nullptr && nodeMap[adjacentX - 1][adjacentY]->constant) || (nodeMap[adjacentX][adjacentY - 1] != nullptr && nodeMap[adjacentX][adjacentY - 1]->constant));
					break;
				//Left-Up	
				case 6:
					adjacentX = lowest->x - 1;
					adjacentY = lowest->y - 1;
					skip = (adjacentX < 0 || adjacentY < 0 || (nodeMap[adjacentX + 1][adjacentY] != nullptr && nodeMap[adjacentX + 1][adjacentY]->constant) || (nodeMap[adjacentX][adjacentY + 1] != nullptr && nodeMap[adjacentX][adjacentY + 1]->constant));
					break;
				//Left-Down	
				case 7:
					adjacentX = lowest->x - 1;
					adjacentY = lowest->y + 1;
					skip = (adjacentX < 0 || adjacentY > height - 1 || (nodeMap[adjacentX + 1][adjacentY] != nullptr && nodeMap[adjacentX + 1][adjacentY]->constant) || (nodeMap[adjacentX][adjacentY - 1] != nullptr && nodeMap[adjacentX][adjacentY - 1]->constant));
					break;
				
			}
			//if (adjacentX >= 0 && adjacentX < width && adjacentY >= 0 && adjacentY < height) //Ensure adjacentX/Y isn't out of bounds
			if (!skip)
			{
				//If there is no node create one
				if (nodeMap[adjacentX][adjacentY] == nullptr)
				{
					nodeMap[adjacentX][adjacentY] = new Node(adjacentX, adjacentY, endX, endY, lowest);
				}
				//If there exists a node that's open check if it's f is lower-
				//when using the path used by N of so then change it's parent to N
				else
				{
					if (nodeMap[adjacentX][adjacentY]->open && nodeMap[adjacentX][adjacentY]->f > (nodeMap[adjacentX][adjacentY]->h + lowest->g + 1))
					{				
						nodeMap[adjacentX][adjacentY]->f = nodeMap[adjacentX][adjacentY]->h + lowest->g + 1;
						nodeMap[adjacentY][adjacentY]->parent = lowest;
					}
				}
			}
		}
	}
	return 0;
}

/********************
*	'.'	= empty		*
*	'#'	= wall		*
*	'O'	= path		*
*	'&'	= closed	*
********************/
void Path::print(int startX, int startY, int endX, int endY) //Debug
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (nodeMap[j][i] != nullptr)
			{
				if (!nodeMap[j][i]->constant)
				{
					if (nodeMap[endX][endY] != nullptr)
					{
						Node* child = nodeMap[endX][endY];
						while(child != nodeMap[j][i] && child != nodeMap[startX][startY])
						{
							if (child->parent != nullptr)
							{
								child = child->parent;
							}
						}
						if (child != nodeMap[j][i])
						{
							std::cout << '&';
						}
						else
						{
							std::cout << 'O';
						}
					}
				}
				else
				{
					std::cout << '#';
				}
			}
			else
			{
				std::cout << '.';
			}
		}
		std::cout << std::endl;
	}
}

Path::Node::Node(unsigned x, unsigned y, unsigned endX, unsigned endY, Node* parent) : x(x), y(y), parent(parent)
{
	//Make sure walls arn't used in the path
	//also make sure that the starting node's scores are correctly calculated
	//if (parent != nullptr)
	//{
	//	g = parent->g + 1;
	//}
	if (parent != nullptr)
	{
		g = parent->g + 1;
	}
	else
	{
		g = 0;
	}
	int vx = endX - x; //vx/vy should probably contain an absolute value
	int vy = endY - y; //
	//h = sqrt((vx*vx)+(vy*vy));
	h = vx + vy;
	f = g + h;
}

int Path::generatePath()
{
	Node* i = nodeMap[lastEndX][lastEndY];
	path.clear();
	while (i != nodeMap[lastStartX][lastStartY])
	{
		if (path.size() != 0)
		{
			//path.insert(path.end(), new Point(i, path[path.size() - 1]));
			//path.push_back(new Point(i, path[0]));
			path.insert(path.begin(), new Point(i, path[0]));
		}
		else
		{
			path.push_back(new Point(i, nullptr));
		}
		i = i->parent;
		/*
		if (path.size() != 0)
		{
			path.push_back(new Point(i, path[path.size() - 1]));
		}
		else
		{
			path.push_back(new Point(i, nullptr));
		}
		*/
	}
	path[0]->vx = (path[1]->x * 32) - (path[0]->x * 32);
	path[0]->vy = (path[1]->y * 32) - (path[0]->y * 32);
	double length = std::sqrt((path[0]->vx * path[0]->vx) + (path[0]->vy * path[0]->vy));
	path[0]->vx = path[0]->vx / length;
	path[0]->vy = path[0]->vy / length;

}

Path::Point::Point(Node* node, Point* prevPoint)
{
	x = node->x;
	y = node->y;

	if (prevPoint != nullptr)
	{
		prevPoint->vx = (prevPoint->x * 32) - (x * 32);
		prevPoint->vy = (prevPoint->y * 32) - (y * 32);
		double length = std::sqrt((prevPoint->vx * prevPoint->vx) + (prevPoint->vy * prevPoint->vy));
		prevPoint->vx = prevPoint->vx / length;
		prevPoint->vy = prevPoint->vy / length;
	}
	vx = 0;
	vy = 0;
	/*
	if (prevPoint != nullptr)
	{
		vx = (prevPoint->x * 32) - (x * 32);
		vy = (prevPoint->y * 32) - (y * 32);
		double length = std::sqrt((vx * vx) + (vy * vy));
		//std::cout << length;
		//prevPoint->vx = vx / length;
		//prevPoint->vy = vy / length;
		vx = (vx / length);
		vy = (vy / length);
	}
	//vx = 0;
	//vy = 0;
	*/
}

Path::Point* Path::operator[](unsigned i)
{
	return path[i];
}

unsigned Path::size()
{
	return path.size();
}