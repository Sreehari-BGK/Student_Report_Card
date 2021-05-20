#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

//  dev. class 'student'
 class student
  {
    int rollno, phy_mark,che_mark, mat_mark, eng_mark, cs_mark;
    char name[50], password, kv;
    float percnt;
    char grade;
     // func. going to be declated inside the class under private!!!
     void calculate()
     {
       percnt = (phy_mark + che_mark + mat_mark + eng_mark + cs_mark)/5 ;

       if(percnt>=60)
	grade = 'A' ;
       else if(percnt>=50)
	grade = 'B';
       else if(percnt>= 33)
	grade = 'C';
       else grade = 'E' ;
     }

   public:
    // functns going to be declared outside the class!!!
    void getdata();
    void showdata();
    void show_tabular();
    int retrollno();

    //declaring func.!!!
    int roll()
    {
     return(rollno);
    }
  } ; // class 'student'over!!!

   //declaring functns of class 'student'!!!

     void student::getdata()
     {
	student s;
	cout<<"\nEnter the roll no. of student";
	cin>>rollno;
	cout<<"Enter the marks in Physics(on 70):";
	cin>>phy_mark;
	cout<<"Enter the marks in Chemistry(on 70):";
	cin>>che_mark;
	cout<<"Enter the marks in C.S(on 70):";
	cin>>cs_mark;
	cout<<"Enter the marks in English:"  ;
	cin>>eng_mark;
	cout<<"Enter the marks in Maths:" ;
	cin>>mat_mark;

	calculate();
	cout<<"Record created!" ;
	last:
     }

     void student::showdata()
     {
       cout<<"\nRoll no. of student:" <<rollno;
       cout<<"\nName of student:"<<name;
       cout<<"\nMarks in Physics:"<<phy_mark;
       cout<<"\nMarks in Chemistry: "<<che_mark;
       cout<<"\nMarks in English:"<<eng_mark;
       cout<<"\nMarks in C.S:"<<cs_mark;
       cout<<"Percentage is:"<<percnt;
       cout<<"Grade is:"<<grade;
       getch();
     }

     void student::show_tabular()
     {
       cout<<rollno<<"\t";
       for(int sd=0; sd<strlen(name)&&sd<15; sd++)
       cout<<name[sd];

       if(strlen(name)<=6)
       cout<<"\t";
       cout<<phy_mark<<che_mark<<eng_mark<<mat_mark<<cs_mark<<percnt<<grade<<endl;
     }

     int student::retrollno()
     {
     return rollno;
     }
      
    //more functns!!!
     void write_student();
     void display_all();
     void display_sp(int);
     void modify_student(int);
     void delete_student(int);
     void class_result(); 
     void result();
     void intro();
     void entry_menu();

// starting main func!!!

int main()
{
  s:
  char ch;
  cout.setf(ios::fixed|ios::showpoint);
  cout<<setprecision(2);
  clrscr();
  intro();

    do
      {
       clrscr();
       cout<<"\n\n\tMENU";
       cout<<"\n\t1.RESULT MENU";
       cout<<"\n\t2.ENTRY/EDIT MENU";
       cout<<"\n\t3.CLEAR ALL RECORDS!\n\t";  cout<<"Exit";

       cout<<"\n\n\tCHOOSE YOUR CHOICE(1-3)";
       cin>>ch;
       clrscr();

	switch(ch)
	{
	   case '1': result();
		break;
	   case '2': entry_menu();
		break;
	   case '3': remove("student.dat");
	      cout<<"\n\n\tAll Records Deleted!";
	      getch();
	      break;
	   case '4':
		      break;
		  default:cout<<"a";
	}
      }while(ch!='4');

       return(0);
}//End of main()!!!

