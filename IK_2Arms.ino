#include <Servo.h>

const float L1 = 100.0; // mm
const float L2 = 120.0; // mm

float SERVO1_ZERO = 90;  // servo1.write(90) → link1 is horizontal (+X)
float SERVO2_ZERO = 0;  // servo2.write(90) → link2 aligned with link1

Servo servo1, servo2;

void setup() {
  servo1.attach(6);
  servo2.attach(5);
  Serial.begin(9600);
  // maybe move to a start pose
}

// Calculate IK; returns false if unreachable
bool solveIK(float x, float y, float &servo1Out, float &servo2Out) {
  float r2 = x*x + y*y;
  float c2 = (r2 - L1*L1 - L2*L2) / (2.0 * L1 * L2);

  if (c2 < -1.0 || c2 > 1.0) {
    return false; // unreachable
  }

  c2 = constrain(c2, -1.0, 1.0);
  float s2 = sqrt(1.0 - c2*c2);

  // elbow-down:
  float theta2 = atan2(s2, c2);

  float k1 = L1 + L2 * c2;
  float k2 = L2 * s2;

  float theta1 = atan2(y, x) - atan2(k2, k1);

  float deg1 = theta1 * 180.0 / PI;
  float deg2 = theta2 * 180.0 / PI;

  // apply offsets; flip signs if needed to match real motion
  servo1Out = SERVO1_ZERO - deg1;
  servo2Out = SERVO2_ZERO + deg2;

  return true;
}

void drawLine(float x1, float y1, float x2, float y2, float step) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  float dist = sqrt(dx*dx + dy*dy);
  int steps = max(1, (int)(dist / step));

  for (int i = 0; i <= steps; i++) {
    float t = (float)i / (float)steps;
    float x = x1 + t * dx;
    float y = y1 + t * dy;
    moveTo(x, y);
  }
  delay(20);
}

void drawRectangle(float x0, float y0, float w, float h, float step) {
  float x1 = x0;
  float y1 = y0;
  float x2 = x0 + w;
  float y2 = y0 + h;

  // Edge A -> B
  drawLine(x1, y1, x2, y1, step);
  // Edge B -> C
  drawLine(x2, y1, x2, y2, step);
  // Edge C -> D
  drawLine(x2, y2, x1, y2, step);
  // Edge D -> A
  drawLine(x1, y2, x1, y1, step);

  drawLine(x1, y1, x2, y1, step);
  delay(1000);
}

float medX, medY;

void moveTo(float x, float y) {
  medX = 0;
  medY = 0;
  float s1, s2;
  if (solveIK(x, y, s1, s2)) {
    servo1.write(s1);
    servo2.write(s2);
    Serial.println("s1 = "); Serial.print(s1);
    Serial.println("s2 = "); Serial.print(s2);
    delay(15); // small step delay
  } else {
    // point outside workspace – maybe ignore
  }
}

void loop() {
  drawRectangle(50, 50, 100, 100, 2);
  delay(1000);
}
