#include <ArduinoFake.h>
#include <unity.h>
#include <NewPing.h>
using namespace fakeit;
#include "../src/Ruedas.h"
#include "../src/Ruedas.cpp"

#include "../src/Cortadora.h"
#include "../src/Cortadora.cpp"  // Include implementation

#include "../src/Alarma.h"
#include "../src/Alarma.cpp"  // Include implementation file

#include "../src/Sensor.h"
#include "../src/Sensor.cpp"

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

void test_cortar(void) {
    // Arrange
    int pinA = 10;
    int pinB = 11;
    Cortadora cortadora(pinA, pinB);

    // Mocking digitalWrite
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();

    // Act: Call the cortar() method
    cortadora.cortar();

    // Assert: Verify if digitalWrite was called with correct pins and values
    Verify(Method(ArduinoFake(), digitalWrite).Using(pinA, HIGH)).Once();  // Expect pinA to be HIGH
    Verify(Method(ArduinoFake(), digitalWrite).Using(pinB, LOW)).Once();   // Expect pinB to be LOW
}

void test_configurar(void) {
    // Arrange
    int pinA = 7;
    Alarma alarma(pinA);

    // Mock pinMode function
    When(Method(ArduinoFake(), pinMode).Using(_, _)).AlwaysReturn();

    // Act
    alarma.configurar();

    // Assert
    Verify(Method(ArduinoFake(), pinMode).Using(pinA, OUTPUT)).Once();
}

void test_encenderAlarma(void) {
    // Arrange
    int pinA = 7;
    Alarma alarma(pinA);

    // Mock digitalWrite function
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();

    // Act
    alarma.encenderAlarma();

    // Assert
    Verify(Method(ArduinoFake(), digitalWrite).Using(pinA, HIGH)).Once();
}

void test_apagarAlarma(void) {
    // Arrange
    int pinA = 7;
    Alarma alarma(pinA);

    // Mock digitalWrite function
    When(Method(ArduinoFake(), digitalWrite).Using(_, _)).AlwaysReturn();

    // Act
    alarma.apagarAlarma();

    // Assert
    Verify(Method(ArduinoFake(), digitalWrite).Using(pinA, LOW)).Once();
}

//TEST SENSORES

void test_getDistancia(void) {
    // Arrange
    int triggerPin = 9;
    int echoPin = 10;
    int maxDistance = 200;
    unsigned int distanciaObstaculo = 15;
    Sensor sensor(triggerPin, echoPin, maxDistance, distanciaObstaculo);

    // Mock ping_median function
    When(Method(ArduinoFake(NewPing), ping_median).Using(TIEMPO_MEDIA)).Return(174);  // Mocked time value
    ArduinoFakeInstance(NewPing, sensor);

    // Act
    unsigned int distancia = sensor.getDistancia();

    // Assert
    TEST_ASSERT_EQUAL_UINT32(3, distancia);  // Expect 174 / 58 ≈ 3
}

void test_detectarObstaculo(void) {
    // Arrange
    int triggerPin = 9;
    int echoPin = 10;
    int maxDistance = 200;
    unsigned int distanciaObstaculo = 15;
    Sensor sensor(triggerPin, echoPin, maxDistance, distanciaObstaculo);

    // Mock getDistancia to return a value within obstacle detection range
    When(Method(ArduinoFake(NewPing), ping_median).Using(TIEMPO_MEDIA)).Return(348);  // Returns ~6cm
    ArduinoFakeInstance(NewPing, sensor);

    // Act
    bool obstaculo = sensor.detectarObstaculo();

    // Assert
    TEST_ASSERT_TRUE(obstaculo);  // Since 6 (348/58) is > DISTANCIA_MAXIMA and <= distanciaObstaculo
}

void test_actualizarEstado(void) {
    // Arrange
    int triggerPin = 9;
    int echoPin = 10;
    int maxDistance = 200;
    unsigned int distanciaObstaculo = 15;
    Sensor sensor(triggerPin, echoPin, maxDistance, distanciaObstaculo);

    // Mock getDistancia to simulate obstacle detection
    When(Method(ArduinoFake(NewPing), ping_median).Using(TIEMPO_MEDIA)).Return(348);  // Returns ~6cm
    ArduinoFakeInstance(NewPing, sensor);

    // Act & Assert
    bool estadoChanged = sensor.actualizarEstado();
    TEST_ASSERT_TRUE(estadoChanged);  // First call to actualizarEstado should return true (new obstacle detected)

    // Call actualizarEstado again; should not change if the distance is the same
    estadoChanged = sensor.actualizarEstado();
    TEST_ASSERT_FALSE(estadoChanged);  // State remains same, expect false
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_inicializar);
    RUN_TEST(test_moverAdelante);
    RUN_TEST(test_moverAtras);
    RUN_TEST(test_detener);

    RUN_TEST(test_cortar);

    RUN_TEST(test_configurar);
    RUN_TEST(test_encenderAlarma);
    RUN_TEST(test_apagarAlarma);

    RUN_TEST(test_getDistancia);
    RUN_TEST(test_detectarObstaculo);
    RUN_TEST(test_actualizarEstado);

    UNITY_END();

    return 0;
}