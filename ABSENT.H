//function to take id of all the teacher who are absent and store there data in the object
int teacher_ab_input()
{
	clrscr();
	cout<<"  Esc to back go to previous menu\n\n  Select tecaher id who is absent:- \n\n  Press any key to continue";
	char a=getch();
	int ans;
	if(a!=27)
	{	
		do
		{
			re:
			clrscr();

			int id=search(1);
			
			if(id==0&&absent_no==0)
				return 0;
			else if(id==0)
				return 1  ;
			
			ag1:
			clrscr();
			gotoxy(2,2);
			cout<<"Add "<<ob.out_name()<<" to absent list \n 1. Yes \n 2. No \n Ans: ";
			cin>>ans;

			if(ans==1)
			{ 
				abst[absent_no].teach(ob);
						
				fileindef
				tmpoutdef
				while(file_in.readdef)
				{
					if(abst[absent_no].out_id()==ob.out_id())
						continue;
					tmp.writedef;
				}
				tmp.close();
				file_in.close();
				remove("teacher2.txt");
				rename("tmp.txt","teacher2.txt");
				
				absent_no++;
								
			}

			else if(ans==2)
				goto re;

			else
			{
				cout<<"\nPlz enter the correct option"     ;
				goto ag1;
			}

			cout<<endl<<abst[absent_no-1].out_name()<<" added to absent list.";

			ag2:
			cout<<"\n\nAre more tecaher absent? \n 1. Yes \n 2. No \n Ans: ";
			cin>>ans;

			if(!(ans==1||ans==2))
			{
				cout<<"Plz enter the correct option"     ;
				goto ag2;
			}

		}while(ans==1);
		return 1;
	}
	else 
		return 0;
}
// function end here


//function to give substitute

void substitute(int day)
{
	
	for(int i=0;i<absent_no;i++)//to change absent tecaher
	{	
		suboutdef
		sub<<abst[i].out_name()<<endl<<endl;
		sub.close();
		for(int j=0;j<8;j++)//to change period
		{
				if(day==5&&j==6)
					break;
				
				teacher obper[100];// record the teacher available
				int avail_no=0;// no of teacher available at that period
				char period_s=abst[i].section(day,j);
				int period_cl=abst[i].clas(day,j);
				
				if(period_cl==0)
					continue; 
			
				fileindef
				while(file_in.readdef)
					if(ob.clas(day,j)==0)
					{	
						obper[avail_no].teach(ob);
						avail_no++;
					
					}
				file_in.close();
				
				// to print the name of the teacher selected as substitute in the file	
				int k;
				
				suboutdef
				sub<<"Period: "<<j+1<<" Class: ";
				if(period_cl<10)
					sub<<"0"    ;
				sub<<period_cl<<"-"<<period_s<<" : ";
				sub.close();
				
				if(avail_no==0)
				{
					suboutdef
					sub<<"No teacher available\n";
					sub.close();
					continue;
				}
				
				else
				{
					int ch=0;
					check:
					for(k=0;k<avail_no;k++)//loop to change avail teacher
					{ 
						// below loop are to check wether the teacher teaches the given class or not
						
						for(int m=0;m<6;m++)//loop to change days
							for(int l=0;l<8;l++)//loop to change period
							{	
								if(m==5&&l==6)
									break;
					
								if(obper[k].clas(m,l)==period_cl)
								{
									if(ch==1)
										goto done;
									
									else if(obper[k].section(m,l)==period_s)
										goto done;
								}
							}
					}
					
					if(ch==0)
					{
						ch=1;
						goto check;
					}
					
					randomize;
					k=random(avail_no);
					
					done:
					suboutdef
					sub<<obper[k].out_name()<<endl;;
					sub.close();
				
				}
				
				// to change the free period to substitute in the copy dfh file
				
				int pos1,pos2   ;
	
				fileindef
				
				pos1 = file_in.tellg() ;
				
				while(file_in.readdef)
				{
					pos2=file_in.tellg()   ;
					if(ob.out_id()==obper[k].out_id())
						break;
					pos1=pos2;
				}
				
				ob.ch_section(day,j,period_s);
				ob.ch_clas(day,j,period_cl);
				filebindef
				file_out.seekp(pos1,ios::beg);
				file_out.writedef;
				file_in.close();
				file_out.close();
				
							
		}
		suboutdef
		sub<<endl<<endl<<endl;
		sub.close();
	}
	
}
// function end here