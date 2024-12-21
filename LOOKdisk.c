#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 8 
int disk_size = 200; 

void LOOK(int arr[], int head, char direction[]) { 
    int seek_count = 0; 
    int distance, cur_track; 
    int left[100], right[100]; 
    int seek_sequence[100]; 
    int left_size = 0, right_size = 0, seek_size = 0; 
    int i, j, run = 2; 

    for (i = 0; i < size; i++) { 
        if (arr[i] < head) 
            left[left_size++] = arr[i]; 
        if (arr[i] > head) 
            right[right_size++] = arr[i]; 
    } 

    for (i = 0; i < left_size - 1; i++) { 
        for (j = i + 1; j < left_size; j++) { 
            if (left[i] > left[j]) { 
                int temp = left[i]; 
                left[i] = left[j]; 
                left[j] = temp; 
            } 
        } 
    } 

    for (i = 0; i < right_size - 1; i++) { 
        for (j = i + 1; j < right_size; j++) { 
            if (right[i] > right[j]) { 
                int temp = right[i]; 
                right[i] = right[j]; 
                right[j] = temp; 
            } 
        } 
    } 

    while (run--) { 
        if (strcmp(direction, "left") == 0) { 
            for (i = left_size - 1; i >= 0; i--) { 
                cur_track = left[i]; 
                seek_sequence[seek_size++] = cur_track; 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            strcpy(direction, "right"); 
        } else if (strcmp(direction, "right") == 0) { 
            for (i = 0; i < right_size; i++) { 
                cur_track = right[i]; 
                seek_sequence[seek_size++] = cur_track; 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            strcpy(direction, "left"); 
        } 
    } 

    printf("Total number of seek operations = %d\n", seek_count); 
    printf("Seek Sequence is:\n"); 

    for (i = 0; i < seek_size; i++) { 
        printf("%d\n", seek_sequence[i]); 
    } 
} 

int main() { 
    int arr[size] = { 98, 183, 41, 122, 14, 124, 65, 67}; 
    int head = 53; 
    char direction[] = "right"; 

    printf("Initial position of head: %d", head); 

    LOOK(arr, head, direction); 

    return 0; 
}
