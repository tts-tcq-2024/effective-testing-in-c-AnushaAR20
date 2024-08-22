#include <stdio.h>
#include <assert.h>
#include <string.h>

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

// Failing test case to validate the output
void testPrintColorMap() {
    // Redirect stdout to a buffer for capturing output
    char buffer[1024] = {0};
    FILE* output = freopen("output.txt", "w+", stdout);

    // Call the function
    printColorMap();

    // Rewind and read the output
    fseek(output, 0, SEEK_SET);
    fread(buffer, sizeof(char), sizeof(buffer), output);

    // Restore stdout
    freopen("/dev/tty", "w", stdout);

    // Check if the output is as expected
    const char* expectedOutput =
        "0 | White | Blue\n"
        "1 | White | Orange\n"
        "2 | White | Green\n"
        "3 | White | Brown\n"
        "4 | White | Slate\n"
        "5 | Red | Blue\n"
        "6 | Red | Orange\n"
        "7 | Red | Green\n"
        "8 | Red | Brown\n"
        "9 | Red | Slate\n"
        "10 | Black | Blue\n"
        "11 | Black | Orange\n"
        "12 | Black | Green\n"
        "13 | Black | Brown\n"
        "14 | Black | Slate\n"
        "15 | Yellow | Blue\n"
        "16 | Yellow | Orange\n"
        "17 | Yellow | Green\n"
        "18 | Yellow | Brown\n"
        "19 | Yellow | Slate\n"
        "20 | Violet | Blue\n"
        "21 | Violet | Orange\n"
        "22 | Violet | Green\n"
        "23 | Violet | Brown\n"
        "24 | Violet | Slate\n";

    // Assert to check if the output matches the expected output
    assert(strcmp(buffer, expectedOutput) == 0 && "The color map output is incorrect.");
}

int main() {
    // Run the test that will fail
    testPrintColorMap();

    // Run the original function and check its return value
    int result = printColorMap();
    assert(result == 25);

    printf("All is well (maybe!)\n");
    return 0;
}
