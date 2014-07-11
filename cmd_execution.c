/* NEK Tech shell */ 
/*
 * cmd_execution.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Pallavi Gadge
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

/* Implementation of redirection output string.
 * Developer:  Neha Choudhary
*/

#include "nektech_shell.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>


extern int redirect_flag;
extern char *file_name;

/* command Execution.*/ 
void run_cmd(char *argv[]) 
{ 
   pid_t child_pid; 
   int fd;

   child_pid=fork(); 
   if(child_pid<0){ 
      printf("SOME ERROR HAPPENED IN FORK\n"); 
      exit(2); 
   }else if(child_pid==0){ 
         /*  redirection output code  */
     if(redirect_flag){
         fd=open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWGRP | S_IWUSR);
  /*  Handling of file creation  */
      if(fd<0)
        switch(errno){
        case EACCES:
              printf("The requested access to the file is not allowed,%s\npermission is denied",file_name);
              break;
           case ENOENT:
              printf("O_CREAT is not set and the named file: %s does not exist",file_name);
              break;
           case ENOMEM:
              printf("Insufficient kernel memory was available.");
              break;
                          default:
                                 printf("Some error is happened in creating the requested file: %s",file_name);
                                 break;
        }
        else{
        dup2(fd,1);
        close(fd);
       }
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

}
