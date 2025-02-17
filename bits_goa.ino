#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Wire.h>
#include "MAX30105.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIFI_SSID "Tarun"
#define WIFI_PASSWORD "Botarun@123"

#define FIREBASE_HOST "joystick-dc535-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "EnMSmfIoMO1D8mawx8y5mtarvpT1bHd6seAbL1QO"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

#define VRX_PIN 34
#define VRY_PIN 35
#define SW_PIN  32

#define TRIG_PIN 18
#define ECHO_PIN 19

MAX30105 particleSensor;

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Firebase.setReadTimeout(firebaseData, 1000);
    Firebase.setwriteSizeLimit(firebaseData, "tiny");

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);

    if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
        Serial.println("MAX30102 not found. Check connections!");
        while (1);
    }
    particleSensor.setup();
}

void loop() {
    int x = analogRead(VRX_PIN);
    int y = analogRead(VRY_PIN);
    int sw = digitalRead(SW_PIN);
    float distance = getUltrasonicDistance();
    int heartRate = getHeartRate();

    if (Firebase.setInt(firebaseData, "/joystick/x", x)) {
        Serial.println("X updated");
    } else {
        Serial.println("Firebase X Error: " + firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, "/joystick/y", y)) {
        Serial.println("Y updated");
    } else {
        Serial.println("Firebase Y Error: " + firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, "/joystick/sw", sw)) {
        Serial.println("SW updated");
    } else {
        Serial.println("Firebase SW Error: " + firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, "/ultrasonic/distance", distance)) {
        Serial.println("Distance updated");
    } else {
        Serial.println("Firebase Distance Error: " + firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, "/heartRate", heartRate)) {
        Serial.println("Heart Rate updated");
    } else {
        Serial.println("Firebase Heart Rate Error: " + firebaseData.errorReason());
    }

    delay(500);
}

float getUltrasonicDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

int getHeartRate() {
    return particleSensor.getIR(); 
}
