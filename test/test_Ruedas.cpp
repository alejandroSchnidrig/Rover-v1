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

void test_inicializar(void)
{
    Ruedas ruedas(3, 4, 5);

    When(Method(ArduinoFake(), pinMode).Using(_, _)).AlwaysReturn();

    ruedas.inicializar();

    Verify(Method(ArduinoFake(), pinMode).Using(3, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(4, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(5, OUTPUT)).Once();
}

void test_moverAdelante() {
    Ruedas ruedas(3, 4, 5);

    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite).Using(_, _)).AlwaysReturn();

    ruedas.moverAdelante(100);

    Verify(Method(ArduinoFake(), digitalWrite).Using(3, LOW)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, HIGH)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(5, 100)).Once();
}

void test_moverAtras() {
    Ruedas ruedas(3, 4, 5);

    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite).Using(_, _)).AlwaysReturn();

    ruedas.moverAtras(150);

    Verify(Method(ArduinoFake(), digitalWrite).Using(3, HIGH)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, LOW)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(5, 150)).Once();
}

void test_detener() {
    Ruedas ruedas(3, 4, 5);

    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();

    ruedas.detener();

    Verify(Method(ArduinoFake(), digitalWrite).Using(3, LOW)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, LOW)).Once();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_inicializar);
    RUN_TEST(test_moverAdelante);
    RUN_TEST(test_moverAtras);
    RUN_TEST(test_detener);

    UNITY_END();

    return 0;
}