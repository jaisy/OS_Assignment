#include<stdio.h> 
 #include<stdlib.h> 
 #include <sys/types.h> 
 #include <dirent.h> 
  
 int main(void) 
 { 
    char *curr_dir = NULL; 
    DIR *dp = NULL; 
    struct dirent *dptr = NULL; 
    unsigned int i = 0; 
  
    curr_dir = getenv("PWD"); 
    if(curr_dir==NULL) 
    { 
        printf("\n ERROR : Could not get the working directory\n"); 
        return -1; 
    } 
  
    dp = opendir((const char*)curr_dir); 
    if(dp==NULL) 
    { 
        printf("\n ERROR : Could not open the working directory\n"); 
        return -1; 
    } 
  
    printf("\n"); 
    for(i= 0;((dptr = readdir(dp))!=NULL); i++) 
    { 
        if(dptr->d_name[0] != '.') 
            printf("%s\t ",dptr->d_name); 
    } 
  
    return 0; 
 }
