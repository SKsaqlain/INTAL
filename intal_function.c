#include <stdio.h>
#include "intal.h"
#include<stdlib.h>
#include<string.h>

//structure to hold the length of the input number and the number itself.
struct holder
{
	int length;
	int number[0];
	
};
typedef struct holder holder;

void *remove_leading_zeros(holder *intal);
void* power(void* intal,void * intal2,void * intal_by_2);
void* power_intal_divide(void* intal1, void* intal2);

//function to convert the intput number in string format to holder format so that specific operations can be performed in proper manner.
void* intal_create(const char* str)
{	
	if(str==NULL)
	{
		return NULL;
	}
	if(str[0]<'0' || str[0]>'9')
	{
			holder *h=(holder *)malloc(sizeof(holder)+1*sizeof(int));
			h->length=1;
			h->number[0]=0;
			return h;
	}
	int n=strlen(str);
	int i;
	
	
	holder *h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
	h1->length=0;
	//holder *h=(holder*)malloc(1*sizeof(holder));
	int k=1;
	for(i=0;i<n;i++)
	{	k++;
		if(str[i]>='0' && str[i]<='9')
		{	
			h1->number[i]=str[i]-'0';
			h1->length=h1->length+1;
			h1=(holder *)realloc(h1,sizeof(holder)+(k)*sizeof(int));
		}
		else
			break;
	}
	long long unsigned int j=0;
	while(h1->number[j]==0 && j<h1->length)j++;//checking for leading zeros
	holder *temp;
	if(j==h1->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		temp=(holder *)malloc(sizeof(holder)+(h1->length-j)*sizeof(int));
		temp->length=h1->length-j;
		i=0;
		while(j<h1->length)
		{
			temp->number[i++]=h1->number[j++];
		}
	}
	free(h1);
	return (void *)temp;
	
	//return h1;
}

//function to conver the number to string format for display purpose.
char* intal2str(void* intal)
{	
	holder *h=(holder *)intal;
	if(intal==NULL||h->length==-1)
	{
		char *str=(char *)malloc(4*sizeof(char));
		//str="NaN";
		strcpy(str,"NaN");
		return str;
		
	}
	char *ch=(char *)malloc((h->length+1)*sizeof(char));
	int i=0;
	int j=0;
	if(i<h->length)
	{
		for(;i<h->length;i++)
		{
			ch[j++]=h->number[i]+'0';
	
		}
	}
	else
		ch[j++]=0+'0';
	ch[j]='\0';
	
	return ch;
}

//function to increment the number by 1
void* intal_increment(void* intal)
{	//printf("here\n");
	holder *h=(holder *)intal;
	if(intal==NULL)
	{
		return NULL;
	}
	if(h->length==-1)
	{
		return intal;
	}
	holder *intal_inc=(holder *)malloc(sizeof(holder)+(h->length+1)*sizeof(int));
	int c=1;
	int counter=h->length-1;
	
	while(counter>=0)
	{
		int sum=h->number[counter]+c;
		intal_inc->number[counter+1]=sum%10;
		c=sum/10;
		counter--;		
	}
	intal_inc->number[0]=c;
	intal_inc->length=h->length+1;
	long long unsigned int j=0;
	while(intal_inc->number[j]==0 && j<intal_inc->length)j++;//checking for leading zeros
	holder *temp;
	if(j==intal_inc->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		temp=(holder *)malloc(sizeof(holder)+(intal_inc->length-j)*sizeof(int));
		temp->length=intal_inc->length-j;
		int i=0;
		while(j<intal_inc->length)
		{
			temp->number[i++]=intal_inc->number[j++];
		}
	}
	free(intal_inc);
	return (void *)temp;
}

