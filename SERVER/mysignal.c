
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "mysignal.h"

// a big thanks to @JonathanLeffler from stackoverflow
// see <http://stackoverflow.com/a/41355435/7158454>
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