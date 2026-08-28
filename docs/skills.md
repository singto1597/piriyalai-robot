# Piriyalai Robot Knowledge Base (skills.md)

ฐานความรู้สำหรับบันทึกบทเรียนจากการแก้บั๊ก / เจอพฤติกรรมแปลกๆ ของบอร์ด เซ็นเซอร์ หรือไลบรารี

**กฎ:** อ่านไฟล์นี้ก่อนแก้บั๊กหรือเขียนฟีเจอร์ใหม่ทุกครั้ง ถ้าเจอบทเรียนใหม่ ให้เพิ่มต่อท้ายไฟล์นี้ตาม format ด้านล่าง (ดูระเบียบใน `CLAUDE.md`)

```markdown
### 🛠️ [ชื่อโมดูล/บอร์ด] - [ชื่อย่อของสิ่งที่เรียนรู้]
- **Context/Problem:** อธิบายสั้นๆ ว่าเกิดปัญหาอะไร หรือมีข้อจำกัดอะไร
- **Root Cause:** สาเหตุที่แท้จริงคืออะไร
- **Correct Pattern/Solution:** สรุปวิธีแก้ หรือ C++/Arduino Pattern ที่ถูกต้อง
- **Date Added:** YYYY-MM-DD
```

---

<!-- บันทึกบทเรียนใหม่ไว้ข้างล่างนี้ -->

### 🛠️ Robot_High_Automation - สถาปัตยกรรม Clean Architecture (config.h + Driver_/Logics_)
- **Context/Problem:** โค้ดหุ่นยนต์ระดับสูงเดิมกระจัดกระจาย magic number เต็มไปหมด ปรับจูนต้องไล่แก้หลายไฟล์ และแยกแยะยากว่าระดับไหนคือฮาร์ดแวร์ ระดับไหนคือลอจิก
- **Root Cause:** ไม่มีจุดรวมค่าคงที่ และไฟล์เดียวรวมทั้งฮาร์ดแวร์และลอจิก (เช่น rgb_sensor.ino เดิม)
- **Correct Pattern/Solution:**
  1. `config.h` = จุดเดียวที่รวมค่าจูนทุกตัว (ความเร็ว/PID/ค่าอ้างอิงเซนเซอร์/ขา/เวลา/เซอร์โว) พร้อมคอมเมนต์บอกผลกระทบถ้าเปลี่ยน — ไปแข่งแก้ไฟล์นี้ไฟล์เดียว
  2. ไฟล์ `Driver_*` = ควบคุมฮาร์ดแวร์ล้วน (มอเตอร์/เซนเซอร์/เซอร์โว/สต็อปวอตช์/อินพุต)
  3. ไฟล์ `Logics_*` = ลอจิกตัดสินใจล้วน (แทร็กเส้น/จัดตำแหน่ง/นำทาง/เช็คสี/เมนู)
  4. ฟังก์ชันเล็กๆ ที่ใช้ซ้ำ (เลี้ยวตามโหมด `turnByMode()`, หมุนหาเส้น `pivotToFindLine()`, รอกด OK `waitOkTap()`) ดึงเป็น helper แยก — ทำให้ "อยากแก้จังหวะไหน หาเจอทันที"
  5. Arduino ต่อไฟล์ .ino เข้าด้วยกันเป็น 1 TU: ตัวแปรกลางประกาศใน main ไฟล์เดียว ฟังก์ชันข้ามไฟล์เรียกกันได้เลย (อย่าลืมว่า config.h ต้อง `#include` ใน main ก่อน)
- **Date Added:** 2026-08-22

### 🛠️ Robot_High_Automation - ขาลิมิตสวิตช์ซ้ำกับเซนเซอร์หลังซ้าย (analog 7)
- **Context/Problem:** `readBackLineSensors()` อ่าน `backL = analog(7)` และ `checkBridge()` อ่านลิมิตสวิตช์จาก `analog(7)` ด้วย — ขาเดียวกัน
- **Root Cause:** การเดินสายจริงของหุ่นยนต์ตัวนี้ใช้ขั้วเดียวร่วมกัน (ไม่ได้ตั้งใจให้เป็นแบบนี้ แต่อยู่ในโค้ดเดิม)
- **Correct Pattern/Solution:** ห้าม "แก้ให้ถูกต้อง" โดยแยกขา เพราะจะเปลี่ยนพฤติกรรมเซนเซอร์หลัง เก็บไว้ให้ตรงกับสายจริง และบันทึกไว้ใน config.h (`PIN_BACK_LEFT = 7`, `PIN_LIMIT_SWITCH = 7`) ถ้าจะเดินสายแยกจริงๆ ต้องแก้ทั้งสองค่านี้พร้อมกัน
- **Date Added:** 2026-08-22

