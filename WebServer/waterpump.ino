#define trigger 5
#define echo 4
#define Relay 6
int sensor = A0;
int val = 0;
float time = 0, distance = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sensor, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Relay, OUTPUT);

  delay(2000);
}

void loop() {
  // อ่านค่าเซนเซอร์น้ำ
  val = analogRead(sensor);
  Serial.println(val);
  
  // ตรวจจับสถานะน้ำ
  if (val > 100) {
    Serial.println("Detected Water");
  }
  if (val < 100) {
    Serial.println("No Water");
  }

  // วัดระยะห่างด้วยเซนเซอร์อัลตราโซนิก
  measure_distance();
  
  // ควบคุมรีเลย์ตามระยะห่าง
  if (distance < 5) {
    digitalWrite(Relay, LOW);  // ถ้าระยะห่างน้อยกว่า 5 ซม. ปิดรีเลย์
  } else {
    digitalWrite(Relay, HIGH); // ถ้าระยะห่างมากกว่า 5 ซม. เปิดรีเลย์
  }

  delay(500);
}

void measure_distance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  // วัดเวลาที่ใช้ใน pulseIn เพื่อคำนวณระยะห่าง
  time = pulseIn(echo, HIGH);
  distance = time * 200 / 20000; // คำนวณระยะห่างในหน่วยเซนติเมตร
}
