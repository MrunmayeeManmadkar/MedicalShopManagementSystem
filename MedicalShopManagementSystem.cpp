/*************************************************************************
                 MEDICAL SHOP MANAGEMENT SYSTEM

Problem statement : C++ mini project to manage the medical shop as an admin as well as
         buy medicines as required by the customer on priority basis too!

GROUP MEMBERS:2411-MRUNMAYEE MANMADKAR
              2410-SEJAL MANGAVE
              2415-SANYUKTA MULEY
              2419-PRACHI NARLAWAR
*************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
/*.....................................................................*/
class a_node                             //create a class node
{
    int Med_ID;                          //info of each medicine
    string Med_Name;
    float Med_Price;
    string Med_Expiry;                   //This is a node class of a LL of medicines on which
    int Med_Quantity;                    //the admin wants to perform different functions.

    a_node * next;

public:
    friend class Admin;                  //friend class for admin and customer to access members of this class
    friend class Customer;
    a_node()                             //initialize all variables
    {
                                         //initialize link to Null
    }
    a_node(int mid, string mname, float mprice, string mexpiry, int mquantity)
                                         //paramertized constructor
    {
        this -> Med_ID = mid;            //this keyword points to variabe in this particular class
        this -> Med_Name = mname;
        this -> Med_Price = mprice;
        this -> Med_Expiry = mexpiry;
        this -> Med_Quantity = mquantity;
        next = NULL;
    }

};
/*.....................................................................*/
class Admin                              //create class list
{
public:
    a_node * head;                      //first node
    a_node * temp;                     //last node
    a_node * create();
    void insert();                      //function declarartion
    void delet();                       //operations admin wants to perform on the medicine stock
    void display();
    int Update(string m, int Q, int fl);
    void count();
    string set_pass();
    int Date_valid(int,int);
    int Expiry_valid(string);
    Admin()
    {
        head=NULL;
        temp = NULL;                     //initilizing the pointers
    }
};
/*.....................................................................*/
a_node *Admin::create()                 //create Linked List
{
    int ch = 0;
    int mid, mquantity,month,year,x=0;
    string mname, mexpiry;
    float mprice;
    do
    {
        cout<<"Enter Medicine details\n"<<endl;
        cout << "Enter Medicine ID :";
        cin >> mid;
        cout << "Enter Medicine Name :";  //accepting the details of medicine
        cin>>mname;
        cout << "Enter Price :";
        cin >> mprice;
        cout << "Enter Expiry month<space>year :";
        cin >>month>>year;
        mexpiry=(to_string(month)+"/"+to_string(year));
        x=Date_valid(month,year);
        while(x!=1)
        {
            cout<<"Invalid date!\n";
            cout << "Enter Expiry month<space>year again : ";
            cin >>month>>year;
            mexpiry=(to_string(month)+"/"+to_string(year));
            x=0;
            x=Date_valid(month,year);
        }
        cout << "Enter Quantity :";
        cin >> mquantity;
        a_node * newnode = new a_node(mid, mname, mprice, mexpiry, mquantity);
        if (head == NULL)               //passing these to initilize through constructor
        {
            head = newnode;
            temp = newnode;             //for first node
        }
        else
        {
            temp -> next = newnode;
            temp = newnode;             //for any other node
        }
        cout << "\nContinue to enter the stock Yes-1 No-0 : ";
        cin >> ch;
        cin.ignore();
    }while (ch == 1);                   //for creating LL with more than one medicinee
    return head;
}
/*.....................................................................*/
int Admin::Date_valid(int month,int year)
{
    int flag=0;
    if(year>2000 && year<2050)
    {
        if(month>=01 && month<=12)
        {
            flag=1;
        }
    }
    return flag;
}
/*.....................................................................*/
void Admin::display()                  //display the data
{
    int flag=0;
    int x;
    a_node * ptr = head;
    cout<<"\n-------------------------------------------------------------------------\n";
    if (ptr != NULL)
    {
        cout<<"\nMedicine_ID\tMedicine_Name\tPrice\tExpiry_Date\tQuantity\n";
        cout<<"\n-------------------------------------------------------------------------\n";
        while (ptr != NULL)
        {
            cout << ptr->Med_ID << "\t\t" << ptr->Med_Name << "\t\t" << ptr->Med_Price << "\t"
            << ptr->Med_Expiry << "\t\t" << ptr-> Med_Quantity << endl;
            ptr = ptr -> next;
        }
        ptr=head;
        cout<<"\n-------------------------------------------------------------------------\n";
        cout<<"EXPIRED MEDICINE INFORMATION : \n";
        while(ptr!=NULL)
        {
            x=Expiry_valid(ptr->Med_Expiry);
            if(x==1)
            {
                cout << ptr->Med_ID << "\t\t" << ptr->Med_Name << "\t\t" << ptr->Med_Price << "\t"
                << ptr->Med_Expiry << "\t\t" << ptr-> Med_Quantity << endl;
                flag=1;
            }
            ptr = ptr -> next;
        }
        if(flag==0)
        {
            cout<<"\nNo Medecine is expired\n";
        }
    }
    else
    {
        cout << "\nStock is empty \n";  //for no medicine present
    }
        cout<<"\n-------------------------------------------------------------------------\n";
}
/*.....................................................................*/
int Admin::Expiry_valid(string mexpiry)
{
    int month1=0,f=0;
    int year1=0;
    month1=stoi(mexpiry.substr(0,2));
    year1=stoi(mexpiry.substr(2,6));
    if(year1<=2020)
    {
        f=1;
    }
    else if(year1==2021 && month1<5)
    {
        f=1;
    }
    else
    {
        f=0;
    }
    return f;
}
/*.....................................................................*/
void Admin::insert()                    //insert new node
{
    a_node * temp = head;
    int mid, mquantity,month,year,x=0;
    string mname, mexpiry;
    float mprice;

    cout<<"Enter Medicine details\n"<<endl;  //input information of medicine
    cout << "Enter Medicine ID : ";
    cin >> mid;
    cout << "Enter Medicine Name : ";
    cin>>mname;
    cout << "Enter Price : ";
    cin >> mprice;
    cout << "Enter Expiry month<space>year :";
        cin >>month>>year;
        mexpiry=(to_string(month)+"/"+to_string(year));
        x=Date_valid(month,year);
        while(x!=1)
        {
            cout<<"Invalid date!\n";
            cout << "Enter Expiry month<space>year again : ";
            cin >>month>>year;
            mexpiry=(to_string(month)+"/"+to_string(year));
            x=Date_valid(month,year);
        }
    cout << "Enter Quantity : ";
    cin >> mquantity;
    a_node * newnode = new a_node(mid, mname, mprice, mexpiry, mquantity);
                                        //passing these to initilize through constructor
    if (head != NULL)
    {
        while (temp -> next != NULL)
        {
            temp = temp -> next;        //for node at any position
        }
        temp -> next = newnode;
    }
    else if (head == NULL)
    {
        head = newnode;                 //for node at first position
    }
    cin.ignore();
    cout << "\nNew medicine is sucessfully being added to your stock !"<<endl;
    cout << "\nAfter Insertion : "<<endl;
    display();                         //to display the medicines added
}
/*.....................................................................*/
void Admin::delet()                        //delete the node of given Medicine ID
{
        int flag = 0;
        a_node * temp = head, * t = NULL;
        int id;
        cout << "Enter ID of the medicine to delete :";
        cin >> id;
        while (temp != NULL)
        {
            if (id == temp -> Med_ID)
            {                             //for traversing till that node using ID,for deleting
                flag = 1;
                break;
            }
            t = temp;
            temp = temp -> next;
        }   //end while
        if (flag == 1 && head != NULL)   //setting of flag==1 says that the node is found
        {
            a_node * ptr = temp;
            if (temp == head)
            {                            //if its the first node
                head = head -> next;
                delete(ptr);
            }
            else
            {
                t -> next = temp -> next;   //for any other node
                delete(ptr);
            }
            cout << "\nDisplay After deletion : \n";
            display();
        }  //end if
        else if (head == NULL && flag == 0)  //as flag is zero medicine is not found
        {
            cout <<"\nOops Nothing is there in the stock...Can't delete this medicine\n";
        }//end else if
        else if (flag == 0 && head != NULL)
        {
            cout << "\nYou Entered wrong details \n";
        } //end else if
}
/*.....................................................................*/
int Admin::Update(string m, int Q, int fl) //update medicine stock
{
    int flag = 0;
    if (head != NULL)
    {
        a_node * ptr = head;
        while (ptr != NULL)
        {
            if (ptr -> Med_Name == m)
            {
                flag = 1;
                break;
            }
            ptr = ptr -> next;
        }
        if (flag == 1)
        {
            if (fl == 0)                 //fl stands for flag to decrease/increase the quantity of medicine
                ptr -> Med_Quantity = ptr -> Med_Quantity - Q;            //passed from customer
            else if (fl == 1)
                ptr -> Med_Quantity = ptr -> Med_Quantity + Q;            //adding for purpose of updation by admin
        }
    }
    return flag;
}
/*.....................................................................*/
void Admin::count()                      //to count the types of medicine available
{
    a_node * t = head;
    int count = 0;
    while (t != NULL)
    {
        count++;
        t = t -> next;
    }
    cout << "\n There are " << count << " types of medicines are available \n";
}
/*.....................................................................*/
string Admin::set_pass()
{
    string Password="password";            //setting password
    return Password;
}
/*.....................................................................*/
class c_node                              //details of medicine customer wants to buy
{
    string Cust_MedName;                  //LL for storing this info
    int cust_quantity;
    float Med_Rate;
    float Med_price;
    c_node * next;
    public:
    friend class Customer;
    friend class Cart;
    c_node(string Buy_MedName, int custQuantity,float med_price,float Med_Rate)
    {
        this -> Cust_MedName = Buy_MedName;     //initilizing
        this -> cust_quantity = custQuantity;
        this-> Med_price=med_price;
        this-> Med_Rate=Med_Rate;
        this -> next = NULL;
    }
};
/*.....................................................................*/
class Cart                                      //cart using stack for storing medicines bought by Customer
{
    c_node * top;
public:
    friend class Customer;
    Cart()
    {
        top = NULL;
    }
    int isEmpty();
    void push_med(string Buy_MedName, int custQuantity,float med_price,float Med_Rate);
    float display_cart();
    void pop_med();
};
/*.....................................................................*/
int Cart::isEmpty()
{
    if(top==NULL)
    {
        return 1;
    }
    else
    return 0;
}
/*.....................................................................*/
void Cart::push_med(string Buy_MedName, int custQuantity,float med_price,float Med_Rate)
{
    c_node * newnode = new c_node(Buy_MedName, custQuantity,med_price,Med_Rate);
    if (top == NULL)
    {
        top = newnode;
    }
    else
    {
        newnode -> next = top;
        top = newnode;
    }
}
/*.....................................................................*/
void Cart::pop_med()
{
    if(isEmpty())
    {
        cout<<"\nCart is Empty"<<endl;
    }
    else
    {
        c_node *ptr=top;
        top=top->next;
        delete ptr;
    }
}
/*.....................................................................*/
float Cart::display_cart()
{
    c_node * ptr = top;
    float tot_amount=0;
    cout<<"----------------------------------------------------"<<endl;
    cout << "\nMedicine_Name" << "\t" << "Quantity" << "\t"<<"Rate"<<"\t"<<"Amount"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    while (ptr != NULL)
    {
        cout << ptr -> Cust_MedName << "\t\t" << ptr -> cust_quantity <<"\t\t Rs."<<ptr->Med_price <<"\t"<< ptr->Med_Rate<<endl;
        tot_amount+=ptr->Med_Rate;
        ptr = ptr -> next;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"The Final paying amount is : Rs."<<tot_amount<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"\n";
    return tot_amount;
}
/*.....................................................................*/
class q_node
{
    string cust_name;
    string Ph_no;
    q_node * next;
public:
    friend class wait_queue;
    friend class Customer;
    q_node()
    {
        next = NULL;
    }
    q_node(string cust_name, string Ph_no)
    {
        this -> cust_name = cust_name;
        this -> Ph_no = Ph_no;
        next = NULL;
    }
};
/*..................................................................... */
class wait_queue
{
    q_node * front;
    q_node * rear;
    public:
    wait_queue()
    {
        front = NULL;
        rear = NULL;
    }
    int IsEmpty();
    void Enque_Cust(string, string);
    q_node * Deque_Cust();
    int Display_wq();
    void Priority();
    friend class Customer;

};
/*..................................................................... */
int wait_queue::IsEmpty()
{
    if (front == NULL && rear == NULL)
        return 1;
    else
        return 0;

}
/*..................................................................... */
void wait_queue::Enque_Cust(string name, string pno)
{
    q_node * newnode = new q_node(name, pno);
    if (IsEmpty())
    {
        rear = newnode;
        front = newnode;
    }
    else
    {
        rear -> next = newnode;
        rear = newnode;
    }
}
/*..................................................................... */
void wait_queue ::Priority()
{

    q_node * temp=front;
    q_node *ptr=rear;
    while(temp->next!=rear)
    {
        temp=temp->next;
    }

    ptr->next=front;
    temp->next=NULL;
    front=ptr;
    rear=temp;

}
/*..................................................................... */
int wait_queue::Display_wq()
{
    int count=0;
    if (IsEmpty())
    {
        cout << "\nNo customer :(" << endl;
    }
    else
    {
        q_node * ptr = front;
        cout<<"\nWaiting Queue\n"<<endl;
        cout<<"-----------------------------------"<<endl;
        cout<<" Name "<<" Mobile Number"<<endl;
        cout<<"-----------------------------------"<<endl;
        while (ptr != NULL)
        {
          cout << ptr -> cust_name << "\t" << ptr -> Ph_no << endl;
          count++;
          ptr = ptr -> next;
        }
        cout<<"-----------------------------------"<<endl;
    }
    return count;
}
/*..................................................................... */
q_node* wait_queue::Deque_Cust()
{
    if (IsEmpty())
    {
        cout << "\nNo Customer wants to buy" << endl;
    }
    else if (front == rear)
    {
        q_node * ptr = front;
        front = NULL;
        rear = NULL;
        return ptr;
    }
    else
    {
        q_node * ptr = front;
        front = front -> next;
        return ptr;
    }
}
/*.....................................................................*/
class Customer
{
    Cart C;
    wait_queue wq;
    float Tot_Earning=0;
 public:
    int search(a_node * head, string Buy_MedName);
    void Buy(a_node * head, Admin l);
    int accept();
    float Billing();
    void empty_Cart();
    friend class wait_queue;
};
/*.....................................................................*/
int Customer::accept()
{
    string name;
    int count1;
    string pno;
    int ch;
    int s=0;
    int flag=1;
    do
    {
        cout<<"Enter your details\n"<<endl;
        cout << "Enter Your Name :";
        cin>>name;
        cout << "Enter Your Contact No :";
        cin >> pno;
        while(flag!=0)
        {
            if((pno.length()==10) && (pno[0]=='9' || pno[0]=='8' || pno[0]=='7'))
            {
                flag=0;
            }
            else
            {
                cout<<"Invalid Contact number !"<<endl;
                cout<<"Enter Valid Contact number : ";
                cin >> pno;
            }
        }

        cout<<"Do you need medicine on urgent basis? Yes-1,No-0 : "; //implementing priority queue for urgent
        cin>>s;                                                   //requirement of medicine
        if(s!=1)
            wq.Enque_Cust(name, pno);
        else if(s==1)
        {
            if(wq.front==NULL)
                wq.Enque_Cust(name, pno);
            else if(wq.front!=NULL)
            {
                wq.Enque_Cust(name, pno);
                wq.Priority();
            }
        }

        cout <<"\nDo you want to continue to add customer? Yes-1,No-0 : ";
        cin >> ch;
        cin.ignore();
        flag=1;
    }while (ch != 0);
    count1=wq.Display_wq();

    return count1;
}
/*......................................................................*/
int Customer::search(a_node * head, string Buy_MedName)
{
    a_node * temp = head;
    a_node * t;
    int flag = 0, ans;
    while (temp != NULL)
    {
        if (Buy_MedName == temp -> Med_Name)
        {
          flag = 1;
          break;
        }
        t = temp;
        temp = temp -> next;
    }
    if (flag == 1)
    {
        cout << "MEDICINE IS AVAILABLE" << endl;
        cout << "Do you want to Buy? Yes-1 No-0 : ";
        cin >> ans;
        return ans;
    }
    else
    {
        cout << "MEDICINE IS NOT AVAILABLE" << endl;
        return -1;
    }
}
/*.....................................................................*/
void Customer::Buy(a_node * head,Admin l)
{
    int custQuantity;
    int ans1,option;
    float Med_Rate;
    float med_price;
    a_node * ptr = head;
    a_node * ptr1=NULL;
    string Buy_MedName;
    cout << "Type the name of medicine you want to buy : ";
    cin >> Buy_MedName;
    ans1 = search(head, Buy_MedName);
    if (ans1 == 1)
    {
        while (ptr != NULL)
        {
            if (Buy_MedName == ptr -> Med_Name)
            {
                cout << "Medicine Name :" << ptr-> Med_Name << endl;
                cout << "Price :" << ptr-> Med_Price << endl;
                cout << "Expiry :" << ptr-> Med_Expiry << endl;
                med_price=ptr->Med_Price;
                ptr1=ptr;
                break;
            }
            ptr = ptr -> next;
        }
        cout << "Enter Quantity of medicine : ";
        cin >> custQuantity;
        if(ptr->Med_Quantity==0)
        {
            cout<<"MEDICINE IS NOT AVAILABLE"<<endl;
            cout<<"We'll let you know when the stock is Available !"<<endl;
        }
        else if(ptr->Med_Quantity<custQuantity)
        {
            cout <<"Available Quantity of medicine :" <<ptr->Med_Quantity<<endl;
            cout <<"Do you want to buy the Available Quantity? Yes-1 No-0 : ";
            cin>>option;
            if(option==1)
            {
                custQuantity=ptr1->Med_Quantity;
            }
            else
            {
                custQuantity=0;
            }
        }
        l.Update(ptr1->Med_Name,custQuantity,0);
        Med_Rate=(custQuantity*med_price);
        if(custQuantity!=0)
        {
            C.push_med(Buy_MedName, custQuantity,med_price,Med_Rate);
        }
        cout << "Do you want to buy any other medicine? Yes-1 No-0 : ";
        int ch1;
        cin >> ch1;
        if (ch1 == 1)
        {
          Buy(head,l);
        }

    }
    else
    {
        cout << "Do you want to buy any other medicine? Yes-1 No-0 : ";
        int ch1;
        cin >> ch1;
        if (ch1 == 1)
        {
          Buy(head,l);
        }
    }
}
/*..................................................................... */
void Customer::empty_Cart()
{
    while(!C.isEmpty())
    {
        C.pop_med();
    }
}
/*..................................................................... */
float Customer::Billing()
{
    float Tot_amount=0;
    q_node * deq = wq.Deque_Cust();
    if(C.isEmpty())
    {
        cout<<"\nCustomer did not buy anything"<<endl;
    }
    else
    {
        cout<<"___________________________________________________________________________\n"<<endl;
        cout<<"                          WELLNESS MEDICAL SHOP"<<endl;
        cout<<"                           Phone No:(020)224466"<<endl;
        cout<<"___________________________________________________________________________\n"<<endl;
        cout<<"                             \nCustomer's Bill \n";
        cout<<"Customer Name : "<<deq->cust_name<<endl;
        cout<<"Customer Mob. No. : "<<deq->Ph_no<<endl;
        cout<<"\n";
        cout<<"Reciept :\n";
        Tot_amount=C.display_cart();
        cout<<"Thank You !!"<<endl;
        cout<<"____________________________________________________________________________\n"<<endl;
        empty_Cart();
    }
        Tot_Earning+=Tot_amount;
        return Tot_Earning;
}
/*..................................................................... */

int main()
{
    int flag=0;
    int ch;
    int count2;
    int i=0;
    a_node* head;
    Admin l; //object of Admin class
    Customer c;
    string password;
    float Earning=0;
    int cho,choice=0;
    int ans;
        cout<<"\n";
        cout<<"                 MEDICAL SHOP MANAGEMENT SYSTEM           ";
    do
    {
        cout<<"\n\n";
        cout<<"---------------------------------------------------------------"<<endl;
        cout<<"|                            1.Admin                           |"<<endl;
        cout<<"|                            2.Customer                        |"<<endl;
        cout<<"|                            3.Exit                            |"<<endl;
        cout<<"---------------------------------------------------------------"<<endl;
        cout<<"\nEnter your choice : ";
        cin>>choice;
        cout<<"\n";
        switch(choice)
        {
            case 1:
            {
                int count=1;
                flag=1;
                cout<<"Enter the password for performing operations : ";
                cin>>password;
                for(int i=0;i<2;i++)
                {
                    if(password==l.set_pass())
                    {
                        cout<<"You have successfully logged in!"<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"Enter correct Password : ";
                        cin>>password;
                        count++;
                    }
                }
                if(count==3)
                {
                    cout<<"Incorrect Password entered."<<endl;
                    cout<<"Try again later."<<endl;
                    break;
                }
                do
                {
                    cout<<"\n";
                    cout<<"\t\t\t  ****MENU****  \n"<<endl;
                    cout<<"\t\t\t1.Accept Medicines"<<endl;
                    cout<<"\t\t\t2.Display Medicines list"<<endl;
                    cout<<"\t\t\t3.Insert new Medicine"<<endl;
                    cout<<"\t\t\t4.Delete Medicine"<<endl;
                    cout<<"\t\t\t5.Update Medicine"<<endl;
                    cout<<"\t\t\t6.Types of Medicines"<<endl;
                    cout<<"\t\t\t7.Display Total Earning"<<endl;
                    cout<<"Enter the choice : ";
                    cin>>cho;
                    cout<<"\n";

                    switch(cho)
                    {
                        case 1:head=l.create();
                        break;
                        case 2:cout<<"\nDATABASE OF MEDICINES\n"<<endl;
                               l.display();
                        break;
                        case 3:l.insert();
                        break;
                        case 4:l.delet();
                        break;
                        case 5:
                        {
                            int Q,fl=0,flag=0;
                            string mdel;
                            cout<<"Enter medicine name : ";
                            cin>>mdel;
                            cout<<"Enter quantity to update : ";
                            cin>>Q;
                            cout<<"YOU want to increase or decrease the quantity 0-Decrease / 1-Increase : ";
                            cin>>fl;
                            flag=l.Update(mdel,Q,fl);
                            if(flag==1)
                            {
                                cout<<"Your stock is successfully updated."<<endl;
                                cout<<"Stock after updation."<<endl;
                                cout<<"\nDATABASE OF MEDICINES\n"<<endl;
                                l.display();
                            }
                            else
                            {
                                cout<<"Medicine not found."<<endl;
                                cout<<"Updation not required."<<endl;
                            }
                        }
                        break;
                        case 6:l.count();
                        break;
                        case 7: cout<<"Total Earning : Rs."<<Earning<<endl;
                        break;
                        default:cout<<"Enter Valid Option!!";
                    }
                    cout<<"\nWould you like to continue as an Admin ? if Yes-1 No-0 : ";
                    cin>>ans;
                }while(ans==1);
            }
            break ;
            case 2 :
            {
                if(flag==1)
                {
                    cout<<"------------------------------------------------------------------------"<<endl;
                    cout<<"|                    WELCOME TO OUR MEDICAL SHOP                        |"<<endl;
                    cout<<"------------------------------------------------------------------------"<<endl;
                    count2=c.accept();
                    while(i<count2)
                    {
                        cout<<"\n\nTurn of Customer "<<i+1<<endl;
                        c.Buy(head,l);
                        cout<<"BILL OF CUSTOMER: "<<i+1<<endl;
                        Earning=c.Billing();
                        i++;
                    }

                }
                else
                {
                    cout<<"\nShop is Closed."<<endl;
                    cout<<"Come Later\n"<<endl;
                }
            }
            break;
            case 3:cout<<"Exit"<<endl;
            break;
            default:cout<<"Wrong choice !!";
        }
        cout<<"Do you want to leave the shop? if (yes-1 ,No-0) : ";
        cin>>ch;
    }while(ch==0);
}
/************************************************************************************
Output :-
MEDICAL SHOP MANAGEMENT SYSTEM          

---------------------------------------------------------------
|                            1.Admin                           |
|                            2.Customer                        |
|                            3.Exit                            |
---------------------------------------------------------------

Enter your choice : 2


Shop is Closed.
Come Later

Do you want to leave the shop? if (yes-1 ,No-0) : 0


---------------------------------------------------------------
|                            1.Admin                           |
|                            2.Customer                        |
|                            3.Exit                            |
---------------------------------------------------------------

Enter your choice : 1

Enter the password for performing operations : pass
Enter correct Password : password
You have successfully logged in!

 ****MENU****  

1.Accept Medicines
2.Display Medicines list
3.Insert new Medicine
4.Delete Medicine
5.Update Medicine
6.Types of Medicines
7.Display Total Earning
Enter the choice : 1

Enter Medicine details

Enter Medicine ID :1234
Enter Medicine Name :crocin
Enter Price :23.34
Enter Expiry month<space>year :05 2022
Enter Quantity :100

Continue to enter the stock Yes-1 No-0 : 0

Would you like to continue as an Admin ? if Yes-1 No-0 : 1

 ****MENU****  

1.Accept Medicines
2.Display Medicines list
3.Insert new Medicine
4.Delete Medicine
5.Update Medicine
6.Types of Medicines
7.Display Total Earning
Enter the choice : 2


DATABASE OF MEDICINES


-------------------------------------------------------------------------

Medicine_ID Medicine_Name Price Expiry_Date Quantity

-------------------------------------------------------------------------
1234 crocin 23.34 5/2022 100

-------------------------------------------------------------------------
EXPIRED MEDICINE INFORMATION :

No Medecine is expired

-------------------------------------------------------------------------

Would you like to continue as an Admin ? if Yes-1 No-0 : 0
Do you want to leave the shop? if (yes-1 ,No-0) : 0


---------------------------------------------------------------
|                            1.Admin                           |
|                            2.Customer                        |
|                            3.Exit                            |
---------------------------------------------------------------

Enter your choice : 2

------------------------------------------------------------------------
|                    WELCOME TO OUR MEDICAL SHOP                        |
------------------------------------------------------------------------
Enter your details

Enter Your Name :priya
Enter Your Contact No :9876543218
Do you need medicine on urgent basis? Yes-1,No-0 : 1

Do you want to continue to add customer? Yes-1,No-0 : 1
Enter your details

Enter Your Name :riya
Enter Your Contact No :9876543213
Do you need medicine on urgent basis? Yes-1,No-0 : 0

Do you want to continue to add customer? Yes-1,No-0 : 0

Waiting Queue

-----------------------------------
 Name  Mobile Number
-----------------------------------
priya 9876543218
riya 9876543213
-----------------------------------


Turn of Customer 1
Type the name of medicine you want to buy : crocin
MEDICINE IS AVAILABLE
Do you want to Buy? Yes-1 No-0 : 1
Medicine Name :crocin
Price :23.34
Expiry :5/2022
Enter Quantity of medicine : 10
Do you want to buy any other medicine? Yes-1 No-0 : 0
BILL OF CUSTOMER: 1
___________________________________________________________________________

                          WELLNESS MEDICAL SHOP
                           Phone No:(020)224466
___________________________________________________________________________

                             
Customer's Bill
Customer Name : priya
Customer Mob. No. : 9876543218

Reciept :
----------------------------------------------------

Medicine_Name Quantity Rate Amount
----------------------------------------------------
crocin 10 Rs.23.34 233.4
----------------------------------------------------
The Final paying amount is : Rs.233.4
----------------------------------------------------

Thank You !!
____________________________________________________________________________



Turn of Customer 2
Type the name of medicine you want to buy : crocin
MEDICINE IS AVAILABLE
Do you want to Buy? Yes-1 No-0 : 1
Medicine Name :crocin
Price :23.34
Expiry :5/2022
Enter Quantity of medicine : 10
Do you want to buy any other medicine? Yes-1 No-0 : 0
BILL OF CUSTOMER: 2
___________________________________________________________________________                               

                          WELLNESS MEDICAL SHOP
                           Phone No:(020)224466
___________________________________________________________________________

                             
Customer's Bill
Customer Name : riya
Customer Mob. No. : 9876543213

Reciept :
----------------------------------------------------

Medicine_Name Quantity Rate Amount
----------------------------------------------------
crocin 10 Rs.23.34 233.4
----------------------------------------------------
The Final paying amount is : Rs.233.4
----------------------------------------------------

Thank You !!
____________________________________________________________________________

Do you want to leave the shop? if (yes-1 ,No-0) : 0


---------------------------------------------------------------
|                            1.Admin                           |
|                            2.Customer                        |
|                            3.Exit                            |
---------------------------------------------------------------

Enter your choice : 1

Enter the password for performing operations : password
You have successfully logged in!

 ****MENU****  

1.Accept Medicines
2.Display Medicines list
3.Insert new Medicine
4.Delete Medicine
5.Update Medicine
6.Types of Medicines
7.Display Total Earning
Enter the choice : 5 2


DATABASE OF MEDICINES


-------------------------------------------------------------------------

Medicine_ID Medicine_Name Price Expiry_Date Quantity

-------------------------------------------------------------------------
1234 crocin 23.34 5/2022 80

-------------------------------------------------------------------------
EXPIRED MEDICINE INFORMATION :

No Medecine is expired

-------------------------------------------------------------------------

Would you like to continue as an Admin ? if Yes-1 No-0 : 0 6
Do you want to leave the shop? if (yes-1 ,No-0) : 0


---------------------------------------------------------------
|                            1.Admin                           |
|                            2.Customer                        |
|                            3.Exit                            |
---------------------------------------------------------------

Enter your choice : 1

Enter the password for performing operations : password
You have successfully logged in!

 ****MENU****  

1.Accept Medicines
2.Display Medicines list
3.Insert new Medicine
4.Delete Medicine
5.Update Medicine
6.Types of Medicines
7.Display Total Earning
Enter the choice : 6


 There are 1 types of medicines are available

Would you like to continue as an Admin ? if Yes-1 No-0 : 1

 ****MENU****  

1.Accept Medicines
2.Display Medicines list
3.Insert new Medicine
4.Delete Medicine
5.Update Medicine
6.Types of Medicines
7.Display Total Earning
Enter the choice : 7

Total Earning : Rs.466.8

Would you like to continue as an Admin ? if Yes-1 No-0 : 0
Do you want to leave the shop? if (yes-1 ,No-0) : 1

************************************************************************************/
