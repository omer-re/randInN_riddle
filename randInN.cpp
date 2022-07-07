#include <iostream>
#include <random>
#include <vector>

using namespace std;
#define N 8
vector<int> arrayOfN{ 58, 36, 7, 94, 12, 47, 22 ,78 };

// returns random number in range of [0,N]
int randInN(int n) {
	return (rand() % (n + 1)); // n+1 is because indexes  starts at 0, and for loops won't get to N
}

void printArr(vector<int> arr) {
	std::cout << "{";
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	std::cout << "}" << std::endl;
}

// what I tried to do, which is wrong:
int lookForFree(vector<int> arr, int ind) {
	// randomize an index
	int rand_ind =randInN(N);
	int j;
	for (j = 0; j<N; j ++) {
		// if it isn't vacant - try +1
		if (arr[(rand_ind + j) % N] == NULL) { 
			return (rand_ind + j) %N; 
		}
	}
	// this promises us that we will eventually find a vacant cell with O(N) at the worst case
}

void shuffledArray(vector<int> srcArr) {
	// create a temp array of NULLs
	vector<int> temp;
	for (int i = 0; i < N; i++)
		temp.push_back(NULL);

	// iterate over the src array and populate the new array
	for (int i = 0; i < N; i++) {
		// for each cell at src- use randInN() to find it a new vacant place
		int new_index = lookForFree(temp, i);
		temp[new_index] = srcArr[i];
		cout << "step " << i + 1 << " ";
		printArr(temp);

	}
	cout << "\nShuffled result : "; 
	printArr(temp); 
	cout<< endl;

}



/*DISCUSSION FOR FIRST SOLUTION*/
//// GOOD ////
/*
we are guarenteed to get a new array at O(N ^ 2)
clashes are handled
*/

//// WHY IT ISN'T A GOOD SOLUTION? ////
/*
1. it creates a copy arr and doesn't print it, which is a redundant operation we could avoid.
2. it has a 1/N chance for a clash, this clash is handled on lookForFree() but it isn't efficient enough.
*/


// Better idea after thinking about it

void shuffledArray2(vector<int> srcArr) {
	// for each index
	std::cout << "{";
	for (int i = 0; i < N; i++) {
		// pick random index [0,N-1]
		int picked_index = randInN(N)%(N-i);  // pick random 
		// print it
		std::cout << srcArr[picked_index]<< "  ";
		// pop it off the srcArr
		srcArr.erase(srcArr.begin() + picked_index);
		// next iteration will run for an array with size of N--
	}
	std::cout << "}" << std::endl;



}

/*DISCUSSION FOR FIRST SOLUTION*/
//// GOOD ////
/*
no clashes- we were asked to JUST PRINT A PERMUTATION!
The fact we just prints stuff assures no clashes on indices because it increments.
We let randInN() do it's thing randomizing an index, it can only choose from what's available,
and once we pop the used item off the array- we guarentee it won't be picked.
Even if we'll pick index 0 all the times- it's still a valid solution

assuming randInN() is O(1),
This implementation is O(N) as it iterates over the array once and that's it.
*/

int main() {

	////  TESTING FIRST SOLUTION

	std::cout << "The idea I tried to explain during our meeting, which wasn't good enough: \n" << endl;
	std::cout << "Original input" << endl;
	printArr(arrayOfN);
	std::cout << "First shuffle:" << std::endl;
	shuffledArray(arrayOfN);
	std::cout << "Second shuffle(should be different):" << std::endl;
	shuffledArray(arrayOfN);


	std::cout << "\n\nBetter idea after thinking about it: \n" << endl;
	std::cout << "Original input" << endl;
	printArr(arrayOfN);
	std::cout << "First shuffle:" << std::endl;
	shuffledArray2(arrayOfN);
	std::cout << "Second shuffle(should be different):" << std::endl;
	shuffledArray2(arrayOfN);


	return 0;
}

