//
// title: arduino signal gen for motor driver
//
// author: gurjal
//

// DIR_PIN -> outputs HIGH or LOW to set motor direction
// PUL_PIN -> outputs PWM where motor speed equals frequency
//
const uint8_t DIR_PIN[] = {2, 4};
const uint8_t PUL_PIN[] = {3, 5};

// cmd[0] -> direction
// cmd[1] -> pwm cycles
// cmd[2] -> pwm delay in microseconds
//
uint32_t cmd[4] = {0};
uint8_t buf;
int cmd_n = 0;
int byte_n = 0;

void setup()
{
  pinMode(DIR_PIN[0], OUTPUT);
  pinMode(PUL_PIN[0], OUTPUT);
  pinMode(DIR_PIN[1], OUTPUT);
  pinMode(PUL_PIN[1], OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // cmds array not full so read cmds from brain
  if (cmd_n < 4) {
    if (byte_n < 4) {
      if (Serial.available() > 0) {
        buf = Serial.read();
        cmd[cmd_n] = (cmd[cmd_n] << 8 | buf);
        byte_n++;
      }
    }
    else {
      byte_n = 0;
      cmd_n++;
    }
  }
  // cmds array full so write cmds to motor driver
  else {
    Serial.print("cmd[0] -> ");
    Serial.println(cmd[0]);
    Serial.print("cmd[1] -> ");
    Serial.println(cmd[1]);
    Serial.print("cmd[2] -> ");
    Serial.println(cmd[2]);
    Serial.print("cmd[3] -> ");
    Serial.println(cmd[3]);

    // set motor direction(cmd[0])
    digitalWrite(DIR_PIN[cmd[0]], cmd[1]);

    // write pwm signal for duration(dur) with pwm delay(cmd[2])
    for (int n = 0; n < cmd[2]; n++) {
      digitalWrite(PUL_PIN[cmd[0]], HIGH);
      delayMicroseconds(cmd[3]);
      digitalWrite(PUL_PIN[cmd[0]], LOW);
      delayMicroseconds(cmd[3]);
    }

    // zero cmd and empty serial port
    cmd_n = 0;
    byte_n = 0;
    memset(cmd, 0, sizeof(cmd));
    while (Serial.available())
      Serial.read();
  }
}
