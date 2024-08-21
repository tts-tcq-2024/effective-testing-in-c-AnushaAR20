#include <stdio.h>
#include <assert.h>

// Failure count and function pointer
static int alertFailureCount = 0;
static int (*networkAlertFunction)(float) = NULL;

// Default stub implementation
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f Celsius.\n", celcius);
    return 200; // Always succeed
}

// Set the function pointer
void setNetworkAlertFunction(int (*func)(float)) {
    networkAlertFunction = func;
}

// Convert Fahrenheit to Celsius and alert
void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertFunction(celcius);
    if (returnCode != 200) {
        // Increment failure count for non-200 responses
        alertFailureCount++;
    }
}

// Reset the alert failure count, for testing purposes
void resetAlertFailureCount() {
    alertFailureCount = 0;
}

// Test case functions
int simulateFailureBelowZero(float celcius) {
    return celcius < 0 ? 500 : 200; // Fail if temperature is below 0 Celsius
}

int alwaysSucceed(float celcius) {
    return 200; // Always succeed
}

int alwaysFail(float celcius) {
    return 500; // Always fail
}

// Test cases
void runTests() {
    // Test 1: Check failure counting
    resetAlertFailureCount();
    setNetworkAlertFunction(simulateFailureBelowZero);
    alertInCelcius(30.0); // 30F -> -1.1C -> Should fail
    alertInCelcius(50.0); // 50F -> 10.0C -> Should not fail
    assert(alertFailureCount == 1); // Expected 1 failure

    // Test 2: Check no failures
    resetAlertFailureCount();
    setNetworkAlertFunction(alwaysSucceed);
    alertInCelcius(100.0); // 100F -> 37.8C -> Should not fail
    alertInCelcius(0.0); // 0F -> -17.8C -> Should not fail
    assert(alertFailureCount == 0); // Expected 0 failures

    // Test 3: Check all failures
    resetAlertFailureCount();
    setNetworkAlertFunction(alwaysFail);
    alertInCelcius(400.5); // 400.5F -> 204.7C -> Should fail
    alertInCelcius(303.6); // 303.6F -> 151.0C -> Should fail
    alertInCelcius(504.6); // 504.6F -> 263.7C -> Should fail
    alertInCelcius(104.6); // 104.6F -> 40.3C -> Should fail
    assert(alertFailureCount == 4); // Expected 4 failures
}

int main() {
    // Run tests
    runTests();
    
    // Reset the function and failure count for normal operation
    setNetworkAlertFunction(networkAlertStub);
    resetAlertFailureCount();

    // Example normal operation
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    alertInCelcius(504.6);
    alertInCelcius(104.6);
    
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");

    return 0;
}
