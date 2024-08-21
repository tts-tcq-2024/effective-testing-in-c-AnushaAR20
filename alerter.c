#include <stdio.h>
#include <assert.h>

// Global variables for alert failure count and network alert function pointer
static int alertFailureCount = 0;
static int (*networkAlertFunction)(float) = NULL; // Function pointer for network alerts

// Default implementation of networkAlertFunction
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f Celsius.\n", celcius);
    return 200; // Always succeeds
}

// Set the function pointer to allow for testing different implementations
void setNetworkAlertFunction(int (*func)(float)) {
    networkAlertFunction = func;
}

// Convert Fahrenheit to Celsius and send an alert
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

// Accessor for the alert failure count, for testing purposes
int getAlertFailureCount() {
    return alertFailureCount;
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
    assert(getAlertFailureCount() == 1); // Expected 1 failure

    // Test 2: Check no failures
    resetAlertFailureCount();
    setNetworkAlertFunction(alwaysSucceed);
    alertInCelcius(100.0); // 100F -> 37.8C -> Should not fail
    alertInCelcius(0.0); // 0F -> -17.8C -> Should not fail
    assert(getAlertFailureCount() == 0); // Expected 0 failures

    // Test 3: Check all failures
    resetAlertFailureCount();
    setNetworkAlertFunction(alwaysFail);
    alertInCelcius(400.5); // 400.5F -> 204.7C -> Should fail
    alertInCelcius(303.6); // 303.6F -> 151.0C -> Should fail
    alertInCelcius(504.6); // 504.6F -> 263.7C -> Should fail
    alertInCelcius(104.6); // 104.6F -> 40.3C -> Should fail
    assert(getAlertFailureCount() == 4); // Expected 4 failures
}

int main() {
    // Set the default function for normal operation
    setNetworkAlertFunction(networkAlertStub);

    // Run tests
    runTests();

    // Example normal operation
    resetAlertFailureCount(); // Ensure no residual failure counts from tests
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    alertInCelcius(504.6);
    alertInCelcius(104.6);
    
    printf("%d alerts failed.\n", getAlertFailureCount());
    printf("All is well (maybe!)\n");

    return 0;
}
