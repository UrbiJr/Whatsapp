
/*! \file mysignal.c
    \author F. Urbinelli federico.urbinelli@gmail.com
    \version 1.0.0
    \date 06/03/2017
*/

#include "mysignal.h"

/*! \fn wait_for_pid
    \brief handle child process
    \pid child pid
    \note see <http://stackoverflow.com/a/41355435/7158454>
*/
void wait_for_pid(int pid){
    
    int status;
    int corpse;
    int curpid = getpid();
    printf("%d: waiting for children to die\n", curpid);
    while ((corpse = wait(&status)) >= 0 && corpse != pid)
        printf("%d: Unexpected child %d exited with status 0x%.4X\n", curpid, corpse, status);
    if (corpse == pid)
        printf("%d: Child %d exited with status 0x%.4X\n", curpid, corpse, status);
    else
        printf("%d: Child %d died without its death being tracked\n", curpid, pid);
}
