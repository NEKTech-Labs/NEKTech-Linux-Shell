
/*
 * cmd_execution.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Pallavi Gadge
 * Developers V2.0:     Jitendra Khasdev    
 * Author and Architect: Pankaj Saraf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms and conditions of NEK Tech.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY` WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "nektech_shell.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
 *Date : 1-july-2014
 *Basic single stage pipe support
 *Developer :jitendra khasdev
 *in this function frisrt detect pipe and then rediect output
 *inside a file and for next command it will be input
 */




void run_cmd(char *argv[]) 
{

char a[1000],i,flag=0,count=0,check,p,temp=0,j=0;
char *newargv[16];


	for(i=0;argv[i] != NULL ;i++){                /* Check weather pipe is present or not */
               

              if( (check = strcmp(argv[i],"|")) == 0){
                 flag = 1;
           }

	}
 

 	if(flag == 0)           /*call execute_cmd function when pipe is not detected*/                         
 	{
             execute_cmd(argv,0);                
	}
 	else{
       
	     for(i=0,j=0;argv[i];i++){
                
                  if(strcmp(argv[i],"|")!=0){
                     
                    
                        newargv[j] = argv[i];

                    j++;
                     
                   }
                   else{
                      newargv[j]='\0';
                        j=0;    
                      argv[i]='\0';
                      execute_cmd(newargv,1);
                   }
                            
               }

            execute_cmd(newargv,2);
	}

}





/* command Execution.*/ 
int execute_cmd(char *argv[] , int signal)
{

int fp;
pid_t child_pid;



   child_pid=fork();
   
   
   if(child_pid<0){
      printf("SOME ERROR HAPPENED IN FORK\n");
      exit(2);
   }else if(child_pid==0){

        if(signal == 1){
        fp=open("nek.txt",O_WRONLY | O_CREAT, 0666);
  	dup2(fp,1);
        }
        if(signal == 2)
        {
        fp=open("nek.txt",O_RDONLY);
        dup2(fp,0);
        }
     
        if(execvp(argv[0],argv)<0)
         switch(errno){
         case ENOENT:
               printf("COMMAND OR FILENAME NOT FOUND\n");
               break;
            case EACCES:
               printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
               break;
                           default:
                                   printf("SOME ERROR HAPPENED IN EXEC\n");
        }
         exit(3);
      }else
         wait(NULL);




return 0;
}
