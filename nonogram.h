#ifndef NONOGRAM_H
#define NONOGRAM_H
#include <ctime> 
#include <cstdlib>
#include "solver.h"

class Nonogram {
 private:
	size_t width, height;
	int solids, dots;
	size_t *field;
	vector<size_t> **xAxis;
	vector<size_t> **yAxis;
	void generateField();
    void generateField(time_t input);
	void generatePuzzle();
	double probability(int above, int left);
    time_t generated_time;
 public:
	Nonogram(int w, int h);
    Nonogram(int w, int h,time_t num);
	~Nonogram();
	void print();
    char* uniq_game_name();
	vector<size_t>** getXAxis();
	vector<size_t>** getYAxis();
	size_t* getField();
};
#endif
