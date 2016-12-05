#include<stdio.h>
#include<stdlib.h>


int main()
{
	int m, n, k;
	int max, min, tmp;
	int flag = 1 ;
    scanf("%d %d %d", &m, &n, &k);
    while(k --) {
        flag = 1;
        max = 0;
        min = 1001;
		int i;
        for (i = 0; i != n; ++ i) {
            scanf("%d", &tmp);
            if (tmp > max) {
                if (tmp - i > m) flag = 0;
                else max = min= tmp;
            } else {
                if ( tmp > min) flag = 0;
                else min = tmp;
            }
        }

        if (flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
