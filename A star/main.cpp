#include <iostream>
#include <tuple>
#include <memory>
#include <queue>
#include <vector>

#include "BasicMap.h"
using namespace std;

struct common_test {
	using type = int;
};

struct ScoreCell {
	int i;
	int pre_index = -1;
	int g_score = 0;
	int f_score;
};

void printPath(BasicMap &map, ScoreCell *cells, int start_x, int start_y, int end_x, int end_y);

void add(BasicMap &map, vector<ScoreCell> &openlist, ScoreCell *cells,
	int now_i, int next_i, int end_x, int end_y);

void A_star(BasicMap map, int start_x, int start_y, int end_x, int end_y);

int main(int argc, char **argv) {
	BasicMap map({
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
		}, 1);
	A_star(map, 1, 1, 23, 23);
	//A_star(BasicMap::randomMap(25, 25, 0.3f, 1), 1, 1, 23, 23);
	system("PAUSE");
}
void A_star(BasicMap map, int start_x, int start_y, int end_x, int end_y) {
	ScoreCell *scoreCells = new ScoreCell[map.size()];
	for (int i = 0; i < map.size(); ++i) {
		scoreCells[i].i = i;
	}
	vector<ScoreCell> openlist = vector<ScoreCell>();
	openlist.push_back(scoreCells[map.pointToIndex(start_x, start_y)]);

	while (openlist.size() > 0) {
		std::push_heap(openlist.begin(), openlist.end(), [&](ScoreCell a, ScoreCell b) { return a.f_score < b.f_score;  });
		ScoreCell cell = openlist[openlist.size() - 1];

		if (cell.i == map.pointToIndex(end_x, end_y)) {
			cout << "found" << endl;
			printPath(map, scoreCells, start_x, start_y, end_x, end_y);
			map.printMap();
			return;
		}
		openlist.pop_back();
		add(map, openlist, scoreCells, cell.i, cell.i + 1, end_x, end_y);
		add(map, openlist, scoreCells, cell.i, cell.i - 1, end_x, end_y);
		add(map, openlist, scoreCells, cell.i, cell.i + map.width(), end_x, end_y);
		add(map, openlist, scoreCells, cell.i, cell.i - map.width(), end_x, end_y);
	}
	cout << "not found" << endl;
	map.printMap();
	delete[] scoreCells;
}
void add(BasicMap &map, vector<ScoreCell> &openlist, ScoreCell *cells,
	int now_i, int next_i, int end_x, int end_y) {

	// int max_i = height * width;
	// if(next_i < 0 || next_i >= max_i) {
	//     return;
	// }
	if (cells[next_i].pre_index != -1)
		return;

	BasicMap::Point point = map.indexToPoint(next_i);
	if (map[next_i] == 1) {
		return;
	}
	map[next_i] = 2;
	int distance = abs(end_x - point.x) + abs(end_y - point.y);
	cells[next_i].g_score = (int)map.getCost(next_i) + cells[now_i].g_score;
	cells[next_i].f_score = distance + cells[next_i].g_score;
	cells[next_i].pre_index = now_i;
	openlist.push_back(cells[next_i]);
}

void printPath(BasicMap &map, ScoreCell *cells, int start_x, int start_y, int end_x, int end_y) {
	int i = map.pointToIndex(end_x, end_y);
	int end = map.pointToIndex(start_x, start_y);
	ScoreCell *now_c = cells + i;
	while (now_c->i != end) {
		map[now_c->i] = 4;
		now_c = now_c->pre_index + cells;
	}
}