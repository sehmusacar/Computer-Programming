#include<stdio.h>
#include<stdlib.h>

// Prototypes of functions
void recursive_helper(int i, int limit, FILE * outf);
void recursive(FILE * inf, int dash, FILE * outf);

int main() {
    int dash = 0, i;
    char c;

    // Open input file in reading mode
    FILE * inf = fopen("input.txt", "r");

    // Open output file in writing mode
    FILE * outf = fopen("output.txt", "w");

    recursive(inf, dash, outf);

    // Close both files
    fclose(inf);
    fclose(outf);

    return 0;

}
void recursive(FILE * inf, int dash, FILE * outf) {
    char c;
    // Base condition 
    if (feof(inf)) {
        // Do nothing at the end
    } else {
        // Get a character from input file
        c = fgetc(inf);
        if (c != EOF) {
            if (c == ' ') {
                // Skip if character is a space
                recursive(inf, dash, outf);
            }
            // Update branching if character is a bracket
            else if (c == '(')
                dash++;
            else if (c == ')')
                dash--;
            // Comma is a seperator between elements so, if character is comma, adds new line to output file
            else if (c == ',')
                fprintf(outf, "\n");
            else {
                // Recursive helper function that prints dashes regarding to branching
                recursive_helper(0, dash, outf);
                // Write character to output file
                fprintf(outf, "%c", c);
            }
        }
        recursive(inf, dash, outf);
    }
}

void recursive_helper(int i, int limit, FILE * outf) {
    // Base condition
    if (i >= limit) {
        // Limit is reached
    } else {
        // Print dash to represent branching
        fprintf(outf, "-");
        // Continue
        recursive_helper(i + 1, limit, outf);
    }
}