#include "loci.h"
#include <fcntl.h>
#include <conio.h>

const char progress_str[] = ".oOo";

int __fastcall__ file_save(const char *file, const void *src, unsigned int count)
{
    int fd = open(file, O_WRONLY | O_CREAT);
    int error;

    if (fd < 0)
    {
        return fd;
    }

    error = write(fd, src, count);
    close(fd);
    return error;
}

int __fastcall__ file_load(const char *file, void *dst, unsigned int count)
{
    int fd = open(file, O_RDONLY | O_EXCL);
    int error;

    if (fd < 0)
    {
        return fd;
    }

    error = read(fd, dst, count);
    close(fd);
    return error;
}

int __fastcall__ file_copy(const char *dst, const char *src, unsigned char prog, unsigned char progx, unsigned char progy)
{
    int fd_dst;
    int fd_src;
    int len;
    unsigned char cnt;

    fd_src = open(src, O_RDONLY | O_EXCL);
    if (fd_src < 0)
        return fd_src;
    fd_dst = open(dst, O_WRONLY | O_CREAT);

    if (fd_dst < 0)
    {
        close(fd_src);
        return fd_dst;
    }

    do
    {
        len = read_xram(FM_XRAM_ADDR, FM_XRAM_SIZE, fd_src);
        write_xram(FM_XRAM_ADDR, len, fd_dst);
        cputcxy(progx, progy, progress_str[0x03 & cnt++]);
    } while (len == FM_XRAM_SIZE);
    close(fd_src);
    close(fd_dst);
    return 0;
}
