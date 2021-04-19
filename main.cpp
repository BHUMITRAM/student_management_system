#include <iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
using namespace std;
void enter(MYSQL* conn)
{
  int qstate=0;
  stringstream ss;
 cout<<"enter roll no"<<endl;
  int roll;
  cin>>roll;
  cout<<"enter student name"<<endl;
  string name;
  cin>>name;
  cout<<"enter course"<<endl;
  string course;
  cin>>course;
  cout<<"enter semester"<<endl;
  int sem;
  cin>>sem;
  cout<<"enter contact no"<<endl;
  string contact;
  cin>>contact;
  cout<<"enter email id"<<endl;
  string email;
  cin>>email;
  ss<<"INSERT INTO student (ROLL,NAME,COURSE,SEMESTER,CONTACT,EMAIL) VALUES('"<<roll<<"','"<<name<<"','"<<course<<"','"<<sem<<"','"<<contact<<"','"<<email<<"')";
  string query=ss.str();
  const char* q=query.c_str();
  qstate=mysql_query(conn,q);
  if(qstate==0)
     cout<<"record inserted"<<endl;
  else
     cout<<"failed to insert"<<endl;
}
void show(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn)
    {
        int qstate=mysql_query(conn,"SELECT * FROM student");
        if(!qstate)
        {

            res=mysql_store_result(conn);
            int count=mysql_num_fields(res);
            while(row=mysql_fetch_row(res))
            {
                for(int i=0;i<count;i++)
                    cout<<"\t"<<row[i];
                cout<<endl;
            }

        }

    }
    else
        cout<<"failed to fetch"<<endl;

}
void search(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    cout<<"roll no"<<endl;
    int x;
    cin>>x;
    if(conn)
    {   stringstream ss;
    int qstate;
        ss<<"SELECT * FROM student where ROLL='"<<x<<"'";
        string query=ss.str();
        const char* q=query.c_str();
        qstate=mysql_query(conn,q);
        if(!qstate)
        {
             res=mysql_store_result(conn);
            int count=mysql_num_fields(res);
            while(row=mysql_fetch_row(res))
            {
                for(int i=0;i<count;i++)
                    cout<<"\t"<<row[i];
                cout<<endl;
            }

        }

    }
    else
        cout<<"failed to search"<<endl;
}
void update(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    cout<<"roll no which is to be updated"<<endl;
    int x;
    cin>>x;
    if(conn)
    {   stringstream ss;
        int qstate;
        cout<<"press 1 to update contact"<<endl;
        cout<<"press 2 to update email"<<endl;
        int value;
        cin>>value;
        switch(value)
        {
        case 1:
               {cout<<"enter contact to update"<<endl;
               string c;
               cin>>c;
               ss<<"UPDATE student SET CONTACT='"<<c<<"' where ROLL='"<<x<<"'";
               string query=ss.str();
               const char* q=query.c_str();
               qstate=mysql_query(conn,q);
               if(!qstate)
                   {

                     cout<<"contact updated"<<endl;
                   }
               else
                   cout<<"contact not updated"<<endl;
               }
                break;

         case 2:
               {cout<<"enter email to update"<<endl;
               string c;
               cin>>c;
               ss<<"UPDATE student SET EMAIL='"<<c<<"' where ROLL='"<<x<<"'";
               string query=ss.str();
               const char* q=query.c_str();
               qstate=mysql_query(conn,q);
               if(!qstate)
                  {

                     cout<<"email updated"<<endl;
                   }
               else
                    cout<<"email not updated"<<endl;}
                break;
        }
    }
    else
        cout<<"failed to update"<<endl;
}
void deleterecord(MYSQL* conn)
{
  cout<<"enter roll no to delete"<<endl;
  int roll;
  cin>>roll;
  stringstream ss;
  int qstate=0;
  ss<<"DELETE FROM student WHERE ROLL='"<<roll<<"'";
 string query=ss.str();
 const char* q=query.c_str();
 qstate=mysql_query(conn,q);
 if(!qstate)
                   {

                     cout<<"record deleted"<<endl;
                   }
               else
                   cout<<"record not deleted"<<endl;
}
int main()
{
   MYSQL* conn;
   conn=mysql_init(0);
   cout<<"enter username"<<endl;
   string user;
   cin>>user;
   const char* username=user.c_str();
   cout<<"enter password"<<endl;
   string pass;
   cin>>pass;
   const char* password=pass.c_str();
   const char* database="student";
   conn=mysql_real_connect(conn,"127.0.0.1",username,password,database,0,NULL,0);
   if(conn)
   {
     cout<<"database connected"<<endl;
    int value;
	while(true)
	{
	cout<<"\nPress 1 to enter data"<<endl;
	cout<<"Press 2 to show data"<<endl;
	cout<<"Press 3 to search data"<<endl;
	cout<<"Press 4 to update data"<<endl;
	cout<<"Press 5 to delete data"<<endl;
	cout<<"Press 6 to exit"<<endl;
	cin>>value;
	switch(value)
	{
		case 1:
			enter(conn);
			break;
		case 2:
			show(conn);
			break;
		case 3:
			search(conn);
			break;
		case 4:
			update(conn);
			break;
		case 5:
			deleterecord(conn);
			break;
		case 6:
			exit(0);
			break;
		default:
			cout<<"Invalid input"<<endl;
			break;
	}
  }
}
   else
   {
       cout<<"database not connected"<<endl;
   }
    return 0;
}
