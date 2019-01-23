#include<iostream>
using namespace std;
struct Node{
	int data;
	Node *next;
};
void add(Node* head,int x){
    Node* newNode=new Node;
	Node* cur=head->next;
	Node* pre=head;
	while(cur!=NULL){
        if(cur->data==x) return;
        cur=cur->next;
        pre=pre->next;
	}
    newNode->data=x;
    newNode->next=NULL;
    pre->next=newNode;
}
struct Node* build(int *arr,int length){
	Node* head=new Node;
	head->data=0;
	head->next=NULL;
	int i=0;
	while(i<length){
		add(head,arr[i]);
		i++;
	}
	return head;
}
void enmrt(struct Node* head){
	Node* temp=head->next;
	while(temp!=NULL){
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<"\n";
}
int crdnlty(Node* head){
	int c=0;
	Node* temp=head;
	while(temp->next!=NULL){
		c++;
		temp=temp->next;
	}
	return c;
}
void isEmpty(Node* head){
	if(head->next==NULL) cout<<"Set is NULL\n";
	else cout<<"Set isn't NULL\n";
}
bool is_element_of(Node* head,int x){
	Node* temp=head->next;
	while(temp!=NULL){
		if(temp->data==x) return true;;
		temp=temp->next;
	}
    return false;
}
void remov(Node* head,int x){
	Node* temp=head;
	while(temp->next!=NULL){
		if(temp->next->data==x){
			temp->next=temp->next->next;
			return;
		}
		temp=temp->next;
	}
}
bool is_empty_(struct Node *head){
if(head->next==NULL) return true;
return false;
}
struct Node* unin(struct Node *headx,struct Node *heady){
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    Node* cur=headx->next;
    while(cur!=NULL){
        add(head,cur->data);
        cur=cur->next;
    }
    cur=heady->next;
    while(cur!=NULL){
        add(head,cur->data);
        cur=cur->next;
    }
    return head;
}
struct Node* diff(struct Node *headx,struct Node *heady){
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    Node* cur=headx->next;
    while(cur!=NULL){
        if(!is_element_of(heady,cur->data)) add(head,cur->data);
        cur=cur->next;
    }
    return head;
}

bool Subset(struct Node *headx,struct Node *heady){
    Node* cur=heady->next;
    while(cur!=NULL){
        if(!is_element_of(headx,cur->data)) return false;
        cur=cur->next;
    }
    return true;
}
struct Node* Intersection(struct Node* headx,struct Node* heady){
    Node *head = new Node;
    head->data = 0;
    head->next = NULL;
    Node* cur=headx->next;
    while(cur!=NULL){
        if(is_element_of(heady,cur->data)) add(head,cur->data);
        cur=cur->next;
    }
    return head;
}
int main(){
	int a[11]={11,1,2,3,4,5,6,6,7,8,9};
	int b[6]={11,1,2,12,14,20};
	int cx[3]={1,6,7};
	Node* head1=build(a,11);
	Node* head2=build(b,6);
	Node* head3=build(cx,3);
	cout<<"First Set elements: ";
	enmrt(head1);
	cout<<"\n";
	cout<<"Second Set elements: ";
	enmrt(head2);
	cout<<"\n";
	cout<<"Third Set elements: ";
	enmrt(head3);
	cout<<"\n";
	int c=crdnlty(head1);
	int d=crdnlty(head2);
	int e=crdnlty(head3);
	cout<<"Cardinality of first Set is: "<<c<<", "<<"Cardinality of second Set is: "<<d<<" and Cardinality of third Set is: "<<e<<"\n";
	cout<<"\n";
	cout<<"Removing 3 elements from first Set.\n";
	remov(head1,5);
	remov(head1,11);
	remov(head1,2);
	cout<<"\n";
	cout<<"Removing 1 element from second Set.\n";
	remov(head2,20);
	cout<<"\n";
	cout<<"First Set elements: ";
	enmrt(head1);
	cout<<"\n";
	cout<<"Second Set elements: ";
	enmrt(head2);
	cout<<"\n";
	c=crdnlty(head1);
	d=crdnlty(head2);
	cout<<"Cardinality of first Set is: "<<c<<" and "<<"Cardinality of second Set is: "<<d<<"\n";
	cout<<"\n";
	Node* headxx=unin(head1,head2);
	cout<<"Union is: ";
	enmrt(headxx);
	cout<<"\n";
	headxx=diff(head1,head2);
	cout<<"Difference is: ";
	enmrt(headxx);
	cout<<"\n";
	if(Subset(head1,head3)) cout<<"Third Set is Subset of first Set\n";
	else cout<<"Third Set is not Subset of first Set\n";
	cout<<"\n";
	headxx=Intersection(head1,head2);
	cout<<"Intersection is: ";
	enmrt(headxx);
	cout<<"\n";
}
