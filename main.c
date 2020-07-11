#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h> // for directory open
//#include <unistd.h>

int check_file_size(FILE *fd);

int main(int argc, char *argv[])
{
    printf("ARGC : %d\n", argc);

    if(argc < 3)
    {
        printf("Usage : ./%s <filename1> <filename2>\n", argv[0]);
        printf("or\nUsage : %s <filename1> <filename2> ... <directory name>\n", argv[0]);
        return 0;
    }

    // <file1> <file2>
    if(argc == 3)
    {
        FILE *fd, *dest;
        int len = 0;

        fd = fopen(argv[1], "r");
        len = check_file_size(fd);
        dest = fopen(argv[argc-1], "w");
        char buf[len];

        while (fread(buf, 1, len, fd))
        {
            buf[len] = '\0';
            fwrite(buf, 1, len, dest);
            printf("Length : %d\n", len);
            printf("%s\n", buf);
        }

        fclose(dest);
        fclose(fd);
    }

    // <file1> <file2> ... <directory>
    else
    {
        DIR *dp;
        struct dirent* entry = NULL;
        struct stat dir_buf;

        printf("%s is Directory!\n", argv[argc-1]);
        if((dp = opendir(argv[argc-1])) == NULL)
        {
            printf("%s can't open\n");
            return 0;
        }

        while((entry = readdir(dp)) != NULL)
        {
            lstat(entry->d_name, &dir_buf);

            if(S_ISDIR(dir_buf.st_mode))
                printf("DIR : %s\n", entry->d_name);
            else if(S_ISREG(dir_buf.st_mode))
                printf("FILE : %s\n", entry->d_name);
        }
        closedir(dp);
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
