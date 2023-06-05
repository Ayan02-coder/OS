 #include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int frames[MAX_FRAMES];
int page_faults = 0;

int find_empty_frame()
{
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == -1)
            return i;
    }
    return -1;
}

bool is_page_present(int page)
{
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

int get_least_recently_used_frame(int page_sequence[], int current_index)
{
    int least_recent_index = current_index;
    int least_recent_page = frames[least_recent_index];

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = current_index - 1; j >= 0; j--) {
            if (frames[i] == page_sequence[j])
                break;
        }

        if (j == -1) {
            least_recent_page = frames[i];
            least_recent_index = i;
            break;
        }

        if (j < least_recent_index) {
            least_recent_page = frames[i];
            least_recent_index = j;
        }
    }

    return least_recent_index;
}

void simulate_lru(int page_sequence[], int length)
{
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < length; i++) {
        int page = page_sequence[i];

        if (!is_page_present(page)) {
            int empty_frame = find_empty_frame();

            if (empty_frame != -1) {
                frames[empty_frame] = page;
            } else {
                int lru_frame = get_least_recently_used_frame(page_sequence, i);
                frames[lru_frame] = page;
            }

            page_faults++;
        }
    }
}

int main()
{
    int page_sequence[MAX_PAGES];
    int length;

    printf("Enter the length of the page sequence (max %d): ", MAX_PAGES);
    scanf("%d", &length);

    printf("Enter the page sequence: ");
    for (int i = 0; i < length; i++) {
        scanf("%d", &page_sequence[i]);
    }

    simulate_lru(page_sequence, length);

    printf("Page faults: %d\n", page_faults);

    return 0;
}

