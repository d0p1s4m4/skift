#include <abi/Syscalls.h>
#include <assert.h>
#include <signal.h>

sighandler_t signal(int sig, sighandler_t handler)
{
    //TODO: connect this handler
    __unused(sig);
    __unused(handler);

    ASSERT_NOT_REACHED();

    return NULL;
}

int raise(int sig)
{
    switch (sig)
    {
    case SIGTERM:
    case SIGKILL:
        return hj_process_exit(-1) == Result::SUCCESS ? 0 : -1;
    default:
        return -1;
    }
}

int sigemptyset(sigset_t *set)
{
    __unused(set);

    return 0;
}

int sigsuspend(const sigset_t *set)
{
    __unused(set);

    return 0;
}

int sigaction(int sig, const struct sigaction *s1, struct sigaction *s2)
{
    __unused(sig);
    __unused(s1);
    __unused(s2);

    return 0;
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    __unused(set);
    __unused(oldset);

    switch (how)
    {
    case SIG_BLOCK:
    case SIG_UNBLOCK:
    case SIG_SETMASK:
        return 0;
    default:
        return -1;
    }
}