### 🛠️ Robot_High_Automation - เซนเซอร์เส้นมองสีเป็นแค่ "ขาว/ดำ" ไม่ใช่สีจริง (RGB ต้องเป็นผู้ตัดสินสี)
- **Context/Problem:** หุ่นอยากเช็คสีช่อง (ปล่อยลูกบาศก์) แต่ line sensor (reflectance) เห็นเหลือง/แดง/ขาว = "ขาว" และเห็นดำ/น้ำเงิน/เขียว = "ดำ" → แยกไม่ออกว่าที่เห็นคือเส้นดำจริง หรือช่องน้ำเงิน/เขียว หรือพื้นขาว
- **Root Cause:** เซนเซอร์สะท้อนแสงวัดแค่ความสว่าง ไม่ได้อ่านคลื่นสีจริง ส่วน TCS34725 (RGB sensor) อ่านสีจริงแยก 6 สีได้หมด
- **Correct Pattern/Solution:**
  1. **อย่าให้ line sensor ตัดสินเรื่องสี** — ใช้จับตำแหน่ง/เส้นเท่านั้น ส่วนสีต้องมาจาก `detectFloorColor()` (RGB) เสมอ
  2. **อ่านสีกลางช่อง (snapshot) ครั้งเดียวตอนวิ่ง** — `stopwatchElapsed() > timeMs*CELL_COLOR_SNAPSHOT_PERCENT/100` ก่อนถึงปลายช่อง ถ้าได้ขาว/ดำ → ปลายช่องเลี้ยวเลยไม่ต้องหยุดเช็ค (เร็วขึ้น ~2 เท่า); ถ้าได้ช่องวาง → ค่อยหยุดปล่อย (อ่านซ้ำยืนยัน)
  3. `stopwatchElapsed()` นับเวลารวมแม้ช่วงอ่านสีหุ่นยังวิ่ง → ตำแหน่งหยุดยังเท่าเดิม ไม่มี overshoot
  4. ตรงนี้ต้องพึ่งตำแหน่งเซนเซอร์อยู่เหนือช่องจริง → ให้จูนได้ผ่าน `CELL_COLOR_SNAPSHOT_PERCENT` (50 = กลางช่อง)
- **Date Added:** 2026-08-22

### 🛠️ Robot_High_Automation - ดีเลย์ซ่อนที่ทำให้เช็คสีช้าทั้งที่เห็นแค่ "50ms"
- **Context/Problem:** คอมเมนต์/ค่าบอกว่าเช็คสีใช้ 50ms แต่หุ่นหยุดจริง ~1-1.5 วินาที
- **Root Cause:** ดีเลย์ซ่อนหลายชั้น: `readRgbColor()` = 60ms (COLOR_READ_DELAY_MS) + integration 154ms ใน `tcs.getRawData()` = ~214ms/ครั้ง; `stopMotors()` มี `STOP_SETTLE_MS=100` ข้างใน; `showColorValue()` อ่าน RGB ซ้ำทุกช่อง; `checkFloorAndKick()` เดิม `else` จับขาว/ดำให้อ่านซ้ำอีก ~314ms ทั้งที่ไม่ต้องใช้ผล
- **Correct Pattern/Solution:** หาต้นตอเวลาที่เสียจริง: (1) ไล่ delay ในไลบรารี (TCS34725 integration) ไม่ใช่แค่ delay ในโค้ดเรา (2) อ่านค่าแล้วนำกลับมาใช้ใหม่ อย่าเรียกฟังก์ชันอ่านซ้ำ (showColorValue → ใช้ `floorColor`) (3) ตรวจ branch ว่า "else" ครอบคลุมเกินจำเป็นหรือไม่ — จำกัดการอ่านซ้ำเฉพาะสีที่เสี่ยง (แดง/เหลือง)
- **Date Added:** 2026-08-22

### 🛠️ Robot_High_Automation - คอมเมนต์ทิศหมุนใน backwardAlign สวนกับ motor pattern
- **Context/Problem:** ใน `backwardAlign()` เดิม คอมเมนต์บอก "หมุนวนไปทางขวา" แต่ motor pattern จริงคือ L=+,R=- (ทางซ้ายตาม convention ที่ followLineAndAlign ใช้)
- **Root Cause:** คอมเมนต์เขียนค้างมาจาก copy-paste (มีแค่ในส่วนถอยหลัง)
- **Correct Pattern/Solution:** เวลา refactor อย่าตั้งชื่อฟังก์ชัน/คอมเมนต์ตาม "ทิศทางที่คาดเดา" เพราะ motor() ของบอร์ดอาจกลับเครื่องหมายกับที่คิด — ต้องคง motor command เดิมเป๊ะ แล้วเขียนคอมเมนต์ให้ตรงกับสิ่งที่โค้ดทำจริง ไม่ใช่สิ่งที่คอมเมนต์เดิมอ้าง
- **Date Added:** 2026-08-22

