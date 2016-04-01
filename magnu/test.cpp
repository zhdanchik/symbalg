#include <stdio.h>

int arr[2][3] = {{0,1}, {3}};

int main(int argc, const char ** arv){
	for(int i=0; i<2; i++)for(int j=0; j<3; j++) printf("%i %i %i\n", i, j, arr[i][j]);
}