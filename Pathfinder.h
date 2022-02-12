//
// Created by Brandon on 2/5/2022.
//
#pragma once

#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

#include "PathfinderInterface.h"
//#include "..\..\_code\Utilities\Toolkit.h"
//using namespace Toolkit;

struct Vector3
{
public:
	double x, y, z;

	Vector3(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}

#pragma region Direction Properties

	static Vector3 back()
	{
		return Vector3(0, 0, -1);
	}

	static Vector3 forward()
	{
		return Vector3(0, 0, 1);
	}

	static Vector3 left()
	{
		return Vector3(-1, 0, 0);
	}

	static Vector3 right()
	{
		return Vector3(1, 0, 0);
	}

	static Vector3 up()
	{
		return Vector3(0, 1, 0);
	}

	static Vector3 down()
	{
		return Vector3(0, -1, 0);
	}

	static Vector3 one()
	{
		return Vector3(1, 1, 1);
	}

	static Vector3 zero()
	{
		return Vector3(0, 0, 0);
	}

#pragma endregion

#pragma region Operator Overloads

	Vector3 operator+(const Vector3& v) const
	{
		Vector3 vector3;
		vector3.x = this->x + v.x;
		vector3.y = this->y + v.y;
		vector3.z = this->z + v.z;
		return vector3;
	}

	void operator+=(const Vector3& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	Vector3 operator-(const Vector3& v) const
	{
		Vector3 vector3;
		vector3.x = this->x - v.x;
		vector3.y = this->y - v.y;
		vector3.z = this->z - v.z;
		return vector3;
	}

	void operator-=(const Vector3& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	Vector3 operator*(const int& i) const
	{
		Vector3 vector3;
		vector3.x = this->x * i;
		vector3.y = this->y * i;
		vector3.z = this->z * i;
		return vector3;
	}

	Vector3 operator*(const double& f) const
	{
		Vector3 vector3;
		vector3.x = this->x * f;
		vector3.y = this->y * f;
		vector3.z = this->z * f;
		return vector3;
	}

	Vector3 operator*(const float& f) const
	{
		Vector3 vector3;
		vector3.x = this->x * f;
		vector3.y = this->y * f;
		vector3.z = this->z * f;
		return vector3;
	}

	Vector3 operator*(const Vector3& v) const
	{
		Vector3 vector3;
		vector3.x = this->x * v.x;
		vector3.y = this->y * v.y;
		vector3.z = this->z * v.z;
		return vector3;
	}

	void operator*=(const Vector3& v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
	}

	Vector3 operator/(const Vector3& v) const
	{
		Vector3 vector3;
		vector3.x = this->x / v.x;
		vector3.y = this->y / v.y;
		vector3.z = this->z / v.z;
		return vector3;
	}

	void operator/=(const Vector3& v)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
	}

	Vector3 operator=(const Vector3& v)
	{
		Vector3 vector3;
		vector3.x = v.x;
		vector3.y = v.y;
		vector3.z = v.z;
		return vector3;
	}

	bool operator==(const Vector3& v) const
	{
		if (this->x != v.x) return false;
		if (this->y != v.y) return false;
		if (this->z != v.z) return false;
		return true;
	}

	bool operator!=(const Vector3& v) const
	{
		if (this->x != v.x) return true;
		if (this->y != v.y) return true;
		if (this->z != v.z) return true;
		return false;
	}

#pragma endregion

};

const int COL_SIZE = 5;
const int ROW_SIZE = 5;
const int HALL_SIZE = 5;

const int WALL = 0;
const int GROUND = 1;
const int TEMPORARY = 2; // Marker to show already explored
const int PATH = 3;

const Vector3 STARTING_POS = Vector3::zero();
const Vector3 ENDING_POS   = {COL_SIZE-1,ROW_SIZE-1,HALL_SIZE-1};

class Pathfinder : public PathfinderInterface
{
protected:
	int maze_grid[ROW_SIZE][COL_SIZE][HALL_SIZE]; // to hold values
	int path_grid[ROW_SIZE][COL_SIZE][HALL_SIZE];

