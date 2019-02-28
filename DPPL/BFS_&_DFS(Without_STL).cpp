#include<iostream>
using namespace std;
class Node {
    public:
    int data;
    Node *next;
};
class Graph{
    public:
    int Vertex,Edge;
    bool Adj[6][6];
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
Graph* AdjMat(){
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
    return Grph;
}
void BFS(Graph *Grph,int St_Root){
    bool *visited=new bool[Grph->Vertex];
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
bool DFS(Graph *Grph,int St_Root,bool *visited){
    if(!visited[St_Root]){
        cout<<St_Root<<" ";
        visited[St_Root]=true;
    }
    for(int i=0;i<Grph->Vertex;i++)
        if(!visited[i]&&Grph->Adj[St_Root][i]){
            *visited=DFS(Grph,i,visited);
        }
    return visited;
}
int main(){
    Graph *Grph=AdjMat();
    BFS(Grph,2);
    cout<<"\n";
    bool *visited=new bool[Grph->Vertex];
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    cout<<"DFS from vertex 2 is: ";
    *visited=DFS(Grph,2,visited);
}
