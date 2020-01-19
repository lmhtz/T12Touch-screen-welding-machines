//增量式PID
void t12_pid()
{
  if (set_temp >= 40 && t12_switch == 1)
  {
    //k0 = set_temp - t12_ad;
    ek0 = set_temp - t12_temp;
    if (ek0 < 0) pid_out = 0; //误差0度以下
    else if (ek0 > 10) //误差大于10度
    {
      t12_temp_read_time = 800;  //加长采样时间
      pid_out = 255;
    }
    else if (ek0 <= 10 && ek0 >= 0) //误差10度内或0度
    {
      t12_temp_read_time = 200; //缩短采样时间
      pid_out = float((p * ek0) - (i * ek1) + (d * ek2));
      //pid_out = float((p * (ek0 - ek1)) + (i * ek0) + (d * (ek0 - 2 * ek1 + ek2)));
      if (pid_out > 255) pid_out = 255;
      else if (pid_out < 0)pid_out = 0;
      ek2 = ek1;
      ek1 = ek0;
    }
    analogWrite(t12_pwm_pin, pid_out);
  }
  else {
    pid_out = 0;
    analogWrite(t12_pwm_pin, pid_out);
  }
  ec_read(); //读取电流
}
