/**
* @example VGAMonitor.cpp
*/

//! [namespace vga, class Monitor]

#include "lib/vga/VGAMonitor.hpp"


VGAMonitor monitor(); // no specific argument to constructor

monitor.init(0); // Initializes the instance with the index of the vga page it will manage. Especially if the instance is defined as global, otherwise it could lead to undefined behavior


//! [namespace vga, class Monitor, stream insertion operator]


monitor << "Hello World!"; //writes "Hello World!" on the vga page handled by the monitor

monitor << 'a'; // takes also a simple char

int nbr = 32;
uint32_t unbr = 12;

monitor << nbr; // takes also an integer

monitor << unbr; //and an unsigned integer

//! [namespace vga, class Monitor, function handle_user_input()]

char user_input = 'a'; // keyboard handler received 'a' as user input.

monitor.handle_user_input(user_input); // The only way to handle user input.

char user_input = 'n';

monitor << user_input; //Not the good way

