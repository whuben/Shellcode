
/*
the shellcode for executing exit(0) written by Ben Chang from WHU
size = 7 bytes
the syscall number of exit:0x01
*/
#include<stdio.h>
char shellcode[]=
    "\x31\xdb"  //xor %ebx,%ebx
    "\x8b\xc3"  //mov %ebx,%eax
    "\x40"      //inc %eax
    "\xcd\x80"; //int $0x80
int main()
{
    void (*testshellcode)() = (void*)&shellcode;
    printf("the size of shellcode_exit:%d",sizeof(shellcode));
    testshellcode();
    return 0;
}