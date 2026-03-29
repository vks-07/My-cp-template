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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    char filename[100];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Send authentication
    strcpy(buffer, "user:1234");
    encrypt_decrypt(buffer, strlen(buffer));
    write(sock, buffer, strlen(buffer));

    read(sock, buffer, BUFFER_SIZE);

    if (strncmp(buffer, "AUTH_OK", 7) != 0) {
        printf("Authentication Failed\n");
        close(sock);
        return 0;
    }

    printf("Authentication Successful\n");

    printf("Enter file name to send: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("File not found");
        close(sock);
        return 0;
    }

    strcpy(buffer, filename);
    encrypt_decrypt(buffer, strlen(buffer));
    write(sock, buffer, strlen(buffer));

    int bytes;
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        encrypt_decrypt(buffer, bytes);
        write(sock, buffer, bytes);
    }

    printf("File sent successfully.\n");

    fclose(fp);
    close(sock);

    return 0;
}