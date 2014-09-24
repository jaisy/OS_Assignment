#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>  
#include <grp.h>  
#include <time.h>  
#include <locale.h>  
#include <langinfo.h>  
#include <stdint.h>  
#include <fcntl.h>


#define FALSE 0
#define TRUE !FALSE

extern  int alphasort();                        //Inbuilt sorting function
static char perms_buff[30];
char pathname[MAXPATHLEN];


 int main(int argc, char* argv[]) {
 char dirname[10];
 DIR*p;                
 struct dirent *d;     
 int i=0;

 /*for(i=0;i<argc;i++)
 {
 printf("count:%d\n parameters: %s\n",argc,argv[i]);
 }*/

 if(argc==2) {
   printf("Enter directory name\n");
   scanf("%s",dirname);
   //dirname=get_current_dir_name();
   p=opendir(dirname);
   if(p==NULL) {
     printf("Cannot find directory");
     exit(-1);
   }
   while(d=readdir(p)) {
     if((d->d_name[0])!='.')
     printf("%s\n",d->d_name);
   }
 }
 else if(argc==3) {
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
    else if(!strcmp(argv[2], "-l")) {
      execls();
    }
    else if(!strcmp(argv[2], "-la")) {
      printf("Enter directory name\n");
      scanf("%s",dirname);
      p=opendir(dirname);
      if(p==NULL) {
        printf("Cannot find directory");
        exit(-1);
      }
    while(d=readdir(p)) {
     //if((d->d_name[0])='.')
       //printf("%s\n",d->d_name);
      execls();
   }

    }

    } 
  
   
 return 0;
}




void die(char *msg)
{
  perror(msg);
  exit(0);
}


int file_selecto(struct direct   *entry)                             
{
     char *ptr;
     char *rindex(const char *s, int c );
     if ((strcmp(entry->d_name, ".")== 0) ||(strcmp(entry->d_name, "..") == 0))  return (FALSE);
 
				                                                         
     ptr = rindex(entry->d_name, '.');
    if ((ptr != NULL) && ((strcmp(ptr, ".c") == 0) ||(strcmp(ptr, ".h") == 0) ||(strcmp(ptr, ".o") == 0) ))
	return (TRUE);
    else
	return(FALSE);
}


const char *get_perms(mode_t mode)                     
{  
  char ftype = '?';  
  
       if (S_ISREG(mode)) ftype = '-';                  
       if (S_ISLNK(mode)) ftype = 'l';  
       if (S_ISDIR(mode)) ftype = 'd';  
       if (S_ISBLK(mode)) ftype = 'b';  
       if (S_ISCHR(mode)) ftype = 'c';  
       if (S_ISFIFO(mode)) ftype = '|';  
  
  sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c %c%c%c", ftype,  
  mode & S_IRUSR ? 'r' : '-',                                   
  mode & S_IWUSR ? 'w' : '-',                                   
  mode & S_IXUSR ? 'x' : '-',                                    
  mode & S_IRGRP ? 'r' : '-',                                           
  mode & S_IWGRP ? 'w' : '-',  
  mode & S_IXGRP ? 'x' : '-',  
  mode & S_IROTH ? 'r' : '-',  
  mode & S_IWOTH ? 'w' : '-',  
  mode & S_IXOTH ? 'x' : '-',  
  mode & S_ISUID ? 'U' : '-',                                           
  mode & S_ISGID ? 'G' : '-',  
  mode & S_ISVTX ? 'S' : '-');  
  
  return (const char *)perms_buff;  
}  



int execls() {
              int count,i;  
              struct direct **files;  
              struct stat statbuf;  
              char datestring[256];  
              struct passwd pwent;  
              struct passwd *pwentp;  
              struct group grp;  
              struct group *grpt;  
              struct tm time;  
              char buf[1024];  
if(!getcwd(pathname, sizeof(pathname)))  
             die("Error getting pathnamen");  
  
      count = scandir(pathname, &files, file_selecto, alphasort);  
  
      if(count > 0)  
           {  
               printf("total %d\n",count);  
  
                  for (i=0; i<count; ++i)  
                   {  
                     if (stat(files[i]->d_name, &statbuf) == 0)  
                         {  
printf("%10.10s", get_perms(statbuf.st_mode));                      /* File mode (type, perms) */       
                            printf(" %d", statbuf.st_nlink);                                     /* Number of links */
  
                    if (!getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))  
                            printf(" %s", pwent.pw_name);  
                    else  
                            printf(" %d", statbuf.st_uid);                                       /* User ID of the file's owner */
  
                    if (!getgrgid_r (statbuf.st_gid, &grp, buf, sizeof(buf), &grpt))  
                            printf(" %s", grp.gr_name);  
                    else  
                            printf(" %d", statbuf.st_gid);                                       /* Group ID of the file's group */  
  
                                                                                                 /* Print size of file. */  
                            printf(" %5d", (int)statbuf.st_size);  
                                                                                  
                            localtime_r(&statbuf.st_mtime, &time);                               /* Time of last data modification */
                                                                                                 /* Get localized date string. */  
                            strftime(datestring, sizeof(datestring), "%F %T", &time);  
  
                            printf(" %s %s\n", datestring, files[i]->d_name);  
                       }  
                        free (files[i]);  
                     } 
                                      free(files);  
                       }                                                                                               
                                      exit(0);

}
