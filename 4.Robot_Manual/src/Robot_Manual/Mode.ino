void SelectSpeed()
{
  switch(Mode)
  {
    case Mode0:  //กด SW_OK(เหลือง) น้อยกว่า 3 วินาที ความเร็วตามที่กำหนดในโปรแกรมตอนแรก
            break;

    case Mode1: ChangeSpeed(70,70);   //กด SW_A(ส้ม) มากกว่า 0.2 วินาที เพิ่มความเร็ว เป็น 70
            break;

    case Mode2: ChangeSpeed(90,90);   //กด SW_A(ส้ม) น้อยกว่า 0.2 วินาที เพิ่มความเร็วเป็น 90
            break;

    case Mode3: ChangeSpeed(80,80);   //กด SW_B(ขาว) มากกว่า 0.2 วินาที เพิ่มความเร็ว 80
           break;

   case Mode4: ChangeSpeed(95,95);   //กด SW_B(ขาว) น้อยกว่า 0.2 วินาที เพิ่มความเร็ว
          break;
   }
}
