#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <windows.h>
#include <sys/wait.h>

pid_t child_pid;

void send_ctrl_event(int s) {
    GenerateConsoleCtrlEvent(0, child_pid);
}

int main(int argc, char* argv[]) {
    struct sigaction sigIntHandler;
    sigset_t set, oset;

    if (argc < 2) {
        printf("Usage: %s <program name> [program args]\n", argv[0]);
        return -1;
    }

    // Block SIGINT
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, &oset);

    child_pid = fork();
    if (child_pid == 0) {
        execvp(argv[1], argv + 1);
        return 0;
    }

    // Unblock SIGINT
    sigprocmask(SIG_SETMASK, &oset, NULL);

    // Install handler
    sigIntHandler.sa_handler = send_ctrl_event;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    // Wait for finish
    while(waitpid(child_pid, NULL, WNOHANG) == 0) {
        sleep(1);
    }

    return 0;
}

