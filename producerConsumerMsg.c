#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\ProducerConsumerPipe"
#define BUFFER_SIZE 1024
#define STOP_MESSAGE "exit"

// Function prototypes
DWORD WINAPI producer(LPVOID lpParam);
DWORD WINAPI consumer(LPVOID lpParam);

int main() {
    HANDLE hProducer, hConsumer;

    // Create producer and consumer threads
    hProducer = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    if (hProducer == NULL) {
        printf("Error creating producer thread: %d\n", GetLastError());
        return 1;
    }

    hConsumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    if (hConsumer == NULL) {
        printf("Error creating consumer thread: %d\n", GetLastError());
        return 1;
    }

    // Wait for threads to finish
    WaitForSingleObject(hProducer, INFINITE);
    WaitForSingleObject(hConsumer, INFINITE);

    // Close thread handles
    CloseHandle(hProducer);
    CloseHandle(hConsumer);

    return 0;
}

DWORD WINAPI producer(LPVOID lpParam) {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesWritten;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_OUTBOUND,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        1, // Number of instances
        BUFFER_SIZE,
        BUFFER_SIZE,
        0,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating named pipe: %d\n", GetLastError());
        return 1;
    }

    printf("Producer: Waiting for consumer to connect...\n");
    // Wait for the consumer to connect
    ConnectNamedPipe(hPipe, NULL);
    printf("Producer: Consumer connected.\n");

    // Produce 10 messages
    for (int i = 1; i <= 10; i++) {
        snprintf(buffer, BUFFER_SIZE, "Message %d", i);
        if (!WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL)) {
            printf("Producer: Error writing to pipe: %d\n", GetLastError());
            break;
        }
        printf("Producer: Sent '%s'\n", buffer);
        Sleep(1000); // Simulate production time
    }

    // Send stop message
    strcpy(buffer, STOP_MESSAGE);
    WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL);
    printf("Producer: Sent stop message.\n");

    // Close the pipe
    CloseHandle(hPipe);
    printf("Producer finished.\n");
    return 0;
}

DWORD WINAPI consumer(LPVOID lpParam) {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    // Open the named pipe
    hPipe = CreateFile(
        PIPE_NAME,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Consumer: Error opening named pipe: %d\n", GetLastError());
        return 1;
    }

    printf("Consumer: Connected to the producer.\n");

    // Consume messages
    while (1) {
        if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Consumer: Received '%s'\n", buffer);
            if (strcmp(buffer, STOP_MESSAGE) == 0) {
                printf("Consumer: Stop message received. Exiting.\n");
                break;
            }
        } else {
            printf("Consumer: Error reading from pipe: %d\n", GetLastError());
            break;
        }
    }

    // Close the pipe
    CloseHandle(hPipe);
    printf("Consumer finished.\n");
    return 0;
}
