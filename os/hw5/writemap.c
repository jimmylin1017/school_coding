#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#ifdef _DEBUG
    #define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
    #define DEBUG(format, args...)
#endif

#define SIZE 100

int main(int argc, const char *argv[])
{

    int fd;
    int choose;
    printf("1:empty file\nelse:exist file\n");
    scanf("%d", &choose);
    getchar();
    if(choose == 1)
        fd = open("text", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    else
        fd = open("text", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(fd == -1)
    {
        printf("file open error!\n");
        exit(EXIT_FAILURE);
    }

    struct stat text_info = {0};
    fstat( fd, &text_info );
    int text_len = (int)text_info.st_size;

    DEBUG("text len : %d\n", text_len);

    char *map = (char *)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, 0);

    if(map == MAP_FAILED)
    {
        close(fd);
        printf("mapping error!\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        char s[SIZE] = {0};


        printf("please input string (input q to exit)\n");
        fgets(s, SIZE, stdin);
        int len = strlen(s);

        if(len == 2 && s[0] == 'q')
            break;

        DEBUG("string : %s", s);
        DEBUG("string len : %d\n", len);

        lseek(fd, text_len + len, SEEK_SET);
        write(fd, "", 1);
        lseek(fd, 0, SEEK_SET);

        for(int i = 0; i < len; ++i)
        {
            map[text_len + i] = s[i];
        }

        text_len += len;

        DEBUG("text len : %d\n", text_len);

    }

    close(fd);

    return 0;
}
