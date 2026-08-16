# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

Arduino competition code for the Piriyalai School robotics club (พิริยาลัย). It is a set of independent line-following / maze robot sketches, split into **four tiers by robot difficulty**. Comments and UI strings are written in Thai — keep new code and messages in Thai to match.

## Build & run

There is **no build system committed** to the repo (no `platformio.ini`, no Makefile). Each robot folder is a single Arduino sketch:

- Open the robot's folder (e.g. `4.Robot_Manual/src/Robot_Manual`) in the **Arduino IDE** (File → Open → pick any `.ino` inside) and upload from there.
- Or use PlatformIO: `pio init -b <board>` in the sketch folder, then `pio run` / `pio run -t upload`. `.pio/` and `.vscode/` are gitignored.

**Compilation requires external board libraries that are not in this repo**: `<POP32.h>`, `<ATX2.h>`, `<popx2.h>` (and for Racing, `popx2.h`) come from the vendor kit's Arduino library pack, plus `Adafruit_TCS34725` (vendored under `3.Robot_High_Automation/lib/`). Without them the code won't compile; they are typically installed via the Arduino Library Manager / vendor instructions.

There are no automated tests. "Testing" means flashing a robot and iterating on the timing/PID constants.

## Repository layout

```
1.Robot_Racing/           Simple 2-motor race bots — PID line following only
  src/field_a, src/field_b   each: popx2 + QTR-8 sensor, robotdefine.h pin map
2.Robot_Medium/           Maze bots on two board variants, task "Box" missions
  src/ATX2, src/POP32         two parallel sketches sharing the same file names
3.Robot_High_Automation/  Camera + RGB sensing bot (HuskyLens, TCS34725), mode dispatch
4.Robot_Manual/           Remote-control bot (WCX wireless controller + POP32)
```

## Arduino multi-file sketch pattern

A robot folder is **one sketch split across many `.ino` files**. The Arduino build concatenates all `.ino` files in the folder alphabetically, so any function can call any other regardless of file. The file whose name matches the folder (e.g. `Robot_Manual.ino`) is compiled first and holds `setup()` / `loop()`.

Consequences when editing:
- Global variables are often declared in the main `.ino` (speeds, sensor refs, PID gains) and used across all files.
- `setup()` is the "main program": it runs the robot through its mission with a sequence of blocking calls, then `loop()` usually just calls `Finish()` / `Remote()`.
- **Tuning is done by editing constants and commenting/uncommenting calls** in `setup()`. Files are littered with commented-out experiment lines — a checked-in `Box1(); Box2();` list is the current program, not dead code.

## Board APIs (from the vendor libraries)

Shared vocabulary used identically across tiers. Line-following/motion functions (provided by `POP32.h` / `ATX2.h` / `popx2.h`):

- Line following: `TracJC()`, `TracJCStop()`, `TracPID()`, `CalError()` + `ConvertADC()`, `TracBalance()`
- Timed drive: `ForwardSpeedTime(speed, ms)`, `BackwardSpeedTime(...)`, `ForwardBalance(speed, ms)`, `TracSpeedTime(...)`
- Turns: `TurnLeft()`, `TurnRight()`, `UTurnLeft()`, `UTurnRight()`, `Left(speed,ms)` / `Right(...)`, `TurnLeftDegree(...)` (MPU6050 compass)
- Raw motor: `motor(id, speed)` (per-wheel), `motorControl(l, r)` / `MaxForward()` (racing bots)
- Sensors: `L3..R3` front line-sensor globals, `C` center, `BL/BR` back sensors — read after `ConvertADC()`
- Output: `oled.text(row,col,...)`, `oled.show()`, `beep()`, `MotorStop()` / `STOP`
- I/O: `knob()` (potentiometer), `SW_A()`, `SW_B()`, `Read_sw_OK()`, `StartTimer()` / `ReadTimer()`
- Servo/grip (Manual + High tiers): `ServoGripUp()`, `ServoGripDown()`, `ServoGrip()`, `ServoPut()`
- WCX controller (`4.Robot_Manual/lib/WCX.h`): `mywcx.getButton()`, booleans `LU/LD/LL/LR`, `L1/L2/LT`, `RU/RD/RL/RR`, `R1/R2/RT`