	vector<string> solution;

public:

	Pathfinder();
	~Pathfinder() override;


	bool find_maze_path(int grid[COL_SIZE][ROW_SIZE][HALL_SIZE], Vector3 position);

	string toString() const override;

	void createRandomMaze() override;

	bool importMaze(string file_name) override;

	vector<string> solveMaze() override;

};
/*
class Node
{
public:
	bool walkable;
	Vector3 worldPosition;

	int gridX, gridY, gridZ;

	bool operator==(const Node& n) const
	{
		if (this->gridX != n.gridX) return false;
		if (this->gridY != n.gridY) return false;
		if (this->gridZ != n.gridZ) return false;
		return true;
	}

	bool operator!=(const Node& n) const
	{
		if (this->gridX != n.gridX) return true;
		if (this->gridY != n.gridY) return true;
		if (this->gridZ != n.gridZ) return true;
		return false;
	}

	int fCost, gCost, hCost;
	Node* parent;

	Node(bool _walkable, Vector3 _worldPos, int _gridX, int _gridY, int _gridZ)
			: walkable(_walkable), worldPosition(_worldPos), gridX(_gridX), gridY(_gridY), gridZ(_gridZ)
	{}

	int fcost() const
	{
		return gCost + hCost;
	};

};



class Grid
{
public:
	bool operator!=(void* ptr)
	{
		for (int c = 0; c < COL_SIZE; c++)
		{
			for (int r = 0; r < ROW_SIZE; r++)
			{
				for (int h = 0; h < HALL_SIZE; h++)
				{
					if (grid[c][r][h] != ptr)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	Node* grid[COL_SIZE][ROW_SIZE][HALL_SIZE];

	int gridSizeX, gridSizeY, gridSizeZ;
	Vector3 gridWorldSize;
	float nodeRadius = 1;

	float nodeDiameter;

	Pathfinder& pf;

	vector<Node> path;

	Grid(Pathfinder& pfPtr) : pf(pfPtr)
	{
		nodeDiameter = nodeRadius * 2;
		gridSizeX = round(gridWorldSize.x / nodeDiameter);
		gridSizeY = round(gridWorldSize.y / nodeDiameter);
		gridSizeZ = round(gridWorldSize.z / nodeDiameter);
		CreateGrid();
	}

	void CreateGrid()
	{
		Vector3 mazeStart = {0, 0, 0};
		//transform.position - Vector3::right() * gridWorldSize.x / 2 - Vector3::forward() * gridWorldSize.y / 2;

		for (int z = 0; z < gridSizeZ; z++)
		{
			for (int y = 0; y < gridSizeY; y++)
			{
				for (int x = 0; x < gridSizeX; x++)
				{
					Vector3 worldPoint = mazeStart +
										 Vector3::right() 	* (x * nodeDiameter + nodeRadius) +
										 Vector3::forward() * (y * nodeDiameter + nodeRadius) +
										 Vector3::up() 		* (z * nodeDiameter + nodeRadius);
					bool walkable = (pf.GetPathGridPos(x,y,z) == 0) ? false : true;
					// bool walkable = !(Physics.CheckSphere(worldPoint, nodeRadius, unwalkableMask));
					grid[x][y][z] = new Node(walkable, worldPoint, x, y, z);
				}
			}
		}
	}

	vector<Node> GetNeighbours(Node node)
	{
		vector<Node> neighbours;

		for (int z = -1; z <= 1; z++)
		{
			for (int y = -1; y <= 1; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (x == 0 && y == 0 && z == 0)
						continue;

					int checkX = node.gridX + x;
					int checkY = node.gridY + y;
					int checkZ = node.gridZ + z;

					if (checkX >= 0 && checkX < gridSizeX &&
						checkY >= 0 && checkY < gridSizeY &&
						checkZ >= 0 && checkZ < gridSizeZ)
					{
						neighbours.push_back(*grid[checkX][checkY][checkZ]);
					}
				}
			}
		}

		return neighbours;
	}

	Node NodeFromWorldPoint(Vector3 worldPosition)
	{
		double percentX = (worldPosition.x + gridWorldSize.x / 2) / gridWorldSize.x;
		double percentY = (worldPosition.y + gridWorldSize.y / 2) / gridWorldSize.y;
		double percentZ = (worldPosition.z + gridWorldSize.z / 2) / gridWorldSize.z;
		percentX *= 100; // Mathf.Clamp01(percentX);
		percentY *= 100; // Mathf.Clamp01(percentY);
		percentZ *= 100; // Mathf.Clamp01(percentZ);

		int x = round((gridSizeX - 1) * percentX);
		int y = round((gridSizeY - 1) * percentY);
		int z = round((gridSizeZ - 1) * percentZ);
		return *grid[x][y][z];
	}


	void OnDrawGizmos()
	{
		//Gizmos.DrawWireCube(transform.position, new Vector3(gridWorldSize.x, 1, gridWorldSize.y));

		if (grid != nullptr)
		{
			//for (Node n : grid)
			for (int c = 0; c < COL_SIZE; c++)
			{
				for (int r = 0; r < ROW_SIZE; r++)
				{
					for (int h = 0; h < HALL_SIZE; h++)
					{

						//Gizmos.color = (n.walkable) ? Color.white : Color.red;
						if (!path.empty())
						{
							if (find(path.begin(), path.end(), grid[c][r][h]) == path.end())
							{
								//Gizmos.color = Color.black;
							}
						}
						//Gizmos.DrawCube(n.worldPosition, Vector3::one() * (nodeDiameter - .1f));
						}
					}
				}
			}
		}


};

class AStar
{
public:
	Grid grid;

	void FindPath(Vector3 startPos, Vector3 targetPos)
	{
		Node startNode  = grid.NodeFromWorldPoint(startPos);
		Node targetNode = grid.NodeFromWorldPoint(targetPos);

		vector<Node> openSet;
		unordered_set<Node> closedSet;
		openSet.push_back(startNode);

		while (openSet.size() > 0)
		{
			Node node = openSet[0];
			for (int i = 1; i < openSet.size(); i++)
			{
				if (openSet[i].fCost < node.fCost || openSet[i].fCost == node.fCost)
				{
					if (openSet[i].hCost < node.hCost)
						node = openSet[i];
				}
			}
			openSet.erase(remove(openSet.begin(), openSet.end(), node), openSet.end());
			closedSet.insert(node);

			if (node == targetNode)
			{
				RetracePath(startNode, targetNode);
				return;
			}

			for (Node neighbour : grid.GetNeighbours(node))
			{

				if (!neighbour.walkable || closedSet.find(neighbour) != closedSet.end())
				{
					continue;
				}

				int newCostToNeighbour = node.gCost + GetDistance(node, neighbour);
				if (newCostToNeighbour < neighbour.gCost ||
					find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
				{
					neighbour.gCost = newCostToNeighbour;
					neighbour.hCost = GetDistance(neighbour, targetNode);
					neighbour.parent = &node;

					if (find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
					{
						openSet.push_back(neighbour);
					}
				}
			}
		}
	}

	void RetracePath(Node startNode, Node endNode)
	{
		list<Node> path;
		Node currentNode = endNode;

		while (currentNode != startNode)
		{
			path.push_back(currentNode);
			currentNode = *currentNode.parent;
		}
		path.reverse();

		grid.path.clear();
		for (Node n : path)
		{
			grid.path.push_back(n);
		}


	}

	int GetDistance(Node nodeA, Node nodeB)
	{
		int dstX = fabs(nodeA.gridX - nodeB.gridX);
		int dstY = fabs(nodeA.gridY - nodeB.gridY);

		if (dstX > dstY)
			return 14 * dstY + 10 * (dstX - dstY);
		return 14 * dstX + 10 * (dstY - dstX);
	}
};
*/