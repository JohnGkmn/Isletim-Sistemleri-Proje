
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	//~ int k=1;
	
	//~ while(k==1) {
	//~ printf("> ");
	//~ fflush(stdout);
	//~ char a[100];
	//~ scanf("%s",a);
	char b[100]="/bin/";
	char g[100];
	char c[100];
	char w[100];
	int j;
	int s=0;
	int i;
	int k=0;
	int z=0;
	int aw=0;
	int sayac=1;
	while(sayac==1) {
	printf("> ");
	fflush(stdout);
	 scanf("%[^\n]s",g);
	printf("%s","deneme");
		
	 for(i = 0; b[i] != '\0'; ++i);

    for(j = 0; g[j] != '\0'; ++j, ++i)
    {
		if (g[j]!=' '&&k==0) {
        b[i] = g[j];
        c[s]=g[j];
        s++;
        }
        else {
			k=1;
			
		}
		
		if(z>0){
			w[aw]=g[j];
			aw++;
		}
		if(k==1){
			z++;
			
		}
    }

    b[i] = '\0';
    c[s] = '\0';
    w[aw]='\0';
    execl(b, c,w, (char *) 0);
    system("./batuhan.c");
    //~ if (execl(b, c,w, (char *) 0) < 0) {
        //~ printf("%s","deneme");
      
    //~ }
}
    //~ printf("%s\n",c);
    //~ printf("%s\n",b);
    //~ printf("%s\n",w);
	
	
	
	
	//~ for(i = 0; b[i] != '\0'; ++i)
	//~ {
		//~ if(b[i]=='/') {
			//~ s++; 
			//~ continue;
		//~ }
		//~ if(s==2){
			//~ c[j]=b[i];
			//~ j++;
			
		//~ }
		
		
	//~ }
	
    
        
    //~ printf("Tamam\n");
//}
        printf("%s","deneme");
    return 0;
}
