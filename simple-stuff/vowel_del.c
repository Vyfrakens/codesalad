#include<stdio.h>

main() {
	char a[80],i,l,j;
	printf("\n Enter the string: ");
	scanf("%s",a);

	for(l=0;a[l]!='\0';l++); //finding the string length by not using strlen
	printf("\n Length = %d",l);
	
	for(i=0;i<l;i++) {
		if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u'||a[i]=='A'||a[i]=='E'||a[i]=='I'||a[i]=='O'||a[i]=='U') {
			l--;
			for(j=i;j<l;j++) {
				a[j]=a[j+1];
			}
		i--;
		}
	}
  
	printf("\n Length after = %d",l);	
	a[l]='\0';
	printf("\n After removing vowels the string: %s \n",a);
}