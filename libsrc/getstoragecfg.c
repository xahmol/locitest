#include <loci.h>
#include <string.h>
#include <conio.h>

struct LOCICFGSTRUCT locicfg;

void get_locicfg()
{
    unsigned char devid;
    
    DIR *dir;
    struct dirent *fil;

    // Wipe config
    memset(&locicfg,0,sizeof(locicfg));

    // Get dir of root dir to parse devices
    dir = opendir("");

    while (fil = readdir(dir), fil->d_name[0] != 0 && locicfg.devnr < MAXDEV + 1)
    {
        devid = fil->d_name[0] - '0'; // Get device number

        if(devid)
        {
            locicfg.devnr++;

            // Check for MSC to know if it is a USB mass storage device
            if(fil->d_name[3] == 'M' && fil->d_name[4] == 'S' && fil->d_name[5] == 'C')
            {
                locicfg.validdev[devid] = 1;
            }
        }
    }
    closedir(dir);

    strcpy(locicfg.path,"0:/");
}

const char* get_loci_devname(unsigned char devid,unsigned char maxlength)
{
    DIR *dir;
    struct dirent *fil;
    unsigned char i;

    dir = opendir("");
    for(i=0;i<devid+1;i++)
    {
        fil = readdir(dir);
    }
    closedir(dir);
    if(maxlength<strlen(fil->d_name+3))
    {
        fil->d_name[maxlength+3]=0;
    }
    return fil->d_name+3;
}