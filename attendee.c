

#include "attendee.h"
#include "utils.h"
#include "event.h"
#include <stdio.h>
#include <stdlib.h>

#define ATT_FILE "attendees.csv"

// attendees CSV: id,event_id,name,contact,email,rsvp
void register_attendee() {
    char name[128], contact[64], email[128];
    int event_id;
    printf("Event ID to register for: ");
    if (scanf("%d", &event_id) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); return; }
    while(getchar()!='\n');

    if (!event_exists(event_id)) {
        printf("Event %d does not exist.\n", event_id);
        return;
    }

    printf("Attendee name: ");
    fgets(name, sizeof(name), stdin); strip_newline(name);
    printf("Contact (phone): ");
    fgets(contact, sizeof(contact), stdin); strip_newline(contact);
    printf("Email: ");
    fgets(email, sizeof(email), stdin); strip_newline(email);

    // find next id
    FILE *f = fopen(ATT_FILE, "a+");
    if (!f) { printf("Error opening attendees file.\n"); return; }
    int next_id = 1;
    char line[MAX_LINE];
    rewind(f);
    while (fgets(line, sizeof(line), f)) {
        int id;
        if (sscanf(line, "%d,", &id) == 1) {
            if (id >= next_id) next_id = id + 1;
        }
    }
    fprintf(f, "%d,%d,%s,%s,%s,Pending\n", next_id, event_id, name, contact, email);
    fclose(f);
    printf("Attendee registered with ID %d\n", next_id);
}

void list_attendees_for_event() {
    int event_id;
    printf("Event ID: ");
    if (scanf("%d", &event_id) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); return; }
    while(getchar()!='\n');

    FILE *f = fopen(ATT_FILE, "r");
    if (!f) { printf("No attendees yet.\n"); return; }
    char line[MAX_LINE];
    printf("\nAttendees for Event %d:\n", event_id);
    printf("ID | Name | Contact | Email | RSVP\n");
    printf("----------------------------------------\n");
    while (fgets(line, sizeof(line), f)) {
        int id, eid;
        char name[128], contact[64], email[128], rsvp[32];
        int scanned = sscanf(line, "%d,%d,%127[^,],%63[^,],%127[^,],%31[^\n]",
                             &id, &eid, name, contact, email, rsvp);
        if (scanned >= 5 && eid == event_id) {
            printf("%d | %s | %s | %s | %s\n", id, name, contact, email, scanned==6? rsvp : "Pending");
        }
    }
    fclose(f);
}
