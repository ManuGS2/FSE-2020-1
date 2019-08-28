#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	int i, veces;

	if(argc > 1){
		veces = atoi(argv[1]);
		for(i=1; i<=veces; i++){
			printf("\033[0;3%im",i);
			printf("#%i: FSE2020-1 Emmanuel Guzman, Aaron Mejia, Ricardo Saenz\n", i);
		}
	}
	return 0;
}
