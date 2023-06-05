#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

void print_frames(int frames[], int size)
{
    for (int i = 0; i < size; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

int is_page_fault(int frames[], int size, int page)
{
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return 0;
        }
    }
    return 1;
}

void simulate_fifo(int pages[], int num_pages)
{
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int frame_index = 0;

    // Initialize frames to -1 to indicate empty frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    printf("Page Replacement Process:\n");

    for (int i = 0; i < num_pages; i++) {
        printf("Page %d: ", pages[i]);

        if (is_page_fault(frames, MAX_FRAMES, pages[i])) {
            page_faults++;

            if (frame_index < MAX_FRAMES) {
                // There are still empty frames, so add the page to an empty frame
                frames[frame_index++] = pages[i];
            } else {
                // All frames are filled, so replace the oldest page (FIFO)
                frames[0] = pages[i];

                // Shift the remaining pages to the left
                for (int j = 1; j < MAX_FRAMES; j++) {
                    frames[j - 1] = frames[j];
                }

                // Add the new page to the last frame
                frames[MAX_FRAMES - 1] = pages[i];
            }

            printf("Page Fault! ");
        } else {
            printf("No Page Fault. ");
        }

        printf("Frames: ");
        print_frames(frames, MAX_FRAMES);
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main()
{
    int pages[MAX_PAGES];
    int num_pages;

    printf("Enter the number of pages (up to %d): ", MAX_PAGES);
    scanf("%d", &num_pages);

    printf("Enter the page references:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\nSimulating FIFO Page Replacement Algorithm:\n");
    simulate_fifo(pages, num_pages);

    return 0;
}
