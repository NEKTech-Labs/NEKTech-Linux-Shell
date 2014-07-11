/* NEK Tech shell */ 
/*
 * input_parser.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Deepika Pandey
 *			Shubhangi Maheshwari
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
#include "nektech_shell.h"

/* Taking User Input and Parsing the input to take action.
 * String operations and intelligece for user input.
 * Developer: Deepika Pandey
*/

/* Identify Redirection output string from the user input.
 * Developer:    Neha choudhary   
*/
 
int redirect_flag =0;
char *file_name=NULL;

main() 
{ 
   char cmd[MAX_LEN]; 
   char *cmd_arg[MAX_ARG]; 
   int cmdlen,i,j,tag; 
  
   do{

      for(i=0;i<MAX_LEN;i++) cmd[i]='\0';

      printf("NEK Tech>> ");
      fgets(cmd,MAX_LEN,stdin);

      cmdlen=strlen(cmd);
      cmdlen--;
      cmd[cmdlen]='\0';


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
         printf("arguments exceed");
         continue;
      }
    
   
    for(i=0; *(cmd_arg+i)!=NULL; i++)
  /*  Identify redirection  */
 	if(strcmp(cmd_arg[i],">")==0){
	redirect_flag=1;
	*(cmd_arg+i)=NULL;
	file_name=*(cmd_arg+i+1);
          if(file_name==NULL){
	     printf("NEKTech_Shell: syntax error near unexpected command\n");
	     exit(1);
	}
     }
      
   /* cmd_arg NULL Condition. */
      if (cmd_arg[0] == NULL )
         continue;
      /* cmd quit/exit/q: exit NEK Tech Shell */
      if((strcmp(cmd_arg[0],"quit")==0) || (strcmp(cmd_arg[0],"exit")== 0) || (strcmp(cmd_arg[0],"q")== 0))
         break;

      /* command change Directory */
      if(strcmp(cmd_arg[0],"cd")==0){
         change_dir(cmd_arg);
         continue;
      } 

      
     /* other cmd for fork/exec*/
  	 
      run_cmd(cmd_arg);
	redirect_flag=0;
  	file_name=NULL;    
}while(1); 
}

/* cd - Change Directory
 * Shell internal Command to chanfe the present working Directory.
 * It calls chdir(). Error conditions: EACCESS, EPERM, ENOENT.
 * Developer: Shubhangi Maheshwari
*/ 
void change_dir(char *argv[]) 
{ 
   if(argv[1]!=NULL){
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
}
