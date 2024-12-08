#include <bits/stdc++.h>
using namespace std;

struct st{
    int x,y,d;
};

int main() {
    priority_queue<st, vector<st>, function<bool(st,st)>>pq(
        [](st a,st b){return a.x<b.x;}//<ならでかいもんが出て>なら小さいほうが出る←逆かも
    );
    st a={1,2,3};
    st b={2,3,4};
    pq.push(a);
    pq.push(b);
    cout<<pq.top().x;
}
