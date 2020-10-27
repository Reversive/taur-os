extern unsigned int get_Time(char t);

int get_Time_format(int t){
    return (t/16)*10+(t%16);
}

void SyscallGetTime (char t,int * result){
  *result = get_Time_format(get_Time(t));
  return;
}

void SyscallGetDay (int * result){
  *result = get_Time(6);
  return;
}
