class date_mg
{	int date_n;
	int month;
	int year;
	public:
	void date_now()
	{
		date_n=date(2);
		month=date(1)    ;
		year=date(0);
	}

	int out(int i)
	{if(i==0)
		return year;
	if(i==1)
		return month;
	if(i==2)
		return date_n;
	}
};
date_mg ob_date;


class teacher
{
	int id, period_cl[6][8];
	char fname[100],lname[100], period_s[6][8];

public:

//constructor func for the class
void teach(teacher &ob)
{
	stpcpy(fname,ob.fname);
	stpcpy(lname,ob.lname);
	id=ob.id;
	for(int i=0;i<6;i++)
		for(int j=0;j<8;j++)
		{
			if(i==5&&j==6)
				break;
			period_cl[i][j]=ob.period_cl[i][j]  ;
			period_s[i][j]=ob.period_s[i][j]     ;
		}
}
//function end here


// function to take input of name
void namein()
{	
	stpcpy(fname,"\0");
	stpcpy(lname,"\0");
	
	cout<<"Enter teacher first name :- ";
	gets(fname);
	cout<<"Enter teacher last name :- ";
	gets(lname);
	
	// to make the first letter of name capital
	fname[0]=toupper(fname[0]);
	lname[0]=toupper(lname[0]);
	
	// to make the other letter of name small
	for(int i=1;i<strlen(fname);i++)
		fname[i]=tolower(fname[i]);
	for(i=1;i<strlen(fname);i++)
		lname[i]=tolower(lname[i]);
}
//function end here


//function take input of singal period
void schd(int i,int j)
{
	char class_ch[100];
	//int cl;
	cout<<"Enter schedule for Period "<<j+1;
	period:
	cout<<"\n Class:";
	cin>>class_ch;
	if(class_ch[0]=='0')
	{
		 period_cl[i][j]=0;
		 period_s[i][j]='0';
		 goto skip;
	}
	
	period_cl[i][j]=atoi(class_ch);
	if(period_cl[i][j]<1||period_cl[i][j]>12)
	{
		cout<<"Plz enter the correct class";
		goto period;
	}
					
	section:
	cout<<"Section: " ;
	cin>>period_s[i][j];
	period_s[i][j]=toupper(period_s[i][j]);
	      
	if(period_s[i][j]<65||period_s[i][j]>90)
	{
		cout<<"Plz enter the correct section \n";
		goto section;
	}
	//	
	skip:
}
//function end here


// function to take input of period
void schdin()
{
	cout<<"Enter teacher schedule \n Eg: Class:1 or Class:12 \n Section: A \n for free period enter zero('0') in class \n";

	for(int i=0;i<6;i++)//loop to change days
	{
		cout<<endl<<day[i]<<endl;
		for(int j=0;j<8;j++)//loop to change periods
		{
			if(i==5&&j==6)
				break;
			schd(i,j);
		}
	}
}

//function end here


//function to allocate id to teacher
void idin(int i)
{
	id=i;
}
//function end here


//function to take teacher data
void input()
{
	namein();
	cout<<endl;
	schdin();

}
//function end here


//function to return teacher id
int out_id()
{
	return id;
}
//function end here


//function to return teacher name
char* out_name(int len=-1,int ch=0)
{
	char nm[100]="\n", name[100]="\n";

	if(len==-1)
	{
		stpcpy(name,fname);
		strcat(name," ");
		strcat(name,lname);
		return name;
	}
	
	if(ch==1)
		stpcpy(name,fname);
	else if(ch==2)
		stpcpy(name,lname);
	
	if(len==-2)
		len=strlen(name) ;
	for(int i=0;i<=len;i++)
		nm[i]=name[i];

		return nm;
}
//function end here


//function to change teacher sechdule(section) of particular period
void ch_section(int i,int j,char a)
{ 
	period_s[i][j]=a;
}
//function end here

//function to change teacher sechdule(class) of particular period
void ch_clas(int i,int j,int a)
{ 
period_cl[i][j]=a;
}
//function end here


//function to return teacher sechdule(section) of particular period
char section(int i,int j)
{
	return period_s[i][j];
}
//function end here


//function to return teacher sechdule(class) of particular period
int clas(int i,int j)
{
	return period_cl[i][j];
}
//function end here


//function to check data of teacher
void show_data()
{	clrscr();
	cout<<"\n Id: "<<id<<"\n Name: "<<fname<<" "<<lname<<endl<<endl;
	
	for(int i=0;i<=10;i++)
	cout<<" ";
	for(i=1;i<9;i++)
	cout<<"|  "<<i<<"  |";
	
	cout<<endl;
	
	for(i=0;i<6;i++)
	{
		cout<<endl<<" "<<day[i]      ;
		for(int space=strlen(day[i]);space<=9;space++)
			cout<<" ";
		for(int j=0;j<8;j++)
		{
			if(i==5&&j==6)
				break;
			
			cout<<"| ";
			if(period_cl[i][j]==0)
				cout<<" - ";
			else
			{
				if(period_cl[i][j]<10)
					cout<<" ";
				cout<<period_cl[i][j];
				cout<<period_s[i][j];
			}
			cout<<" |";
		}
	}
}
//function end here

};
// teacher class end here

//gobal objects used in program of different purposes
teacher abst[100];
teacher ob;
