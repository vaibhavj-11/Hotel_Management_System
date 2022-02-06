#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<iomanip.h>
#include<ctype.h>
struct CUST  //checkin in main menu
{
	int rmno;
	char name[30];
	char address[30];
	long Phone;
	int member;
	char date[15];
	int ndys;
	float rmcst;
}c;
struct BILL   //checkout in main menu
{
	int rmno;
	char name[30];
	char address[30];
	long Phone;
	int member;
	char date[15];
	int ndys;
	float rmcst,orcst;
	float total;
}b;
struct RUM    //roomtype in master menu
{
		int roomno;
		int p_ebed;
		int p_eplw;
		int p_eblk;
		int p_etwl;
		char bed[15];
		char roomtype[30];
		float roomcst;
		int avl;
}r;
void CURRENT()                      //in check in menu
{
	clrscr();
	RUM r1;
	ofstream fout("record.dat",ios::app);
	fstream fin("roomtype.txt",ios::in);
	textcolor(WHITE);
	cout<<"\n";
	cout<<"ROOM NO   ROOM TYPE   BED TYPE        PRICE        AVAILABILITY\n";
	for(int i=0;i<65;i++){ cout<<"-"; }
	cout<<endl;
	int rr=6;
	int rmm[50],rmmcst[50];int rnc=0;
	while(fin.read((char *)&r1, sizeof(r1)))
	{
		if(r1.avl==1)
		{
			cprintf("  %d ",r1.roomno);
			cprintf("      %s ",r1.roomtype);
			cprintf("     %s ",r1.bed);
			cprintf("    %f   ",r1.roomcst);
			cout<<"   AVAILABLE";
			cout<<endl;
			rmm[rnc]=r1.roomno;
			rmmcst[rnc]=r1.roomcst;
			rnc++;
		}
		else
		{
			cprintf("  %d ",r1.roomno);
			cprintf("      %s ",r1.roomtype);
			cprintf("     %s ",r1.bed);
			cprintf("    %f   ",r1.roomcst);
			cout<<" UNAVAILABLE";
			cout<<"\n";
		}
		rr++;
	}
	fin.close();
	cout<<"\n";
	textcolor(WHITE);
	if(rnc==0)
		cout<<"ROOM NOT AVAILABLE.\n";
	else
	{
		cout<<"\n**********************";
		cout<<"\nENTER CUSTOMER DETAILS";
		cout<<"\n**********************";
		int flg=0,i;
		while(1)
		{
			cout<<"\nENTER ROOM NUMBER or PRESS 0 TO EXIT: ";
			cin>>c.rmno;
			if(c.rmno==0)
			   break;
			else
			{
				for(i=0;i<rnc;i++)
				{
					if(c.rmno==rmm[i])
					{	flg=1;
						break;
					}
				}
				if(flg==1)
				{
					c.rmcst=rmmcst[i];
					cout<<"\nNAME: ";
					cin>>c.name;
					fflush(stdin);
					cout<<"\nNO.OF FAMILY MEMBERS: ";
					cin>>c.member;
					cout<<"\nADDRESS: ";
					cin>>c.address;
					fflush(stdin);
					cout<<"\nNUMBER OF DAYS: ";
					cin>>c.ndys;
					cout<<"\nPHONE NUMBER: ";
					cin>>c.Phone;
					fflush(stdin);
					cout<<"\n";
					break;
				}
				else
				{
					cout<<"INVALID ROOM NUMBER.\nPRESS ANY KEY TO ENTER CORRECT ROOM NUMBER:";
					getch();
				}
			}
		}
		if(c.rmno>0)
		{
			cout<<"DO YOU WANT TO SAVE(Y/N) :";
			char ch;
			cin>>ch;
			if(toupper(ch)=='Y')
			{
				cout<<"\nHAVE A GOOD DAY!";
				fout.write((char*)&c,sizeof(c));
				fstream fin("roomtype.txt",ios::in|ios::out);
				while(fin.read((char *)&r1, sizeof(r1)))
				{
					if(r1.roomno==c.rmno)
					{
						int pos=fin.tellg();
						fin.seekp(pos-sizeof(r1));
						r1.avl=0;
						fin.write((char*)&r1,sizeof(r1));
						break;
					}
				}
				fin.close();
			}
		}
	}
	fout.close();
}
void CHECKIN_MENU()              //in main menu
{
	clrscr();
	char ch;
	while(1)
	{
		clrscr();
		cout<<"\n**********************";
		cout<<"\nSELECT TYPE OF BOOKING";
		cout<<"\n**********************";
		cout<<"\n1. CURRENT BOOKING";
		cout<<"\n2. RETURN";
		cout<<"\nENTER YOUR CHOICE:";
		ch=getch();
		switch(ch)
		{
			case '1': clrscr();
				  CURRENT();
				  getch();
				  break;
			case '2': return;
		}
	}
}
void R_MODIFY_FORAVL(int);
void C_DELETE(int);
void CHECKOUT()
{
	fstream fout("bill.txt",ios::app);
	fstream fin("record.dat",ios::in);
	fin.read((char *)&c,sizeof(c));
	for(int i=0;i<80;i++){ cout<<"-"; } 
	cout<<"\t\t\t\tSRMIST KTR HOTEL";cout<<"\n";
	for(i=0;i<80;i++){ cout<<"-"; } cout<<"\n";
	cout<<"\n";
	int rno;
	cout<<"\nENTER ROOM NUMBER TO GENERATE BILL FOR: ";
	cin>>rno;
	if(rno==c.rmno)
	{
		float btotal;
		cout<<"\nROOM NUMBER: "<<c.rmno;
		cout<<"\nNAME: "<<c.name;
		printf("\nNO.OF FAMILY MEMBERS: %d",c.member);
		cout<<"\nADDRESS: "<<c.address;
		cout<<"\nPHONE NUMBER: "<<c.Phone;
		cout<<"\nNUMBER OF DAYS: "<<c.ndys;
		cout<<"\nPER DAY COST: "<<c.rmcst;
		btotal=c.ndys*c.rmcst;
		cout<<"\nROOM COST FOR "<<c.ndys<<" DAYS: "<<btotal;
		float gtotal=btotal;
		cout<<"\nGRAND TOTAL COST: "<<gtotal;
		cout<<"\nAMOUNT TO BE PAID (Y/N): ";
		fflush(stdin);
		char ch;
		cin>>ch;
		if(toupper(ch)=='Y')
		{
			b.rmno=c.rmno;strcpy(b.name,c.name);strcpy(b.address,c.address);
			b.Phone=c.Phone;b.member=c.member;strcpy(b.date,c.date);
			b.ndys=c.ndys;b.rmcst=c.rmcst;
			b.total=gtotal;
			fout.write((char *)&b,sizeof(b));
			R_MODIFY_FORAVL(c.rmno);
			fin.close();
			C_DELETE(c.rmno);
		}
	}
	fout.close();
	fin.close();
	getch();
}
void R_ADD()                       //in room type
{
	clrscr();
	fstream fout("roomtype.txt",ios::out|ios::app|ios::binary);
	cout<<"\n**********************";
	cout<<"\nENTER ROOM DETAILS";
	cout<<"\n**********************";
	fflush(stdin);
	cout<<"\nROOM NUMBER: ";
	cin>>r.roomno;
	fflush(stdin);
	cout<<"\nROOMTYPE: ";
	cin>>r.roomtype;
	fflush(stdin);
	cout<<"\nTYPE OF BED: ";
	gets(r.bed);
	cout<<"\nROOMCOST: ";
	cin>>r.roomcst;
	r.avl=1;
	cout<<"DO YOU WANT TO SAVE(Y/N): ";
	char ch;
	cin>>ch;
	if(toupper(ch)=='Y')
	{
		fout.write((char*)&r,sizeof(r));
		cout<<"\nROOMTYPE ADDED.";
	}
	fout.close();
}

