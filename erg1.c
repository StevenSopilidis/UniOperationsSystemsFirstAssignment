#include "sys/wait.h"
#include "sys/types.h"
#include "unistd.h"
#include "stdio.h"

int main() {
    pid_t pid = fork(); // p0 creates p1
    if(pid == 0) { // in p1
        pid = fork(); // p1 creates p3
        if(pid == 0) { // in p3
            printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 3); // p3 prints its pid 
        } else {
            waitpid(pid, NULL, 0); // p1 waits for p3 and then prints pid
            printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 1); // p1 prints its pid
        }
    } else { // in p0
        pid = fork(); // p0 creates p2
        if(pid == 0) { // in p2
            pid = fork(); // p2 creates p4
            if(pid == 0) { // in p4
                printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 4); // p4 prints its pid
            } else { // in p2
                pid = fork(); // p2 creates p5
                if(pid == 0) { // in p5
                    pid = fork(); // p5 creates p6
                    if (pid == 0) { // in p6
                        printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 6);
                    } else { //inn p5
                        printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 5);
                    }
                } else { // in p2
                    wait(NULL);
                    printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 2); // p2 prints its pid
                }
            }
        }else { // in p0
            waitpid(pid, NULL, 0);
            printf("My id: %d| Parent id: %d, Process number: %d \n", getpid(), getppid(), 0); // p0 prints its pid
            printf("\n\n\n Core for project1: ");            
            char* args[] = {"/bin/cat", "./erg1.c", NULL};
            execve("/bin/cat", args, NULL);
        }
    }
}