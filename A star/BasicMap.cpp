#include "BasicMap.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

BasicMap BasicMap::randomMap(int width, int height, float rate, float cost)
{
	srand(time(NULL));
	BasicMap map(width, height, cost);
	for (int y = 1; y < height - 1; ++y) {
		for (int x = 1; x < width - 1; ++x) {
			map[map.pointToIndex(x, y)] = (((float)rand() / RAND_MAX) < rate) ? BasicMap::WALL : BasicMap::SPACE;
		}
	}
	return map;
}

BasicMap::BasicMap(const BasicMap & obj)
{
	this->map = new int[obj.size()];
	this->cost = new float[obj.size()];
	for (int i = 0; i < obj.size(); ++i) {
		this->map[i] = obj.map[i];
		this->cost[i] = obj.cost[i];
	}
	this->m_height = obj.m_height;
	this->m_width = obj.m_width;
}

BasicMap::BasicMap(BasicMap && obj)
{
	this->map = obj.map;
	this->cost = obj.cost;
	this->m_height = obj.m_height;
	this->m_width = obj.m_width;
	obj.map = nullptr;
	obj.cost = nullptr;
	obj.m_width = 0;
	obj.m_height = 0;
}

BasicMap::BasicMap(int width, int height, int cost_val)
{
	this->m_width = width;
	this->m_height = height;
	map = new int[width * height];
	cost = new float[width * height];
	std::fill(map, map + width * height, SPACE);
	std::fill(cost, cost + width * height, cost_val);
	for (int i = 0; i < height; ++i) {
		map[width * i] = WALL;
		map[-1 + width * (i + 1)] = WALL;
	}
	for (int i = 0; i < width; ++i) {
		map[i] = WALL;
		map[width * height - 1 - i] = WALL;
	}
}

BasicMap::BasicMap(const std::initializer_list<std::initializer_list<int>> &init_list, float cost_val)
{
	this->m_height = init_list.size();
	this->m_width = init_list.begin()->size();
	this->map = new int[m_width * m_height];
	this->cost = new float[m_width * m_height];
	int i = 0;
	for (auto f_iter = init_list.begin(); f_iter != init_list.end(); ++f_iter) {
		if (this->m_width != f_iter->size()) {
			throw std::exception("Map width Must Match");
		}
		for (auto s_iter = f_iter->begin(); s_iter != f_iter->end(); ++s_iter) {
			this->map[i] = *s_iter;
			this->cost[i] = cost_val;
			i += 1;
		}
	}
}

BasicMap::~BasicMap()
{
	delete[] map;
	delete[] cost;
}

BasicMap::Point BasicMap::indexToPoint(int index)
{
	return Point(index / m_width, index % m_width);
}

int BasicMap::pointToIndex(int x, int y)
{
	return y * m_width + x;
}

float BasicMap::getCost(int index)
{
	return cost[index];
}

int & BasicMap::operator[](int index)
{
	if (index < 0 || this->size() <= index) {
		throw std::exception("OUT OF RANGE");
	}
	return map[index];
}

BasicMap & BasicMap::operator=(const BasicMap & obj)
{
	this->map = new int[obj.size()];
	this->cost = new float[obj.size()];
	for (int i = 0; i < obj.size(); ++i) {
		this->map[i] = obj.map[i];
		this->cost[i] = obj.cost[i];
	}
	this->m_height = obj.m_height;
	this->m_width = obj.m_width;
	return *this;
}

const int BasicMap::width() const
{
	return this->m_width;
}

const int BasicMap::height() const
{
	return this->m_height;
}

const int BasicMap::size() const
{
	return m_width * m_height;
}

void BasicMap::printMap()
{
	for (int i = 0; i < m_width*m_height; ++i) {
		if (i != 0 && i % m_width == 0) {
			std::cout << std::endl;
		}
		std::cout << map[i] << " ";
	}
	std::cout << std::endl;
}