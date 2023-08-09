#ifndef IO_H
#define IO_H

#include "Str.h"

Buf io_read_fd(int fd);
Str io_read_txt_fd(int fd);
Str io_read_txt(const char * name);
Vec io_read_txt_by_line(const char * name);
idx io_write_fd(Buf buf, int fd);
idx io_write(Buf buf, const char * name);
idx io_create_file(const char * name);

#endif