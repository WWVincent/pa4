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
            // also allow keyboard interrupts
            set_cpu_status(current_cpu_status() | (1 << (8+INTR_NETWORK)));
            puts("...network driver is ready.");
            
            struct dma_ring_slot* ring = (struct dma_ring_slot*) malloc(sizeof(struct dma_ring_slot) * RING_SIZE);
            dev_net.rx_base=&ring; //not sure if this is the physical address
            for (int i = 0; i < RING_SIZE; ++i) {
                void* space = malloc(BUFFER_SIZE);
                ring[i].dma_base = &space;
                ring[i].dma_len = BUFFER_SIZE;
            }
            return;
        }
    }
}

// Starts receiving packets!
void network_start_receive(){
    //not sure if we need to instantiate dev_net??
    dev_net.cmd = NET_SET_POWER;
    dev_net.data = 1;
    //set receive
    dev_net.cmd = NET_SET_RECEIVE;
    dev_net.data = 1;
}

// If opt != 0, enables interrupts when a new packet arrives.
// If opt == 0, disables interrupts.
void network_set_interrupts(int opt){
    if (opt !=0){
        dev_net.cmd = NET_SET_INTERRUPTS;
        dev_net.data = 1;
    }
    else {
        dev_net.cmd = NET_SET_INTERRUPTS;
        dev_net.data = 0;
    }
}

// Continually polls for data on the ring buffer. Loops forever!
void network_poll(){
    
    
}

// Called when a network interrupt occurs.
void network_trap(){
    //This function (or any function of your choice, really, depending on how you modify kernel.c) gets called in response to a network interrupt. Presumably, you handle a packet in here.
    
}