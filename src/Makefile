


TARGET := pic_display

# 编译器的名字 C Compilor
CC := arm-linux-gcc

# 头文件搜索路径 
INC := -I  ../inc 
# INC += ...


# 依赖的库的路径及依赖库名字
LIBS :=  -l pthread  -l m
LIBS += -L  ../libs  -l jpeg
# LIBS += -L  ./abc/  -l abc  

# 所有的.c文件列表
CSRCS := $(wildcard *.c) 
# CSRCS += $(wildcard media/*.c)

# 所有的.o文件列表
OBJS :=  $(patsubst  %.c, %.o,  $(CSRCS))


# CUR := $(shell pwd)

$(TARGET): $(OBJS)
	$(CC)  $^  $(LIBS) -o $@
	cp $(TARGET)   /tftpboot
	


%.o: %.c 
	$(CC) -c  $<  $(INC) -o $@


# “清空目标”：把所有的中间文件(如: .o)和最终的可执行文件 都删除掉
clean:
	rm -rf $(OBJS)  $(TARGET)



