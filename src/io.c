#include "io.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

Buf io_read_fd(int fd)
{
    struct stat stat;
    Buf         buf;

    fstat(fd, & stat);
    buf = Buf_new(stat.st_size + 1);

    read(fd, Buf_first(buf), stat.st_size);
    Buf_shift_index(& buf, stat.st_size);

    return buf;
}

Str io_read_txt_fd(int fd)
{
    return Str_ctr(io_read_fd(fd));
}

Str io_read_txt(const char * name)
{
    int fd;

    if ((fd = open(name, O_RDONLY)) < 0) return Str_new_empty();

    return io_read_txt_fd(fd);
}

Vec io_read_txt_by_line(const char * name)
{
    Vec lines;
    Str str;

    str = io_read_txt(name);
    lines = Str_split(str, '\n');
    Str_del(& str);

    return lines;
}

idx io_create_file(const char * name)
{
    return creat(name, 0777);
}

idx io_write_fd(Buf buf, int fd)
{
    return write(fd, Buf_first(buf), Buf_index(buf));
}

idx io_write(Buf buf, const char * name)
{
    int fd;

    if ((fd = open(name, O_TRUNC | O_RDWR)) < 0) return fd;

    return io_write_fd(buf, fd);
}
