void moveMot(char motNum, int spd) {
  digitalWrite(motDir[motNum], spd > 0 ? LOW : HIGH);
  spd = abs(spd);
  spd = map(spd, 0, 255, 256, 0);
  analogWrite(motPwn[motNum], spd);
}

void moveAllMot(int pwm0, int pwm1, int pwm2, int pwm3) {
  if (pwm0 != 1000) {
    moveMot(0, pwm0);
  }
  if (pwm1 != 1000) {
    moveMot(1, pwm1);
  }
  if (pwm2 != 1000) {
    moveMot(2, -pwm2);
  }
  if (pwm3 != 1000) {
    moveMot(3, -pwm3);
  }
}

void stopAllMot() {
  moveMot(0, 0);
  moveMot(1, 0);
  moveMot(2, 0);
  moveMot(3, 0);
  enc0.write(0);
  enc1.write(0);
  enc2.write(0);
  enc3.write(0);
}

void motorsInit() {
  for (int i = 0; i < 4; i++) {
    pinMode(motPwn[i], OUTPUT);
    pinMode(motDir[i], OUTPUT);
    moveMot(i, 0);
  }
}
void moveSingleMot(byte motNum, long countToMove) {
  if (!motStopped) {
    bool moveDir;
    if (countToMove > 0) {
      moveDir = true;
    }
    else {
      moveDir = false;
    }
    countToMove = abs(countToMove);
    long encCount;
    switch (motNum) {
      case 0: encCount = enc0.read();
        break;
      case 1: encCount = enc1.read();
        break;
      case 2: encCount = enc2.read();
        break;
      case 3: encCount = enc3.read();
        break;
    }
    long countToGo = countToMove - abs(encCount);
    int spd;
    if (countToGo > 500) {
      spd = map(countToGo, 500, 140000, 40, 255);
    }
    else if (countToGo > 10) {
      spd = 35;
    }
    else {
      spd = 0;
      stopAllMot();
      motStopped = true;
    }

    if (!moveDir) {
      spd = spd * -1;
    }
    Serial.print(" EncCount : ");
    Serial.print(encCount);
    Serial.print(" countToGo : ");
    Serial.print(countToGo);
    Serial.print(" Spd : ");
    Serial.print(spd);
    if (motNum == 0 || motNum == 1)
      moveMot(motNum, spd);
    if (motNum == 3 || motNum == 2)
      moveMot(motNum, -spd);
  }
}
long leg12Sync(bool dir, int baseSpd, long countToMove, bool * motStat) {
  auto enc1Count = enc1.read();
  auto enc2Count = enc2.read();
  long error, correction, masterPwm;
  if (dir) {
    //Serial.print(" FORWARD ");
    error = enc2Count - enc1Count;
    correction = baseSpd + Kp * error;
    masterPwm = baseSpd;
    correction = constrain(correction, 0, 255);
  }
  else {
    //Serial.print(" BACKWARD ");
    error = enc2Count - enc1Count;
    correction = -baseSpd + Kp * error;
    masterPwm = -baseSpd;
    correction = constrain(correction, -255, 0);
  }
  if (abs(enc1Count) > countToMove) {
    correction = 0;
  }
  if (abs(enc2Count) > countToMove) {
    masterPwm = 0;
  }
  if (abs(enc2Count) > countToMove && abs(enc1Count) > countToMove) {
    *motStat = false;
  }
  moveAllMot(1000, correction, masterPwm, 1000);
  Serial.print(" Error : ");
  Serial.print(error);
  Serial.print(" Correction : ");
  Serial.print(correction);
  Serial.print(" MasterPWM : ");
  Serial.print(masterPwm);
  return(abs(countToMove) - abs(enc2Count));
}
long leg03Sync(bool dir, int baseSpd, long countToMove, bool * motStat) {
  auto enc0Count = enc0.read();
  auto enc3Count = enc3.read();
  long error, correction, masterPwm;
  if (dir) {
    //Serial.print(" FORWARD ");
    error = enc0Count - enc3Count;
    correction = baseSpd + Kp * error;
    masterPwm = baseSpd;
    correction = constrain(correction, 0, 255);
    masterPwm = constrain(masterPwm, 0, 255);
  }
  else {
    //Serial.print(" BACKWARD ");
    error = enc0Count - enc3Count;
    correction = -baseSpd + Kp * error;
    masterPwm = -baseSpd;
    correction = constrain(correction, -255, 0);
    masterPwm = constrain(masterPwm, -255, 0);
  }
  if (abs(enc0Count) > countToMove) {
    masterPwm = 0;
  }
  if (abs(enc3Count) > countToMove) {
    correction = 0;
  }
  if (abs(enc0Count) > countToMove && abs(enc3Count) > countToMove) {
    *motStat = false;
  }
  moveAllMot(masterPwm, 1000, 1000, correction);
  Serial.print(" Error : ");
  Serial.print(error);
  Serial.print(" Correction : ");
  Serial.print(correction);
  Serial.print(" MasterPWM : ");
  Serial.print(masterPwm);
  return (abs(countToMove) - abs(enc0Count));
}
void motTest() {
  Serial.println("-------All motors and encoders test-------");
  Serial.println("Moving Motors Forward");

  moveAllMot(80, 80, 80, 80);
  delay(200);

  Serial.print(enc0.read());
  Serial.print(" ");
  Serial.print(enc1.read());
  Serial.print(" ");
  Serial.print(enc2.read());
  Serial.print(" ");
  Serial.print(enc3.read());
  Serial.println();

  moveAllMot(-80, -80, -80, -80);
  delay(200);

  Serial.println("Moving Motors Backward");
  Serial.print(enc0.read());
  Serial.print(" ");
  Serial.print(enc1.read());
  Serial.print(" ");
  Serial.print(enc2.read());
  Serial.print(" ");
  Serial.print(enc3.read());
  Serial.println();

  stopAllMot();
}
void moveSingleMotBack(byte motNum, int delayms) {
  if (motNum == 0 || motNum == 1 )
    moveMot(motNum, -80);
  if (motNum == 3 || motNum == 2)
    moveMot(motNum, 80);
  delay(delayms);
  moveMot(motNum, 0);
}
void moveSingleMotForward(byte motNum, int delayms) {
  if (motNum == 0 || motNum == 1)
    moveMot(motNum, 80);
  if (motNum == 3 || motNum == 2)
    moveMot(motNum, -80);
  delay(delayms);
  moveMot(motNum, 0);
}
void singleMotTest(byte motNum) {
  Serial.println("-------Single motor and encoder test-------");
  Serial.println("Moving Motor Forward");
  moveSingleMotForward(motNum, 200);

  switch (motNum) {
    case 0: Serial.println(enc0.read());
      break;
    case 1: Serial.println(enc1.read());
      break;
    case 2: Serial.println(enc2.read());
      break;
    case 3: Serial.println(enc3.read());
      break;
  }
  moveSingleMotBack(motNum, 200);

  switch (motNum) {
    case 0: Serial.println(enc0.read());
      break;
    case 1: Serial.println(enc1.read());
      break;
    case 2: Serial.println(enc2.read());
      break;
    case 3: Serial.println(enc3.read());
      break;
  }

  moveMot(motNum, 0);
}
