#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

// Structure to implement the linked lists indicating connections between vertices and edges

struct node
{
       int a;
       int edges;
       node * next;
       void read(int val)
       {
            a = val;
       }
       void show()
       {
            cout<<a;
       }
            
};

// Structure to implement queue as a linked list

struct q
{
       int b;
       q * next;
       void getdata(int m)
       {
            b=m;
       }
       void putdata()
       {
            
            cout<<b<<" ";
       }

}*front = NULL, *rear, *t, *y;

//  Function to add a vertex to the queue

void add(int k)
{
     if(front==NULL)
	{
		front=new q;
		front->getdata(k);
		front->next = NULL;
		rear=front;
	}
	else
	{
		y=new q;
		y->getdata(k);
		y->next = NULL;
		rear->next=y;
		rear=y;
	}
}

// Function to delete an element from the queue and display it in the output

void del()
{
      if (front == NULL)
     {
         cout<<" Queue is empty! "<<endl;
     }
     
     else if (front->next == NULL)
     {
         front->putdata();
         front = NULL;
     }
     else
     {
         front->putdata();
         front = front->next;
         
     }
}       
     
// Beginning of main()
      
int main()
{
    
    node *x, *temp, *f;
    char ch, line[2000];
    char *pch;
    int intval, n = 0, j=0;
        
    //To count the number of lines in the file, to get the number of vertices
    
    FILE *fp;
    fp = fopen("in1.txt", "r");
    
    while ((ch = fgetc(fp)) != EOF)    
    {
        if (ch == '\n')
            n++;
    }
    
        
    rewind(fp);
    
    node *ptr[n];  //Create an array of pointers with length = no: of vertices
    fclose(fp);

// Read data from input file and create linked list 

    ifstream file;
    file.open("in1.txt");

 while (file)
 {
       file.getline(line, 2000);
       pch = strtok(line," ");
       intval = atoi(pch);
       ptr[j] = new node;
       ptr[j] -> read(intval);
       ptr[j] -> next = NULL;
       ptr[j] -> edges = 0;
       temp = ptr[j];
       
       pch = strtok(NULL," ");
       
       while(pch != 0)
       {
                  intval = atoi(pch);
                  x = new node;
                  x->read(intval);
                  x->next = NULL;
                  temp->next = x;
                  temp = x;
                  ptr[j]->edges = ptr[j]->edges + 1;
                  pch = strtok(NULL," ");
       }
       
       j++;
 }

     
cout<<endl<<"The data you have entered is : "<<endl;

    // Display entered data in the form of an adjacency list
    int i;
    for(i=0;i<n;i++)
    {
       f = ptr[i];
       while( f != NULL)
       {
              f->show();
              cout<<"  ";
              f = f->next;
       }
       cout<<endl;
    }                    
   // .............. Algorithm Begins ..............
   
    //Calculate In-degree array D
                    
    int d[n+1];
    int vcharge[110];
    int echarge[110][110];
    for (i=0;i<n+1;i++)
    {
        vcharge[i]=1;
        d[i]=0;
    }
    
    for(i=0;i<n;i++)
    {
       f = ptr[i]->next;
       vcharge[i]++;
       while (f != NULL)
       {
             d[f->a] = d[f->a] + 1;
             echarge[i][(f->a)-1]=1;
             f = f->next;
       }
    }
    
    
    //Checking for in degree 0 nodes and adding to queue, sending to output, decrementing 
    // values in array D and adding more vertices if indices become zero
    

    cout<<endl<<"The output is :  ";
    
    for (i=1;i<n+1;i++)
    {
        vcharge[i-1]++;
        if (d[i] == 0)
        {
             add(i);
             vcharge[i-1]++;   
        }
    }
    
    
    while (front != NULL)
    {    
    t = front;
    temp = ptr[(t->b)-1];
    f = temp -> next;
    while (f != NULL)
    {
          d[f->a] = d[f->a] - 1; 
          echarge[(front->b)-1][(f->a)-1]++;
          if (d[f->a] == 0)  
          { add (f->a);
            vcharge[(f->a)-1]++;
          }
          echarge[(front->b)-1][(f->a)-1]++;
          f = f->next;   
    }
    
  vcharge[(front->b)-1]++; 
  del();
  
 
}

for (i=0;i<n;i++)
{
    vcharge[i]++;
    if (d[i] != 0)
    {
             cout<<" There is a loop in the graph"<<endl;
             break;
             }
    }
   
    
 cout<<endl<<endl<<endl;
 
 //Calculating node and edge charges and adding both at the end
 
	int totVcharge = 0; int k;
	int totEcharge = 0;
	
	for (i=0; i<n; i++)
	{
		cout<<"Operations charged to Vertex "<<i<<" : ";
		for (j=0; j<vcharge[i]; j++)
			cout<<"1 ";
		cout<<endl;
		totVcharge += vcharge[i];
	}
	for (i=0; i<n; i++)
	{
        f = ptr[i]->next;
		for (j=0; j<ptr[i]->edges; j++)
		{
			cout<<"Edge from Vertex number "<<i+1<<" to Vertex number " << f->a<<" : ";
			
			
			for (k=0; k<echarge[i][(f->a)-1]; k++)
			{
				printf("1 ");
            }
			cout<<endl;
			
			totEcharge += echarge[i][(f->a)-1];
			f = f->next;
		}
	}
	cout<<endl<<"Total number of operations charged to vertices is : "<<totVcharge<<endl;
	cout<<"Total number of operations charged to edges is : "<<totEcharge<<endl;
	cout<<"Total number of operations is : "<<totVcharge+totEcharge<<endl;
	
	
	

system("pause"); 
return 0;
}
