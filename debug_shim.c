#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static int signal_recieved_ = 0;

void sig_handler(int signo)
{
  if (signo == SIGUSR1)
  {
    printf("debug_shim: eceived SIGUSR1\n");
    signal_recieved_ = 1;
  }
}

int main(int argc, char *const argv[])
{
    const char* debug_shim_program = "/debug_shim_link";
    
    while (!signal_recieved_);

    execv(debug_shim_program, argv);
}