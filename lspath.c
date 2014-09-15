#include<dirent.h>
#include<stdlib.h>
int main(){
 char dirname[10];
 DIR*p;                 //The DIR data type represents a directory stream.
 struct dirent *d;      //The structure, struct dirent refers to directory entry.
 
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
}
