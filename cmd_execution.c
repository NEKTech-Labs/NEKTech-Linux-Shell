/*
 * cmd_execution.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Pallavi Gadge
 *
 * Developers V2.0:     Jitendra Khasdev    
 * run_cmd is renamed as nektech_run_cmd()
 *
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

extern char *redirt_file;
extern int redirection, append;

/*
 *NEKTech Research Labs
 *
 *Function name : nektech_run_cmd()
 *Description   : This fuction forks a new process and exec() it with the 
 *                respective binaries provided in the arguments.
 *Developer     : Pallavi Gadge
 *		: jitendra khasdev
 */
void nektech_run_cmd(char *argv[]) 
{
   pid_t child_pid;
   int fd;

   child_pid=fork();

   if(child_pid<0){
      printf("SOME ERROR HAPPENED IN FORK\n");
      exit(2);
   }else if(child_pid==0){
	 if (redirection == 1){
         if (append == 1)
               fd = open(redirt_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
         else
               fd = open(redirt_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
               dup2(fd, 1);   // make stdout go to file
               dup2(fd, 2);   // make stderr go to file - you may choose to not do this
               close(fd);     // fd no longer needed - Duped to another fd#s
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
