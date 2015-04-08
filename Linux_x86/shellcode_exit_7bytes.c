
/*
the shellcode for executing exit(0) written by Ben Chang from WHU
size = 7 bytes
the syscall number of exit:0x01
Tips:You can test the shellcode on your system(Linux) as follows:
$gcc -fno-stack-protector -z execstack shellcode_exit_7bytes.c -o shellcode_exit
$./shellcode_exit
*/
#include<stdio.h>
#include<string.h>
char shellcode[]=
    "\x31\xdb"  //xor %ebx,%ebx
    "\x8b\xc3"  //mov %ebx,%eax
    "\x40"      //inc %eax
    "\xcd\x80"; //int $0x80
int main()
{
    void (*testshellcode)() = (void*)&shellcode;
    printf("the size of shellcode:%dbytes\n",strlen(shellcode));
    testshellcode();
}