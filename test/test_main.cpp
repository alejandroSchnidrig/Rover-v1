#include <ArduinoFake.h>
#include <unity.h>
using namespace fakeit;
#include "../src/Ruedas.h"
#include "../src/Ruedas.cpp"


void setUp(void)
{
    ArduinoFakeReset();
}
void tearDown(void) {}

void test_loop(void)
{
    // Create an instance of Ruedas with arbitrary pin numbers
    Ruedas ruedas(3, 4, 5);

    // Stub pinMode function
    When(Method(ArduinoFake(), pinMode).Using(_, _)).AlwaysReturn();

    // Call the method
    ruedas.inicializar();

    // Verify pinMode was called with each pin and set to OUTPUT
    Verify(Method(ArduinoFake(), pinMode).Using(3, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(4, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(5, OUTPUT)).Once();
}

void test_moverAdelante() {
    Ruedas ruedas(3, 4, 5);

    // Stub digitalWrite and analogWrite
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite).Using(_, _)).AlwaysReturn();

    // Call the method with a speed of 100
    ruedas.moverAdelante(100);

    // Verify the function calls
    Verify(Method(ArduinoFake(), digitalWrite).Using(3, LOW)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, HIGH)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(5, 100)).Once();
}

// Test case for the `moverAtras` method
void test_moverAtras() {
    Ruedas ruedas(3, 4, 5);

    // Stub functions
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite).Using(_, _)).AlwaysReturn();

    // Call the method with a speed of 150
    ruedas.moverAtras(150);

    // Verify the function calls
    Verify(Method(ArduinoFake(), digitalWrite).Using(3, HIGH)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, LOW)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(5, 150)).Once();
}

// Test case for the `detener` method
void test_detener() {
    Ruedas ruedas(3, 4, 5);

    // Stub digitalWrite
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();

    // Call the method
    ruedas.detener();

    // Verify the function calls
    Verify(Method(ArduinoFake(), digitalWrite).Using(3, LOW)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, LOW)).Once();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_loop);
    RUN_TEST(test_moverAdelante);
    RUN_TEST(test_moverAtras);
    RUN_TEST(test_detener);

    UNITY_END();

    return 0;
}