<<<<<<< HEAD

=======
/* NEK Tech shell */ 
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
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
<<<<<<< HEAD
=======
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
 */

#include <sys/wait.h> 
#include <string.h> 
<<<<<<< HEAD
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
=======
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
#include "nektech_shell.h"

/* Taking User Input and Parsing the input to take action.
 * String operations and intelligece for user input.
 * Developer: Deepika Pandey
*/ 

<<<<<<< HEAD
int search_path(char *,int,int );


=======
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
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
         change_dir(cmd_arg);
         continue;
      }
       
      /* other cmd for fork/exec*/
      run_cmd(cmd_arg);
   }while(1); 
}

/* cd - Change Directory
 * Shell internal Command to chanfe the present working Directory.
 * It calls chdir(). Error conditions: EACCESS, EPERM, ENOENT.
 * Developer: Shubhangi Maheshwari
*/ 
void change_dir(char *argv[]) 
{ 
<<<<<<< HEAD

int fp;
int c;
int i=0;
static char buffer[200];
int End_File_Position;
int Current_Position=1;
int flag=0;
int repeat=0;


=======
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
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
<<<<<<< HEAD
   else{
       
    		fp = open("/etc/passwd",O_RDONLY);
    		if( fp == -1 )
    		{
        		//printf("\n Unable to reach /dir with error [%s]\n",strerror(errno));
    		}
    		else
    		{
        	    // printf("\n Open() Successful\n");
                     
                      End_File_Position=lseek(fp,0L,2);  //reach the end of the file
                        
                      lseek(fp,0L,0);     // set file pointer to start


                       if( read(fp,buffer,End_File_Position) )
                       {
    		         
                         search_path(buffer,End_File_Position,getuid());  //call serching function for search home path
                       			
                       }					
                
 	      } 
         }
       
}     



int search_path(char *ptr,int size,int userid)
{
int count=0,i=0,j=0,k=0,flag=0;
char temp[100];
char *temp_arg[1];

         while(	i < size)
         {
                       if( *ptr == '\n'  ){
                          
                          		for(k=0;k<100;k++) temp[k]='\0';
                         
                			count = 0;   // intializing delimiter for every new line
                         		j=0;
                        		flag=0;
  		       }

       		       if(*ptr == ':')
          		   	count++;
       					  

         		if(count == 2){
                                         
					temp[j]= *ptr;
        			        j++;
                                      
         		}
       			if(count == 3)
         		{
          			    temp[j] = '\0';
           			    j=0;  
                          
                                 for(k=0; temp[k] != '\0';k++)      // for removing : so that swapping performed
                                 temp[k]=temp[k+1];
                                 temp[k]='\0';
                            
			    if(atoi(temp)==userid) 
                            flag=1;
                                            
         		}

         		if(count == 5 && flag == 1)
                        {
                         
                              temp[j] = *ptr;
                    
                         j++;
                        }

       
                       if(count == 6 && flag == 1  )
                        {
                             for(k=0; temp[k] != '\0';k++)      // for removing : so that swapping performed
                                 temp[k]=temp[k+1];
                                 temp[k]='\0';

                         flag=0;

                         temp_arg[1]=temp;
                         
                         /*printf("%s\n",temp);


                         */
                         change_dir(temp_arg);
                         break;
                        }
       
        ptr++;
        i++;
 	
	}

return 0;
}






=======
}
>>>>>>> d7f52761e98c3e5e5b5c6062e1a5e7bd45d47402
