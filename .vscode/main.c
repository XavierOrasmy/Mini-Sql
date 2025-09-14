// Required standard libraries
#include <stdbool.h>  // Provides the `bool` type (true/false)
#include <stdio.h>    // For input/output functions (e.g., printf, getline)
#include <stdlib.h>   // For memory management (malloc, free, exit)
#include <string.h>   // For string handling (strcmp, etc.)

// Structure to store user input information
typedef struct {
  char* buffer;          // Pointer to the actual input string
  size_t buffer_length;  // Size of the allocated buffer (managed by getline)
  ssize_t input_length;  // Actual length of the input (excluding newline)
} InputBuffer;

// Creates and initializes a new InputBuffer structure
InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer)); // Allocate memory
  input_buffer->buffer = NULL;       // No memory assigned yet for the string
  input_buffer->buffer_length = 0;   // getline will allocate space dynamically
  input_buffer->input_length = 0;    // No input yet
  return input_buffer;               // Return pointer to the new InputBuffer
}

// Prints the database prompt to the terminal
void print_prompt() {
  printf("db > "); 
}

// Reads a line of input from the user into the buffer
void read_input(InputBuffer* input_buffer) {
  // getline dynamically allocates/expands buffer as needed
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  // If no input was read, exit with an error
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Store actual input length (excluding newline character at the end)
  input_buffer->input_length = bytes_read - 1;

  // Replace the trailing newline with a null terminator for string safety
  input_buffer->buffer[bytes_read - 1] = '\0';
}

// Frees the memory allocated for the InputBuffer
void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);  // Free memory for the input string
  free(input_buffer);          // Free memory for the struct itself
}

// Entry point of the program
int main(int argc, char* argv[]) {
  // Create an input buffer to hold user input
  InputBuffer* input_buffer = new_input_buffer();

  // Infinite loop: keeps prompting until user exits
  while (true) {
    print_prompt();              // Show "db > " prompt
    read_input(input_buffer);    // Wait for and read user input

    // If user typed ".exit", clean up and exit program
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } 
    // Otherwise, command is not recognized
    else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
