#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>


//some statment defined for convenience
#define writedef write((char*)&ob,sizeof(ob))
#define readdef read((char*)&ob,sizeof(ob))
#define fileoutdef  file_out.open("teacher2.txt",ios::app);
#define filebindef  file_out.open("teacher2.txt",ios::app||ios::binary);
#define fileindef   file_in.open("teacher2.txt",ios::in||ios::binary);
#define mainoutdef  main_out.open("teacher.txt",ios::app);
#define mainbindef  main_out.open("teacher.txt",ios::app||ios::binary);
#define mainindef   main_in.open("teacher.txt",ios::in||ios::binary);
#define suboutdef   sub.open("subs.txt",ios::app);
#define tmpoutdef 	tmp.open("tmp.txt",ios::out||ios::binary);



//dfh file required in program
ofstream sub;
ofstream date_out;
ifstream date_in("date.txt",ios::in||ios::binary);
ofstream file_out;
ifstream file_in;
ofstream main_out;
ifstream main_in;
ofstream tmp;


// a file for all gobal variable in program
int absent_no=0;
char day[6][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

// prototype of function declared below
int date(int);
void date_crt();
int search(int=0);
void change(int);
void sdlchange();

//self made header file used in program
#include "class.h" //file conatins class and function related to data manupulation
#include "absent.h"//file conatins  function related to substitution

// prototype of function declared below
void class_id(teacher &ob);
char* out_data(teacher ob);

void data_manpu()//a udf used to manupulate dat of data file
{
	int ans;
	char menu[5][50]={"Add teacher","Change info of teacher","See Teacher data","For Substitution","To exit"}      ;
	int y=4,x=2;
	char ch;
	menu:
	clrscr();
	gotoxy(23,2);
	cout<<"WELCOME to Teacher Data Manager";

	for(int i=0;i<5;i++)
	{
		gotoxy(5,4+i);
		cout<<i+1<<". "<<menu[i]     ;
	}

	cout<<"\n\n  enter the option number to navigate and enter to select.";

	gotoxy(x,y);
	cout<<">";
	while(1)
	{
		ch=getch();

		if(ch==13)
			break;

		if(ch<49||ch>53)
		continue;

		gotoxy(x,y);
		cout<<" ";

		y=ch-45;

		gotoxy(x,y);
		cout<<">";
	}

	ans=y-3;
	answ:
	cout<<endl;

	// to enter teacher data
	if(ans==1)
	{
		clrscr();
		cout<<"  Esc to back go to previous menu\n\n  Press any key to continue";
		char a=getch();
		 int ans;
		if(a!=27)
		{
			do
			{

				clrscr();
				cout<<"ADD TEACHER WIZARD\n\n";

				ob.input();
				cout<<"************Processing************\n\n";
				delay(random(2000));
				class_id(ob);
				mainoutdef
				if(main_out.writedef)
					cout<<endl<<ob.out_name()<<" added to database. \n\n";
				else
					cout<<"There is prb in adding data. Plz try again." ;
				main_out.close();

				ag1:
				cout<<"Want to add more teachers to database \n 1. Yes \n 2. No \n Ans: ";
				cin>>ans;
				if(!(ans==1||ans==2))
				{	cout<<"Plz enter the correct option"     ;
					goto ag1;
				}
				cout<<endl;
			}while(ans==1);
		}
	}

	// to change teacher data
	else if(ans==2)
	{
		int id;
		do
		{	
			id=search();

			if(id==0)
				break;

			cout<<endl;

			change(id);// function to change the teacher data

			ag:
			cout<<"\n\nWant to change more teacher's to database \n 1. Yes \n 2. No \n Ans: ";
			cin>>ans;
			
			if(!(ans==1||ans==2))
			{
				cout<<"Plz enter the correct option"     ;
				goto ag;
			}
			
			cout<<endl;
		}while(ans==1);
	}

	// to check teacher data
	else if(ans==3)
	{
		int id=search();
		if(id==0)goto skip;

		ob.show_data();//class function to show data of the teacher
		cout<<"\n\n Want to get it in a file\n 1. Yes \n 2. No";
		re:
		cout<<"\nAns: " ;
		cin>>ans;
		
		if(ans==1)
			cout<<"File has been created with the name '"<<out_data(ob)<<"' .";
		else if(ans!=2)
		{
			cout<<"enter correct option";
			goto re;
		}
		cout<<"\n\nPress any key to continue" ;
		getch();
		skip:
	}

	// to add substitution
	else if(ans==4)
	{	
		if(date(3)==-1)
		{
			clrscr();	
			cout<<"Today is a SUNDAY.";
			getch();
			goto menu;
		}
		if(teacher_ab_input()==0)
			goto menu;
		
		substitute(date(3));
		cout<<"\nSubstitution are ready. Plz check the file 'subs.txt'\n\nPress any key to continue" ;
		getch();
	}
	
	//to exit from program
	else if(ans==5)
		exit(0);
	
	goto menu;//to go back to start menu after completing it
}


//function to change data of teacher
void change(int id)
{
	int pos1,pos2   ;
	
	mainindef
	
	pos1 = main_in.tellg() ;
	
	while(main_in.readdef)
	{
		pos2=main_in.tellg()   ;
		if(ob.out_id()==id)
			break;
		pos1=pos2;
	}
	
	int ans;
	ansre:
	clrscr();
	
	char menu1[3][50]={"Name","Schedule","All data "};
	int y=6,x=40;
	menu:
	clrscr();
	gotoxy(30,2);
	cout<<"Teacher Data Changer";
	cout<<"\n\nYou selected"<<ob.out_name()<<". Want to change:";
	gotoxy(2,y);
	for(int i=0;i<3;i++)
	{
		gotoxy(2,y+i);
		cout<<i+1<<". "<<menu1[i]     ;
	}
	
	cout<<"\n\n  Use 2 & 8 to navigate and enter to select.";

	gotoxy(x,y);
	cout<<"<";
	while(1)
	{ 
		char ch=getch();
	
		gotoxy(x,y);
		cout<<" ";
			
		if(ch==56)
		{
			if(y<8)
				y++;
			else
				y=5+i;
		}
			
		else if(ch==50)
		{
			if(y>6)
				y--;
			else
				y=6;
		}
			
		else if(ch==13)
			break;
			
		gotoxy(x,y);
		cout<<"<";
	}
	
	ans=y-5;
			
	clrscr();
	gotoxy(2,1);
	
	if(ans==1)
	{
		cout<<"\n Enter new data\n";
		ob.namein();
	}
		
	else if(ans==2)
		sdlchange();
	
	else if(ans==3)
	{
		cout<<"\n Enter new data\n";
		ob.input();
	}
		
	cout<<"\n\n************Processing************\n\n";
			delay(random(1000));
	mainbindef
	main_out.seekp(pos1,ios::beg);

	if(main_out.writedef)
		cout<<"\n"<<ob.out_name()<<" data modified"		  ;
	else
		cout<<"There is prb in updating data. Plz try again." ;

	main_in.close();
	main_out.close();
}
//function end here


//to return id of last entry in the data file
void class_id(teacher &ob)
{ 
	teacher ob1;
	mainindef;
	while(main_in.read((char*)&ob1,sizeof(ob1)));
	main_in.close();

	if(ob1.out_id()=='\0'||ob1.out_id()<=0)
		ob.idin(1);
	else
		ob.idin(ob1.out_id()+1);
	
}
//function end here

// function to search teacher from database
int search(int chk)
{ 	
	char a,name[100]="\0";
	
	//loop to take input of name
	for(int i=0;1;i++)
	{
		clrscr();
		int count=0, y=4, x=2;
		teacher save[100];// to save the possible outcomes of given name

		cout<<" Plz enter the name of techer to search and use 2 & 8 to navigate and enter to select. And Esc to go to previous menu";

		if(strlen(name)>=1&&i>0)
		{
			

			if(chk==0)
			{
				mainindef
				while(main_in.read((char*)&save[count],sizeof(save[count])))
				{
					if(strcmpi(name,save[count].out_name(i-1,1))==0||strcmpi(name,save[count].out_name(i-1,2))==0)
					{	
						gotoxy(4,6+count)  ;
						cout<<" Name: "<<save[count].out_name()<<" Id: "<<save[count].out_id();
						count++;
					}
				}
				main_in.close();
			}	
			else if(chk==1)
			{	
				fileindef
				while(file_in.read((char*)&save[count],sizeof(save[count])))
				{
					if(strcmpi(name,save[count].out_name(i-1,1))==0||strcmpi(name,save[count].out_name(i-1,2))==0)
					{	
						gotoxy(4,6+count) ;
						cout<<" Name: "<<save[count].out_name()<<" Id: "<<save[count].out_id()<<endl;
						count++;
					}
				}
				file_in.close();
			}
			
		}

		gotoxy(2,y) ;

		cout<<"teacher name:- ";
		if(strlen(name)>=1&&i>0)
		cout<<name;

		a=getch()     ;
		
		back:
		if(a==27)
			return 0;
		
		else if(a==8)
		{	
			if(i!=0)
			{
				name[i-1]='\0';
				i-=2;
			}
	
			else
				i=-1;
		}

		else if(a==56||a==50)
		{
			i--;
			if(a==56)
				y=6;
			else if(a==50)
				y=count+5;
	
			gotoxy(x,y);

			if(count!=0)
				cout<<"->"  ;
			else 
				continue;
	
			char in;

			while(1)
			{
				in=getch();
	
				gotoxy(x,y);
				cout<<"  ";

				if(in==50)
				{
					if(y==6)
						break;	
	
					y-=1;
					gotoxy(x,y) ;
					cout<<"->";
				}
	
				else if(in==56)
				{
					if(y!=count+5)
					y+=1;
	
					gotoxy(x,y) ;
					cout<<"->";
				}
				
				else if(in==13)
				{ 
					ob.teach(save[y-6]);
					return save[y-6].out_id();
				}
				
				else
				{
					i++;
					a=in;
					goto back;
				}
			}	
		}	

		else if((65<=a&&a<=90)||(97<=a&&a<=122))
			name[i]=a;
	
		else 
			i--;
		}
}
//function end here


//function to change schedule
void sdlchange()
{
	int ans,per;
	char sec;
	answ:
	gotoxy(2,2);
	cout<<"Want to change \n 1.whole schedule \n 2.specific period \n Ans: ";
	cin>>ans;


	if(ans==1)
		ob.schdin();
	
	else if(ans==2)
	{
		int dayin,periodin;

		cout<<"\nEnter the day you want to change:\n";
		for(int i=0;i<6;i++)
			cout<<"\n "<<i+1<<". "<<day[i];
				
		dayre:
		cout<<"\nAns: ";
		cin>>dayin;
		
		if(6<dayin||dayin<1)
		{
			cout<<"Plz enter the correct option"    ;
			goto dayre;
		}
		
		// to change the no of period in case of sat
        int per_lim=8;
		if(dayin==6)
			per_lim=6  ;
		
		
		cout<<"\nEnter the period you want to change";
		periodre:
		cout<<"\nAns: ";
		cin>>periodin;
		
		if(periodin<1||periodin>per_lim)
		{
			cout<<"Plz enter the correct period"    ;
			goto periodre;
		}
  
		cout<<"\nEnter the new data:\n"     ;
		ob.schd(dayin-1,periodin-1);
			
	 }

	else
	{
		cout<<"Plz enter the correct option"    ;
		goto answ;
	}
	 
}
//function end here

//
char* out_data(teacher ob)
{  
	char file_nm[10],id[2];
	strcpy(file_nm,ob.out_name(0,1));
	strcat(file_nm,ob.out_name(0,2));
	itoa(ob.out_id(),id,10);
	strcat(file_nm,id)	;
	strcat(file_nm,".txt");
	ofstream out(file_nm,ios::out);
	out<<"\n Id: "<<ob.out_id()<<"\n Name: "<<ob.out_name()<<endl<<endl;
	
	for(int i=0;i<=10;i++)
	out<<" ";
	for(i=1;i<9;i++)
	out<<"|  "<<i<<"  |";
	
	for(i=0;i<6;i++)
	{
		out<<endl<<" "<<day[i]      ;
		for(int space=strlen(day[i]);space<=9;space++)
			out<<" ";
		for(int j=0;j<8;j++)
		{
			if(i==5&&j==6)
				break;
			
			out<<"| ";
			if(ob.clas(i,j)==0)
				out<<" - ";
			else
			{
				if(ob.clas(i,j)<10)
					out<<" ";
				out<<ob.clas(i,j);
				out<<ob.section(i,j);
			}
			out<<" |";
		}
	}
	return file_nm;
}
//

// to create a copy of original dfh file 'tecaher_curr.txt' if a new day
void date_check()
{	
	date_in.read((char*)&ob_date,sizeof(ob_date));
	
	if(date_in)
	{
		for(int i=0;i<3;i++)
		{
			if(date(i)!=ob_date.out(i))
				{	
					remove("subs.txt");
					remove("teacher2.txt");
					date_crt();
					mainindef
					fileoutdef

					while(main_in.readdef)
						file_out.writedef;
					
					main_in.close();
					file_out.close(); 
					break;
				}		
		}
	}
	else 
	{
		remove("subs.txt");
		remove("teacher2.txt");
		date_crt();
		mainindef
		fileoutdef

		while(main_in.readdef)
			file_out.writedef;
		
		file_out.close(); 			
		main_in.close();
		
	}
	date_in.close();
}
//function end here


//function to reurn todays date
int date(int in)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int a;
   
   // various components of tm structure.
   if(in==0)
		a=1900 + ltm->tm_year;
	else if(in==1)
		a= 1 + ltm->tm_mon;
	else if(in==2)
		a=0+ltm->tm_mday;
	else if(in==3)
		a=ltm->tm_wday-1;
	
	return a;
}
// function end here	


// function to create date file
void date_crt()
{	
	ob_date.date_now();
	date_out.open("date.txt",ios::out||ios::binary);
	date_out.write((char*)&ob_date,sizeof(ob_date));
	date_out.close();
}
// function end here	

// main function start here
void main()
{
	date_check();
	data_manpu();
}
// function end here