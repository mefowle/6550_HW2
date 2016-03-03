#include <iostream>
#include <stdlib.h> 
#include <vector>

using namespace std;

struct Cell{
	bool status;	//true - alive
						//false - dead
							
	int location; 	// 0 - center						
						// 1 - top left corner			5 - bottom right corner
						// 2 - top border					6 - bottom border 
						// 3 - top right corner			7 - bottom left corner
						// 4 - right border				8 - left border

	Cell(){status = false;}
  
};

int main (int argc, char *argv[]){
  
	int rows = atoi(argv[1]);
	int columns = atoi(argv[2]);
	int seed = atoi(argv[3]);

	vector<int> list;

	for(int i = 4; i < argc; i++){
		list.push_back(atoi(argv[i]));  
	}

	Cell gridStart[rows][columns];
	Cell gridEnd[rows][columns];
	
	//set location of all cells. This tell the cells where the neighbors are located
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			if(i == 0){
				gridStart[i][j].location = 2;		//top border
				gridEnd[i][j].location = 2;
			}
			else if(i == rows-1){
				gridStart[i][j].location = 6;		//bottom border
				gridEnd[i][j].location = 6;
			}
			else if(j == 0){
				gridStart[i][j].location = 8;		//left border
				gridEnd[i][j].location = 8;
			}
			else if(j == columns -1){
				gridStart[i][j].location = 4;		//right border
				gridEnd[i][j].location = 8;
			}
			else{
				gridStart[i][j].location = 0;		//center
				gridEnd[i][j].location = 0;
			}   
		}
	}
	
	gridStart[0][0].location = 1;					//top left corner
	gridStart[0][columns-1].location = 3;		//top right corner
	gridStart[rows-1][columns-1].location = 5;//bottom right corner
	gridStart[rows-1][0].location = 7;			//bottom left corner
	
	gridEnd[0][0].location = 1;
	gridEnd[0][columns-1].location = 3;
	gridEnd[rows-1][columns-1].location = 5;
	gridEnd[rows-1][0].location = 7;
	
	
	int neighbors;

	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			neighbors = 0;
			if(gridStart[i][j].location == 1){
				for(int k = 0; k <= 1; k++){
					for(int l = 0; l <=1; l++){
						if(gridStart[i+k][j+l].status == true && k != 0 && l !=0){
							neighbors++;
						}
					}
				}
				
				
				
			}
			
		}
	}	
	
	



	/*Print out of gridStart*/
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			cout << gridStart[i][j].location << " ";
		}
		cout << "\n";
	}	


}


bool determineStatus(int x, bool life){
	if(life == true && x < 2){				//live cell w/ fewer than 2 neighbors
		return false;							//dies - under-population
	}
	else if(life == true && x > 3){		//live cell w/ more than 3 neighbors
		return false;							//dies - over-population
	}
	else if(life == true){					//live cell w/ 2 or 3 neighbors
		return true;							//lives on
	}
	else if(life == false && x == 3){	//dead cell w/ 3 neighbors
		return true;							//lives - reproduction
	}
}
