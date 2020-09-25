/**
 * @file test.c 测试驱动
 * @author raven (zhang.xingrui@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd, ret;

    fd = open("/dev/hello", O_RDWR);
    if(fd == -1){
        perror("open error\n");
        return -1;
    }else{
        printf("open /dev/hello success\n");
    }

    /* write test */
    char buf[10] = "hello";
    ret = write(fd, buf, sizeof(buf) / sizeof(char));
    printf("write %d bytes\n", ret);

    /* read test */
    ret = read(fd, buf, sizeof(buf) / sizeof(char));
    printf("read %d bytes\n", ret);

    close(fd);
    return 0;
}
