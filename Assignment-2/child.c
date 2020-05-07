#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pwd.h>
#define PORT 80

int main(int argc, char const *argv[])
{

    char buffer[1024] = {0};
    int valread = 0;
    int userid = setuid(65534);
    if (userid == -1)
    {
        printf("Error changing user id");
        exit(EXIT_FAILURE);
    }
    int new_socket = *argv[1];
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
}
