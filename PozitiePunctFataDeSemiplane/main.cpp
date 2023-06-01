#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;


struct semiplane {
    double a, b, c;
};
int n, m;
vector<semiplane> semiplanes;
semiplane l;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> l.a >> l.b >> l.c;
        semiplanes.push_back(l);
    }

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        double x, y;
        cin >> x >> y;

        double x_min = -INT_MAX;
        double x_max = INT_MAX;
        double y_min = -INT_MAX;
        double y_max = INT_MAX;

        for (semiplane semiplane : semiplanes)
        {
            double left = -INT_MAX;
            double right = INT_MAX;

            ///if the point is not inside the semiplane
            if (semiplane.a * x + semiplane.b * y + semiplane.c >= 0)
                continue;

            if (semiplane.a == 0) ///vertical
            {
                if (semiplane.b < 0) ///point in the pozitive part
                    left = -1 * semiplane.c / semiplane.b;
                else
                    right= -1 * semiplane.c / semiplane.b;

            }

            else ///horizontal
            {
                if (semiplane.a < 0)
                    ///determine x_max using the equation of the semiplane
                    left = -1 * semiplane.c / semiplane.a;
                else
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
        ///semiplanes intersected in one point/not intersected etc
        if (x_min > x_max || y_min > y_max || x_min == -INT_MAX || x_max == INT_MAX || y_min == -INT_MAX || y_max == INT_MAX || x_min == x_max || y_min == y_max)
            cout << "NO"<<endl;
        else
        {
            cout << "YES"<<endl;
            double aria = (x_max - x_min) * (y_max - y_min);
            cout << fixed << setprecision(6) << aria << endl;
        }
    }
    return 0;
}
