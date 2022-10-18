#include <stdio.h>

int main(){
    int n = 0, seq = 0;
    int onestart = 0, oneend = 0, secone = 0, maxone = 0, onelast = -1, onemstart = 0, onemend = 0;
    int twostart = 0, twoend = 0, sectwo = 0, maxtwo = 0, twolast = -1, twomstart = 0, twomend = 0;
    int threestart = 0, threeend = 0, secthree = 0, maxthree = 0, threelast = -1, threemstart = 0, threemend = 0;
    while (scanf("%d", &n) != EOF){
        switch (n){
            case 1:{
                if (onelast != -1){
                    int temp = seq - onelast;
                    if (temp > maxone) {
                        secone = maxone; onestart = onemstart; oneend = onemend;
                        maxone = temp; onemstart = onelast; onemend = seq;
                    }
                    else if (temp == maxone){
                        onemstart = onelast; onemend = seq;
                    }
                    else if (temp >= secone && temp < maxone){
                        secone = temp; onestart = onelast; oneend = seq;
                    }
                }
                onelast = seq;
                break;
            }
            case 2:{
                if (twolast != -1){
                    int temp = seq - twolast;
                    if (temp > maxtwo) {
                        sectwo = maxtwo; twostart = twomstart; twoend = twomend;
                        maxtwo = temp; twomstart = twolast; twomend = seq;
                    }
                    else if (temp == maxtwo){
                        twomstart = twolast; twomend = seq;
                    }
                    else if (temp >= sectwo && temp < maxtwo){
                        sectwo = temp; twostart = twolast; twoend = seq;
                    }
                }
                twolast = seq;
                break;
            }
            case 3:{
                if (threelast != -1){
                    int temp = seq - threelast;
                    if (temp > maxthree){
                        secthree = maxthree; threestart = threemstart; threeend = threemend;
                        maxthree = temp; threemstart = threelast; threemend = seq;
                    }
                    else if (temp == maxthree){
                        threemstart = threelast; threemend = seq;
                    }
                    else if (temp >= secthree && temp < maxthree){
                        secthree = temp; threestart = threelast; threeend = seq;
                    }
                }
                threelast = seq;
                break;
            }
        }
        ++seq;
    }
    printf("%d %d %d\n%d %d %d\n%d %d %d", secone, onestart, oneend, 
           sectwo, twostart, twoend, secthree, threestart, threeend);
    return 0;
}