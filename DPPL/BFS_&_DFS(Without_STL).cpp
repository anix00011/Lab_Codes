#include<iostream>
using namespace std;
bool chk=false;
bool *visited=new bool[1000];
class Node {
    public:
    int data;
    Node *next;
};
class Graph{
    public:
    int Vertex,Edge;
    bool Adj[100][100];
};
Node* newNode(int data){
    Node *tmp=new Node;
    tmp->data=data;
    tmp->next=NULL;
    return tmp;
}
bool isempty(Node* root){
    if(root==NULL) return true;
    return false;
}
Node* push(Node* root, int data){
    if(root==NULL) return newNode(data);
    root->next=push(root->next,data);
}
Node* pop_queue(Node* root){
    if(root==NULL) return NULL;
    root=root->next;
    return root;
}
int peek_queue(Node* root){
    return root->data;
}
int MV(Graph *Grph,int St_Root){
    int c=1;
    bool *visited=new bool[Grph->Vertex];
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    Node* queue_=NULL;
    queue_=push(queue_,St_Root);
    visited[St_Root]=true;
    while(!isempty(queue_)){
        int val=peek_queue(queue_);
        queue_=pop_queue(queue_);
        for(int i=0;i<Grph->Vertex;i++)
            if(!visited[i]&&Grph->Adj[val][i]){
                queue_=push(queue_,i);
                visited[i]=true;
                c++;
            }
    }
    if(c==Grph->Vertex&&!chk){
        cout<<St_Root<<" is the Mother Vertex\n";
        chk=true;
        return St_Root;
    }
    return -1;
}
void BFS(Graph *Grph,int St_Root){
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    Node* queue_=NULL;
    queue_=push(queue_,St_Root);
    visited[St_Root]=true;
    cout<<"BFS from vertex "<<St_Root<<" is: ";
    while(!isempty(queue_)){
        int val=peek_queue(queue_);
        cout<<val<<" ";
        queue_=pop_queue(queue_);
        for(int i=0;i<Grph->Vertex;i++)
            if(!visited[i]&&Grph->Adj[val][i]){
                queue_=push(queue_,i);
                visited[i]=true;
            }
    }
}
void DFS(Graph *Grph,int St_Root){
    if(!visited[St_Root]){
        cout<<St_Root<<" ";
        visited[St_Root]=true;
    }
    for(int i=0;i<Grph->Vertex;i++)
        if(!visited[i]&&Grph->Adj[St_Root][i]){
            DFS(Grph,i);
        }
}
void Left_Node(bool *visited,Graph *Grph){
    for(int i=0;i<Grph->Vertex;i++)
        if(!visited[i]){
            cout<<i<<" ";
            visited[i]=true;
        }
}
int main(){
    Graph *Grph=new Graph;
    cout<<"Enter the number of Nodes and Edges:\n";
    cin>>Grph->Vertex>>Grph->Edge;
    for(int i=0;i<Grph->Vertex;i++) for(int j=0;j<Grph->Vertex;j++) Grph->Adj[i][j]=false;
    cout<<"Enter Edges:\n";
    int x,y;
    for(int i=0;i<Grph->Edge;i++){
        cin>>x>>y;
        Grph->Adj[x][y]=true;
    }
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    int val=-1;
    for(int i=0;i<Grph->Vertex;i++) if(MV(Grph,i)>=0) val=MV(Grph,i);
    if(val>=0) BFS(Grph,val);
    else{
        val=0;
        BFS(Grph,val);
    }
    Left_Node(visited,Grph);
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    cout<<"\nDFS from vertex "<<val<<" is: ";
    DFS(Grph,2);
    Left_Node(visited,Grph);
}
