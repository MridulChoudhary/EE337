#include <at89c5131.h>
#include "serial.h"   // UART communication functions

// Define the available lab resources
#define NUM_RESOURCES 4

unsigned char resource_names[NUM_RESOURCES][4] = {"DSO", "AFG", "DMM", "DPS"};
unsigned char max_resources[NUM_RESOURCES] = {5, 5, 8, 6};
unsigned char available_resources[NUM_RESOURCES] = {5, 5, 8, 6}; // Track current availability

// Function declarations
void display_resources();
void issue_resource();
void return_resource();

void main(void) {
    char ch;

    uart_init(); // Initialize UART

    // Initial display of resources
    display_resources();

    while(1) {
        transmit_string("Press 'I' for Issue and 'R' for Return\r\n");
        ch = receive_char(); // Get user input

        switch(ch) {
            case 'I': case 'i':
                issue_resource();
                break;
            case 'R': case 'r':
                return_resource();
                break;
            default:
                transmit_string("Invalid Input! Try again.\r\n");
                break;
        }
    }
}

// Function to display available resources
void display_resources() {
    unsigned char i;
    transmit_string("Resources available:\r\n");
    for(i = 0; i < NUM_RESOURCES; i++) {
        transmit_string(resource_names[i]);
        transmit_string("-");
        transmit_char(available_resources[i] + '0'); // Convert to char
        transmit_string(" ");
    }
    transmit_string("\r\n");
}

// Function to issue a resource
void issue_resource() {
    char resource_index, quantity;
    
    transmit_string("Enter Resource Index (1-4):\r\n");
    resource_index = receive_char() - '1'; // Convert char to int index

    if (resource_index < 0 || resource_index >= NUM_RESOURCES) {
        transmit_string("Invalid resource index!\r\n");
        return;
    }

    transmit_string("Enter Quantity:\r\n");
    quantity = receive_char() - '0'; // Convert char to int

    if (available_resources[resource_index] >= quantity) {
        available_resources[resource_index] -= quantity;
        transmit_string("Requested resource allocated!\r\n");
    } else {
        transmit_string("Requested resource not available...\r\n");
    }

    display_resources(); // Update resource availability
}

// Function to return a resource
void return_resource() {
    char resource_index, quantity;

    transmit_string("Enter Resource Index (1-4):\r\n");
    resource_index = receive_char() - '1'; // Convert char to int index

    if (resource_index < 0 || resource_index >= NUM_RESOURCES) {
        transmit_string("Invalid resource index!\r\n");
        return;
    }

    transmit_string("Enter Quantity:\r\n");
    quantity = receive_char() - '0'; // Convert char to int

    if (available_resources[resource_index] + quantity <= max_resources[resource_index]) {
        available_resources[resource_index] += quantity;
        transmit_string("Returned resource received!\r\n");
    } else {
        transmit_string("Returned resource out of bounds...\r\n");
    }

    display_resources(); // Update resource availability
}