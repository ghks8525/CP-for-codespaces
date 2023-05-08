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

const int SZ = 25;
const int dx[4]={0,0,-1,1};
const int dy[4]={1,-1,0,0};

int wall[SZ][SZ][5];
int cels[SZ][SZ];
int r,c;
// rgt:0, lft:1, up:2, down:3
class Heater{
private:
    struct elem{
        int x,y,d;
    };
    int dir,xpos,ypos;
public:
    Heater(int dir, int xpos, int ypos):dir(dir),xpos(xpos),ypos(ypos){}
    void heat_air(){
        int nx=xpos, ny=ypos;
        for(int i=1;i<=5;i++){
            if(wall[nx][ny][dir]==1) break;
            nx+=dx[dir]; ny+=dy[dir];
            if(nx<0 || nx>=r) break;
            if(ny<0 || ny>=c) break;
            cels[nx][ny]+=6-i;

            for(int j=0;j<2;j++){
                int nd=(dir<2?2+j:j);
                int px=nx, py=ny;
                for(int k=1;k<i;k++){
                    if(wall[px][py][nd]==1) break;
                    px+=dx[nd]; py+=dy[nd];
                    if(px<0 || px>=r) break;
                    if(py<0 || py>=c) break;
                    cels[px][py]+=6-i;
                }
            }
        }
    }
};

class Solver{
private:
    vector<Heater> heats;
    vector<pii> chks;
    int goal;
    inline int dec_cels(int i,int j){
        return max(cels[i][j]-1,0);
    }
public:
    Solver(){
        cin>>r>>c>>goal;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                int x; cin>>x;
                if(x==0) continue;
                if(x==5) chks.push_back({i,j});
                else heats.push_back({x-1,i,j});
            }
        }
        int w; cin>>w;
        for(int i=0;i<w;i++){
            int a,b,c; cin>>a>>b>>c;
            if(c==0){
                wall[a-1][b][3]=1;
                wall[a][b][2]=1;
            }
            else{
                wall[a][b+1][1]=1;
                wall[a][b][0]=1;
            }
        }
    }
    bool my_check(){
        for(pii xx:chks){
            if(cels[xx.first][xx.second]<goal) return false; 
        }
        return true;
    }
    void border(){
        for(int i=1;i+1<c;i++){
            cels[0][i]=dec_cels(0,i);
            cels[r-1][i]=dec_cels(r-1,i);
        }
        for(int i=1;i+1<r;i++){
            cels[i][0]=dec_cels(i,0);
            cels[i][c-1]=dec_cels(i,c-1);
        }
        cels[0][0]=dec_cels(0,0);
        cels[0][c-1]=dec_cels(0,c-1);
        cels[r-1][0]=dec_cels(r-1,0);
        cels[r-1][c-1]=dec_cels(r-1,c-1);
    }
    void control(){
        int dif[SZ][SZ]={0,};
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                for(int k=0;k<4;k++){
                    int nx=i+dx[k], ny=j+dy[k];
                    if(nx<0 || nx>=r) continue;
                    if(ny<0 || ny>=c) continue;
                    if(wall[i][j][k]==1) continue;
                    int dt=cels[i][j]-cels[nx][ny];
                    if(dt>=0){
                        dif[i][j]-=dt/4;
                        dif[nx][ny]+=dt/4;
                    }
                    else{
                        dt=-dt;
                        dif[i][j]+=dt/4;
                        dif[nx][ny]-=dt/4;                        
                    }
                }
            }
        }
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                cels[i][j]+=dif[i][j];
            }
        }
    }
    int solve(){
        int res=0;
        do{
            for(auto xx:heats) xx.heat_air();
            control();
            border();
            res++;
        } while (!my_check());
        return res;
    }
};


int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout<<Solver().solve();
    return 0;
}