### 🛠️ Robot_High_Automation - วางบล็อค unified ด้วยเซนเซอร์หลัง (ถอยจนเส้นดำ)
- **Context/Problem:** เดิมการวางบล็อคแบ่งตามสี — น้ำเงิน/เขียวถอยสั้น (`KICK_BACKUP_MS`), แดง/เหลืองถอยไกล + U-turn (`RED_YELLOW_BACKUP_MS`/`UTURN_MS`) + caller ถอยเพิ่มอีกชั้น → ใช้เวลา ms คงที่จูนยาก เปลี่ยนตำแหน่งเซนเซอร์/สนามแล้วเพี้ยน พอเพิ่งต่อเซนเซอร์หลังเสร็จก็อยากใช้เซนเซอร์จริงตัดสินระยะ
- **Root Cause:** ใช้เวลา (ms) กำหนดระยะถอย ไม่ได้ใช้อินพุตเซนเซอร์หลัง → ระยะทางจริงเปลี่ยนตามสนาม/แบตเตอรี่/น้ำหนัก
- **Correct Pattern/Solution:** routine วางบล็อคเดียวทุกสี `placeBlockAndExit()` = (1) `kickForColor()` ปล่อยลูกบาศก์ก่อน (2) `reverseUntilBackLine()` ถอยจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ (`backL==0 && backR==0`) พร้อม `PLACE_REVERSE_TIMEOUT_MS` กันค้าง (3) `backwardAlign()` ปรับให้ตรง (4) `turnByMode()` เลี้ยวตามโหมด แล้วลูปหลักวนต่อ เก็บการอ่านสีแดง/เหลืองซ้ำเพื่อยืนยันสี (skill เดิม) แต่ motion ไม่แบ่งสีแล้ว — constant ทั้งหมดรวมใน config.h section `วางบล็อค`
- **Date Added:** 2026-08-26

