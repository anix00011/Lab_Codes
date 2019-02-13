#include<iostream>
#include<queue>
using namespace std;
class Node{
public:
int data;
Node* left;
Node* right;
};
Node* newNode(int x){
    Node *tmp=new Node;
    tmp->data=x;
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}

void inorder(Node* root){
    if(root!=NULL){
        inorder(root->left);
        cout<<root->data<<"\n";
        inorder(root->right);
    }
}

Node* insert(int x,Node* root){
    if(root==NULL) root=newNode(x);
    if(x<root->data) root->left=insert(x,root->left);
    if(x>root->data) root->right=insert(x,root->right);
    return root;
}

Node* minValueNode(Node* node) {
    Node* cur=node;
    while (cur->left!=NULL) cur=cur->left;
    return cur;
}

Node* deleteNode(int data,Node* root){
    if(root==NULL) return root;
    if(data<root->data) root->left=deleteNode(data,root->left);
    else if(data>root->data) root->right=deleteNode(data,root->right);
    else{
        if((root->left==NULL)||(root->right==NULL)){
            Node* tmp=root->left?root->left:root->right;
            if(tmp==NULL){
                tmp=root;
                root=NULL;
            }else *root=*tmp;
            delete(tmp);
        }else{
            Node* tmp=minValueNode(root->right);
            root->data=tmp->data;
            root->right=deleteNode(tmp->data,root->right);
        }
    }
    return root;
}

bool idntcl(Node* root1,Node* root2){
    if (root1==NULL&&root2==NULL) return 1;
    if (root1!=NULL&&root2!=NULL) return root1->data==root2->data && idntcl(root1->left,root2->left) && idntcl(root1->right,root2->right);
    return 0;
}

bool Sidntcl(Node* root1,Node* root2){
    if (root1==NULL&&root2==NULL) return 1;
    if (root1!=NULL&&root2!=NULL) return Sidntcl(root1->left,root2->left)&&Sidntcl(root1->right,root2->right);
    return 0;
}

void mirror(Node* root){
    if(root==NULL) return;
    else{
        Node* tmp;
        mirror(root->left);
        mirror(root->right);
        tmp=root->left;
        root->left=root->right;
        root->right=tmp;
    }
}
void mirror2(Node* root){
    if(root==NULL) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* cur=q.front();
        q.pop();
        swap(cur->left,cur->right);
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
}

Node* insertbt(Node* root,int key){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* tmp=q.front();
        q.pop();
        if(!tmp->left){
            tmp->left=newNode(key);
            break;
        }else q.push(tmp->left);
        if(!tmp->right){
            tmp->right=newNode(key);
            break;
        }else q.push(tmp->right);
    }
    return root;
}

bool isBSTUtil(Node* root,int mn,int mx){
    if(root==NULL)  return 1;
    if(root->data<mn||root->data>mx)  return 0;
    return isBSTUtil(root->left,mn,root->data-1)&&isBSTUtil(root->right,root->data+1,mx);
}

bool checkBST(Node* root){
  return(isBSTUtil(root,INT_MIN,INT_MAX));
}

int CountBST(int n,int X[])
{
    if (n==1||n==0) return 1;
    int Possible = 0;
    for (int i=1; i<=n; i++){
        X[i-1]=CountBST(i-1, X);
	X[n-i]=CountBST(n-i, X);
	Possible += X[i-1]*X[n-i];
    }
    return Possible;
}

bool path(int sum,Node* root){
    if(sum==0&&root==NULL) return true;
    if(sum!=0&&root==NULL) return false;
    return path(sum-root->data,root->left)|path(sum-root->data,root->right);
}

void RLpath(Node* root,int a[],int l){
    if(root!=NULL){
        a[l]=root->data;
        if(root->left==NULL||root->right==NULL){
            for(int i=0;i<=l;i++){
                cout<<a[i]<<" ";
            }
            cout<<"\n";
        }
        RLpath(root->left,a,l+1);
        RLpath(root->right,a,l+1);
    }
}

void printS(Node* root,int l){
    if(root!=NULL){
        printS(root->right,l+1);
        for(int i=0;i<l;i++) cout<<"  ";
        cout<<root->data<<"\n";
        printS(root->left,l+1);
    }
}

int main(){
    Node* root1=NULL;
    root1=insert(39,root1);
    root1=insert(9,root1);
    root1=insert(12,root1);
    root1=insert(99,root1);
    root1=insert(49,root1);
    root1=insert(23,root1);
    inorder(root1);
    cout<<"\n";
    root1=deleteNode(99,root1);
    root1=deleteNode(23,root1);
    inorder(root1);
    cout<<"\n";
    Node* root2=NULL;
    root2=insert(39,root2);
    root2=insert(9,root2);
    root2=insert(12,root2);
    root2=insert(99,root2);
    root2=insert(49,root2);
    root2=insert(23,root2);
    inorder(root2);
    cout<<"\n";
    if(idntcl(root1,root2)) cout<<"Identical\n";
    else cout<<"Different\n";
    if(Sidntcl(root1,root2)) cout<<"Structurally identical\n";
    else cout<<"Structurally different\n";
    mirror(root2);
    cout<<"Mirrored 2nd Tree: \n";
    inorder(root2);
    cout<<"\n";
    mirror(root2);
    cout<<"Again Mirrored 2nd Tree: \n";
    inorder(root2);
    cout<<"\n";
    Node* root3=newNode(3);
    root3=insertbt(root3,2);
    insertbt(root3,5);
    insertbt(root3,1);
    insertbt(root3,4);
    cout<<"Binary Tree: \n";
    inorder(root3);
    cout<<"\n";
    if(checkBST(root3)) cout<<"Tree is BST\n";
    else cout<<"Tree is not BST";
    cout<<"\n";
    int X[6]={0};
    cout<<"Number of BST possible: "<<CountBST(5,X)<<"\n";
    if(path(6,root3)) cout<<"Path is available\n";
    else cout<<"Path is not available\n";
    cout<<"Root to leaf path of root3: \n";
    int a[20]={0};
    RLpath(root3,a,0);
    cout<<"\n";
    Node* root4=newNode(1);
    root4=insertbt(root4,2);
    insertbt(root4,3);
    insertbt(root4,4);
    insertbt(root4,5);
    insertbt(root4,6);
    insertbt(root4,7);
    printS(root4,0);
}