void R_MODIFY_FORAVL(int rno)
{
	ofstream fout("rtype.tmp",ios::out|ios::binary);
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO ROOM FOUND.");
	}
	else
	{
		while(fin.read((char*)&r,sizeof(r)))
		{
			if(rno==r.roomno)
			{
				r.avl=1;
				fout.write((char*)&r,sizeof(r));
			}
			else
				fout.write((char*)&r,sizeof(r));
		}
		fout.close();
		fin.close();
		remove("roomtype.txt");
		rename("rtype.tmp","roomtype.txt");
	}
}


void R_DISPLAY()                       //in room type
{
	clrscr();
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO ROOM FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ cout<<"*"; }
		gotoxy(33,2);printf("ROOM DETAIL INFORMATION\n");
		for(i=0;i<80;i++){ printf("*"); }printf("\n");
		printf("\tROOM NUMBER\t    ROOM TYPE\t      ROOM COST\t\tBED TYPE\n");
		for(i=0;i<80;i++){ printf("-"); }
		int rr=7;
		while(fin.read((char*)&r,sizeof(r)))
		{
			gotoxy(12,rr);
			printf("%d",r.roomno);
			gotoxy(31,rr);
			printf("%s",r.roomtype);
			gotoxy(46,rr);
			printf("%f",r.roomcst);
			gotoxy(67,rr);
			printf("%s",r.bed);
			printf("\n");
			rr++;
		}
	}
	fin.close();
}


