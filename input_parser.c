
/*
 * input_parser.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Deepika Pandey
 *			Shubhangi Maheshwari
 *
 * Copyright (C) NEK Tech 2014
 * Developer  V2.0:     Jitendra Khasdev
 *                      Neha Choudhary
 *                      Vikas Kumar
 *
 * Author and Architect: Pankaj Saraf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms and conditions of NEK Tech.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <sys/wait.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "nektech_shell.h"

/* Taking User Input and Parsing the input to take action.
 * String operations and intelligece for user input.
 * Developer: Deepika Pandey

 * Provide suppoert for cd command when no argument pass.
 * then cd cammand redirect automatically user's home 
 * folder.
 * Developer: Jitendra Khasdev
 */
int nektech_etc_passwd_search();
int nektech_search_path(char *,int);

char *nk_temp_arg[1];
int redirection = 0, append = 0; 
char *redirt_file = NULL;

int main() 
{ 
   char cmd[MAX_LEN]; 
   char *cmd_arg[MAX_ARG]; 
   int cmdlen,i,j,tag, pending_exec = 0, error = 0;

   do{
      /* init cmd */
      for(i=0;i<MAX_LEN;i++) cmd[i]='\0';

      printf("NEK Tech>> ");
      fgets(cmd,MAX_LEN,stdin);

      cmdlen=strlen(cmd);
      cmdlen--;
      cmd[cmdlen]='\0';
      redirt_file = NULL;
      redirection = 0;
      append = 0;

      for(i=0;i<MAX_ARG;i++) cmd_arg[i]=NULL;
      i=0; j=0; tag=0;
      while(i<cmdlen && j<MAX_ARG){
         if(cmd[i]==' '){
            cmd[i]='\0';
            tag=0;
         }else{
            if(tag==0)
               cmd_arg[j++]=cmd+i;
            tag=1;
         }
         i++;
      }
       
      if(j>=MAX_ARG && i<cmdlen){
         printf("TOO MANY ARGUMENTS\n");
         continue;
      }
      /* cmd_arg NULL Condition. */
      if (cmd_arg[0] == NULL )
         continue;
      /* cmd quit/exit/q: exit NEK Tech Shell */
      if((strcmp(cmd_arg[0],"quit")==0) || (strcmp(cmd_arg[0],"exit")== 0) || (strcmp(cmd_arg[0],"q")== 0))
         break;

      /* command change Directory */
      if(strcmp(cmd_arg[0],"cd")==0){
         nektech_change_dir(cmd_arg);
         continue;
      }
      /* Handling Redirection out output to a file.*/
      i = 0;
      while (cmd_arg [i]){
         if(strcmp(cmd_arg[i],">")==0 || strcmp(cmd_arg[i],">>")==0){
            if (cmd_arg[i+1] != NULL){
               redirt_file = cmd_arg[i+1];
               if (strcmp(cmd_arg[i],">>")==0)
                  append = 1;
               while (cmd_arg[i] != NULL){
                  cmd_arg[i++] = cmd_arg[i+2];
               }
               redirection = 1;
               break;
            }
            else{
               error = 1;
               break;
            }
         }
         i++;
      }
      if (error){
         printf ("SHELL PARSING ERROR. WRONG INPUT.\n");
         continue;
      }
      /* other cmd for fork/exec*/
      nektech_run_cmd(cmd_arg);
   }while(1); 
}