### 🛠️ Robot_High_Automation - ถอยหลังด้วย PID เซนเซอร์หลัง + กันเบรกไม่ทันที่แยก
- **Context/Problem:** หุ่นเร็ว เบรกไม่ทัน วิ่งเลยเส้นดำที่แยก → RGB sensor อาจไปอ่านสีฝั่งตรงข้ามเส้น (เช็คสีผิดช่อง); และตอนถอยหลังหุ่นถอยเอียง/ไม่ตรงเพราะความเร็วล้อเท่ากันทุกข้าง ไม่มีตัวปรับ
- **Root Cause:** ใช้เวลา (ms) กำหนดระยะถอยอย่างเดียว ไม่มีเซนเซอร์ป้อนกลับ; การถอยตรงใช้ความเร็วล้อเท่ากันหมด ไม่มีกลไกปรับให้ตรงตอนถอย
- **Correct Pattern/Solution:**
  1. **กันเบรกไม่ทัน (เซนเซอร์หน้าเจอเส้น):** `backOffJunction()` = `reverseForWithBackPid(slowSpeed, JUNCTION_BACKOFF_MS)` — เรียกก่อน `checkFloorAndKick()` ทุกครั้งที่ `followLineAndAlign()` คืน `STATUS_JUNCTION` (เซนเซอร์หน้าเจอเส้นดำตอนเดินไปข้างหน้า) → ถอยนิดหน่อยให้ RGB อยู่เหนือช่องเดิม ก่อนค่อยอ่านสี (เวลาถอยอยู่ใน config.h)
  2. **PID เซนเซอร์หลัง:** `reverseWithBackPid()` (ถอยจนหลังทั้ง 2 ข้างเจอเส้น) / `reverseForWithBackPid()` (ถอยตามเวลา) — ฝั่งที่เห็นเส้นก่อน = หุ่นเอียง → หน่วงล้อฝั่งนั้น เร่งล้อตรงข้าม (`BACK_PID_ADJUST` อยู่ใน config.h) ให้ถอยตรง
  3. วางบล็อค: แดง/เหลืองปล่อยลึก → `kickForColor` ถอยออกก่อนปล่อย (`KICK_RED_YELLOW_BACKUP_MS`); หลัง `backwardAlign` เดินหน้าให้ห่างเส้น (`PLACE_LEAVE_LINE_FORWARD_MS`) ก่อนเลี้ยว; สีที่เคยวางไปแล้ว (count>0) ถือเป็นขาว → ข้าม ไม่วางซ้ำ
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - ลิมิตสวิตช์เปลี่ยนจาก analog read เป็น digital read
- **Context/Problem:** เดิม `checkBridge()` อ่านลิมิตสวิตช์จาก `analog(PIN_LIMIT_SWITCH)` เทียบ `refLimitSwitch` (4000) — แต่วงจรจริงเดินสายลิมิตสวิตช์บนขา GPIO แยก (PIN_LIMIT_SWITCH=22) แล้ว การอ่าน analog บนขาดิจิทัลไม่ถูกต้อง
- **Root Cause:** โค้ด analog ค้างมาจากช่วงที่ลิมิตสวิตช์ใช้ขาเดียวกับเซนเซอร์หลังซ้าย (analog 7); เปลี่ยนสายจริงแยกขาแล้ว (commit แก้พิน) แต่โค้ดยังอ่าน analog
- **Correct Pattern/Solution:** อ่านแบบดิจิทัล `limitSwitchPressed() = (digitalRead(PIN_LIMIT_SWITCH) == LIMIT_SWITCH_PRESSED_LEVEL)` + `pinMode(PIN_LIMIT_SWITCH, INPUT)` ใน setup; ถ้าสายต่อกลับขั้ว → แก้ `LIMIT_SWITCH_PRESSED_LEVEL` (1/0) ใน config.h; ลบ `refLimitSwitch`/`REF_LIMIT_SWITCH` (ค่า analog) ทิ้งทั้งหมด
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - ตะเกียบ/สะพานยุบรวมเป็นอันเดียว (ถ้ากดสวิช → เดินตามเวลาให้พ้น)
- **Context/Problem:** เดิม `checkBridge()` แยกสถานะ 3 แบบ (ตะเกียบ probe / ขาขึ้นสะพาน / ขาลงสะพาน) พร้อม state machine `bridgeStatus` (0/1/2) — โค้ดยาว ซับซ้อน จูนเยอะ (`BRIDGE_PROBE_MS`, `FORK_CLEAR_MS`, `BRIDGE_UP_MS`, `BRIDGE_DOWN_MS`, ...)
- **Root Cause:** ตะเกียบกับสะพานต่างก็ใช้ลิมิตสวิตช์ตัวเดียวกัน และพฤติกรรม "เดินข้ามไปให้พ้น" ก็เหมือนกัน — ไม่จำเป็นต้องแยก แต่แยกเพราะกลัวระยะไม่พอ
- **Correct Pattern/Solution:** `checkBridge()` เป็น `void`: ถ้าสวิชถูกกด → `followLineFor(speed, BRIDGE_CLEAR_MS)` เดียวจบแล้ว `stopMotors()`; ลบ `bridgeStatus` + ค่าคงที่เกินทั้งหมด เหลือ `BRIDGE_CLEAR_MS` ตัวเดียว (ค่าต้องครอบคลุมสะพานที่ยาวที่สุด = ขาขึ้น+ลง) — เวลาเลี้ยว/ถอยไม่ต้องพึ่งสถานะสะพานอีกต่อไป
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - หน้าจอ OLED รวมศูนย์ที่ Logics_Display.ino + ฟอนต์เป็น ASCII เท่านั้น
- **Context/Problem:** หน้าจอ OLED กระจัดกระจายในหลายไฟล์ (init, setup, kick, menu, calibrate, finish) และ `textSize` ตกค้าง (ตั้ง 2x ที่หน้า Starting แล้วไม่กลับเป็น 1x → หน้าจอระหว่างวิ่งเพี้ยน) — แก้หน้าจอทีละจุดสับสน
- **Root Cause:** ไม่มีจุดรวมวาดหน้าจอ; ฟอนต์ OLED เป็น ASCII (ใส่ไทย/ยูนิโค้ดไม่ได้)
- **Correct Pattern/Solution:** สร้าง `Logics_Display.ino` = จุดเดียวรวมฟังก์ชันวาดหน้าจอทั้งหมด (`drawWelcomeScreen`, `drawStartScreen`, `drawRunStatus`, `drawKickScreen`, `drawSpeedMenuScreen`, `drawFrontCalib`, `drawFinishScreen` + helper `oledReset()` ที่เซ็ต `textSize(1)` ทุกครั้งกัน textSize ตกค้าง, `modeName()`, `colorName()`, `countFor()`); ตัวลอจิกเรียกแค่ฟังก์ชันเดียว อย่าแตะ `oled.text()` ตรงๆ ข้างนอก; คงการแสดงผลเป็น ASCII เท่านั้น
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - ข้ามสะพาน/ตะเกียบ = เดินตรงตามเวลา ไม่ตามเส้น (เซนเซอร์เส้นมั่วช่วงนั้น)
- **Context/Problem:** เดิม `checkBridge()` ใช้ `followLineFor(speed, BRIDGE_CLEAR_MS)` เดินตามเส้นข้ามสะพาน/ตะเกียบ แต่บนสะพาน/ตะเกียบเซนเซอร์เส้นอ่านค่ามั่ว (พื้นเอียง/เปลี่ยนเงา/เซนเซอร์ลอย) → PID ตามเส้นเพี้ยน หุ่นวิ่งไม่ตรง
- **Root Cause:** ตอนข้ามสะพาน/ตะเกียบไม่ต้องการ "ตามเส้น" เลย — แค่ข้ามไปให้พ้นตามเวลา (เส้นที่ต้องตามจริงอยู่หลังพ้นสะพาน)
- **Correct Pattern/Solution:** `checkBridge()` = ถ้าสวิชถูกกด → `forwardFor(speed, BRIDGE_CLEAR_MS)` เดินตรงตามเวลาอย่างเดียว (ไม่แตะ PID/เซนเซอร์เส้น) แล้ว `stopMotors()`; `BRIDGE_CLEAR_MS` ตัวเดียวต้องครอบคลุมสะพานที่ยาวที่สุด (ขาขึ้น+ลง)
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - ช่องสีที่วางลูกบาศก์ไปแล้ว = เคสพิเศษ Dup (แยกจากขาว/ดำ, ถอยเยอะกว่าเดิม)
- **Context/Problem:** เดิมเจอช่องสีที่ count>0 (วางลูกบาศก์ไปแล้ว) → จับมาเป็น `floorColor = White` ปนกับแยกขาว/ดำ → ถอยสั้นแค่ `JUNCTION_BACKUP_MS` แล้วเลี้ยว บางทีถอยไม่พอ ติดลูกบาศก์/เลี้ยวไม่หลุด
- **Root Cause:** พื้นที่วางซ้ำกับแยกธรรมดาใช้ค่า floorColor เดียวกัน (White) → แยกพฤติกรรมไม่ออก
- **Correct Pattern/Solution:** เพิ่มค่า sentinel `#define Dup 6` (ต่อจาก Red=5) — ช่องวางซ้ำตั้ง `floorColor = Dup` ไม่ใช่ White; caller ทั้งโหมด 5/6 (สอง path: ครบเวลา + เจอแยก) และ 7/8 ตรวจ `else if (floorColor == Dup)` → ถอย `DUP_CELL_BACKUP_MS` (เยอะกว่า JUNCTION_BACKUP_MS) แล้วเลี้ยว; `colorName()` ต้องรองรับ Dup → "DUP!"; ⚠️ ในโหมด 7/8 อย่าตรวจแค่ `(floorColor != White && != Black)` ไม่งั้น Dup จะหลุดไปทาง handleDropZoneCell — ต้องแยก Dup เป็นเคสก่อน
- **Date Added:** 2026-08-27

