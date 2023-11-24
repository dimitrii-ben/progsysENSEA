#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void displayFile(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    struct stat sb;
    fstat(fd,&sb);
    char buffer[sb.st_blksize];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sb.st_blksize)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to STDOUT");
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

void copyFile(const char *srcFilename, const char *destFilename) {
    int srcFd = open(srcFilename, O_RDONLY);
    if (srcFd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    /*O_EXCL prevent overwriting a file that already exists*/
    int destFd = open(destFilename, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (destFd == -1) {
        perror("Error creating destination file, file may already exist");
        close(srcFd);
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    fstat(srcFd,&sb);
    char buffer[sb.st_blksize];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        if (write(destFd, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(srcFd);
            close(destFd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
        close(srcFd);
        close(destFd);
        exit(EXIT_FAILURE);
    }

    close(srcFd);
    close(destFd);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <source_file> [destination_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /*Source file*/
    const char *srcFilename = argv[1];

    struct stat srcStat;
    if (stat(srcFilename, &srcStat) == -1) {
        perror("Error getting file status");
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(srcStat.st_mode)) {
        fprintf(stderr, "Error: %s is not an ordinary file\n", srcFilename);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        const char *destFilename = argv[2];

        struct stat destStat;
        if (stat(destFilename, &destStat) != -1) {
            fprintf(stderr, "Error: %s already exists\n", destFilename);
            exit(EXIT_FAILURE);
        }

        copyFile(srcFilename, destFilename);
    } else {
        displayFile(srcFilename);
    }

    return EXIT_SUCCESS;
}
