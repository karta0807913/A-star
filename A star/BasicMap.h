#pragma once
#include <iostream>
class BasicMap
{
public:
	static const int SPACE = 0;
	static const int WALL = 1;

	static BasicMap randomMap(int width = 20, int height = 20, float rate = 0.2f, float cost = 10);

	BasicMap() = delete;
	BasicMap(const BasicMap &obj);
	BasicMap(BasicMap &&obj);
	BasicMap(int width, int height, int cost_val = 10);
	BasicMap(const std::initializer_list<std::initializer_list<int>> &list, float cost_val);
	BasicMap &operator=(const BasicMap &obj);
	int &operator[](int index);

	~BasicMap();

	struct Point {
		int x;
		int y;
		Point(int x, int y) :x(x), y(y) {};
	};

	Point indexToPoint(int index);
	int pointToIndex(int x, int y);

	// get move cost
	float getCost(int index);
	const int width() const;
	const int height() const;
	const int size() const;
	void printMap();
private:
	int *map = nullptr;
	float *cost = nullptr;
	int m_width, m_height;
};