Consider this example

int i = 32;
int *a = &i;    ==> a =87994 (address = 87994)
a++;            ==> now a = 87998

char a = 'A';
char *b = &a;   ==> b = 87994
b++;            ==> now b = 87995

float i = 1.7;
float*a = &i;   ==> Address of i or a = 87994
a++;            ==> Now a = 87998