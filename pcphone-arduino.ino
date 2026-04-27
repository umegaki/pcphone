// PC Phone コントローラ
// arduino nano r3
// M.Umegaki 2025-12-11 (birthday)

#define PUSH_TIME 250    // 番号ボタンを押す時間
#define RELEASE_TIME 250  // 番号ボタンを押した後の休止時間
#define WAIT_TIME 1000

#define POWER_LED 13
#define DR0 12
#define DR1 11
#define DR2 2
#define DR3 3
#define DR4 4
#define DR5 5
#define DR6 6
#define DR7 7

#define C1 4
#define C2 5
#define C3 6

#define R1 12
#define R2 11
#define R3 2
#define R4 3

/* definition DR[0..7] */
const unsigned int DR_PORT[8] = { DR0, DR1, DR2, DR3, DR4, DR5, DR6, DR7 };

#define HANDS_FREE 7

/* definition 2 relay ports to push button*/

const unsigned int BUTTON_0_CR[2] = { C2, R4 };     /* 0 C2 R2 */
const unsigned int BUTTON_1_CR[2] = { C1, R1 };     /* 1 C1 R1 */
const unsigned int BUTTON_2_CR[2] = { C2, R1 };     /* 2 C2 R1 */
const unsigned int BUTTON_3_CR[2] = { C3, R1 };     /* 3 C3 R1 */
const unsigned int BUTTON_4_CR[2] = { C1, R2 };     /* 4 C1 R2 */
const unsigned int BUTTON_5_CR[2] = { C2, R2 };     /* 5 C2 R2 */
const unsigned int BUTTON_6_CR[2] = { C3, R2 };     /* 6 C3 R2 */
const unsigned int BUTTON_7_CR[2] = { C1, R3 };     /* 7 C1 R3 */
const unsigned int BUTTON_8_CR[2] = { C2, R3 };     /* 8 C2 R3 */
const unsigned int BUTTON_9_CR[2] = { C3, R3 };     /* 9 C3 R3 */
const unsigned int BUTTON_ASTERISK_CR[2] = { C1, R4 }; /* "*" C1 R4 */
const unsigned int BUTTON_SHARP_CR[2] = { C3, R4 };    /* "#" C1 R4 */

// 初期化
void setup() {
  PORTB = 0x00;
  PORTD = 0x00;
  DDRD = B11111100;  // D0-D7
  DDRB = B11100000;  // D8-D13
  // pinMode(POWER_LED, OUTPUT);
  digitalWrite(POWER_LED, HIGH);
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  Serial.println("ready\n");
}

// メインループ
void loop() {
  if (Serial.available() > 0) sread();
}

// シリアル受信
void sread() {
    char data = Serial.read();
    Serial.print(data);
    switch (data) {
      case '0':
        push_button(BUTTON_0_CR);
        break;
      case '1':
        push_button(BUTTON_1_CR);
        break;
      case '2':
        push_button(BUTTON_2_CR);
        break;
      case '3':
        push_button(BUTTON_3_CR);
        break;
      case '4':
        push_button(BUTTON_4_CR);
        break;
      case '5':
        push_button(BUTTON_5_CR);
        break;
      case '6':
        push_button(BUTTON_6_CR);
        break;
      case '7':
        push_button(BUTTON_7_CR);
        break;
      case '8':
        push_button(BUTTON_8_CR);
        break;
      case '9':
        push_button(BUTTON_9_CR);
        break;
      case '#':
        push_button(BUTTON_SHARP_CR);
        break;
      case '*':
        push_button(BUTTON_ASTERISK_CR);
        break;
      case 'F':  // hand free on
      case 'f':  // hand free on
        hands_free(1);
        break;
      case 'G':  // hand free o
      case 'g':  // hand free o
        hands_free(0);
        break;
      case 'H':  // hand free o
      case 'h':  // hand free o
        hands_free(2);
        break;
      case 'T':
      case 't':
        port_test(1);
        break;
      case 'W':
      case 'w':
        wait1(1);
        break;
      case 'L':
      case 'l':
        wait1(10);
        break;

    }
}

void wait1(int c){
  if (c==1) {
    digitalWrite(POWER_LED, LOW);
    delay(WAIT_TIME);
    digitalWrite(POWER_LED, HIGH);
  } else {
    for (int i=0;i<c;i++) {
      digitalWrite(POWER_LED, LOW);
      delay(WAIT_TIME/2);
      digitalWrite(POWER_LED, HIGH);
      delay(WAIT_TIME/2);
    }
  }
}
// test circult
void port_test(int count) {
  Serial.println(" port test start");
  for (int c = 0; c < count; c++) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(DR_PORT[i], HIGH);
      digitalWrite(POWER_LED, LOW);
      delay(1000);
      digitalWrite(DR_PORT[i], LOW);
      digitalWrite(POWER_LED, HIGH);
      delay(1000);
    }
  }
   Serial.println("port test end");
}

// hands free
void hands_free(int on) {
  if (on == 2) {
    digitalWrite(HANDS_FREE, HIGH);
    delay(PUSH_TIME);
    digitalWrite(HANDS_FREE, LOW);
    delay(RELEASE_TIME);
  } else if (on == 1) {
    digitalWrite(HANDS_FREE, HIGH);
    delay(PUSH_TIME);
  } else {
    digitalWrite(HANDS_FREE, LOW);
    delay(RELEASE_TIME);
  }
}

// push the button
void push_button(unsigned int *port_cr) {
  digitalWrite(port_cr[0], HIGH);
  digitalWrite(port_cr[1], HIGH);
  delay(PUSH_TIME);
  digitalWrite(port_cr[0], LOW);
  digitalWrite(port_cr[1], LOW);
  delay(RELEASE_TIME);
}