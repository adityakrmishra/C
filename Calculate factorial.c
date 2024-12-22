// Function to calculate factorial using recursion

int factorial(int x){
int f;
if(x==0||x==1)
return 1;	
else
f=x * factorial(x-1);
return f;
}