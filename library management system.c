#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>
//#include<bios.h>

#define RETURNTIME 15

char catagories[][15]={"IT","Law","Novels","Maths","Political","Historical"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void show_mouse(void);
void Password();
void issuerecord();
void loaderanim();
//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;
COORD coord = {0, 0};
//list of global variable
int s;
char findbook;
//char password[10]={"alpha"};
void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y; // X and Y coordinates
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct meroDate
{
int mm,dd,yy;
};
struct books
{
int id;
char stname[20];
char name[20];
char Author[20];
int quantity;
float Price;
int count;
int rackno;
char *cat;
struct meroDate issued;
struct meroDate duedate;
};
struct books a;
int main()
{
Password();
getch();
return 0;
}
void mainmenu()
{
loaderanim();
system("cls");
    textbackground(13);
int i;
gotoxy(20,3);
printf("\t\t******* MAIN MENU ******* ");
//    show_mouse();
printf("\n\n\t 1. Add Books   ");
printf("\n\n\t 2. Delete books");
printf("\n\n\t 3. Search Books");
printf("\n\n\t 4. Issue Books");
printf("\n\n\t 5. View Book list");
printf("\n\n\t 6. Edit Book's Record");
printf("\n\n\t 7. Close Application");
t();
printf("\n\n\tEnter your choice:");
switch(getch())
{
case '1':
addbooks();
break;
case '2':
deletebooks();
break;
case '3':
searchbooks();
break;
case '4':
issuebooks();
break;
case '5':
viewbooks();
break;
case '6':
editbooks();
break;
case '7':
{
system("cls");
gotoxy(16,3);
exit(0);
}
default:
{
gotoxy(10,23);
printf("\aWrong Entry!!Please re-entered correct option");
if(getch())
mainmenu();
}
}
}
void addbooks(void)    //funtion that add books
{
system("cls");
int i;

printf("\t\t**** SELECT CATEGORIES ****\n\n\n");
printf("\t\t 1. IT\n\n");
printf("\t\t 2. Law\n\n");
printf("\t\t 3. Novels\n\n");
printf("\t\t 4. Maths\n\n");
printf("\t\t 5. Political\n\n");
printf("\t\t 6. Historical\n\n");
printf("\t\t 7. Back to main menu");
printf("Enter your choice:");
scanf("%d",&s);
if(s==7)
mainmenu() ;
system("cls");
fp=fopen("Bibek.dat","ab+");
if(getdata()==1)
{
a.cat=catagories[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("\n\t\tThe record is sucessfully saved\n\n");
printf("\t\tSave any more?(Y / N):");
if(getch()=='n')
mainmenu();
else
system("cls");
addbooks();
}
}
void deletebooks()    //function that delete items from file fp
{
system("cls");
int d;
char another='y';
while(another=='y')  //infinite loop
{
system("cls");
printf("\n\tEnter the Book ID to  delete:");
scanf("%d",&d);
fp=fopen("Bibek.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
printf("\n\tThe book record is available\n\n");
printf("\tBook name is %s\n\n",a.name);
printf("Rack No. is %d",a.rackno);
findbook='t';
}
}
if(findbook!='t')
{
printf("\n\n\tNo record is found modify the search\n\n");
if(getch())
mainmenu();
}
if(findbook=='t' )
{
gotoxy(10,9);
printf("\tDo you want to delete it?(Y/N):");
if(getch()=='y')
{
ft=fopen("test.dat","wb+");  //temporary file for delete
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
}                              //we want to delete
}
fclose(ft);
fclose(fp);
remove("Bibek.dat");
rename("test.dat","Bibek.dat"); //copy all item from temporary file to fp except that
fp=fopen("Bibek.dat","rb+");    //we want to delete
if(findbook=='t')
{
printf("\n\tThe record is sucessfully deleted\n\n");
printf("\tDelete another record?(Y/N)");
}
}
else
mainmenu();
fflush(stdin);
another=getch();
}
}
gotoxy(10,15);
mainmenu();
}
void searchbooks()
{
system("cls");
int d;
printf("\t\t\t******* Search Books *******\n\n");
printf("\t 1. Search By ID\n\n");
printf("\t 2. Search By Name\n\n");
printf("\tEnter Your Choice");
fp=fopen("Bibek.dat","rb+"); //open file for reading propose
rewind(fp);   //move pointer at the begining of file
switch(getch())
{
case '1':
{
system("cls");
printf("\n****Search Books By Id****\n\n");
printf("\tEnter the book id:\n\n");
scanf("%d",&d);
printf("\tSearching........");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
Sleep(2);
printf("\n\tThe Book is available\n\n");
printf("\t\xB2 ID:%d \n",a.id);
printf("\t\xB2 Name:%s \n",a.name);
printf("\t\xB2 Author:%s \n",a.Author);
printf("\t\xB2 Qantity:%d \n",a.quantity);
printf("\t\xB2 Price:Rs.%.2f \n",a.Price);
printf("\t\xB2 Rack No:%d ",a.rackno);
findbook='t';
}
}
if(findbook!='t')  //checks whether conditiion enters inside loop or not
{
gotoxy(20,8);
printf("\xB2");  gotoxy(38,9);printf("\xB2");
gotoxy(20,10);
printf("\aNo Record Found");
}
gotoxy(20,17);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
printf("\n\t****Search Books By Name****\n\n");
printf("\tEnter Book Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
{
printf("\n\tThe Book is available\n\n");
gotoxy(20,8);
printf("\t ID:%d\n\n",a.id);
printf("\t Name:%s\n\n",a.name);
printf("\t Author:%s\n\n",a.Author);
printf("\t Qantity:%d\n\n",a.quantity);
printf("\t Price:Rs.%.2f\n\n",a.Price);
printf("\t Rack No:%d ",a.rackno);
d++;
}
}
if(d==0)
{
printf("\n\n\tNo Record Found");
}
printf("\n\n\tTry another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
mainmenu();
break;
}
default :
getch();
searchbooks();
}
fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
int t;
system("cls");
printf("\t\t******* ISSUE SECTION *******");
printf("\n\n\t 1. Issue a Book");
printf("\n\n\t 2. View Issued Book");
printf("\n\n\t 3. Search Issued Book");
printf("\n\n\t 4. Remove Issued Book");
printf("\n\n\tEnter a Choice:");
switch(getch())
{
case '1':  //issue book
{
system("cls");
int c=0;
char another='y';
while(another=='y')
{
system("cls");
printf("\n\t\t***Issue Book section***\n\n");
printf("\tEnter the Book Id:\n\n");
scanf("%d",&t);
fp=fopen("Bibek.dat","rb");
fs=fopen("Issue.dat","ab+");
if(checkid(t)==0) //issues those which are present in library
{
printf("\n\n\tThe book record is available\n\n");
printf("\tThere are %d unissued books in library \n\n",a.quantity);
printf("\tThe name of book is %s \n\n",a.name);
printf("\tEnter student name:");
scanf("%s",a.stname);
//struct dosdate_t d; //for current date
//_dos_getdate(&d);
//a.issued.dd=d.day;
//a.issued.mm=d.month;
//a.issued.yy=d.year;
printf("\n\n\tIssued date=%d-%d-%d\n\n",a.issued.dd,a.issued.mm,a.issued.yy);
printf("\tThe BOOK of ID %d is issued",a.id);
a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
a.duedate.mm=a.issued.mm;
a.duedate.yy=a.issued.yy;
if(a.duedate.dd>30)
{
a.duedate.mm+=a.duedate.dd/30;
a.duedate.dd-=30;
}
if(a.duedate.mm>12)
{
a.duedate.yy+=a.duedate.mm/12;
a.duedate.mm-=12;
}
printf("\nTo be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
fseek(fs,sizeof(a),SEEK_END);
fwrite(&a,sizeof(a),1,fs);
fclose(fs);
c=1;
}
if(c==0)
{
printf("\n\n\tNo record found");
}
printf("\n\n\tIssue any more(Y/N):");
fflush(stdin);
another=getche();
fclose(fp);
}
break;
}
case '2':  //show issued book list
{
system("cls");
int j=4;
printf("\t\t******* Issued book list *******\n\n");
printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE\n\n");
fs=fopen("Issue.dat","rb");
while(fread(&a,sizeof(a),1,fs)==1)
{
gotoxy(2,j);
printf("%s",a.stname);
gotoxy(18,j);
printf("%s",a.cat);
gotoxy(30,j);
printf("%d",a.id);
gotoxy(36,j);
printf("%s",a.name);
gotoxy(51,j);
printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
gotoxy(65,j);
printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
//struct dosdate_t d;
//_dos_getdate(&d);
gotoxy(50,25);
//            printf("Current date=%d-%d-%d",d.day,d.month,d.year);
j++;
}
fclose(fs);
gotoxy(1,25);
returnfunc();
}
break;
case '3':   //search issued books by id
{
system("cls");
printf("\n\nEnter Book ID:");
int p,c=0;
char another='y';
while(another=='y')
{
scanf("%d",&p);
fs=fopen("Issue.dat","rb");
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id==p)
{
issuerecord();
printf("\n\n\tPress any key.......");
getch();
issuerecord();
c=1;
}
}
fflush(stdin);
fclose(fs);
if(c==0)
{
printf("\n\n\tNo Record Found");
}
printf("\n\n\tTry Another Search?(Y/N)");
another=getch();
}
}
break;
case '4':  //remove issued books from list
{
system("cls");
int b;
FILE *fg;  //declaration of temporary file for delete
char another='y';
while(another=='y')
{
printf("\n\n\tEnter book id to remove:");
scanf("%d",&b);
fs=fopen("Issue.dat","rb+");
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id==b)
{
issuerecord();
findbook='t';
}
if(findbook=='t')
{
printf("\n\n\tDo You Want to Remove it?(Y/N)");
if(getch()=='y')
{
fg=fopen("record.dat","wb+");
rewind(fs);
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id!=b)
{
fseek(fs,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,fg);
}
}
fclose(fs);
fclose(fg);
remove("Issue.dat");
rename("record.dat","Issue.dat");
printf("\n\n\tThe issued book is removed from list");
}
}
if(findbook!='t')
{
printf("\n\n\tNo Record Found");
}
}
printf("\n\n\tDelete any more?(Y/N)");
another=getch();
}
}
default:
printf("\n\n\tWrong Entry!!");
getch();
issuebooks();
break;
}
gotoxy(1,30);
returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
int i=0,j;
system("cls");
gotoxy(1,1);
printf("\n\t\t\t******* Book List *******");
gotoxy(2,2);
printf("\n\n CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ");
j=4;
fp=fopen("Bibek.dat","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
gotoxy(3,j);
printf("%s",a.cat);
gotoxy(16,j);
printf("%d",a.id);
gotoxy(22,j);
printf("%s",a.name);
gotoxy(36,j);
printf("%s",a.Author);
gotoxy(50,j);
printf("%d",a.quantity);
gotoxy(57,j);
printf("%.2f",a.Price);
gotoxy(69,j);
printf("%d",a.rackno);
printf("\n\n");
j++;
i=i+a.quantity;
}
printf("\n\n\tTotal Books =%d",i);
fclose(fp);
gotoxy(35,25);
returnfunc();
}
void editbooks(void)  //edit information about book
{
system("cls");
int c=0;
int d,e;
printf("\n\t\t****Edit Books Section****");
char another='y';
while(another=='y')
{
system("cls");
printf("\n\n\tEnter Book Id to be edited:");
scanf("%d",&d);
fp=fopen("Bibek.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
printf("\n\n\tThe book is availble");
printf("\n\n\tThe Book ID:%d",a.id);
printf("\n\n\tEnter new name:");scanf("%s",a.name);
printf("\n\n\tEnter new Author:");scanf("%s",a.Author);
printf("\n\n\tEnter new quantity:");scanf("%d",&a.quantity);
printf("\n\n\tEnter new price:");scanf("%f",&a.Price);
printf("\n\n\tEnter new rackno:");scanf("%d",&a.rackno);
printf("\n\n\tThe record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
printf("\n\n\tNo record found");
}
}
printf("\n\n\tModify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
{
printf("\n\t Press ENTER to return to main menu");
}
a:
if(getch()==13) //allow only use of enter
mainmenu();
else
goto a;
}
int getdata()
{
int t;
printf("\n\n\tEnter the Information Below");
printf("\n\n\tCategory:");
printf("\n\n\t%s",catagories[s-1]);
printf("\n\n\tBook ID:\n\n\t");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\n\n\tThe book id already exists\a");
getch();
mainmenu();
return 0;
}
a.id=t;
printf("\n\n\tBook Name :\n\t");
scanf("%s",a.name);
printf("\n\n\tAuthor :\n\t");
scanf("%s",a.Author);
printf("\n\n\tQuantity :\n\t");
scanf("%d",&a.quantity);
printf("\n\n\tPrice:\n\t");
scanf("%f",&a.Price);
printf("\n\n\tRack No:\n\t");
scanf("%d",&a.rackno);
return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.id==t)
return 0;  //returns 0 if book exits
return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
/*void show_mouse(void) //show inactive mouse pointer in programme
{
union REGS in,out;
       in.x.ax = 0x1;
       int86(0x33,&in,&out);
}*/
void Password(void) //for password option
{
system("cls");
char ch,pass[10];
int i=0,j;
//textbackground(WHITE);
//textcolor(RED);
printf("\n\n\tEnter Password :");
while(ch!=13)
{
ch=getch();
if(ch!=13 && ch!=8){
putch('*');
pass[i] = ch;
i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
textcolor(BLINK);
printf("\n\n\tPassword match");
printf("\n\n\tPress any key to countinue.....");
getch();
mainmenu();
}
else
{
printf("\n\n\tWarning!! Incorrect Password");
getch();
Password();
}
}
void issuerecord()  //display issued book's information
{
system("cls");
printf("\n\n\tThe Book has taken by Mr. %s",a.stname);
printf("\n\n\tIssued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
printf("\n\n\tReturnin");}
