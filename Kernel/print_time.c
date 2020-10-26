extern void SyscallGetTime(char t,int * result);

/* En kernel por motivos de debug.*/
void numToString(long num, char * buffer){
    int i=0;
    int j=0;
    while(num > 0){
        buffer[i++] = num%10 + '0';
        num = num / 10 ;
    }
    char aux;   //j apunta al comienzo del buffer, i al final
    buffer[i--]=0;
     while(j<i){
        aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
}

/* En kernel y probado de forma directa por motivos de debug.*/
void printTime(){
	int hours,minutes,seconds;
	SyscallGetTime(4,&hours);
	SyscallGetTime(2,&minutes);
	SyscallGetTime(0,&seconds);

  char buffer [3];
	ncPrint("Time: ");
  numToString(hours,buffer);
	ncPrint(buffer);
	ncPrint(" hs ");
  numToString(minutes,buffer);
	ncPrint(buffer);
	ncPrint(" m ");
  numToString(seconds,buffer);
	ncPrint(buffer);
	ncPrint(" s");

	ncNewline();
  return;
}
