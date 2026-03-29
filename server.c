#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000
#define BUFFER_SIZE 1024
#define KEY 0x5A   

void encrypt_decrypt(char *data, int len) {
    for(int i = 0; i < len; i++)
        data[i] ^= KEY;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    printf("Server waiting on port %d...\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, BUFFER_SIZE);
    encrypt_decrypt(buffer, strlen(buffer));

    if (strcmp(buffer, "user:1234") != 0) {
        write(new_socket, "AUTH_FAIL", 9);
        close(new_socket);
        return 0;
    }

    write(new_socket, "AUTH_OK", 7);

    read(new_socket, buffer, BUFFER_SIZE);
    encrypt_decrypt(buffer, strlen(buffer));
    FILE *fp = fopen(buffer, "wb");
    if (fp == NULL) {
        perror("File error");
        close(new_socket);
        return 0;
    }

    printf("Receiving file: %s\n", buffer);

    int bytes;
    while ((bytes = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        encrypt_decrypt(buffer, bytes);
        fwrite(buffer, 1, bytes, fp);
        if (bytes < BUFFER_SIZE)
            break;
    }

    printf("File received successfully.\n");
    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}