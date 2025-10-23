#include "event.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define EVENTS_FILE "events.csv"

// Create event: id,name,date,time,venue,description
void create_event() {
    char name[128], date[32], time[32], venue[128], desc[256];
    printf("Event name: ");
    fgets(name, sizeof(name), stdin); strip_newline(name);
    printf("Date (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin); strip_newline(date);
    printf("Time (HH:MM): ");
    fgets(time, sizeof(time), stdin); strip_newline(time);
    printf("Venue: ");
    fgets(venue, sizeof(venue), stdin); strip_newline(venue);
    printf("Description: ");
    fgets(desc, sizeof(desc), stdin); strip_newline(desc);

    // compute next id by reading last line
    FILE *f = fopen(EVENTS_FILE, "a+");
    if (!f) {
        printf("Error opening events file for writing.\n");
        return;
    }

    // find next id
    int next_id = 1;
    char line[MAX_LINE];
    rewind(f);
    while (fgets(line, sizeof(line), f)) {
        // ignore empty
        strip_newline(line);
        if (line[0] == '\0') continue;
        // parse id at start
        int id = atoi(line);
        if (id >= next_id) next_id = id + 1;
    }

    fprintf(f, "%d,%s,%s,%s,%s,%s\n", next_id, name, date, time, venue, desc);
    fclose(f);
    printf("Event created with ID %d\n", next_id);
}

void list_events() {
    FILE *f = fopen(EVENTS_FILE, "r");
    if (!f) {
        printf("No events yet.\n");
        return;
    }
    char line[MAX_LINE];
    printf("\nID | Name | Date | Time | Venue\n");
    printf("-----------------------------------------------\n");
    while (fgets(line, sizeof(line), f)) {
        strip_newline(line);
        if (line[0] == '\0') continue;
        // simple print: split by commas
        int id;
        char name[128], date[32], time[32], venue[128], desc[256];
        int scanned = sscanf(line, "%d,%127[^,],%31[^,],%31[^,],%127[^,],%255[^\n]",
                             &id, name, date, time, venue, desc);
        if (scanned >= 5) {
            printf("%d | %s | %s | %s | %s\n", id, name, date, time, venue);
        }
    }
    fclose(f);
}

int event_exists(int id) {
    FILE *f = fopen(EVENTS_FILE, "r");
    if (!f) return 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        int eid;
        if (sscanf(line, "%d,", &eid) == 1) {
            if (eid == id) { fclose(f); return 1; }
        }
    }
    fclose(f);
    return 0;
}

