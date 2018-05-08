//jonesjon 932709446

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <ctime>
#include <ratio>
#include <string>
#include <sstream>

using namespace std;

enum {
	Q1 = 1,
	Q2 = 2,
	Q3 = 3,
	Q4 = 4
};

struct Point {
	int x, y;
};

class tileBoard {

private:
	int w;
	int h;
	Point p;
public:
	vector<vector<int>> tiles;
	//Constructor and destructor
	tileBoard()
	{
		w = 0; h = 0; p = { 0, 0 };
	}
	tileBoard(int w, int h, Point p)
	{
		this->tiles.resize(w+1);
		this->w = w;
		this->h = h;
		this->p = { p.x, p.y };
		//Build column wise
		for (int i = 0; i < w; i++)
		{
			this->tiles[i].resize(h, 0);
		}
		this->tiles.at(p.x - 1).at(p.y - 1) = 1;
	}
	~tileBoard()
	{
		tiles.clear();
		w = 0; h = 0; p = { 0, 0 };
	}

	string toString() //Print out tiles
	{
		vector<vector<int>>::iterator hiIt;
		vector<int>::iterator loIt;
		string s;
		stringstream ss;
		int x = 0, y = 0;
		for (hiIt = tiles.begin(); hiIt != tiles.end(); hiIt++)
		{
			x++;
			y = 0;
			for (loIt = hiIt->begin(); loIt != hiIt->end(); loIt++)
			{
				y++;
				if (p.x == x && p.y == y)
					ss << setw(4) << "X" << setw(4);
				else if (*loIt)
					ss << setw(4)<< *loIt << setw(4);
				else
					ss << setw(4) << 0 << setw(4);
			}
			ss << "\n";
		}
		s = ss.str();
		return s;
	}

	bool isFilled(Point xy)
	{
		if (tiles[xy.x][xy.y] > 0)
		{
			return true;
		}
		return false;
	}

	int getW()
	{
		return this->w;
	}
	int getH()
	{
		return this->h;
	}
};

void getInput(int&, Point&);
int hasMissingTile(int, int, int, Point);
void recurseTiles(tileBoard&, int, int, int, Point);

int calls = 0;
int callsMade = 0;

int main()
{
	using namespace std::chrono;
	//Get user input
	int k;
	Point p;
	getInput(k, p);
	tileBoard b = tileBoard((int)pow(2, k), (int)pow(2, k), p);
	cout << b.toString() << endl;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	recurseTiles(b, pow(2, k), b.getW(), b.getH(), p);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Tiles took " << time_span.count() << " seconds." << endl;
	cout << "Recursive calls: " << callsMade << endl;

	cout << b.toString() << endl;

	system("pause");
	return 0;
}

void getInput(int& k, Point& p)
{

	cout << "Usage: k px py (2^k tiles by 2^k tiles, px = x coord for empty tile, py = y coord for empty tile)\n k >= 1, 0 < px <= 2^k && 0 < py <= 2^k\nParams: ";
	cin >> k >> p.y >> p.x;
}

int hasMissingTile(int n, int w, int h, Point p)
{
	if (p.x <= (w - (n / 2)) && p.y <= (h - (n / 2)))
		return Q1;
	else if (p.x > (w - (n / 2)) && p.y <= (h - (n / 2)))
		return Q2;
	else if (p.x > (w - (n / 2)) && p.y > (h - (n / 2)))
		return Q3;
	else
		return Q4;
}

/***************************************************************************************************
 * Algorithm used: https://www.geeksforgeeks.org/divide-and-conquer-set-6-tiling-problem/, the below code is mine however.
***************************************************************************************************/
void recurseTiles(tileBoard& tb, int n, int w, int h, Point p)
{
	Point p1, p2, p3, p4;
	//Base case
	if (n == 2)
	{
		calls++;
		if (!tb.isFilled({w - n, h - n}))
		{
			tb.tiles[w - n][h - n] = calls;
		}
		if (!tb.isFilled({ w - (n / 2), h - n }))
		{
			tb.tiles[w - (n / 2)][h - n] = calls;
		}
		if (!tb.isFilled({ w - (n / 2), h - (n / 2) }))
		{
			tb.tiles[w - (n / 2)][h - (n / 2)] = calls;
		}
		if (!tb.isFilled({ w - n, h - (n / 2) }))
		{
			tb.tiles[w - n][h - (n / 2)] = calls;
		}
		return;
	}
	calls++;
	//If missing square at Q1 then fill center of Q2,3,4 and pass new missing point
	if (Q1 == hasMissingTile(n, w, h, p))
	{
		tb.tiles[w - (n / 2)][h - (n / 2) - 1] = calls; //2
		tb.tiles[w - (n / 2)][h - (n / 2)] = calls; //3
		tb.tiles[w - (n / 2) - 1][h - (n / 2)] = calls; //4
		p1 = p; p2 = { w - (n / 2) + 1, h - (n / 2) }; p3 = { w - (n / 2) + 1, h - (n / 2) + 1 }; p4 = { w - (n / 2), h - (n / 2) + 1 };
	}
	else if (Q2 == hasMissingTile(n, w, h, p))
	{
		tb.tiles[w - (n / 2) - 1][h - (n / 2) - 1] = calls; //1
		tb.tiles[w - (n / 2)][h - (n / 2)] = calls; //3
		tb.tiles[w - (n / 2) - 1][h - (n / 2)] = calls; //4
		p1 = { w - (n / 2), h - (n / 2) }; p2 = p; p3 = { w - (n / 2) + 1, h - (n / 2) + 1 }; p4 = { w - (n / 2), h - (n / 2) + 1 };

	}
	else if (Q3 == hasMissingTile(n, w, h, p))
	{
		tb.tiles[w - (n / 2) - 1][h - (n / 2) - 1] = calls; //1
		tb.tiles[w - (n / 2)][h - (n / 2) - 1] = calls; //2
		tb.tiles[w - (n / 2) - 1][h - (n / 2)] = calls; //4
		p1 = { w - (n / 2), h - (n / 2) }; p2 = { w - (n / 2) + 1, h - (n / 2) }; p3 = p; p4 = { w - (n / 2), h - (n / 2) + 1 };
	}
	else if (Q4 == hasMissingTile(n, w, h, p))
	{
		tb.tiles[w - (n / 2) - 1][h - (n / 2) - 1] = calls; //1
		tb.tiles[w - (n / 2)][h - (n / 2) - 1] = calls; //2
		tb.tiles[w - (n / 2)][h - (n / 2)] = calls; //3
		p1 = { w - (n / 2), h - (n / 2) }; p2 = { w - (n / 2) + 1, h - (n / 2) }; p3 = { w - (n / 2) + 1, h - (n / 2) + 1 }; p4 = p;
	}
	//Quad 1
	recurseTiles(tb, n / 2, w - (n / 2), h - (n / 2), p1);
	//Quad 2
	recurseTiles(tb, n / 2, w, h - (n / 2), p2);
	//Quad 3
	recurseTiles(tb, n / 2, w, h, p3);
	//Quad 4
	recurseTiles(tb, n / 2, w - (n / 2), h, p4);
	
	callsMade += 4;

}