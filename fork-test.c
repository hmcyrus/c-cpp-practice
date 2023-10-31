#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

//On success, the PID of the child process is returned in the parent, and 0 is returned 
//in the child.  On failure, -1 is returned in the parent, no child process is created, 
//and errno is set to indicate the error.

int main()
{
    printf("From the function, the thread id = %ld\n", pthread_self());

    pid_t process;
    process = fork();

    if (process == 0){            
        printf("Hi! I am a Child process with pid %ld\n", pthread_self());                
    }        
    else{
        printf("I am the parent process of the process with with pid %ld\n", pthread_self());
    }
        
}