#include<iostream>
#define vert1 1000
#define vert2 100
using namespace std;
bool chk=false;
bool *visited=new bool[vert1];
class Node {
    public:
    int data;
    Node *next;
};
class Graph{
    public:
    int Vertex,Edge;
    bool Adj[vert2][vert2];
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
Node* pop_stack(Node* root){
    int i=0;
    if(root==NULL) return NULL;
    Node* temp=NULL;
    Node* temp2=NULL;
    temp = root;
    if(temp->next==NULL){
        root=NULL;
        return root;
    }
    while(temp->next != NULL){
        temp2=temp;
        temp = temp->next;
        i++;
    }
    temp2->next=NULL;
    return root;
}
int peek_stack(Node* root){
    while(root->next != NULL) root=root->next;
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
Node* topo_Sort(int St_Root,Node* Stack,Graph *Grph){
    visited[St_Root]=true;
    for(int i=0;i<Grph->Vertex;i++) if(!visited[i]&&Grph->Adj[St_Root][i]) Stack=topo_Sort(i,Stack,Grph);
    Stack=push(Stack,St_Root);
    return Stack;
}

void topo_SortUtil(Graph *Grph){
    Node* Stack=NULL;
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    for(int i=0;i<Grph->Vertex;i++) if(!visited[i]) Stack=topo_Sort(i,Stack,Grph);
    while(!isempty(Stack)){
        cout<<peek_stack(Stack)<<" ";
        Stack=pop_stack(Stack);
    }
}
void maxEdge(Graph *Grph){
    Node* Stack=NULL;
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    for(int i=0;i<Grph->Vertex;i++) if(!visited[i]) Stack=topo_Sort(i,Stack,Grph);
    int tsort[Grph->Vertex];
    for(int i=0;i<Grph->Vertex;i++){
        tsort[i]=peek_stack(Stack);
        Stack=pop_stack(Stack);
    }
    int c=0;
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    for(int i=0;i<Grph->Vertex;i++){
        int t=tsort[i];
        for(int j=0;j<Grph->Vertex;j++) if(Grph->Adj[t][j]) visited[j]=true;
        for(int j=i+1;j<Grph->Vertex;j++){
            if(!visited[tsort[j]]) c++;
            visited[tsort[j]]=false;
        }
    }
    cout<<c;
}
bool isCyclicUtilD(int x,bool *r,Graph *Grph){
    if(!visited[x]){
        visited[x]=true;
        r[x]=true;
        for(int i=0;i<Grph->Vertex;i++){
            if(!visited[i]&&Grph->Adj[x][i]&&isCyclicUtilD(i,r,Grph)) return true;
            else if(r[i]&&Grph->Adj[x][i]) return true;
        }
    }
    r[x]=false;
    return false;
}
bool isCyclicD(Graph *Grph){
    bool *r=new bool[Grph->Vertex];
    for(int i=0;i<Grph->Vertex;i++){
        visited[i]=false;
        r[i]=false;
    }
    for(int i=0;i<Grph->Vertex;i++) if(isCyclicUtilD(i,r,Grph)) return true;
    return false;
}
bool bipartiteUtil(int St_Root,int *color,Graph *Grph,int c=0){
    color[St_Root]=c%2;
    for (int i=0;i<Grph->Vertex;i++){
        if (Grph->Adj[St_Root][i]||Grph->Adj[i][St_Root]&&i!=St_Root){
            if(color[i]==color[St_Root]) return false;
            if(color[i]==-1) if (!bipartiteUtil(i,color,Grph,c+1)) return false;
        }
    }
    return true;
}
bool bipartite(Graph *Grph){
    int color[Grph->Vertex];
    for(int i=0;i<Grph->Vertex;i++) color[i]=-1;
    for(int i=0;i<Grph->Vertex;i++) if (color[i]==-1) if (!bipartiteUtil(i, color,Grph)) return false;
    return true;
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
        //Grph->Adj[y][x]=true;
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
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    cout<<"\nTopologically Sorted Graph: ";
    topo_SortUtil(Grph);
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    cout<<"\nMax Edges: ";
    maxEdge(Grph);
    if(isCyclicD(Grph)) cout<<"\nGraph is Cyclic";//For Directed
    else cout<<"\nGraph is not Cyclic";
    //if(bipartite(Grph)) cout<<"\nGraph is bipartite";
    //else cout<<"\nGraph is not bipartite";//Use only for Undirected Graph
    int cx=0;
    for(int i=0;i<Grph->Vertex;i++) visited[i]=false;
    Node* xx=path(6,1,Grph);
    cout<<"\nPath: \n";
    while(!isempty(xx)){
        cout<<peek_stack(xx)<<" ";
        xx=pop_stack(xx);
    }
}
