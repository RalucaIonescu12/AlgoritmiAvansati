#include <iostream>
#include <vector>
#include <algorithm>
///Odd-even rule
///AB, CD intersect if A and B are on diff sides of CD and
///C and D are in diff sides of AB(orientation test)
using namespace std;
int nPoints, nQueries;

struct point {
    long long x,y;
};
point M;
vector<point> points;

///p, q, r are collinear, checks if q is on pr
bool onSegment(point p, point q, point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}


/// 0 -> p, q and r are collinear
/// 1 -> Clockwise
/// 2 -> Counterclockwise
int orientation(point p, point q, point r)
{
    long long val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  ///collinear

    return (val > 0)? 1: 2; /// 1->clock or 2->counterclock wise
}

/// true->p1q1 and p2q2 intersect
bool doIntersect(point p1, point q1,point p2, point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    ///special cases
    /// p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    /// p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    ///p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    /// p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; ///no intersection
}

long long det(point a, point b, point c)
{
///function to compute the determinant of three points
///if det < 0, the three points are oriented clockwise (to the right)
///if det > 0, the three points are oriented counterclockwise (to the left)
///if det == 0, the three points are collinear
    return b.x * c.y + a.x * b.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y;
}
int is_inside(point p)
{
    int cnt = 0;
    ///iterate through each edge of the polygon, and checking whether
    /// the segment [p,first point] intersects with that edge.
    for (int i = 1; i < nPoints; i++)
    {
        point a=points[i-1];
        point b=points[i];
        if(det(a,b,p) == 0) ///collinear
            ///if p is between a and b
        {
            ///if p is collinear and between the 2 points
            if (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y))
                return -1;///boundary
        }
        ///not collinear
        else if (doIntersect(M,p,a,b))
            cnt+=1;
    }

    point a=points[nPoints-1];
    point b=points[0];


    if(det(a,b,p) == 0) ///collinear
        ///if p is between a and b
        if(min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y) )
            return -1;///boundary

    if (doIntersect(M,p,a,b))
        cnt+=1;

    if (cnt%2==1 ) return 1; ///inside
    else return 0;  ///outside

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
    ///if two points have the same x coordonate needs to start from the biggest y coordonate
    ///so if i find points with smaller y then i move them to the end
    for (int i = nPoints-1; i >=0; i--) {
        if(points[i].x != points[0].x)
            break;
        else if (points[0].y<points[i].y)
            index=i;
    }

    if (index!=-1)rotate(points.begin(), points.begin() + index, points.end());

    M={points[0].x,points[0].y};

/// removes any points in a polygon that are
/// collinear with their adjacent points
/// simplifying the polygon
    for(int i = 0;i < nPoints; i++)
    {
        if(M.x<points[i].x) M.x=points[i].x;
        if(M.y<points[i].y) M.y=points[i].y;
        if(det(points[i], points[(i + 1) % nPoints],points[(i + 2) % nPoints]) == 0)
        {
            points.erase(points.begin() + (i + 1) % nPoints);
            nPoints--;
            i--;
        }
    }

    M.x+=10;
    M.y+=11;
//    for (int i = 0; i < nPoints; ++i) {
//        cout<<points[i].x<<" "<<points[i].y<<endl;
//    }

    long long v[100001];
    int i=0;
    for (int j = 0; j < nQueries; ++j)
    {
        cin>>a.x>>a.y;
        if(is_inside(a)==1) ///inside
            v[i++]=1;
        else if (is_inside(a)==0)
            v[i++]=0;       ///outside
        else if (is_inside(a)==-1)
            v[i++]=-1;
    }

    for (int j = 0; j < nQueries; ++j)
    {
        if(v[j]==1)
            cout<<"INSIDE"<<endl;
        else if(v[j]==0)
            cout<<"OUTSIDE"<<endl;
        else
            cout<<"BOUNDARY"<<endl;
    }

    return 0;
}
