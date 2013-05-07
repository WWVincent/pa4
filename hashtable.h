//hash function : key*101 % num_entry

typedef struct hash_node {
	int key;
	int value;
} hash_node;

//use an array of entry size to implement this hash table
//alloc enough space
//us the a link for conflict
struct hash_node *create_hashtable(int entry);

//set the value of key x in hash_base to be num
//return 1 if put succeeded
//else return 0
int hash_put(struct hash_node* hash_base,int x, int num);

//remove key x from hashtable hash_base 
//return 1 if remove succeeded
//else return 0
int hash_remove(struct hash_node* hash_base,int x);

//increase the value of key x in hash_base by 1
//return 1 if increase succeeded
//else return 0
int hash_increase(struct hash_node* hash_base, int x);

//return the value of key x in hash_base
//return 1 if key x is in the hash
//else reutrn 0
int hash_get(struct hash_node* hash_base ,int x);

//print keys and values in array hash_base
void hash_output(struct hash_node* hash_base);