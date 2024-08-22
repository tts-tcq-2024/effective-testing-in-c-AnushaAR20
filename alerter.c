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
        // Incorrectly does nothing with the failure count
        alertFailureCount += 0;
    }
}

int main() {
    // Test case that will fail
    alertFailureCount = 0; // Reset failure count

    alertInCelcius(400.5); // Should trigger a failure
    alertInCelcius(303.6); // Should trigger a failure
    alertInCelcius(504.6); // Should trigger a failure
    alertInCelcius(104.6); // Should not trigger a failure

    // Check the failure count
    assert(alertFailureCount != 0); // This should fail, as the failure count is not incremented
    
    // Output the result to observe
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");

    return 0;
}
