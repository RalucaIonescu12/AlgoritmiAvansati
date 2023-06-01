#include <iostream>
#include <algorithm>
#include <vector>
/// RAY CASTING FOR POINT IN CONVEX POLYGON
using namespace std;
int nPoints, nQueries,l,r,m;

struct point {
    long long x,y;
};
vector<point> points;


long long det(point a, point b, point c)
{
///function to compute the determinant of three points
///if det < 0, the three points are oriented clockwise (to the right)
///if det > 0, the three points are oriented counterclockwise (to the left)
///if det == 0, the three points are collinear

    return b.x * c.y + a.x * b.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y;
}

int cBetweenAB(point a, point b, point c)
{
    if(det(a,b,c) == 0) ///collinear
        ///if c is between a and b
        if(min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y) )
            return 1;

    return 0;
}
int position(point x)
{
    int low = 1;
    int up = nPoints-1;


    if(cBetweenAB(points[0], points[low], x)  || cBetweenAB(points[0], points[up], x) )
        return 0; ///boundary

    ///if points (0, low , x) are counterclockwise and points(0,up,x) are clockwise
    if(det(points[0], points[low], x) > 0 && det(points[0], points[up], x) < 0 )
    {
        ///binary search to find the indexes of the closest vertexes to x
        while(up-low != 1)
        {
            int mid = (up + low) / 2;

            if(det(points[0], points[mid], x) > 0)
                low = mid;
            else
                up = mid;
        }

        ///we found the triangle but we still have to check if x is inside it
        if(cBetweenAB(points[low], points[up], x))
            return 0;///boundary

        if(det(points[low], points[up], x) > 0 )
            return 1; ///inside
    }
    return -1;///outside
}

int main()
{
    cin>>nPoints;
    point a;
    for (int i = 0; i < nPoints; ++i) {
        cin>>a.x>>a.y;
        points.push_back(a);
    }
    cin>>nQueries;
    int index=-1;
    for (int i = nPoints-1; i >=0; i--) {
        if(points[i].x != points[0].x)
            break;
        else if (points[0].y<points[i].y)
            index=i;
    }
    if (index!=-1)rotate(points.begin(), points.begin() + index, points.end());

/// removes any points in a polygon that are
/// collinear with their adjacent points
/// simplifying the polygon
    for(int i = 0;i < nPoints; i++)
    {
        if(det(points[i], points[(i + 1) % nPoints],points[(i + 2) % nPoints]) == 0)
        {
            points.erase(points.begin() + (i + 1) % nPoints);
            nPoints--;
            i--;
        }
    }


//    for (int i = 0; i < nPoints; ++i) {
//        cout<<points[i].x<<" "<<points[i].y<<endl;
//    }
    long long v[100001];
    int i=0;
    for (int j = 0; j < nQueries; ++j)
    {
        cin>>a.x>>a.y;
        if(position(a)==1)
            v[i++]=1;
        else if (position(a)==0)
            v[i++]=0;
        else
            v[i++]=-1;
    }

    for (int j = 0; j < nQueries; ++j)
    {
        if(v[j]==1)
            cout<<"INSIDE"<<endl;
        else if (v[j]==0)
            cout<<"BOUNDARY"<<endl;
        else
            cout<<"OUTSIDE"<<endl;
    }
}






















////versiunea veche
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//struct point{
//    long long x,y;
//};
//
//long long cross_product(point a, point b){
//    return a.x*b.y-b.x*a.y;
//}
//
//long long sq_dist(point a, point b){
//    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
//}
//
//bool is_inside(long long x, long long y, vector<point>&points){
//    point p1 = {points[points.size()-1].x-points[0].x, points[points.size()-1].y-points[0].y};
//    point p2 = {points[1].x-points[0].x, points[1].y-points[0].y};
//    point pq = {x-points[0].x, y-points[0].y};
//
//    if(!(cross_product(p1, pq)<=0 && cross_product(p2,pq)>=0)) return false;
//
//    int l = 0, r = points.size();
//    while (r - l > 1) {
//        int mid = (l + r) / 2;
//        point cur = {points[mid].x-points[0].x, points[mid].y-points[0].y};
//        if (cross_product(cur, pq)<0) {
//            r = mid;
//        } else {
//            l = mid;
//        }
//    }
//
//    if(l == points.size()-1){
//        return sq_dist(points[0], {x,y}) <= sq_dist(points[0], points[l]);
//    }else{
//        point l_l1 = {points[l+1].x-points[l].x, points[l+1].y-points[l].y};
//        point lq = {x-points[l].x, y-points[l].y};
//        return (cross_product(l_l1,lq) >=0);
//    }
//}
//
//void pick_p0(vector<point>&points){
//    long long min_x=1e9+5;
//    long long max_y=-1e9-5;
//    int min_i=0;
//    for(int i=0;i<points.size();i++){
//        if(points[i].x < min_x || (points[i].x == min_x && points[i].y > max_y)){
//            min_x=points[i].x;
//            max_y=points[i].y;
//            min_i = i;
//        }
//    }
//
//    rotate(points.begin(), points.begin() + min_i, points.end());
//}
//
//
//int main() {
//    int n,m,k;
//    cin>>n>>m>>k;
//
//    vector<point>points(n);
//
//    for(int i=0;i<n;i++){
//        cin>>points[i].x>>points[i].y;
//    }
//
//    pick_p0(points);
//
//    for(int i=0;i<m;i++){
//        long long x,y;
//        cin>>x>>y;
//        cout <<  (is_inside(x,y, points) ? "YES\n" : "NO\n");
//    }
//
//    return 0;
//}


