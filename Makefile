cc = gcc
flags = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined

flags_release = -Wall -Wextra -Winline \
-Ofast \
-flto \
-funroll-loops \
-D NDEBUG \
-fprefetch-loop-arrays \
-ffast-math \
-fpeel-loops \
-march=native -mtune=native \
-funsafe-math-optimizations \
-g -fsanitize=address -fsanitize=undefined \

src_dir = ./src
obj_dir = ./obj
exe = a.out
include_dir = $(src_dir)
src = $(wildcard $(src_dir)/*.c)
headers = $(wildcard $(src_dir)/*.h)
obj = $(addprefix $(obj_dir)/,$(subst .c,.o,$(notdir $(src)))) $(test_obj)
test_src = _test.c
test_obj = $(obj_dir)/$(subst .c,.o,$(test_src))

VPATH = $(src_dir)

all: $(exe)

release: flags := $(flags_release)
release: re

$(test_obj) : $(test_src)
	$(cc) $(flags) -I $(include_dir) -c $^ -o $(test_obj)

$(exe) : $(obj) $(test_obj)
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