void R_DELETE()
{
	clrscr();
	ofstream fout("rtype.tmp",ios::out|ios::binary);
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"NO ROOM FOUND.";
	}
	else
	{
		int rno;
		printf("\nENTER ROOM NUMBER TO DELETE: ");
		cin>>rno;
		int flg=0;
		while(fin.read((char*)&r,sizeof(r)))
		{
			if(rno==r.roomno)
				flg=1;
			else
				fout.write((char *)&r, sizeof(r));
		}
		if(flg==1)
			printf("ROOM DELETED.");
		else
			printf("ROOM NOT AVAILABLE TO DELETE.");
	}

	fout.close();
	fin.close();
	remove("roomtype.txt");
	rename("rtype.tmp","roomtype.txt");
}

void M_ROOMTYPE_MENU()            //room in master
{
	clrscr();
	int ch;
	while(1)
	{
		clrscr();
		cout<<"**********************";
		cout<<"\n     ROOM OPTIONS";
		cout<<"\n**********************";
		cout<<"\n1. ADD ";
		cout<<"\n2. DISPLAY";
		cout<<"\n3. DELETE";
		cout<<"\n4. RETURN";
		cout<<"\nENTER YOUR CHOICE:";
		ch=getch();
		switch(ch)
		{
			case '1': clrscr();
				  R_ADD();
				  getch();
				  break;
			case '2': clrscr();
				  R_DISPLAY();
				  getch();
				  break;
			case '3': clrscr();
				  R_DELETE();
				  getch();
				  break;
			case '4': return;
		}
	}
}

void C_DISPLAY()
{
	clrscr();
	ifstream fin("record.dat",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ printf("*"); }
		gotoxy(33,2);printf("CUSTOMER DETAIL INFORMATION\n");
		for(i=0;i<80;i++){ printf("*"); } printf("\n");
		gotoxy(2,5);printf("R.NO");
		gotoxy(15,5);printf("CUSTOMER NAME");
		gotoxy(35,5);printf("ADDRESS");
		gotoxy(50,5);printf("PHONE");
		gotoxy(60,5);printf("DAYS");
		gotoxy(70,5);printf("COST");printf("\n");
		for(i=0;i<80;i++){ printf("-"); }printf("\n");
		int rr=7;
		while(fin.read((char*)&c,sizeof(c)))
		{
			gotoxy(3,rr);printf("%d",c.rmno);
			gotoxy(17,rr);printf("%s",c.name);
			gotoxy(37,rr);printf("%s",c.address);
			gotoxy(50,rr);printf("%ld",c.Phone);
			gotoxy(62,rr);printf("%d",c.ndys);
			gotoxy(70,rr);printf("%f",c.rmcst);
			rr++;
		}
		fin.close();
	}
}


