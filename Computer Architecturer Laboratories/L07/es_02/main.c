
extern unsigned int average(unsigned int *, unsigned int);

int main(void){

	volatile unsigned int vet[]={1,2,3,3,1};
	unsigned int n=5;
	unsigned int r;

	r = average(vet,n);
	
	if(r==2)
		n=5;
	else
		n=0;
		
	while(1);
}
