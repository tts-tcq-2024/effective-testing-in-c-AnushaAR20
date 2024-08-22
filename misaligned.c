#include <stdio.h>
#include <assert.h>

// Function to print the color map
int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);  // Bug: Using 'i' for minorColor
        }
    }
    return i * j;
}

int main() {
    // Run the function and visually inspect or capture output (here, a simplified check)
    printColorMap();

    // Failing test case
    const char* expectedMajorColor = "White";
    const char* expectedMinorColor = "Orange";
    int index = 1;  // The second entry in the table (index 1) should be "White | Orange"
    const char* actualMinorColor = "Blue";  // This is what the bug in the code will produce

    // Assert to fail when minor color does not match expected output
    assert(expectedMajorColor == "White" && actualMinorColor == "Orange" && "The color map output is incorrect.");

    printf("All is well (maybe!)\n");
    return 0;
}
