#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
	printf(1,"\nSimple Addition");
	if (argc <= 2){
	  printf(1,"\nI need at least 2 numbers\n");
	  exit();
	}
	int sum=0;
        for(int i = 1; i < argc; i++){
    	  sum += atoi(argv[i]);
      	}		
	printf(1,"\nTotal = %d\nExiting Simple Addition\n",sum);
	exit();
}

