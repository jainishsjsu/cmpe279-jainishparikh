// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    //if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    //                                              &opt, sizeof(opt))) 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    
    // printf("Current process id before fork: %d \n",getpid());
    // printf("Current user id before fork: %d \n",getuid());
    int p_id = fork();
    // printf("Current process id after fork: %d \n",getpid());
    
    if (p_id == 0){
        // printf("In child process: %d \n",getpid());
        int userid = setuid(65534);
        if(userid == -1){
            printf("Error changing user id");
            exit(EXIT_FAILURE);
        }
        valread = read( new_socket , buffer, 1024); 
        printf("%s\n",buffer ); 
    
    }else if(p_id > 0){
        wait(NULL);
        // printf("In parent process\n");
        send(new_socket , hello , strlen(hello) , 0 ); 
        printf("Hello message sent\n"); 
    
    }else{
        printf("Error in forking the process");
    }

    // printf("Current process id: %d \n",getpid());
    // printf("Current user id: %d \n",getuid());
    
    
    return 0; 
} 
