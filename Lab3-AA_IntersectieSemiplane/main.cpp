#include <iostream>
#include<vector>
#include<climits>
using namespace std;

struct semiplane{
    long long a, b, c;
};

long long a, b, c;
int n;
vector<semiplane> semiplanes;

string intersect()
{
    /// variables for the intersection intervals
    long long x_max = LLONG_MAX;
    long long x_min = -LLONG_MAX;
    long long y_max = LLONG_MAX;
    long long y_min = -LLONG_MAX;

    for (semiplane semiplane : semiplanes)
    {
        long long left = -LLONG_MAX;
        long long right = LLONG_MAX;

        if (semiplane.a == 0) // vertical
        {
            /// if the semiplane goes downwards
            if (semiplane.b < 0)
                /// determine the minimum value on the y-axis intersection
                left = -1 * semiplane.c / semiplane.b; /// intersection with the oy axis

                /// if the semiplane goes upwards
            else
                /// determine the maximum value on the y-axis intersection
                right= -1 * semiplane.c / semiplane.b;

        }
        else /// horizontal
        {
            /// if the semiplane goes to the left
            if (semiplane.a < 0)
                /// determine the minimum value on the x-axis intersection
                left = -1 * semiplane.c / semiplane.a;

                /// if the semiplane goes to the right
            else
                /// determine the maximum value on the x-axis intersection
                right = -1 * semiplane.c / semiplane.a;

        }


        if (semiplane.a == 0) /// vertical
        {
            /// determine the minimum value of the intersection interval on the y-axis
            y_min = max(y_min, left);
            /// determine the maximum value of the intersection interval on the y-axis
            y_max = min(y_max, right);
        }
        else /// horizontal
        {
            /// determine the minimum value of the intersection interval on the x-axis
            x_min = max(x_min, left);
            /// determine the maximum value of the intersection interval on the x-axis
            x_max = min(x_max, right);
        }
    }

    /// if the minimum values become greater than the maximum values => the semiplanes don't intersect
    if (x_min > x_max || y_min > y_max)
        return "VOID";

    if (x_min != -LLONG_MAX && x_max != LLONG_MAX && y_min != -LLONG_MAX && y_max != LLONG_MAX)
        return "BOUNDED";

    return "UNBOUNDED";
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> c;
        semiplanes.push_back({a, b, c});
    }

    cout << intersect();
    return 0;
}























//// iterates through each semiplane, and for each one,
/// it determines the interval of intersection
/// with the x-axis or y-axis (depending on whether the
/// semiplane is vertical or horizontal).
/// Then, it updates the minimum and maximum
/// values for the intersection intervals based
/// on these intervals of intersection.