/* Function name	: nektech_change_dir () 
 * Description		: Changes Directory of the shell process to the directory
 *			  given as user input.cd is Shell internal Command to 
 *			  change the present working Directory.It calls chdir(). 
 * Error conditions	: EACCESS, EPERM, ENOENT, ENOTDIR
 * Developer		: Shubhangi Maheshwari
 * 			  Jitendra Khasdev (cd command with home directoty intelligence)
*/ 
int nektech_change_dir(char *argv[]) 
{ 

   if(argv[1]!=NULL){
      
	/*
	 * cd ~ command support to change the 
 	 * directory to user home directory. 
 	 */
       if(*argv[1] == '~'){
          argv[1]=strcat(nk_temp_arg[1],(*(argv+1)+1));         
       }
      if(chdir(argv[1])<0)
         switch(errno){
         case ENOENT:
            printf("DIRECTORY NOT FOUND\n");
            break;
         case ENOTDIR:
            printf("NOT A DIRECTORY NAME\n");
            break;
         case EACCES:
            printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
            break;
         default:
            printf("SOME ERROR HAPPENED IN CHDIR\n");
         }
   } 
   else{
        if (nektech_etc_passwd_search()){
		printf("Missing system file./n");
		return -1;
	}
        nektech_change_dir(nk_temp_arg);    
   }

   return 1;    
}

/*
 *NEKTech Research Labs
 *
 *Function name : nektech_etc_passwd_search()
 *Description   : This fuction is used for getting home directory path 
 *                from /etc/passwd file.
 *
 *Fucntion Design : 1. open /etc/passwd file 
 *                  2. store line till '\n' character  
 *                  3. then call nektech_search_path(char *ptr,int userid)
 *                  4. which give path in global variable nk_temp_arg[1]
 *                  5. it is used in change_dir function.
 * 
 *Developer       : jitendra khasdev
 *
 */
int nektech_etc_passwd_search()
{

int fp, c, i=0, k, j, ret = 0;
static char buffer[200],temp[200];
int end_file_position, current_position=1,flag=0,repeat=0,count=0;
 
     fp = open("/etc/passwd",O_RDONLY);
     if( fp == -1 ){
       printf("\n Unable to reach /dir with error [%s]\n",strerror(errno));
       ret = -1;
     }
     else{
        end_file_position=lseek(fp,0L,2);  //reach the end of the file
        lseek(fp,0L,0);     // set file pointer to start
        while(i < end_file_position){
         for(k=0;k<200;k++) buffer[k]='\0';    //initiallzation of buffer
             
            if(count = read( fp, buffer, sizeof(buffer))){
                 for(k=0,j=0;k<200;k++,j++){
                    temp[j]=*(buffer+k);
                    if(*(buffer+k)=='\n'){
                       if(nektech_search_path(temp,getuid())!= 0){
                         for(j=0;j<200;j++)temp[j]='\0';
                       j=0;
                     }
                     else
                        break;
                   }
                }
           }
        i=i+count;
        }
     } 
     return ret;
}

/*
 *NEKTech Research Labs
 *
 *
 *function name     : nektech_search_path()
 *Description       : This fuction is give path with respect to userid.
 *
 *Function Design   : 1. it is called by nektech_etc_passwd_search()
 *                    2. now it search delimitor(":")
 *                    3. if second delimitor then start storing string till third delimitor
 *                    4. now compare with uid if this is found same
 *                    5. then it start storing path from 5 to 6 delimitor.
 *
 *Developer         : jitendra khasdev
 */
int nektech_search_path(char *ptr,int userid)
{
  int count=0,i=0,j=0,k=0,flag=0;
  char nk_temp[200];
  char temp_cd[2]="cd";

                        	
  for(k=0;k<100;k++) nk_temp[k]='\0';
  while(*(ptr) != '\n')
  {
    if(*(ptr) == ':')
      count++;
           
    if(count == 2){
      nk_temp[j]= *(ptr+1);
      j++;
    }
       			
    if(count == 3){
      nk_temp[j-1] = '\0';
      j=0;  
    

      if(atoi(nk_temp)==userid){        
      flag=1;
      }
    }

    if(count == 5 && flag == 1){
     nk_temp[j] = *(ptr+1);
      j++;
    }

    if(count == 6 && flag == 1  ){
      
      nk_temp[j-1]='\0';
      flag=0;
      j=0;
      nk_temp_arg[1]=nk_temp;
      return 0;
    }
     ptr++;
  }
  return 1;
}
