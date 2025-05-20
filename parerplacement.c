#include <stdio.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void fifo_pr(int referenceString[], int pages, int frames);
void lru_pr(int referenceString[], int pages, int frames);
void optima_pr(int referenceString[], int pages, int frames);
int findOptimalPage(int referenceString[], int pages, int current, int frames[], int numPages);

int main() {
    int referenceString[MAX_PAGES], pages, frames;

    
    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter the reference string:\n");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    
    printf("\n--- FIFO Page Replacement ---\n");
    fifo_pr(referenceString, pages, frames);

    
    printf("\n--- LRU Page Replacement ---\n");
    lru_pr(referenceString, pages, frames);

   
    printf("\n--- Optimal Page Replacement ---\n");
    optima_pr(referenceString, pages, frames);

    return 0;
}


void fifo_pr(int referenceString[], int pages, int frames) {
    int frameArray[MAX_FRAMES], pageFaults = 0, idx = 0;

   
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == page) {
                pageFound = 1;
                break;
            }
        }

       
        if (!pageFound) {
            frameArray[idx] = page;
            idx = (idx + 1) % frames;
            pageFaults++;
        }

       
        printf("Frames after processing page %d: ", page);
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] != -1)
                printf("%d ", frameArray[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total page faults (FIFO): %d\n", pageFaults);
}


void lru_pr(int referenceString[], int pages, int frames) {
    int frameArray[MAX_FRAMES], pageFaults = 0;
    int lastUsed[MAX_FRAMES]; 

   
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        int page = referenceString[i];
        int pageFound = 0;

      
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == page) {
                pageFound = 1;
                lastUsed[j] = i; 
                break;
            }
        }

        
        if (!pageFound) {
            int leastUsedIdx = 0;
            for (int j = 1; j < frames; j++) {
                if (lastUsed[j] < lastUsed[leastUsedIdx]) {
                    leastUsedIdx = j;
                }
            }

            frameArray[leastUsedIdx] = page;
            lastUsed[leastUsedIdx] = i;
            pageFaults++;
        }

       
        printf("Frames after processing page %d: ", page);
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] != -1)
                printf("%d ", frameArray[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total page faults (LRU): %d\n", pageFaults);
}


void optima_pr(int referenceString[], int pages, int frames) {
    int frameArray[MAX_FRAMES], pageFaults = 0;

   
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        int page = referenceString[i];
        int pageFound = 0;

       
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == page) {
                pageFound = 1;
                break;
            }
        }

       
        if (!pageFound) {
            int optimalIdx = findOptimalPage(referenceString, pages, i, frameArray, frames);
            frameArray[optimalIdx] = page;
            pageFaults++;
        }

      
        printf("Frames after processing page %d: ", page);
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] != -1)
                printf("%d ", frameArray[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total page faults (Optimal): %d\n", pageFaults);
}


int findOptimalPage(int referenceString[], int pages, int current, int frames[], int numPages) {
    int farthest = current, optimalIdx = -1;

    for (int i = 0; i < numPages; i++) {
        int j;
        for (j = current + 1; j < pages; j++) {
            if (frames[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    optimalIdx = i;
                }
                break;
            }
        }

      
        if (j == pages) {
            return i;
        }
    }

    return optimalIdx;
}