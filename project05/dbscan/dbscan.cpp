#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <math.h>
#include <iomanip>

float **p;	//���Դ洢�ĵ����ݵģ������ĵ�ʱ�������ռ�ģ������ʾ��
bool *bpt;	//״̬��ǣ����ڱ�ʾ�Ƿ񱻷��ʹ�
int *stp;		//-1��ʶΪ�����㣬0Ϊδ����������������ʾ������Ӧ������
int id;			//��¼��ĺ���
						//��������Ϊ�˱��ڲβ������ݣ����Ծ�����Ϊȫ�ֱ���
char **dataset_class;						
				
using namespace std;
	
struct Neighbors	//Neighbors�ṹ�壬ע����Neighbor�ṹ�������
{
	int self;
	Neighbors *next;
};
struct Neighbor	//getNeighbor()�����ķ���ֵ���ͣ���ʾĳ������ھӣ������ھӵĸ�����δ֪��
								//�������˺���ָ��Neighbor������̬�����¸��ھ�
{
	int self;
	int num;
	Neighbors neighbor;
};
struct Cluster	//Cluster�࣬idΪ���ţ�num��ʾ���е�Ԫ�ظ�����member�м�¼����Ԫ��
{
	int id;
	int num;
	int member[1000];
	Cluster *next;

};
float distance(float *a,float *b,int n) //a��bΪ�������� n��ά�ȣ�����ŷʽ����
{
	float re=0;
	for(int i=0;i<n;i++)
	{
		re+=((a[i]-b[i])*(a[i]-b[i]));
	}
	re=sqrt(re);
	return re;
}
float distance_sq(float *a,float *b,int n) //a��bΪ�������� n��ά�ȣ�����ŷʽ����
{
	float re=0;
	for(int i=0;i<n;i++)
	{
		re+=((a[i]-b[i])*(a[i]-b[i]));
	}
	return re;
}
//getneighbor()�������������ھӣ�epsΪһ���ھ��ж�����ֵ
void getNeighbors(Neighbor * nei,int self,float **data,float eps,int n,int m)

{
	Neighbors *next;
	float *a,*b;
	int num=0;
	nei->self=self;
	a=data[self];
	next=&nei->neighbor;
	for(int i=0;i<n;i++)
		{
			if(i==self)
				continue;
			b=data[i];	
			if(distance(a,b,m)<eps)
			{
				num++;
				next->self=i;
				next->next=new Neighbors;
				next=next->next;
			}
		}
	nei->num=num;
}

//�˺���Ϊ��������������ݺ���
void newexp(char *name,int n,int m)
{
	ofstream file;
	int a,b;
	float q;
	file.open(name);

	file<<n<<" "<<m<<endl;
	srand((unsigned int)time(NULL));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			a=rand();
			a%=100;
			b=rand();
			b%=100;
			if(b!=0)
			q=(float)a/(float)b;
			else
				q=0;
			file<<q;
			if(j!=m-1)
				file<<" ";
		}
		file<<endl;
	}

}
//
void expandCluster(int np,Neighbor *nei,Cluster *c,float eps,int MinPts,int n,int m)
{
	int pp;
	stp[np]=c->id;	//add p to cluster c
	c->member[c->num]=np;
	c->num++;
	Neighbors *next,*n2n;
	next=&nei->neighbor;
	for(int i=0;i<nei->num;i++)
	{
		pp=next->self;
		if(bpt[pp]==false)	//if pp is not visited
		{
			bpt[pp]=true;	//mark pp as visited
			Neighbor *n2;
			n2=new Neighbor;
			getNeighbors(n2,pp,p,eps,n,m);
			if(n2->num>=MinPts-1)//N = N joined with N'	
								//because when I calc the neighbor I didn't include itself ,so MinPts-1
			{
				int max,thisnum=0,flag=0;
				Neighbors *last,*n1n;
				last=&nei->neighbor;
				max=nei->num;
				for(int ii=0;ii<max;ii++)
				{
					last=last->next;
				}
				n2n=&n2->neighbor;
				
				for(int ii=0;ii<(n2->num);ii++)
				{
					n1n=&nei->neighbor;
					if(n2n->self==nei->self)
					{
						n2n=n2n->next;
						continue;
					}
					for(int j=0;j<max;j++)
					{
						if(n2n->self==n1n->self)
						{
							flag=1;
							break;
						}
						n1n=n1n->next;
					}
					if(flag==0)
					{
						thisnum++;
						last->self=n2n->self;
						last->next=new Neighbors;
						last=last->next;
					}
					n2n=n2n->next;
				}
				nei->num+=thisnum;
			}

		}
		if(stp[pp]==0)
		{
			stp[pp]=c->id;
			c->member[c->num]=pp;
			c->num++;
		}
		next=next->next;
	}
}
void dbscan(Cluster *c,float **d,float eps,int MinPts,int n,int m)
{
	int cid;
	c->id=1;
	Neighbor * nei;
	nei =new Neighbor;
	for(int i=0;i<n;i++)
	{
		if(bpt[i]==false)
		{
			getNeighbors(nei,i,d,eps,n,m);
			if(nei->num<MinPts-1)	
				stp[i]=-1;	//noise
			else
			{
				expandCluster(i,nei,c,eps,MinPts,n,m);
				c->next=new Cluster;
				cid=c->id;
				c=c->next;
				c->num=0;
				c->id=cid+1;
				id=c->id;
			}
		}
	}
}