//declaring the functns declared before starting of main()!!!

  void write_student()
  {
    student st;
    ofstream outfile;
    outfile.open("student.dat",ios::binary|ios::app); 
    st.getdata(); 

    outfile.write((char*)&st, sizeof(student));
    getch();
  }
   
  void display_all()
  { 
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);

    if(!infile)
    {
     cout<<" file could not be open !!press any key..."; 
     getch();
     return;
    } 
     
     cout<<"Display all records!";

    while(!infile.eof())
    {
       infile.read((char*)&st,sizeof(student));
    
      if(infile.eof()||!infile) 
       break;
      st.showdata();

      cout<<"\n\n\t==================\n\n" ;
  }
   
  void display_sp(int n)
  {
    student st;
    ifstream infile;
    infile.open("student.dat", ios::binary);
    
    if(!infile)
    {
      cout<<"File could not be opened!!! Press any key!";
       getch()
       return();
    }

          int cpy=0;
      while(infile.read((char*)&st,sizeof(student)))
      {
          if(st.retrollno()==n)
          {
            st.showdata();
            cpy=1;
          } 
      }

     infile.close();
     if(cpy==0)
     cout<<"\n\nRecord does not exist";
     getch();
  }

  void modify_student(int n)
  {
   int found=0;
   student st; 
   
   fstream file; 
   file.open("student.dat",ios::binary|ios::in|ios::out);
   if(!file)
   {
     cout<<"File could'nt be opened!";
     getch();
   }

   while(file.read((char*)&st,sizeof(student)&&found==0)
   {
     if(st.retrollno()==n)
     {
        st.showdata();
        cout<<"\nPlease enter the new details of the student"<<endl;
        st.getdata();
        int pos=(-1)*sizeof(st);
        file.seekp(pos,ios::cur);
         file.write((char*)&st, sizeof(student));

         cout<<"Record updates!";
               found=-1;

     }
   }
   file.close();
   if(found==0)
   cout<<"\n\nRecord not found";
   getch();
  }


  void delete_student(int n)
  {
    int flag=0; 
    student st; 
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
      cout<<"File could not be opened... Press any key!";
      getch();
      return; 
    } 
    
    ofstream outfile; 
    outfile.open("temp.dat",ios::out|ios::binary);
    infile.seekg(0,ios::beg); 
   
    while(!infile.eof())
     { 
      infile.read((char*)&st, sizeof(student));
      if(infile.eof())
      break; 
    
      if(st.retrollno()!=n)
      {
       outfile.write((char*)&st,sizeof(student));
      }
      else if(st.retrollno()==n) 
      {  
       flag=1;
      }
     }
    outfile.close();
    infile.close();

    remove("student.dat");
    rename("temp.dat","student.dat");
    if(flag==1)
    cout<<"\n\nRecord deleted!";
    else 
    cout<<"\n\nNo record found";
    getch();
  }
  
  void class_result() 
  {
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);  
    if(!infile)
    {
       cout<<"File could not be opened... Press any key!";
       getch();
       return; 
    }

    cout<<"All students result!";
    cout<<"===================";
    cout<<"R.No\tName\tPhy\tChem\tMath\tEng\tC.S\tPercentage\tGrade"<<endl;
    cout<<"===================";
   
    while(infile.read((char*)&st, sizeof(student)))
    { st.show_tabular();
    } 
     cout<<"===================";
    getch(); 
    infile.close(); 
  } 

  void result()
  {
    char ch; int rno;
    cout<<"\n\n\tResult menu";
    cout<<"\n\n\t1.Class Result";
    cout<<"\n\n\t2.Student Report Card";
    cout<<"\n\n\t3.Back to Main Menu";
    cout<<"\n\n\tEnter your choice(1-3)...";
    cin>>ch;

      switch(ch)
      {
        case '1': class_result();
                  break;

        case '2': cout<<"\n\n\tEnter roll no. of student:";
                  cin>>rno;
                  display_sp(rno);
                  break;
        case '3': break;
                  default: cout<<"\a";
      }     
   }

  void entry_menu()
  {
    char ch; 
    int num;
    clrscr(); 

    cout<<"\n\n\t Entry Menu"; 
    cout<<"\n\n\t1.Create Student Record"; 
    cout<<"\n\n\t2.Display all Student Records";
    cout<<"\n\n\t3.Search Student Record";
    cout<<"\n\n\t4.Modify Mtudent Record";
    cout<<"\n\n\t5.Delete Student Record";
    cout<<"\n\n\t6.Back to Main Menu";

    cout<<"Enter your choice";
    cin>>ch;

     switch(ch)
     {
        case '1': write_student();
                  break; 
        case '2': display_all();
                  break; 
        case '3': cout<<"\n\tPlease enter the roll no:";
                  cin>>num;
                  display_sp(num);
                  break;
        case '4': cout<<"\n\n\tPlease enter the roll no."; 
                  cin>>num;
                  modify_student(num);  
                  break;
        case '5': cout<<"\n\n\tPlease enter the roll no.";
                  cin>>num;
                  delete_student(num);
                  break;
        case '6': break;
                  default: cout<<"\a";
                  entry_menu();
     }
  }// End of all functns!!!

// End of program!!!
    