void BILL_DISPLAY()
{
	clrscr();
	ifstream fin("bill.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ printf("*"); }
		gotoxy(25,2);printf("CUSTOMER WISE BILL DETAIL INFORMATION\n");
		for(i=0;i<80;i++){ printf("*"); }
		gotoxy(2,5);printf("R.NO");
		gotoxy(10,5);printf("CUSTOMER NAME");
		gotoxy(25,5);printf("  ADDRESS");
		gotoxy(36,5);printf("PHONE");
		gotoxy(47,5);printf("DAYS");
		gotoxy(56,5);printf("COST");
		gotoxy(69,5);printf("T.COST");printf("\n");
		for(i=0;i<80;i++){ printf("-"); }printf("\n");
		int rr=7;
		while(fin.read((char*)&b,sizeof(b)))
		{  	gotoxy(2,rr);printf("%d",b.rmno);
			gotoxy(13,rr);printf("%s",b.name);
			gotoxy(27,rr);printf("%s",b.address);
			gotoxy(35,rr);printf("%ld",b.Phone);
			gotoxy(48,rr);printf("%d",b.ndys);
			gotoxy(54,rr);printf("%f",b.rmcst);
			gotoxy(68,rr);printf("%f",b.total);
			rr++;
		}
		fin.close();
	}
}

void C_DELETE(int rno)
{
	clrscr();
	ofstream fout("ctype.tmp",ios::out|ios::binary);
	ifstream fin("record.dat",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}


	else
	{
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(rno!=c.rmno)
				fout.write((char *)&c, sizeof(c));
		}

	}
	fout.close();
	fin.close();
	remove("record.dat");
	rename("ctype.tmp","record.dat");
}

void CUSTOMER_MENU()
{
	int ch;
	while(1)
	{
		clrscr();
		cout<<"**********************";
		cout<<"\n   CUSTOMER OPTIONS        ";
		cout<<"\n**********************";
		cout<<"\n1. DISPLAY";
		cout<<"\n2. BILL DISPLAY";
		cout<<"\n3. RETURN";
		cout<<"\nENTER YOUR CHOICE:";
		ch=getch();
		switch(ch)
		{
			case '1': clrscr();
				  C_DISPLAY();
				  getch();
				  break;
			case '2': clrscr();
				  BILL_DISPLAY();
				  getch();
				  break;
			case '3': return;
		}
	}
}
void MASTER_MENU()
{
	clrscr();
	int ch;
	while(1)
	{
		clrscr();
		printf("**********************");
		printf("\n        MASTER        ");
		printf("\n**********************");
		printf("\n1. ROOM TYPE");
		printf("\n2. RETURN");
		printf("\nENTER YOUR CHOICE: ");
		ch=getch();
		switch(ch)
		{
			case '1': 	clrscr();
					M_ROOMTYPE_MENU();
					break;
			case '2': 	return;
		}
	}
}
void intro()
{
	clrscr();
	printf("\t\t\t\tHOTEL MANAGEMENT SYSTEM");
	printf("\n\t\t\t\tPRESS ANY KEY TO CONTINUE.");
	getch();
}
void main()
{
	clrscr();
	intro();
	char choice;
	while(1)
	{
		clrscr();
		printf("\n*************");
		printf("\n* MAIN MENU *");
		printf("\n*************");
		printf("\n1.CHECK-IN");
		printf("\n2.CHECK-OUT");
		printf("\n3.CUSTOMER INFO");
		printf("\n4.MASTER");
		printf("\n5.EXIT");
		printf("\nENTER YOUR CHOICE:");
		choice=getch();
		switch(choice)
		{
			case '1': clrscr();
				  CHECKIN_MENU();
				  break;
			case '2': clrscr();
				  CHECKOUT();
				  break;
			case '3': clrscr();
				  CUSTOMER_MENU();
				  break;
			case '4': clrscr();
				  MASTER_MENU();
				  break;
			case '5': exit(0);
		}
	}
}