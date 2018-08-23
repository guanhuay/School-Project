//
//  myshell.c
//  Student: Gunahua Yang
//  Student ID:301158515
//  Create Date: 2016-01-20
//  Copyright (c) 2016 Guanhua Yang. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

//tokenize the input string into arr
void tokenize(char *input, char **arr)
{
    //set the last position of input to \0
    //such that the strcmp not compare command
    //with command+\n
	input[strlen(input)-1] = '\0';
    int i=0;
    char *token;
    token = strtok(input, " \t");
    while(token!=NULL)
    {
        arr[i++] = token;
        token = strtok(NULL, " \t");
    }
    //after tokenize the input, put NULL
    //in the last position to end the arr
    arr[i]=NULL;
}

//execute the arr
void execute(char **arr)
{
    pid_t cpid;
    int stat;
    if((cpid = fork())<0){
        //fork failed
        perror("there is an error");
        exit(1);
    }
    else if(cpid==0)
    {
        //child process
        if(execvp(*arr,arr)<0)
        {
            //error if the execvp failed
            perror("there is an error");
            exit(1);
        }
        exit(0);
    }
    else {
        //parent process
        if(waitpid(cpid, &stat, 0)==-1)
        {
            perror("waitpid");
            exit(1);
        }
    }
}

int main(void)
{
    char input[1024];
    time_t currtime;
    char *arr[100];
    while(1)
    {
        //transform the timeinfo to
        //string time
        struct tm * timeinfo;
        time(&currtime);
        char buffer[80];
        timeinfo = localtime(&currtime);
        strftime (buffer,80,"%F %T",timeinfo);
        printf("%s# ",buffer);
        //read in the input
        fgets(input, 1024, stdin);
        tokenize(input,arr);
        //if the input equal to exit
        //terminate the program
        if(strcmp(arr[0], "exit")==0)
        {
            exit(0);
        }
        execute(arr);
        //reset the arr to NULL after each
        //execute command
        int i = 0;
        while (arr[i] != NULL) arr[i] = NULL;
        i++;
    }
}
