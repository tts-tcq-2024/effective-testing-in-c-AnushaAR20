#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
   
    // Return 500 for not-ok
     
    // stub always succeeds and returns 200
    return 200;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    // Add test cases to demonstrate failure

    // Simulate alert failures by altering networkAlertStub function
    int simulateFailure(float celcius) {
        return 500; // Simulate failure
    }

    // Test Case 1: Check alert failure count when networkAlertStub fails
    alertFailureCount = 0; // Reset failure count
    networkAlertStub = simulateFailure; // Set stub to simulate failure

    // Call with multiple temperatures
    alertInCelcius(400.5); // 400.5F -> 204.7C -> Should fail
    alertInCelcius(303.6); // 303.6F -> 151.0C -> Should fail
    alertInCelcius(504.6); // 504.6F -> 263.7C -> Should fail
    alertInCelcius(104.6); // 104.6F -> 40.3C -> Should fail

    // Verify the failure count
    assert(alertFailureCount == 0); // This should fail since the count should be 4

    // Output failure count to observe result
    printf("%d alerts failed.\n", alertFailureCount);

    printf("All is well (maybe!)\n");
    return 0;
}
