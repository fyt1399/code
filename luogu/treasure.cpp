#include <stdio.h>

struct edgeNode{
    int e;
    int v;
};
int mi2[12]={1,2,4,8,16,32,64,128,256,512,1024,2048};
int lj[12]={0,1,3,6,10,15,21,28,36,45,55,66};
int status[4096];
int maze[12][12];
struct edgeNode edge[12][11];
int edgeNum[12];
int n;
int hashd[40000]={0};

int hashcode(int d[12]){
    int tot=0;
    for (int i=0;i<n;i++){
        tot=(tot+(i+1)*d[i])%32767;
    }
    return tot;
}

void dfs(int d[12],int visit){
    for (int i=0;i<n;i++)
        if (!(mi2[i]&visit)){
            //printf("%d\n",i);
            for (int j=0;j<edgeNum[i];j++){
                int e=edge[i][j].e;
                int v=edge[i][j].v;
                //printf("%d\n",e);
                if ((mi2[e]&visit) && ((d[e]+1)*v+status[visit]<=status[mi2[i]+visit])){
                    d[i]=d[e]+1;
                    int hashv=hashcode(d);
                    if (((d[i])*v+status[visit]<status[mi2[i]+visit]) || ((d[i])*v+status[visit]<hashd[hashv]))
                        {
                            status[mi2[i]+visit]=(d[i])*v+status[visit];
                            hashd[hashv]=(d[i])*v+status[visit];
                            dfs(d,mi2[i]+visit);
                        }
                    d[i]=0;
                }
            }
        }
}

int main(){
    for (int i=0;i<40000;i++) hashd[i]=99999999;
    int d[12]={0};
    int m,i,j,x,y,v;
    scanf("%d%d",&n,&m);
    for (i=0;i<4096;i++) status[i]=99999999;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            maze[i][j]=-1;
    for (i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&v);
        if (v<maze[x-1][y-1] || maze[x-1][y-1]==-1){
            maze[x-1][y-1]=v;
            maze[y-1][x-1]=v;
        }
    }
    for (i=0;i<n;i++){
        edgeNum[i]=0;
        for (j=0;j<n;j++)
            if ((i!=j) && (maze[i][j]>0)){
                edge[i][edgeNum[i]].e=j;
                edge[i][edgeNum[i]].v=maze[i][j];
                edgeNum[i]++;
            }
    }
    for (i=0;i<n;i++){
        status[mi2[i]]=0;
        dfs(d,mi2[i]);
    }
    int tot=0;
    for (i=0;i<n;i++) tot=tot+mi2[i];
    //for (i=0;i<tot;i++) printf("%d\n",status[i]);
    printf("%d",status[tot]);
}
