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

char buffer[80];
char buffer2[80];

void main()
{
    unsigned char i,value;
    DIR *dir;
    struct dirent *fil;
    char filename[] = "1:/DEV/test.bin";
    int error;

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
    for (i = 0; i < locicfg.devnr + 1; i++)
    {
        if (i == 0 || locicfg.validdev[i])
        {
            cprintf("[%u] %s\n\r", i, get_loci_devname(i, 35));
        }
    }

    // Listing root dir drive 1
    cprintf("\n\rList root dir of device 1:\n\r");
    dir = opendir("1:/");

    while (fil = readdir(dir), fil->d_name[0] != 0)
    {
        cprintf("FD:%2X AT:%2X %s (%u)\n\r", fil->d_fd, fil->d_attrib, fil->d_name, fil->d_size);
    }
    closedir(dir);

    cprintf("Press a key.\n\r");
    cgetc();

    // Memcopy function test
    clrscr();
    cprintf("%c%cTesting the Loci API: XRAM MemCopy\n\n\r", A_BGGREEN, A_FWBLACK);

    cprintf("Generating numbers to write:\n\r");
    for (i = 0; i < 80; i++)
    {
        buffer[i] = i;
        cprintf("%2x", buffer[i]);
    }
    cprintf("\n\rWriting.\n\r");
    xram_memcpy_to((void *)FM_XRAM_ADDR, &buffer, 80);
    cprintf("Reading.\n\r");
    xram_memcpy_from(&buffer2, (void *)FM_XRAM_ADDR, 80);
    cprintf("Printing read numbers:\n\r");
    for (i = 0; i < 80; i++)
    {
        cprintf("%2x", buffer2[i]);
    }

    cprintf("\n\rPoking value $40 to XRAM\n\r");\
    xram_poke((void *)FM_XRAM_ADDR, 0x40);
    cprintf("Peeking value from XRAM: %2x\n\r", xram_peek((void *)FM_XRAM_ADDR));

    cprintf("Press a key.\n\r");
    cgetc();

    // File Ops test
    clrscr();
    cprintf("%c%cTesting the Loci API: File Ops\n\r", A_BGGREEN, A_FWBLACK);
    memset(&buffer2, 0, 80);

    cprintf("\n\rSave to file.\n\r");
    error = file_save(filename, &buffer, 80);
    if (error < 1)
    {
        cprintf("Error %4x\n\r", error);
        exit(1);
    }
    cprintf("Return code: %4X\n\r", error);

    cprintf("\n\rRead from file.\n\r");
    error = file_load(filename, &buffer2, 80);
    if (error < 1)
    {
        cprintf("Error %4x\n\r", error);
        exit(1);
    }
    cprintf("Return code: %4X\n\r", error);

    cprintf("Printing read numbers:\n\r");
    for (i = 0; i < 80; i++)
    {
        cprintf("%2x", buffer2[i]);
    }

    cprintf("\n\rClean file.\n\r");
    if (remove(filename))
    {
        cprintf("Error\n\r", error);
        exit(1);
    }

    cprintf("Press a key.\n\r");
    cgetc();

    // Overlay RAM test
    clrscr();
    cprintf("%c%cTesting the Loci API: Overlay RAM\n\r", A_BGGREEN, A_FWBLACK);
    memset(&buffer2, 0, 80);

    cprintf("Copy to overlay RAM $C000.\n\r");
    enable_overlay_ram();
    memcpy((void *)0xC000, &buffer, 80);
    memcpy(&buffer2, (void *)0xC000, 80);
    disable_overlay_ram();
    cprintf("Printing read numbers:\n\r");
    for (i = 0; i < 80; i++)
    {
        cprintf("%2x", buffer2[i]);
    }

    cprintf("\n\rPoking value $40 to overlay RAM\n\r");
    enable_overlay_ram();
    POKE((void *)0xC000, 0x40);
    disable_overlay_ram();
    cprintf("Peeking value from XRAM: ");
    enable_overlay_ram();
    value = PEEK((void *)0xC000);
    disable_overlay_ram();
    cprintf("%2x\n\r", value);

    cprintf("\n\rSaving to a file from overlay RAM.\n\r");
    enable_overlay_ram();
    error = file_save(filename, (void *)0xC000, 80);
    disable_overlay_ram();
    if (error < 1)
    {
        cprintf("Error %4x\n\r", error);
        exit(1);
    }
     cprintf("Return code: %4X\n\r", error);

    cprintf("\n\rRead from file.\n\r");
    error = file_load(filename, &buffer2, 80);
    if (error < 1)
    {
        cprintf("Error %4x\n\r", error);
        exit(1);
    }
    cprintf("Return code: %4X\n\r", error);

    cprintf("Printing read numbers:\n\r");
    for (i = 0; i < 80; i++)
    {
        cprintf("%2x", buffer2[i]);
    }

    cprintf("\n\rClean file.\n\r");
    if (remove(filename))
    {
        cprintf("Error\n\r", error);
        exit(1);
    }

    cprintf("\n\rPress a key.\n\r");
    cgetc();

    // Clear screen on exit
    setflags(SCREEN);
    clrscr();
}