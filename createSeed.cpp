#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(){

	srand(time(NULL));
	    
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			cout << (rand() % 2) << " ";
		}
		cout << "\n";
	}
  
}