## Mode/state conventions

- **Medium tier**: each `BOX#.ino` is one mission (place a cube at grid position N) — a `Box1()...Box5()` call chain in `setup()`.
- **High tier**: `RobotMode` (0–8) selects behavior; the startup loop maps `SW_A`/`SW_B` press-vs-hold to pick a mode, then `loop()` switches on it. RGB vs camera sensing is chosen by `RobotMode < 5`.
- **Manual tier**: `Remote()` is a full controller loop; `R2`-hold switches to `Auto()`.

## Conventions to preserve

- Keep Thai comments; they explain intent (e.g. เลี้ยวซ้าย = turn left, เจอแยก = found junction).
- Speed parameters are 0–100 (percent); raw `motorControl` / `analogWrite` values are 0–255.
- When adding a `.ino` file to a sketch, keep the same name as its sibling in the parallel board variant (e.g. both `ATX2` and `POP32` have `Balance.ino`, `BOX1.ino`) so the two stay in sync.

---

# ระเบียบการทำงาน (นำมาจากโปรเจค classroom-management)

## 🔔 วิธีการแจ้งเตือน — Autonomous Agent Notifications (n8n Webhook) [บังคับ]

เมื่อทำงานในฐานะ agent อัตโนมัติ ต้องแจ้งเตือนผู้ใช้ผ่าน webhook n8n ด้วย `curl` ทุกครั้งที่ถึง milestone, ทำงานเสร็จชิ้นงาน, หรือต้องการ input จากผู้ใช้ — **แจ้งเป็นระยะ ๆ อย่ารอให้จบงานใหญ่ทีเดียว** (เริ่มงาน → `info`, กำลังทำ → `info`, เสร็จชิ้นงาน → `success`, เจอปัญหา → `error`, ต้องการให้มนุษย์ตัดสินใจ → `question`)

**Webhook URL:** `https://n8n.singto1597.xyz/webhook/7158145d-5df8-4dc6-93aa-a5693ea0d675`

**Payload Types** — ฟิลด์ `type` ต้องเป็นค่าใดค่าหนึ่งจาก 4 ค่านี้เท่านั้น:

| type | เมื่อไหร่ |
|---|---|
| `"success"` | ฟีเจอร์ / บั๊ก / เทส เสร็จสมบูรณ์และยืนยันแล้ว |
| `"question"` | ติดขัด ต้องการให้ผู้ใช้ตัดสินใจ (เช่น ใช้ A หรือ B?) หรือต้องการ action ด้วยมือจากผู้ใช้ |
| `"info"` | อัปเดตความคืบหน้าของงานที่ยาว |
| `"error"` | เจอ error ที่แก้เองไม่ได้หลังลองหลายครั้ง |

ฟิลด์ `message` ต้องเป็น **ภาษาไทย** กระชับ ชัดเจน

```bash
curl -X POST "https://n8n.singto1597.xyz/webhook/7158145d-5df8-4dc6-93aa-a5693ea0d675" \
  -H "Content-Type: application/json" \
  -d '{"type": "success", "message": "เขียนโปรแกรมเลี้ยวซ้ายเสร็จแล้ว ทดสอบผ่านครับ พร้อมรับคำสั่งต่อไป"}'
```

## 🔀 Git Workflow [บังคับ]