int main ()
{
	
	int n,m,i,j,MinPts;
	float eps;
	char a[10];
	char temp;
/*	
	cout<<"Do you want to generate random testing file(Y/N)?"<<endl;
	cin>>a;
	if(a[0]=='y'||a[0]=='Y')
	{
		cout<<"Please enter the name for the random testing file:"<<endl;
		cin>>a;
		cout<<"Please enter the dimention of each data:"<<endl;
		cin>>m;
		cout<<"Please enter the number of data:"<<endl;
		cin>>n;
		newexp(a,n,m);	//produce a random test case
	}
	else if(a[0]=='N'||a[0]=='n')
	{
		cout<<"Please enter the name of the file to read data in:";
		cin>>a;
	}
*/	
	ifstream ifile;
	ifstream setupfile;
	ofstream ofile;
	
	ifile.open("iris.csv");	
	ofile.open("result");
	setupfile.open("setup");
	
	//cout<<"Please enter the name of output file:";
	//cin>>a;
	//ofile.open(a);

	//cout<<"MinPts:";
	//cin>>MinPts;
	//cout<<"eps:";
	//cin>>eps;
	setupfile>>MinPts>>eps>>m>>n;
	//ofile<<MinPts<<" "<<eps<<" "<<m<<" "<<n<<endl;
	//new a space of n*m to store the data
	dataset_class = (char**)malloc(n*sizeof(char*));
	p=new float *[n];
	bpt=new bool [n];
	stp=new int [n];
	for(i=0;i<n;i++)
	{
		dataset_class[i] = (char*)malloc(100*sizeof(char));
		p[i]=new float [m];
		bpt[i]=false;
		stp[i]=0;
	}
	for(i=0;i<n;i++) {
		for(j=0;j<m;j++)
		{
			ifile>>p[i][j]>>temp;
		}
	  ifile>>dataset_class[i];	
	}
	Cluster *c;
	c=new Cluster;
	c->num=0;

	dbscan(c,p,eps,MinPts,n,m);


  ofile<<"The number of clusters: "<<id-1<<endl;
  double dis=0;
  unsigned int count=0;
  for (int k=1;k<id;k++) {
  	dis = 0;
  	count = 0;
    for (i=0;i<n;i++) {
    	if (stp[i]==k) count++;
      for(j=0;j<n;j++)
        {
        	if (stp[i]==k&&stp[j]==k) 
        		dis += distance_sq(p[i],p[j],m);
        }
    }   
    dis = dis/count;
    ofile<<"SSE of Cluster "<<k<<": "<<dis<<endl;    
  }
  // print
/*  
	for(i=0;i<n;i++)
	{
		cout<<"("<<setw(4)<<i<<") ";
		for(j=0;j<m;j++)
			cout<<setprecision(3)<<setw(10)<<p[i][j]<<", ";
		cout<<"                    -->";
		if(stp[i]==-1)
			cout<<" NOISE"<<endl;
		else
		cout<<" "<<stp[i]<<endl;
	//	printf("%d ",stp[i]);
	}
*/
	//result print

	for(i=0;i<n;i++)
	{
		ofile<<"("<<setw(4)<<i<<") ";
		for(j=0;j<m;j++)
			ofile<<setprecision(3)<<setw(10)<<p[i][j]<<", ";
		ofile<<"                    -->";
		if(stp[i]==-1)
			ofile<<" NOISE"<<endl;
		else
		ofile<<" "<<stp[i]<<endl;
	//	printf("%d ",stp[i]);
	}
	cout<<"The number of clusters: "<<id-1<<endl;
	cout<<"Please check the default file: result"<<endl;	
	return 0;

}
