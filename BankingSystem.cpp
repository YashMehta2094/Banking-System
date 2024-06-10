#include <bits/stdc++.h>

using namespace std;

class Node{
    private:
    int AccNo;
    int balance;
    Node* next;
    
    Node(int acc){
        AccNo = acc;
        balance = 1000;
        next = NULL;
    }
    
    friend class SLL;
};

class SLL{
  private:
    Node* first;
    Node* last;
    int len;
  
  public:
    SLL(){
        first = last = NULL;
        len = 0;
    }
  
    void pushNode(int d){
        Node* addNode = new Node(d);
        if(len == 0){
            first = last = addNode;
            len++;
            return;
        }
      
        if(first == last){
          first->next = addNode;
          last = addNode;
          len++;
          return;
        }
        
        last->next = addNode;
        last = addNode;
        len++;
    }
    
    Node* findNode(int acc){
        Node* temp = first;
        while(temp!=NULL){
            if(temp->AccNo == acc){
                return temp;
            }
            temp = temp->next;
        }
        
        return nullptr;
    }
    
    void transaction(int acc, char m, int val){
        Node* processNode = findNode(acc);
        if (m == 'D'){
            processNode->balance = processNode->balance + val;
        }
        
        else if(m == 'W'){
            processNode->balance = processNode->balance - val;
        }
    }
    
    void PrintBalMoreX(int x){
        int count =0;
        Node* temp = first;
        while(temp!=NULL){
            if(temp->balance >= x){
                count++;
            }
            temp = temp->next;
        }
        cout<<count<<endl;
    }
    
    void PrintMaxBalance(){
        int max;
        Node* temp = first;
        max = temp->balance;
        temp = temp->next;
        while(temp!=NULL){
            if(temp->balance > max){
                max = temp->balance;
            }
            temp = temp->next;
        }
        
        temp = first;
        while(temp!=NULL){
            if(temp->balance == max){
                cout<<temp->AccNo<<" ";
            }
            temp = temp->next;
        }
        cout<<endl;
    }
    
    void PrintBalX(int x){
        Node* temp = findNode(x);
        cout<<temp->balance<<endl;
    }
  
};

class Dnode{
    private:
    int Acc;
    char Action;
    int Amount;
    Dnode* next;
    Dnode* prev;
    
    Dnode(int acc = -1, char act = 'A', int val= -1){
        Acc = acc;
        Action = act;
        Amount = val;
        next = NULL;
        prev = NULL;
    }
    
    friend class DLL;
};

class DLL{
    private:
    Dnode* head, *tail, *cursor;
    int dlen, cursoridx;
    
    public:
    DLL(){
        head = new Dnode();
        tail = new Dnode();
        
        head->next = tail;
        tail->prev = head;
        cursor = head;
        dlen = 0;
        cursoridx = 0;
    }
    
    void pushDNode(int a, char b, int c){
        Dnode* NewNode = new Dnode(a, b, c);
        
        if (head->next == tail){
            head->next = NewNode;
            NewNode->prev = head;
            NewNode->next = tail;
            tail->prev = NewNode;
            dlen++;
            return;
        }
        
        NewNode->prev = tail->prev;
        tail->prev->next = NewNode;
        NewNode->next = tail;
        tail->prev = NewNode;
        dlen++;
    }
    
    void ProcessX(int x, SLL &l1){
        while(cursor->next!=tail && x>0){
            cursor = cursor->next;
            cursoridx++;
            l1.transaction(cursor->Acc, cursor->Action, cursor->Amount);
            x--;
            // cout<<cursoridx<<endl;
        }
    }
    
    void UndoY(int y, SLL &l1){
        while((cursor)!=head && y>0){
            l1.transaction(cursor->Acc, cursor->Action, -(cursor->Amount));
            cursor = cursor->prev;
            cursoridx--;
            y--;
            // cout<<cursoridx<<endl;
        }
    }
    
    void InsertNodeK(int a, char b, int c, int k, SLL &l1){
        int i, flag=0;
        Dnode* addNode = new Dnode(a, b, c);
        if(k>=1 && k<=dlen){
            Dnode* temp = head;
            for(i=0;i<k;i++){
                temp = temp->next;
                if(temp == cursor){
                    flag = 1;
                }
            }
            temp->next->prev = addNode;
            addNode->next = temp->next;
            temp->next = addNode;
            addNode->prev = temp;
            if(flag==0){
                l1.transaction(a, b, c);
            }
        }
    }
    
    void DeleteAM(int acc, int m, SLL &l1){
        Dnode* temp = cursor;
        if(m>0){   
            Dnode* back, *front;
            temp = temp->next;
            while(temp!=tail && m>0){
                if(temp->Acc == acc){
                    Dnode* DelNode = temp;
                    back = temp->prev;
                    front = temp->next;
                    back->next = front;
                    front->prev = back;
                    temp = temp->next;
                    delete DelNode;
                    dlen--;
                    m--;
                }
                else{
                    temp = temp->next;
                }
            }
            
        }
        
        else if(m<0){
            Dnode* back, *front;
            temp = temp->prev;
            while(temp!=head && m<0){
                if(temp->Acc == acc){
                    Dnode* DelNode = temp;
                    l1.transaction(DelNode->Acc, DelNode->Action, -(DelNode->Amount));
                    back = temp->prev;
                    front = temp->next;
                    back->next = front;
                    front->prev = back;
                    temp = temp->prev;
                    delete DelNode;
                    dlen--;
                    cursoridx--;
                    m++;
                }
                else{
                    temp = temp->prev;
                }
            }
        }
            
        // cout<<cursoridx<<" "<<dlen<<endl;
    }
    
    void ProcessAll(SLL &l1){
        ProcessX(dlen, l1);
    }
    
    void PrintAllofY(int acc){
        Dnode* temp = head->next;
        while(temp!=cursor->next){
            if(temp->Acc == acc){
                cout<<temp->Acc<<" "<<temp->Action<<" "<<temp->Amount<<endl;
            }
            temp = temp->next;
        }
    }
    
};

int main()
{
    int c, n, acs, am, x, y, m, k, check =0;
    char choice;
    char dw;
    SLL Accounts;
    DLL Transactions;
    cin>>c;
    while(c--){
        cin>>acs;
        Accounts.pushNode(acs);
    }
    
    cin>>n;
    while(n--){
        cin>>acs>>dw>>am;
        Transactions.pushDNode(acs, dw, am);
    }
    
    while(check==0){
        cin>>choice;
        switch(choice){
            case 'F': cin>>x;
                      Transactions.ProcessX(x, Accounts);
                      break;
            
            case 'R': cin>>y;
                      Transactions.UndoY(y, Accounts);
                      break;
                      
            case 'I': cin>>acs>>dw>>am>>k;
                      Transactions.InsertNodeK(acs, dw, am, k, Accounts);    
                      break;
                      
            case 'D': cin>>acs>>m;
                      Transactions.DeleteAM(acs, m, Accounts);
                      break;
                      
            case 'C': Transactions.ProcessAll(Accounts);
                      break;
                      
            case 'S': cin>>y;
                      Transactions.PrintAllofY(y);
                      break;
                      
            case 'G': cin>>x;
                      Accounts.PrintBalMoreX(x);
                      break;
                      
            case 'M': Accounts.PrintMaxBalance();
                      break;
                      
            case 'V': cin>>x;
                      Accounts.PrintBalX(x);
                      break;
                      
            case 'E': check = 1;
                      break;    
            
        }
    }
    

    return 0;
}
