#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#ifdef _DEBUG
    #define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
    #define DEBUG(format, args...)
#endif

int main(int argc, const char *argv[])
{    
    int fd = open("text", O_RDONLY);

    if(fd == -1)
    {
        printf("file open error!\n");
        exit(EXIT_FAILURE);
    }

    struct stat text_info = {0};
    fstat( fd, &text_info );
    int text_len = (int)text_info.st_size;

    DEBUG("text len : %d\n", text_len);

    char *map = (char *)mmap(0, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    if(map == MAP_FAILED)
    {
        close(fd);
        printf("mapping error!\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        char c;

        printf("please input g to get text (input q to exit)\n");
        scanf("%c", &c);
        getchar();

        if(c == 'q')
            break;
        else if(c != 'g')
            continue;

        for(int i = 0; i < getpagesize(); ++i)
        {
            printf("%c", map[i]);
        }

    }

    return 0;
}