#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // optional, not needed if linked in Code::Blocks
#include "event.h"
#include "attendee.h"

int main() {
    int choice;
    while (1) {
        printf("\n==== Community Event System ====\n");
        printf("1) Create Event\n");
        printf("2) List Events\n");
        printf("3) Register Attendee\n");
        printf("4) List Attendees for Event\n");
        printf("5) Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n'); // clear
            continue;
        }
        while(getchar()!='\n'); // clear newline

        switch (choice) {
            case 1: create_event(); break;
            case 2: list_events(); break;
            case 3: register_attendee(); break;
            case 4: list_attendees_for_event(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
