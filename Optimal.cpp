#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

int page_faults = 0;

void print_frames(int frames[], int n)
{
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("  ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

bool is_page_in_frame(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

int get_optimal_page(int pages[], int n, int frames[], int n_frames, int current_index)
{
    int farthest_index = current_index;
    int optimal_page = -1;

    for (int i = 0; i < n_frames; i++) {
        int page = frames[i];
        bool found = false;

        for (int j = current_index; j < n; j++) {
            if (pages[j] == page) {
                found = true;
                if (j > farthest_index) {
                    farthest_index = j;
                    optimal_page = page;
                }
                break;
            }
        }

        if (!found)
            return page;
    }

    return optimal_page;
}

void simulate_optimal_page_replacement(int pages[], int n)
{
    int frames[MAX_FRAMES];
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        if (!is_page_in_frame(frames, MAX_FRAMES, page)) {
            int index = get_optimal_page(pages, n, frames, MAX_FRAMES, i + 1);
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == index) {
                    frames[j] = page;
                    break;
                }
                else if (frames[j] == -1) {
                    frames[j] = page;
                    break;
                }
            }
            page_faults++;
        }

        print_frames(frames, MAX_FRAMES);
    }
}

int main()
{
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);

    simulate_optimal_page_replacement(pages, n);

    printf("Total page faults: %d\n", page_faults);

    return 0;
}
