// Includes
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <peekpoke.h>
#include <ctype.h>
#include <atmos.h>
#include "osdklib.h"
#include "loci.h"

void main()
{
    char i;
    DIR *dir;
    struct dirent *fil;

    // Init screen
    setflags(SCREEN + NOKEYCLICK);
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
    clrscr();

    // Welcome
    cprintf("%c%cTesting the Loci API.\n\n\r", A_BGGREEN, A_FWBLACK);

    // Getting valid drices on LOCI
    get_locicfg();

    // Printing valid LOCI drives
    cprintf("Valid storage devices on LOCI:\n\r");
    for(i=0;i<locicfg.devnr+1;i++)
    {
        if(i==0 || locicfg.validdev[i])
        {
            cprintf("[%u] %s\n\r",i,get_loci_devname(i,35));
        }
    }

    cprintf("\n\rList root dir of device 1:\n\r");
    dir = opendir("1:/");

    while (fil = readdir(dir), fil->d_name[0] != 0)
    {
        cprintf("FD:%2X AT:%2X %s (%u)\n\r",fil->d_fd,fil->d_attrib,fil->d_name,fil->d_size);
    }
    closedir(dir);

    cprintf("Press a key.\n\r");
    cgetc();

    // Clear screen on exit
    setflags(SCREEN);
    clrscr();
}