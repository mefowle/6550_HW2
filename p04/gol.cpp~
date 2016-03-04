#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <fstream>
#include "mpi.h"

using namespace std;

bool determineStatus(int x, bool life);

int main (int argc, char *argv[]){
  
	int rows = atoi(argv[1])+2;
	int columns = atoi(argv[2]+2);
	char * seed = argv[3];

	vector<int> list;

	for(int i = 4; i < argc; i++){
		list.push_back(atoi(argv[i]));  
	}
	
	int divisor;
	if((rows+2)% 3 == 0){
		divisor = 3;
	}
	else{
		divisor = 2;
	}
	
	MPI_Datatype newtype;
	int sizes[2] = {(rows + 2), (columns + 2)};
	int subsizes[2] = {(((rows + 2)/divisor)+2), (columns + 2)};
	int starts[2] = {1,1};
	
	MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_C, MPI_INT, &newtype);
   MPI_Type_commit(&newtype);

	MPI_Send(&(global[1][1]), 1, newtype, dest, tag, MPI_COMM_WORLD);
   

	bool gridStart[rows][columns];
	bool gridEnd[rows][columns];
	
	ifstream myfile;
	myfile.open(seed);
	int input;
	
	for(int i = 1; i < rows-1; i++){
		for(int j = 1; j < columns-1; j++){
			gridStart[i][j] = false;
			gridEnd[i][j] = false;
		}
	}	
	
	for(int i = 1; i < rows-1; i++){
		for(int j = 1; j < columns-1; j++){
			myfile >> input;
			if(input == 1){
				gridStart[i][j] = true;
			}
			else{
				gridStart[i][j] = false;
			}
		}
	}	
	
	/*Print out of gridStart*/
	for(int i = 1; i < rows-1; i++){
		for(int j = 1; j < columns-1; j++){
			if(gridStart[i][j] == false){
				cout << "  ";
			}
			else{
				cout << gridStart[i][j] << " ";
			}
		}
		cout << "\n";
	}	
	
	
	
	
	int neighbors;
	
	for(int count = 0; count < 20; count++){
	
		for(int i = 1; i < rows -1; i++){
			for(int j = 1; j < columns -1; j++){
				/*neighbors of center cells*/
				neighbors = 0;
			
				for(int k = -1; k <= 1; k++){
					for(int l = -1; l<= 1; l++){
						if(gridStart[i+k][j+l] == true){
							neighbors++;
							
						}
					}
				}
				if(gridStart[i][j] == true){
					neighbors--;
				}
				
				gridEnd [i][j] = determineStatus(neighbors, gridStart[i][j]);
			} 
		}	
		
		
		for(int i = 1; i < rows-1; i++){
			for(int j = 1; j < columns-1; j++){
				gridStart[i][j] = gridEnd[i][j];
			}
		}
		
		
		
			cout << "\n\n";
			/*Print out of gridStart*/
			for(int i = 1; i < rows-1; i++){
				for(int j = 1; j < columns-1; j++){
					if(gridStart[i][j] == false){
						cout << "  ";
					}
					else{
						cout << gridStart[i][j] << " ";
					}
				}
				cout << "\n";
			}
		
	
	}
	

}


bool determineStatus(int x, bool life){
	//cout << "n:" << x << " ";
	if(life == true && x < 2){				//live cell w/ fewer than 2 neighbors
		return false;							//dies - under-population
	}
	else if(life == true && x > 3){		//live cell w/ more than 3 neighbors
		return false;							//dies - over-population
	}
	else if(life == true){					//live cell w/ 2 or 3 neighbors
		return true;							//lives on
	}
	if(life == false && x == 3){			//dead cell w/ 3 neighbors
		return true;							//lives - reproduction
	}
	else{
		return false;
	}

	
}
