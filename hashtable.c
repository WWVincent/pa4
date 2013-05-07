#include "kernel.h"

#define PROBE_COUNT 10
#define HASH 7

static int num_entry = 0;
static int put_mutex = 0;

struct hash_node* create_hashtable(int entry){
	struct hash_node* hash_base = (struct hash_node*)malloc(sizeof(hash_node)*entry);
	for (int i = entry - 1 ; i > -1; i--){
		hash_base[i].key = 0;
		hash_base[i].value = -1;
	}
	num_entry = entry;
	return hash_base;
}

int hash_put(struct hash_node* hash_base, int x, int num){
	int index = (x * HASH) % num_entry;
	for (int j=0; j< PROBE_COUNT; j++){
		if (hash_base[index].key == x) {
			return;
		}
		if (hash_base[index].value == -1){
			hash_base[index].value = num;
			hash_base[index].key = x;
			return 1;
		}else{index= (index + 1) % num_entry;}
	}
	return 0;
}

int hash_remove(struct hash_node* hash_base, int x){
	int index = (x * HASH) % num_entry;
	for (int j=0; j<PROBE_COUNT; j++){
		if (hash_base[index].key == x && hash_base[index].value != -1){
			hash_base[index].key = 0;
			hash_base[index].value = -1;
			return 1;
		}else{index = (index + 1) % num_entry;}
	}
	return 0;
}

int hash_increase(struct hash_node* hash_base, int x){
	int index = (x * HASH) % num_entry;
	for (int j=0; j<PROBE_COUNT; j++){
		if (hash_base[index].key == x && hash_base[index].value != -1){
			hash_base[index].value++;
			return 1;
		}else{index = (index + 1) % num_entry;}
	}
	return 0;
}


int hash_get(struct hash_node* hash_base, int x){
	int index = (x * HASH) % num_entry;
	for (int j=0; j<PROBE_COUNT; j++){
		if (hash_base[index].key == x && hash_base[index].value != -1 ){
			return hash_base[index].value;
			;
		}else{index = (index + 1) % num_entry;}
	}
	return 0;
}

void hash_output(struct hash_node* hash_base){
	for (int i = 0; i < num_entry; i++ ){
		if (hash_base[i].value != -1){
			printf("\tkey: %x --> times: %d\n", hash_base[i].key, hash_base[i].value);
		}
	}
}