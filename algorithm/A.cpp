#include <bits/stdc++.h>

using namespace std;

#ifndef __TOPCYBERFLOWER
#define debug(...) 0
#else
#define debug(...) cout << " [-] ", _dbg(#__VA_ARGS__, __VA_ARGS__)
template<class TH> void _dbg(const char *sdbg, TH h){ cout << sdbg << '=' << h << endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
    while(*sdbg != ',') cout << *sdbg++;
    cout << '=' << (h) << ',';
    _dbg(sdbg+1, a...);
}
#endif

#define TYPEMAX(type)   numeric_limits<type>::max()
#define TYPEMIN(type)   numeric_limits<type>::min()
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int SZ1 = 1'000'005;
const int SZ2 = 100'005;

int idx[SZ1];
int arr[SZ2];
int rct[SZ2];
int rev[SZ2];
int ans[SZ2];

struct query{
    int lft,rgt,idx;
    bool operator<(const query &other){
        if(lft==other.lft) return rgt<other.rgt;
        return lft<other.lft;
    }
};

class Segment_Tree{
private:
    vi seg;
    int n;
public:
    Segment_Tree(int n):n(n){
        seg.resize(4*n,0);
    }
    void update(int idx, int l, int r, int f, int xx){
        if(r<f || f<l) return;
        seg[idx]+=xx;
        if(l==r) return;
        int mid=(l+r)/2;
        update(2*idx,l,mid,f,xx);
        update(2*idx+1,mid+1,r,f,xx);
    }
    int find(int idx, int l, int r, int fl, int fr){
        if(r<fl || fr<l) return 0;
        if(fl<=l && r<=fr) return seg[idx];
        int mid=(l+r)/2;
        return find(2*idx,l,mid,fl,fr)+find(2*idx+1,mid+1,r,fl,fr);
    }
};

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    Segment_Tree seg = Segment_Tree(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        rct[i]=idx[arr[i]];
        rev[idx[arr[i]]]=i;
        idx[arr[i]]=i;
        if(rct[i]==0) seg.update(1,1,n,i,1);
    }
    int q; cin>>q;
    vector<query> qry(q);
    for(int i=0;i<q;i++){
        cin>>qry[i].lft>>qry[i].rgt;
        qry[i].idx=i;
    }    
    sort(qry.begin(),qry.end());
    
    int i=1;
    for(auto x:qry){
        int l=x.lft, r=x.rgt;
        while(i<l){
            if(rev[i]) seg.update(1,1,n,rev[i],1);
            i++;
        }
        ans[x.idx]=seg.find(1,1,n,l,r);
    }
    for(int i=0;i<q;i++) cout<<ans[i]<<'\n';
    return 0;
}