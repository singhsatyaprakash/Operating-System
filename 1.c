//Write a program to create a child process using system call fork(). 
#include<stdio.h>
#include <unistd.h>
int main(){
    //create child process
    pid_t pid=fork();
    if(pid<0){
        printf("Fork failed.");
        return 1;
    }
    else if(pid==0){
        
    }
}