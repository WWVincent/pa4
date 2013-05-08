#include "kernel.h"
#define RING_SIZE 8
#define BUFFER_SIZE 1024 // bad choice, need to change later


// network device driver

// Initializes the network driver, allocating the space for the ring buffer.
void network_init(){
    /* Find out where I/O region is in memory. */
    for (int i = 0; i < 16; i++) {
        if (bootparams->devtable[i].type == DEV_TYPE_NETWORK){
            puts("Detected network device...");
            dev_net = physical_to_virtual(bootparams->devtable[i].start);
            
            // also allow network interrupts
            set_cpu_status(current_cpu_status() | (1 << (8+INTR_NETWORK)));
            puts("...network driver is ready.");
            
            struct dma_ring_slot* ring = (struct dma_ring_slot*) malloc(sizeof(struct dma_ring_slot) * RING_SIZE);
            dev_net->rx_base=virtual_to_physical(ring);
            dev_net->rx_capacity = RING_SIZE;
            
            //does it matter if it was i in notes?
            for (int j = 0; j < RING_SIZE; ++j) {
                void* space = malloc(BUFFER_SIZE);
                if (j==0){
                    dev_net->rx_head = 0;
                    dev_net->rx_tail = 0;
                    dev_net->rx_base = virtual_to_physical(ring);
                }
                ring[j].dma_base = virtual_to_physical(space);
                ring[j].dma_len = BUFFER_SIZE;
            }
            return;
        }
    }
    puts("Did not detect network device");
    shutdown();
}

// Starts receiving packets!
void network_start_receive(){
    dev_net->cmd = NET_SET_POWER;
    dev_net->data = 0x1;
    //set receive
    dev_net->cmd = NET_SET_RECEIVE;
    dev_net->data = 0x1;
}

// If opt != 0, enables interrupts when a new packet arrives.
// If opt == 0, disables interrupts.
void network_set_interrupts(int opt){
    if (opt){
        puts("...enable interrupts");
    }
    else {
        puts("...disable interrupts");
    }
    dev_net.cmd = NET_SET_INTERRUPTS;
    dev_net.data = opt;
    
}

// Continually polls for data on the ring buffer. Loops forever!
void network_poll(){
    //if not used, do not need to handle this part
}

// Called when a network interrupt occurs.
void network_trap(){
    //This function (or any function of your choice, really, depending on how you modify kernel.c) gets called in response to a network interrupt. Presumably, you handle a packet in here.
    
}