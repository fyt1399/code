#include <stdio.h>

int main(){
    int n,i;
    int minh;
    scanf("%d",&n);
    int f[n+2];
    int g[n+2];
    int p;
    int q[n+2];
    int h[n+2]={0};
    int v[n+2]={0};
    int arrlen[n+2];
    int key[n+2];
    for (i=1;i<=n;i++){
        scanf("%d",&f[i]);
        g[i]=-1;
        q[f[i]]=i;
    }
    g[n+1]=-1;
    q[n+1]=-1;
    int l=1;h[l]=1;int loop=1;minh=2;
    while (1){
        int len=1;
        while (h[f[l]]==0){
            l=f[l];
            h[l]=loop;
            len++;
        }
        arrlen[loop]=len;
        loop++;
        while (h[minh]) minh++;
        if (minh>n) break;
        l=minh;
        h[l]=loop;
    }
    l=1;g[1]=1;key[1]=1;v[1]=1;p=1;
    int alloop=0;minh=1;
    while (1){
        while (g[f[l]]==-1){
            g[f[l]]=f[g[l]];
            l=f[l];
            v[l]=1;
        }
        alloop++;
        int flag=0;
        while (g[p]>0) p++;
        if (p>n) break;
        for (i=1;i<=alloop;i++){
            if (arrlen[h[p]]%arrlen[i]==0){
                g[p]=key[i];
                key[h[p]]=key[i];
                flag=1;
                break;
            }
        }
        if (!flag){
            g[p]=p;
            key[h[p]]=p;
        }
        v[p]=1;
        l=p;
    }
    for (i=1;i<=n;i++) printf("%d ",g[i]);

}
