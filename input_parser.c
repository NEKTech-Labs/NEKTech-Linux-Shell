
/*
 * input_parser.c - Linux Shell 
 *
 * Copyright (C) NEK Tech 2013
 * Developers V1.0:  	Deepika Pandey
 *			Shubhangi Maheshwari
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

 

int search_path(char *,int);


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

/*
 *cd - Change Direcotry
 *when this command is passed without any argument then
 *it will rediredt to home folder of the user
 *Developer: Jitendra Khasdev
 */
int change_dir(char *argv[]) 
{ 

int fp,c,i=0,k,j;
static char buffer[200],temp[200];
int End_File_Position;
int Current_Position=1,flag=0,repeat=0,count=0;

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
   else{
         fp = open("/etc/passwd",O_RDONLY);
         
         if( fp == -1 ){
               printf("\n Unable to reach /dir with error [%s]\n",strerror(errno));
         }
    	 else{
              End_File_Position=lseek(fp,0L,2);  //reach the end of the file
                        
              lseek(fp,0L,0);     // set file pointer to start

              while(i < End_File_Position){
                   
                for(k=0;k<200;k++) buffer[k]='\0';    //initiallzation of buffer

                if(count =  read( fp, buffer, sizeof(buffer) ) ){

                      for(k=0,j=0;k<200;k++,j++){
                         temp[j]=*(buffer +k);
                         if( *(buffer+k) == '\n' ){
                                 if( search_path(temp,getuid()) != 0){
                                             for(j=0;j<500;j++)
                                               temp[j]='\0';				     
												
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
     }

return 1;    
}     

/*
 *This function finds the path of the current user's home 
 *folder 
 */

int search_path(char *ptr,int userid)
{
int count=0,i=0,j=0,k=0,flag=0;
char temp[100];
char *temp_arg[1];

                      	
	 for(k=0;k<100;k++) temp[k]='\0';
       	 while(*(ptr) != '\n')
         {
           if(*(ptr) == ':')
           count++;
           
           if(count == 2){
           temp[j]= *ptr;
           j++;
           }
       			
           if(count == 3){
            temp[j] = '\0';
            j=0;  
                 
            for(k=0; temp[k] != '\0';k++)      // for removing : so that swapping performed
            temp[k]=temp[k+1];
                                 
            temp[k]='\0';
                            
	      if(atoi(temp)==userid) 
               flag=1;
            }

            if(count == 5 && flag == 1){
             temp[j] = *ptr;
             j++;
            }

            if(count == 6 && flag == 1  ){
              for(k=0; temp[k] != '\0';k++)      // for removing : so that swapping performed
              temp[k]=temp[k+1];
                                 
              temp[k]='\0';

              flag=0;

              temp_arg[1]=temp;
                         
              change_dir(temp_arg);

              return 0;
           }
            
        ptr++;
 	}

return 1;
}