//function to decrement the number by 1
void* intal_decrement(void* intal)
{	
	holder *h=(holder *)intal;
	if(intal==NULL)
		return NULL;
	if(h->length==-1)
	{
		return intal;
	}
	holder *intal_dec=(holder *)malloc(sizeof(holder)+(h->length)*sizeof(int));
	int c=1;
	int counter=h->length-1;
	int flag=0;
	while(counter>=0)
	{
		if(h->number[counter]==0 && flag==0)
		{	
			intal_dec->number[counter]=10-c;
			c=1;
		}
		else
		{
			intal_dec->number[counter]=h->number[counter]-c;
			flag=1;
			c=0;
		}
		counter--;		
	}
	if(c==1)
	{	free(intal_dec);
		return intal;
	}
	intal_dec->length=h->length;
	//free(h);
	holder *temp;
	long long unsigned int j=0;
	while(intal_dec->number[j]==0 && j<intal_dec->length)j++; //removing leading zeroes
	if(j==intal_dec->length)
	{
		temp=(holder *)malloc(sizeof(holder)+(1)*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(holder *)malloc(sizeof(int)+(intal_dec->length-j)*sizeof(int));
		temp->length=intal_dec->length-j;
		
		while(j<intal_dec->length)
			{
				temp->number[i++]=intal_dec->number[j++];
			}
	}
	
	free(intal_dec);
	return (void *)temp;
}

//function to compare two numbers
int intal_compare(void* intal1, void* intal2)
{	
	holder *h1=(holder *)intal1;
	holder *h2=(holder *)intal2;
	if(intal1==NULL || intal2==NULL)
	{
		return -2;
	}
	if(h1->length==-1 || h2->length==-1)
	{
		return 0;//changed here
	}
	int first=h1->length-1;
	int second=h2->length-1;
	int i,j;
	i=j=0;
	/*while(h1->number[i]==0)i++;
	while(h2->number[j]==0)j++;*/
	if((first)>(second))
		return 1;
	else if((second)>(first))
		return -1;
	else
	{
	int flag1,flag2;
	flag1=flag2=0;
	while(i<=first && j<=second)
	{
		if(h1->number[i]>h2->number[j])
		{		
			flag1=1;
			flag2=0;
			break;
			
			
		}
		else if(h1->number[i]<h2->number[j])
		{
			flag2=1;
			flag1=0;
			break;
		}
		else
		{
			flag1=flag2=0;
		}
		i++;
		j++;
	}
		if(flag1==1)
			return 1;
		else if(flag2==1)
			return -1;
		else 
			return 0;
	}	
}

//Adds two intals and returns their sum.
void* intal_add(void* intal1, void* intal2)
{	
	holder *h1=(holder *)intal1;
	holder *h2=(holder *)intal2;
	if(intal1==NULL || intal2==NULL)
	{
		return NULL;
	}
	if(h1->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	if(h2->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	int size;
	size=(h1->length>=h2->length)?h1->length:h2->length;
	holder *new_intal=(holder *)malloc(sizeof(holder )+(size+1)*sizeof(int));
	new_intal->length=size+1;
	//int i;
	//i=0;
	/*while(h1->number[i]==0)i++;
	while(h2->number[j]==0)j++;*/
	int first=h1->length-1;
	int second=h2->length-1;
	int sum=0;
	int c=0;
	while(first>=0 && second>=0)
	{
		sum=h1->number[first]+h2->number[second]+c;
		new_intal->number[size]=sum%10;
		c=sum/10;
		first--;
		second--;
		size--;
		
	}
	while(first>=0)
	{
		sum=h1->number[first]+c;
		new_intal->number[size]=sum%10;
		c=sum/10;
		first--;
		size--;
	}
	while(second>=0)
	{
		sum=h2->number[second]+c;
		new_intal->number[size]=sum%10;
		c=sum/10;
		second--;
		size--;
	}
	while(size>=0)
	{
		new_intal->number[size--]=0+c;
		c=0;
	}
	//printf("here\n");
	long long unsigned int j=0;
	holder *temp;
	while( new_intal->number[j]==0 && j<new_intal->length)j++;
	//printf("here1\n");
	if(j==new_intal->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(holder *)malloc(sizeof(holder)+(new_intal->length-j)*sizeof(int));
		temp->length=new_intal->length-j;
		while(j<new_intal->length)
		{
			temp->number[i++]=new_intal->number[j++];
		}
	}
	free(new_intal);
	
	return (void *)temp;
}



//Returns the difference (obviously, nonnegative) of two intals.
void* intal_diff(void* intal1, void* intal2)
{	holder *h1,*h2,*new_intal;
	h1=(holder *)intal1;
	h2=(holder *)intal2;
	if(intal1==NULL || intal2==NULL)
	{
		return NULL;
	}
	if(h1->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	if(h2->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}

	int cmp=intal_compare(intal1,intal2);
	if(cmp>0)
	{	
		h1=(holder *)intal1;
		h2=(holder *)intal2;
		
	}
	else if(cmp<0)
	{
		h1=(holder *)intal2;
		h2=(holder *)intal1;
	
	}
	else
	{
		new_intal=(holder *)malloc(sizeof(holder )+1*sizeof(int));
		new_intal->length=1;
		new_intal->number[0]=0;
		return (void *)new_intal;
	}
	int size;
	size=h1->length;
	new_intal=(holder *)malloc(sizeof(holder )+(size+1)*sizeof(int));
	new_intal->length=size+1;
	//int i=0;
	/*while(h1->number[i]==0)i++;
	while(h2->number[j]==0)j++;*/
	int first=h1->length-1;
	int second=h2->length-1;
	int diff=0;
	int c=0;
	while(first>=0 && second>=0)
	{
		diff=h1->number[first]-h2->number[second]-c;
		if(diff <0)
		{	
			diff=10+diff;
			c=1;
		}
		else
			c=0;
		new_intal->number[size]=diff;
		first--;
		second--;
		size--;
		
	}
	while(first>=0)
	{
		diff=h1->number[first]-c;
		if(diff <0)
		{
			diff=diff+10;
			c=1;
		}
		else
			c=0;
		new_intal->number[size]=diff;
		
		first--;
		size--;
	}
	while(second>=0)
	{
		diff=h2->number[second]-c;
		if(diff<0)
		{
			diff=diff+10;
			c=1;
		}
		else
			c=0;
		new_intal->number[size]=diff;
		
		second--;
		size--;
	}
	while(size>=0)
	{
		new_intal->number[size--]=0;
	}
	long long unsigned int j=0;
	holder *temp;
	while( new_intal->number[j]==0 && j<new_intal->length)j++;
	//printf("here1\n");
	if(j==new_intal->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(holder *)malloc(sizeof(holder)+(new_intal->length-j)*sizeof(int));
		temp->length=new_intal->length-j;
		while(j<new_intal->length)
		{
			temp->number[i++]=new_intal->number[j++];
		}
	}
	free(new_intal);
	return (void *)temp;
	
}

void* intal_multiply(void* intal1, void* intal2)
{	holder *h1,*h2,*new_intal;
	h1=(holder *)intal1;
	h2=(holder *)intal2;
	if(intal1==NULL || intal2==NULL)
	{
		return NULL;
	}
	if(h1->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;;
	}
	if(h2->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;;
	}
	
	int size=h1->length+h2->length;
	new_intal=(holder *)malloc(sizeof(holder )+size*sizeof(int));
	new_intal->length=size;
	int i;
	for(i=0;i<size;i++)
		new_intal->number[i]=0;
	int r=size-1;
	for (i =h2->length-1; i>=0; i--) 
	{
        	int c=0;
        	int k=0;
        	int j;
        	for (j=h1->length-1;j>=0;j--) 
        	{	
		    int temp =h2->number[i] * h1->number[j];
		    temp=temp+c+new_intal->number[r-k];
		    c = temp /10;
		    new_intal->number[r-k] = temp%10;
		    

		    k++;
        	}
        	if (c>0) 
        		new_intal->number[r-k] =c ;
        
        	r--;
    	}
    	long long unsigned int j=0;
	holder *temp;
	while( new_intal->number[j]==0 && j<new_intal->length)j++;
	//printf("here1\n");
	if(j==new_intal->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(holder *)malloc(sizeof(holder)+(new_intal->length-j)*sizeof(int));
		temp->length=new_intal->length-j;
		while(j<new_intal->length)
		{
			temp->number[i++]=new_intal->number[j++];
		}
	}
	free(new_intal);
    
    return (void *)temp;
}

//function to remove leading zeros
void *remove_leading_zeros(holder *intal)
{
	long long unsigned int j=0;
	holder *temp;
	while( intal->number[j]==0 && j<intal->length)j++;
	//printf("here1\n");
	if(j==intal->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(holder *)malloc(sizeof(holder)+(intal->length-j)*sizeof(int));
		temp->length=intal->length-j;
		while(j<intal->length)
		{
			temp->number[i++]=intal->number[j++];
		}
	}
	return (void *)temp;
}

//Integer division
//Returns the integer part of the quotient of intal1/intal2.


void* intal_divide(void* intal1, void* intal2)
{	//printf("here\n");
	holder *h1,*h2;
	h1=(holder *)intal1;
	h2=(holder *)intal2;
	if(intal1==NULL || intal2==NULL)
	{
		return NULL;
	}
	if(h1->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	
	if(h2->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	if(h2->number[0]==0 && h2->length==1)
	{
		holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=-1;
		h3->number[0]=0;
		return (void *)h3;
	}
	if(h1->length==1 && h1->number[0]==0)
	{
		//return (void*)h1;
		holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=1;
		h3->number[0]=0;
		return (void *)h3;
	}
	if(h2->length==1 && h2->number[0]==1)
	{
		//return (void*)h1;
		holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=h1->length;
		int i;
		int n=h1->length;
		for(i=0;i<n;i++)
			h3->number[i]=h1->number[i];
		return (void *)h3;
	}
	if(intal_compare(intal1,intal2)==0)
	{
		holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=1;
		h3->number[0]=1;
		return (void *)h3;
	}
	else if(intal_compare(intal1,intal2)==-1)
	{
		holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=1;
		h3->number[0]=0;
		return (void *)h3;
	}
	else
	{
		holder *new_intal=(holder *)malloc(sizeof(holder)+(h1->length)*sizeof(int));
		holder *numerator=(holder *)malloc(sizeof(holder)+(h2->length)*sizeof(int));
		holder *denominator=(holder *)malloc(sizeof(holder)+(h2->length)*sizeof(int));
		numerator->length=denominator->length=h2->length;
		holder *result=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		result->length=1;
		result->number[0]=0;
		int m=h1->length;
		int n=h2->length;
		int i;
		for(i=0;i<n;i++)
		{
			numerator->number[i]=h1->number[i];
			denominator->number[i]=h2->number[i];
		}
		int t=n;
		int count=0;
	
		while(t<=m)
		{
			int flag=0;
			if(intal_compare(numerator,denominator)>=0)
			{
				while(intal_compare(numerator,denominator)>=0)
				{	//printf("here1\n");
					
					numerator=(holder *)intal_diff(numerator,denominator);
					
					//printf("here2\n");
					
					
					numerator=(holder *)remove_leading_zeros(numerator);
					//printf("%s\n",intal2str(numerator));
					result=(holder *)intal_increment(result);
					//printf("here3\n");
				}
				//printf("\n");
				new_intal->number[count++]=result->number[0];
				result->number[0]=0;
				result->length=1;
				flag=1;
			}
			else
			{
				if(t==m)
					break;
				numerator=(holder *)realloc(numerator,sizeof(holder)+(numerator->length+1)*sizeof(int));
				numerator->length++;
				//printf("carry->down %d\n",h1->number[t]);
				numerator->number[numerator->length-1]=h1->number[t];
				numerator=(holder *)remove_leading_zeros(numerator);
				
			    
			   t++;
				
			}
			if(!flag && intal_compare(numerator,denominator)==-1)
			{
				new_intal->number[count++]=0;
			}
			
		}
		new_intal->length=count;
		free(numerator);
		free(denominator);
		free(result);
	
		return (void *)new_intal;
	}	
}

void* power_intal_divide(void* intal1, void* intal2)
{	//printf("here\n");
	holder *h1,*h2,*new_intal;
	h1=(holder *)intal1;
	h2=(holder *)intal2;
	
	
	int size;
	//int size=h1->length-h2->length;
	
	size=h1->length;
	
	
	new_intal=(holder *)malloc(sizeof(holder)+size*sizeof(int));
	new_intal->length=size;
	long long unsigned int i=0;
	long long unsigned int j=0;
	long unsigned int sum=0;
	/*while(h1->number[i]==0)i++;
	while(h2->number[j]==0)j++;
	*/
	while(j<h2->length)
	{
		sum=sum*10+h2->number[j++];
		//printf("%lu\n",sum);
	}
	//printf("%d %lu\n",h2->length,sum);

	int rem=0;
	int k=0;
	
	while(i<h1->length)
	{
		rem=rem*10+h1->number[i++];
		new_intal->number[k++]=rem/sum;
		rem=rem%sum;
	}
	//printf("here\n");
	new_intal->length=k;
	j=0;
	holder *temp;
	while( new_intal->number[j]==0 && j<new_intal->length)j++;
	//printf("here1\n");
	if(j==new_intal->length)
	{
		temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		temp->length=1;
		temp->number[0]=0;
	}
	else
	{
		long long unsigned int i=0;
		temp=(holder *)malloc(sizeof(holder)+(new_intal->length-j)*sizeof(int));
		temp->length=new_intal->length-j;
		while(j<new_intal->length)
		{
			temp->number[i++]=new_intal->number[j++];
		}
	}
	free(new_intal);
	return (void *)temp;
	
}

void* intal_pow(void* intal1, void* intal2)
{
    holder *h1=(holder *)intal1;
    holder *h2=(holder *)intal2;
    if(intal1==NULL || intal2==NULL)
    {
    	return NULL;
    }
    if(h1->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
	
    if(h2->length==-1)
	{
		h1=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h1->length=-1;
		h1->number[0]=0;
		return h1;
	}
    holder *new_intal=(holder *)intal1;
    holder *intal;
//	printf("here1\n");
    if(h1->length==1)
    {
        if(h1->number[0]==0)
        {  
        	//return h1;
        	holder *h3=(holder *)malloc(sizeof(holder)+1*sizeof(int));
		h3->length=1;
		h3->number[0]=0;
		return (void *)h3;
        }
    }
    if(h2->length==1)
    {
        if(h2->number[0]==0)
        {
            holder *temp=(holder *)malloc(sizeof(holder)+1*sizeof(int));
            temp->length=1;
            temp->number[0]=1;
            return temp;
        }
        if(h2->number[0]==1)
        {
        	holder *temp=(holder *)malloc(sizeof(holder)+(h1->length)*sizeof(int));
            temp->length=h1->length;
            int i;
            for(i=0;i<h1->length;i++)
            	temp->number[i]=h1->number[i];
            return temp;
        }
    }
    
    //int j=0;
    //long long unsigned int number=0;
    /*while(j<h2->length)
    {

        number=number*10+h2->number[j];
        j++;
    }*/
    char *str_2="2";
    void *intal_by_2=intal_create(str_2);
    //long long unsigned int i;
    intal=power(intal1,intal2,intal_by_2);
    new_intal=(holder *)intal;
    
    return (void *)new_intal;

}
void* power(void* intal,void * intal2,void * intal_by_2)
{
    void *new_intal;
    holder *intal_2=( holder*)intal2;
    if(intal_2->length==1 && intal_2->number[0]==0)
    {
        holder *h=(holder*)malloc(sizeof(holder)+1*sizeof(int));
        h->length=1;
        h->number[0]=1;
        return (void *)h;
    }
    void *intal_q=power_intal_divide(intal2, intal_by_2);
    new_intal=power(intal,intal_q,intal_by_2);
    new_intal=intal_multiply(new_intal,new_intal);
    if(intal_2->number[intal_2->length-1]%2!=0)
    	new_intal=intal_multiply(new_intal,intal);
    
    return (void *)new_intal;


}


//Destroy the created "object".
//It mainly frees the memory allocated by intal_create().
void intal_destroy(void* intal)
{
	holder *h=(holder *)intal;
	if(intal!=NULL)
		free(h);
}
