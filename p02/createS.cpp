#include <iostream>
#include <cmath>

using namespace std;

int main(){

    signed char c = 1;    
    
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < pow(2,i); j++){
        cout << c;
      }
      cout << "\n";
    }
  
}