### 🛠️ Robot_High_Automation - วางบล็อคเสร็จแล้วให้เลี้ยวสวนโหมด (ตรงข้ามกับโหมด) เสมอ
- **Context/Problem:** เดิม `placeBlockAndExit()` วางลูกบาศก์ → ถอย (เจอเส้นหรือไม่เจอเส้น) → ปรับตรง → `turnByMode()` (เลี้ยวตามโหมด) — จากสนามจริงพบว่าเลี้ยวตามโหมดหุ่นไปผิดทาง/ติดช่อง
- **Root Cause:** หลังถอยออกจากช่องวาง รถต้องกลับออกไปทิศตรงข้ามกับโหมดเสมอ (โหมดซ้าย 6/8 → เลี้ยวขวา) เพื่อวนไปช่องถัดไป ไม่ใช่ทิศเดียวกับโหมด
- **Correct Pattern/Solution:** `placeBlockAndExit()` ขั้นสุดท้ายใช้ `turnAgainstMode()` (โหมด 5/7 = เลี้ยวซ้าย, โหมด 6/8 = เลี้ยวขวา) — สอดคล้องกับเคสแยกธรรมดา/ช่องวางซ้ำ (Dup) ที่เลี้ยวสวนโหมดอยู่แล้ว; คอมเมนต์ท้ายไฟล์ลอจิกต้องไม่บอก "เลี้ยวตามโหมด" หลงเหลือ
- **Date Added:** 2026-08-28
