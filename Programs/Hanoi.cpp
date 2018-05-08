//USES C++11 so make sure to enable compatability in your compiler

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <ratio>
#include <cmath>

using namespace std;

void iterativeHanoi(int, vector<vector<int>>&);
void recurseHanoi1(vector<int>&, vector<int>&, vector<int>&, int);
void moveDisk(vector<int>&, vector<int>&);
void printHanoi(vector<vector<int>>);
unsigned int rightmostBitPosition(int);
int getPosOfRightMostUnsetBit(int, int);
int mod(int,int);
void moveDisk2(int,int);
unsigned int countSetBits(int);
unsigned int countSetBitsInGivenRange(unsigned int, unsigned int);


vector<int> Ar, Br, Cr, Ai, Bi, Ci;
int moves = 0;

int main()
{
	using namespace std::chrono;

	int n;
	//Get the number of disks from user
	cout << "Enter number of disks: ";
	cin >> n;

	//Fill stack A
	for (int i = n; i > 0; i--)
	{
		Ar.push_back(i);
		Ai.push_back(i);
	}
	vector<vector<int>> iter = { Ai, Bi, Ci };

	//printHanoi({ Ar,Br,Cr });
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	recurseHanoi1(Ar, Br, Cr, n);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Recursive Hanoi took " << time_span.count() << " seconds." << endl;;


	//printHanoi({ Ai,Bi,Ci });
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	iterativeHanoi(n, iter);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t4 - t3);
	cout << "Iterative Hanoi took " << time_span.count() << " seconds." << endl;;

	system("pause");

	return 0;
}

void recurseHanoi1(vector<int>& A, vector<int>& B, vector<int>& C, int n)
{
	if (n == 1)
	{
		moveDisk(A, C);
		//printHanoi({ Ar,Br,Cr });
	}
	else
	{
		recurseHanoi1(A, C, B, n - 1);
		moveDisk(A, C);
		//printHanoi({ Ar,Br,Cr });
		recurseHanoi1(B, A, C, n - 1);
	}
}

//Moves top disk from tower 1 to tower 2
void moveDisk(vector<int>& tower1, vector<int>& tower2)
{
	//moves++;
	tower2.push_back(tower1.back());
	tower1.pop_back();
}

void printHanoi(vector<vector<int>> v)
{
	vector<vector<int>>::iterator hiIt;
	vector<int>::iterator loIt;

	cout << endl;
	for (hiIt = v.begin(); hiIt != v.end(); hiIt++)
	{
		cout << "|";
		for (loIt = hiIt->begin(); loIt != hiIt->end(); loIt++)
		{
			cout << *loIt << " ";
		}
		cout << endl;
	}
}

/*******************************Original code below available at**********************************
 * https://www.geeksforgeeks.org/get-position-rightmost-unset-bit/
 * https://www.geeksforgeeks.org/count-set-bits-range/
 ************************************************************************************************/

unsigned int rightmostBitPosition(int n)
{
	unsigned int r = log2(n&-n);
		return r;
}

int getPosOfRightMostUnsetBit(int n, int r)
{
	// if n = 0, return 1
	if (n == 0)
		return 1;

	if (countSetBitsInGivenRange(n, r) == r)
		return -1;

	// position of rightmost unset bit in 'n'
	// passing ~n as argument
	return rightmostBitPosition(~n);
}

// Function to get no of set bits in the
// binary representation of 'n'
unsigned int countSetBits(int n)
{
	unsigned int count = 0;
	while (n) {
		n &= (n - 1);
		count++;
	}
	return count;
}

// function to count set bits in the given range 1 to r
unsigned int countSetBitsInGivenRange(unsigned int n, unsigned int r)
{
	// calculating a number 'num' having 'r' number
	// of bits and bits in the range 1 to r are the 
	// only set bits
	int num = ((1 << r) - 1) ^ ((1 << 0) - 1);

	// returns number of set bits in the range
	// 1 to 'r' in 'n'
	return countSetBits(n & num);
}

/*******************************************************************************************/

void iterativeHanoi(int n, vector<vector<int>>& v)
{
	signed int t = 0; //Tower number computed mod 3
	int c = 0; //Counter bits

	int p; //1 if n is even -1 if n is odd
	if (n % 2 == 0) // if even
		p = 1;
	else //If odd
		p = -1;

	while (true)
	{
		moveDisk2(t, mod(t + p, 3));
		//printHanoi({ Ai,Bi,Ci });
		t = mod(t + p, 3);
		c++;

		if (getPosOfRightMostUnsetBit(c, n) == -1)
		{
			return;
		}
		else if ((getPosOfRightMostUnsetBit(c, n) - 1) % 2 == 0)
		{
			moveDisk2(mod(t - p, 3), mod(t + p, 3));
			//printHanoi({ Ai,Bi,Ci });
		}
		else
		{
			moveDisk2(mod(t + p, 3), mod(t - p, 3));
			//printHanoi({ Ai,Bi,Ci });
		}
		c++;
	}
}

int mod(int a, int b)
{
	int r;
	r = a % b;
	//If number is negative, add a to b
	if (r < 0)
	{
		r += b;
	}
	return r;
}

void moveDisk2(int t1, int t2)
{
	if (t1 == 0 && t2 == 1)
	{
		moveDisk(Ai, Bi);
	}
	else if (t1 == 0 && t2 == 2)
	{
		moveDisk(Ai, Ci);
	}
	else if (t1 == 1 && t2 == 0)
	{
		moveDisk(Bi, Ai);
	}
	else if (t1 == 1 && t2 == 2)
	{
		moveDisk(Bi, Ci);
	}
	else if (t1 == 2 && t2 == 0)
	{
		moveDisk(Ci, Ai);
	}
	else if (t1 == 2 && t2 == 1)
	{
		moveDisk(Ci, Bi);
	}
}