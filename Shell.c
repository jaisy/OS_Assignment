OS_Assignment
=============
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>

void ls() {
char dirname[1000];
 DIR*p;                 
 struct dirent *d; 
printf("Enter directory name\n");
 scanf("%s",dirname);
 p=opendir(dirname);
 if(p==NULL)
   {
    perror("Cannot find directory");
    exit(-1);
   }
 while(d=readdir(p)) {
  if((d->d_name[0])!='.')
   printf("%s\n",d->d_name);
 }
        char c = '\0';

while(c != EOF) {
                c = getchar();
                if(c == '\n') 
                        printf("[jpj ] ");
}
}

int main(int argc, char *argv[], char *envp[])
{
        char c = '\0';
	char dirname[10];
	DIR*p;
	struct dirent *d;
	int i=0;
        printf("\n[jpj ] ");

        while(c != EOF) {
                c = getchar();
                if(c == '\n') {
                        printf("[jpj ] ");
		if (argc==1) 
ls();
else if(argc==2) {
//printf("hi");
  if (!strcmp(argv[2], "-a")) {
  printf("Enter directory name\n");
  scanf("%s",dirname);
  p=opendir(dirname);
  if(p==NULL) {
  printf("Cannot find directory");
  exit(-1);
  }
  while(d=readdir(p))
  printf("%s\n",d->d_name);
  }
}
	
}
    }
        return 0;
}