1. **ซิงก์กับ remote ก่อนทำงานเสมอ:** ก่อนเริ่มงานใหม่ทุกครั้ง (หรือก่อนแก้บั๊ก) ต้องรัน `git fetch origin --prune` + `git pull origin main` ก่อนเสมอ เพื่อให้มี commit ล่าสุด และรู้ว่า branch/PR ไหนถูก merge, ลบ, หรือปิดไปแล้ว (remote branch ที่ merge แล้วจะหายจาก `git branch -a`) — ถ้าเจอว่า branch ที่กำลังทำงานถูกปิด/ลบไปแล้ว ให้สลับมาทำบน `main` ที่อัปเดตแล้ว หรือสร้าง branch ใหม่
2. **ห้ามทำงานบน `main` ตรง ๆ:** ก่อนเริ่มงานใหม่ทุกครั้ง ต้องสร้าง branch ใหม่ — `git checkout -b feat/<ชื่อ>` สำหรับฟีเจอร์, `git checkout -b fix/<ชื่อ>` สำหรับแก้บั๊ก
3. **Commit + push ทันทีเมื่อทำงานเสร็จ:** เมื่อทำงานส่วนใดเสร็จ ให้ `git add` + `git commit` (ข้อความอธิบายชัดเจนว่าทำอะไร ลงท้ายด้วย `Co-Authored-By: Claude <noreply@anthropic.com>`) แล้ว `git push` ขึ้น `origin` ทันที — อย่าปล่อยให้งานค้างไม่ถูกบันทึก
4. **เสนอ Pull Request เมื่อเสร็จ:** เมื่องานใน branch เสร็จสมบูรณ์และเทสผ่านแล้ว ให้เสนอ PR กลับเข้าสู่ `main` เสมอ พร้อม body อธิบายว่า **อะไร / ทำไม / ผลเทส** — `gh pr create --base main --head <branch> --title 'feat: ...' --body '...'` (ถ้าเครื่องไม่มี `gh` ให้ใช้ GitHub REST API ผ่าน token จาก `git credential fill`) ลงท้าย PR body ด้วย `🤖 Generated with [Claude Code](https://claude.com/claude-code)`

## ✍️ ระเบียบการเขียน & การสื่อสาร

- ตอบ/เขียนคอมเมนต์เป็น **ภาษาไทย** แบบกระชับ ตรงไปตรงมา (Bro-Tone)
- **Show, Don't Tell:** เขียนโค้ดมาให้ก๊อปวางได้เลย พร้อมคอมเมนต์จุดสำคัญ
- ถ้างานกระทบหลายโฟลเดอร์/หลายส่วนของโปรเจค (เช่น แก้ Racing แล้วกระทบ Medium) ให้คิดล่วงหน้าและให้โค้ดครบจบในคำตอบเดียว
- ใช้ชื่อตัวแปร/ฟังก์ชัน/คอมเมนต์ให้สอดคล้องกับโค้ดรอบข้าง (ในโปรเจคนี้คือ ภาษาไทย + ชื่อ CamelCase จากไลบรารีบอร์ด เช่น `ForwardSpeedTime`, `TracJC`, `InitialRef`)

## 🧠 Knowledge Retention (`docs/skills.md`) [บังคับ]

- **Check First:** ก่อนเริ่มคิดวิธีแก้บั๊ก หรือเขียนฟีเจอร์ใหม่ ต้องอ่าน `docs/skills.md` ก่อนเสมอว่ามี Pattern หรือข้อจำกัดที่เคยบันทึกไว้แล้วหรือไม่
- **Document the Skill:** เมื่อแก้บั๊กสำคัญสำเร็จ, วางสถาปัตยกรรมใหม่, หรือเจอพฤติกรรมแปลกๆ ของบอร์ด/เซ็นเซอร์/ไลบรารี ต้องบันทึกลง `docs/skills.md` ทันที
- **Format มาตรฐาน:**

  ```markdown
  ### 🛠️ [ชื่อโมดูล/บอร์ด] - [ชื่อย่อของสิ่งที่เรียนรู้]
  - **Context/Problem:** อธิบายสั้นๆ ว่าเกิดปัญหาอะไร หรือมีข้อจำกัดอะไร (เช่น QTR อ่านค่าเส้นพลิกขาว-ดำ)
  - **Root Cause:** สาเหตุที่แท้จริงคืออะไร
  - **Correct Pattern/Solution:** สรุปวิธีแก้ หรือ C++/Arduino Pattern ที่ถูกต้อง
  - **Date Added:** YYYY-MM-DD
  ```
