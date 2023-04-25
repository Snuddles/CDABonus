#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 32
#define BLOCK_SIZE 4
#define NUM_SETS (CACHE_SIZE / BLOCK_SIZE)
struct cache_entry
{
    unsigned int tag;
    int lru_counter;
};
struct cache_entry cache[NUM_SETS];
void init_cache() {
    // Initialize all cache sets
    for (int i = 0; i < NUM_SETS; i++) {
        cache[i].tag = 0;
        cache[i].lru_counter = 0;
        // Initialize any other necessary bookkeeping data here
    }
}
int access_cache(unsigned int address) {
    // Compute set index and tag from the address
    int set_index = (address / BLOCK_SIZE) % NUM_SETS;
    unsigned int tag = address / (NUM_SETS * BLOCK_SIZE);
    
    // Check if the tag matches the one in the cache
    if (cache[set_index].tag == tag) {
        // Cache hit: update LRU counter and return 1
        cache[set_index].lru_counter++;
        return 1;
    } else {
        // Cache miss: update tag and LRU counter, perform bookkeeping, and return 0
        cache[set_index].tag = tag;
        cache[set_index].lru_counter = 0;
        // Perform any other necessary cache bookkeeping here
        return 0;
    }
}

int main() {
    // Initialize variables
    int num_hits = 0, num_accesses = 0;
    unsigned int address;

    // Initialize cache
    init_cache();

    // Read addresses from input file
    FILE *fp = fopen("traces.txt", "r");
    while (fscanf(fp, "%x", &address) != EOF) {
        num_accesses++;
        num_hits += access_cache(address);
    }
    fclose(fp);

    // Compute and print hit rate
    double hit_rate = (double) num_hits / num_accesses;
    printf("Direct-mapped LRU cache hit rate: %f\n", hit_rate);
    // Compute and print number of hits and misses
    int num_misses = num_accesses - num_hits;
    printf("Number of cache hits: %d\n", num_hits);
    printf("Number of cache misses: %d\n", num_misses);

    return 0;
}
