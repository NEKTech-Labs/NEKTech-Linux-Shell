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

main() 
{ 
   char cmd[MAX_LEN]; 
   char *cmd_arg[MAX_ARG]; 
   int cmdlen,i,j,tag; 

   do{ 
      /* init cmd */ 
      for(i=0;i<MAX_LEN;i++) cmd[i]='\0'; 

      printf("NEK Tech>> "); 
      fgets(cmd,MAX_LEN,stdin); 

      cmdlen=strlen(cmd); 
      cmdlen--; 
      cmd[cmdlen]='\0'; 

   }while(1); 
} 

/* cd - Change Directory
 * Shell internal Command to chanfe the present working Directory.
 * It calls chdir(). Error conditions: EACCESS, EPERM, ENOENT.
 * Developer: Shubhangi Maheshwari
*/ 
void change_dir(char *argv[]) 
{ 

}
