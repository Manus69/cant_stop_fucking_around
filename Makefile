cc = gcc
flags = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined

flags_release = -Wall -Wextra -Ofast -flto -funroll-loops -D NDEBUG \
-funsafe-math-optimizations \
-fprefetch-loop-arrays \
-ffast-math \
-fpeel-loops \
-march=native -mtune=native \
-Winline \

src_dir = ./
obj_dir = ./obj
exe = a.out
include_dir = $(src_dir)
src = $(wildcard *.c)
headers = $(wildcard *.h)
obj = $(addprefix $(obj_dir)/,$(subst .c,.o,$(src)))

all: $(exe)

release: flags := $(flags_release)
release: re

$(exe) : $(obj)
	$(cc) $(flags) $^ -o $@

$(obj_dir)/%.o : %.c $(headers)
	$(cc) $(flags) -I $(include_dir) -c $< -o $@

clean:
	rm -f $(obj)

rm_exe:
	rm -f $(exe)

rm_lib:
	rm -f $(lib)

re: clean rm_exe rm_lib all