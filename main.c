#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int check_file_size(FILE *fd);
void cp(char *src, char *dst);
char *reset_path(char *path, int num);

int main(int argc, char *argv[])
{
    char *dir[argc-1];
    char *path = argv[argc-1];
    int path_len = strlen(path);
    int tmp;

    printf("[+]---Path Len : %d---[+]\n", path_len);
    printf("[+]---ARGC : %d---[+]\n", argc);

    if(argc < 3)
    {
        printf("Usage : ./%s <filename1> <filename2>\n", argv[0]);
        printf("or\nUsage : %s <filename1> <filename2> ... <directory name>\n", argv[0]);
        return 0;
    }

    if(argc == 3)
        cp(argv[1], argv[2]);

    else
    {
        if(path[path_len-1] != '/')
        {
            strcat(path, "/");
            path_len++;
        }

        for(int i = 1; i < argc-1; i++)
        {
            tmp = strlen(argv[i]);
            dir[i] = strcat(path, argv[i]);
            cp(argv[i], dir[i]);
            path = reset_path(path, tmp);
        }
    }
    return 0;
}

int check_file_size(FILE *fd)
{
    fseek(fd, 0, SEEK_END);
    int size = ftell(fd);
    rewind(fd);

    printf("file size : %d\n", size);
    return size;
}

void cp(char *src, char *dst)
{
    FILE *src_file, *dst_file;
    int size = 0;
    src_file = fopen(src, "r");

    size = check_file_size(src_file);

    printf("File Size : %d\n", size);

    char buf[size];
    dst_file = fopen(dst, "w");

    while(fread(buf, 1, size, src_file))
    {
        buf[size] = '\0';
        fwrite(buf, 1, size, dst_file);
        printf("Length : %d\n", size);
        printf("%s\n", buf);
    }
    fclose(src_file);
    fclose(dst_file);
}

char *reset_path(char *path, int num)
{
    int len = strlen(path);
    for(int i = 1; i <= num; i++)
    {
        path[len-i] = '\0';
    }
    return path;
}
