#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std; //jonesjon 932709446

enum {
	EQUAL = 0,
	LIGHTER = 1,
	HEAVIER = 2
};

void getInput(int&);
void fillBag(int);
void recurseCoins(int, int);
int scales(int, int, int, int);

//odd weight and position
int oPos, oW, comps = 0;


int main()
{
	using namespace std::chrono;
	int n;

	getInput(n);
	fillBag(n);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	recurseCoins(0, n);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Coins took " << time_span.count() << " seconds." << endl;
	cout << "Number of weightings: " << comps << endl;

	system("pause");
	return 0;
}

void getInput(int& a)
{
	cout << "Usage: a (a = # coins that is a power of 3\nParams: ";
	cin >> a;
}

void fillBag(int n)
{
	srand(time(NULL));
	oW = (rand() % 2) + 1;

	default_random_engine generator;
	generator.seed(time(NULL));
	uniform_int_distribution<int> distribution(0, n - 1);
	oPos = distribution(generator);
	cout << "Randomized coin position: " << oPos << endl;
}

int scales(int si1, int ei1, int si2, int ei2)
{
	//Odd position is within the first subrange
	if (oPos >= si1 && oPos < ei1)
	{
		if (oW == LIGHTER)
			return LIGHTER;
		else
			return HEAVIER;
	}
	else if (oPos >= si2 && oPos < ei2) //Odd position is within the second sub range
	{
		if (oW == LIGHTER)
			return HEAVIER;
		else
			return LIGHTER;
	}
	else //Odd position is not within either of the sub ranges
		return EQUAL;
}

void recurseCoins(int sI, int eI)
{
	if ((eI - sI) == 1)
	{
		cout << "Found odd coin at position: " << sI << endl;
		return;
	}
	int size = (eI - sI) / 3;
	if (scales(sI, sI + size, sI + size, sI + (2 * size)) != EQUAL) //first and second
	{
		if (scales(sI, sI + size, sI + (2 * size), sI + (3 * size)) == EQUAL) //first and third
		{
			recurseCoins(sI + size, sI + (2 * size));
		}
		else //At this point it must be the first
		{
			recurseCoins(sI, sI + size);
		}
		comps += 2;
	}
	else
	{
		recurseCoins(sI + (2 *size), sI + (3 * size)); //If first and second are equal then it must be the third
		comps++;
	}
}

//Base case
/*
if ((eI - sI) == 3)
{
//Compare first and second
if (scales(sI, sI + 1, sI + 1, eI - 1) == EQUAL)
{
if (scales(sI, sI + 1, eI - 1, eI) != EQUAL) //First and third
{
cout << "Found odd coin at position: " << eI - 1 << endl;
}
comps += 2;
}
else if (scales(sI, sI + 1, eI - 1, eI) == EQUAL) //Compare second and third
{
cout << "Found odd coin at position: " << sI + 1 << endl;
comps += 2;
}
else
{
cout << "Found odd coin at position: " << sI << endl;
comps += 2;
}
return;
}
*/