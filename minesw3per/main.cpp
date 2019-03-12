#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "rlutil.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int f,g;
    bool debug = false;
    string sm;
    //menu
    while(1){
        system("cls");
        printf("Welcome to Minesweeper!\nUse !help to get started.\n\n");
        cin >> sm;
        if(sm == "!help"){
            system("cls");
            printf("Menu Commands\n!info - information about this program\n!start - start a new game of minesweeper\n!debug - toggle debug mode\n!quit - quit program\n");
            printf("\nGame Commands\n!plot - plot point\n!flag - toggle flag mode\n!quit - quit program\n\n");
            system("pause");
            continue;
        }
        if(sm == "!quit") return 0;
        if(sm == "!info"){
            system("cls");
            rlutil::setColor(9);
            printf("Minesw3per v 1.2");
            rlutil::resetColor();
            rlutil::setColor(7);
            printf("\nCoded by Dragon Eye#1708\n\n");
            system("pause");
            continue;
        }
        if(sm == "!debug"){
            system("cls");
            if(debug == true){
                debug=false;
                printf("Debug Toggled: False\n");
            }
            else if(debug == false){
                debug=true;
                printf("Debug Toggled: True\n");
            }
            system("pause");
        }
        if(sm == "!start") break;
    }
    system("cls");
    printf("Input Canvas Size: ");
    scanf("%d", &f);
    printf("Input Bomb Amount: ");
    scanf("%d", &g);
    char vf [f+2] [f+2];
    char af [f+2] [f+2];
    int b1 [g+2], b2 [g+2], x, y;
    bool flag = false;
    int fcount = g;
    string cmd;

    //Visual field setup
    for(int i=1; i<=f; i++){
        for(int j=1; j<=f; j++){
            vf [i] [j] = 'x';
        }
    }

    //Bomb location setup
    for (int i=1; i<=g; i++){
        while(1){
            int c = 0;
            b1[i] = 1 + rand() % f;
            b2[i] = 1 + rand() % f;
            for (int j=1; j<i; j++){
                if(b2[i]==b2[j] && b1[i]==b1[j]){
                    c++;
                }
            }
            if (c == 0){
                af [b1[i]] [b2[i]] = 'B';
                break;
            }
        }
    }

    //Number values setup
    for(int i=1; i<=f; i++){
        for(int j=1; j<=f; j++){
            if (af[i][j]!='B'){
                int c = 0;
                if(af [i+1][j] == 'B') c++;
                if(af [i-1][j] == 'B') c++;
                if(af [i][j+1] == 'B') c++;
                if(af [i][j-1] == 'B') c++;
                if(af [i+1][j+1] == 'B') c++;
                if(af [i-1][j-1] == 'B') c++;
                if(af [i+1][j-1] == 'B') c++;
                if(af [i-1][j+1] == 'B') c++;
                char o = '0' + c;
                af[i][j] = o;
                if (debug) printf("char is = '%c'", af[i][j]);
            }
        }
    }
    system("pause");
    //The Game
    while(1){
        int c1 = 0;
        system("cls");
        rlutil::setColor(8);
        for(int i=0; i<=f; i++) printf("%d ", i%10);
        rlutil::resetColor();
        printf("\n");
        for(int i=1; i<=f; i++){
            rlutil::setColor(8);
            printf("%d ", i%10);
            rlutil::resetColor();
            for(int j=1; j<=f; j++){
                if (vf[i][j]=='0' || vf[i][j]=='1' || vf[i][j]=='2' || vf[i][j]=='3' || vf[i][j]=='4' || vf[i][j]=='5' || vf[i][j]=='6' || vf[i][j]=='7' || vf[i][j]=='8' || vf[i][j]=='!') c1++;
                rlutil::setColor(7);
                printf("%c ", vf[j][i]);
            }
            printf("\n");
        }
        if (c1==f*f){
            printf("\nCongratulations, You Win!\n");
            system("pause");
            return 0;
        }
        if(flag==true){
            printf("\nFlag mode is on!\n");
        }
        else{
            printf("\nFlag mode is off!\n");
        }
        printf("Flags: %d\n\n", fcount);
        cin >> cmd;
        if(cmd=="!quit") return 0;
        if(cmd=="!flag"){
            if(flag == true){
                flag = false;
                continue;
            }
            if(flag == false) flag = true;
            continue;
        }
        if(cmd=="!plot"){
            printf("\nCMD: ");
            scanf("%d %d", &x, &y);
            if(flag == true){
                if(vf[x][y]=='x' && fcount > 0){
                    vf[x][y] = '!';
                    fcount--;
                }
                else if(vf[x][y]=='!'){
                    vf[x][y] = 'x';
                    fcount++;
                }
                continue;
            }

            if(af[x][y]=='B'){
                if(vf[x][y]=='!') continue;
                system("cls");
                for(int i=1; i<=f; i++){
                    for(int j=1; j<=f; j++){
                        printf("%c ", af[j][i]);
                   }
                    printf("\n");
                }
                printf("\nBombs Away!\n\n");
                system("pause");
                return 0;
            }
            else if(af[x][y]=='0'){
                if (debug) printf("hit\n");
                int ax [10000];
                int ay [10000];
                int n = 1;
                int i = 0;
                int z = 0;
                ax [0] = x;
                ay [0] = y;
                while(n>0){
                    n--;
                    if (debug) printf("%d: ", n);
                    if (debug) printf("dealing with %d %d\n", ax[i], ay[i]);
                    if (vf[ax[i]][ay[i]] == '!'){
                        i++;
                        continue;
                    }
                    vf [ax[i]] [ay[i]] = af [ax[i]] [ay[i]];
                    //Uncovering all adjacent blocks if not flagged
                    if(vf [ax[i]+1] [ay[i]+1] != '!') vf [ax[i]+1] [ay[i]+1] = af [ax[i]+1] [ay[i]+1];
                    if(vf [ax[i]-1] [ay[i]-1] != '!') vf [ax[i]-1] [ay[i]-1] = af [ax[i]-1] [ay[i]-1];
                    if(vf [ax[i]+1] [ay[i]-1] != '!') vf [ax[i]+1] [ay[i]-1] = af [ax[i]+1] [ay[i]-1];
                    if(vf [ax[i]-1] [ay[i]+1] != '!') vf [ax[i]-1] [ay[i]+1] = af [ax[i]-1] [ay[i]+1];
                    if(vf [ax[i]+1] [ay[i]] != '!') vf [ax[i]+1] [ay[i]] = af [ax[i]+1] [ay[i]];
                    if(vf [ax[i]-1] [ay[i]] != '!') vf [ax[i]-1] [ay[i]] = af [ax[i]-1] [ay[i]];
                    if(vf [ax[i]] [ay[i]-1] != '!') vf [ax[i]] [ay[i]-1] = af [ax[i]] [ay[i]-1];
                    if(vf [ax[i]] [ay[i]+1] != '!') vf [ax[i]] [ay[i]+1] = af [ax[i]] [ay[i]+1];
                    //Looking for and marking down adjacent zeros
                    if(af [ax[i]+1] [ay[i]+1] == '0' && vf [ax[i]+1] [ay[i]+1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]+1 == ax[j] && ay[i]+1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]+1;
                            ay[z] = ay[i]+1;
                        }

                    }

                    if(af [ax[i]-1] [ay[i]-1] == '0' && vf [ax[i]-1] [ay[i]-1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]-1 == ax[j] && ay[i]-1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]-1;
                            ay[z] = ay[i]-1;
                        }

                    }

                    if(af [ax[i]+1] [ay[i]-1] == '0' && vf [ax[i]+1] [ay[i]-1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]+1 == ax[j] && ay[i]-1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]+1;
                            ay[z] = ay[i]-1;
                        }

                    }

                    if(af [ax[i]-1] [ay[i]+1] == '0' && vf [ax[i]-1] [ay[i]+1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]-1 == ax[j] && ay[i]+1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]-1;
                            ay[z] = ay[i]+1;
                        }

                    }
                    if(af [ax[i]] [ay[i]+1] == '0' && vf [ax[i]] [ay[i]+1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i] == ax[j] && ay[i]+1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i];
                            ay[z] = ay[i]+1;
                        }

                    }

                    if(af [ax[i]] [ay[i]-1] == '0' && vf [ax[i]] [ay[i]-1] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i] == ax[j] && ay[i]-1 == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i];
                            ay[z] = ay[i]-1;
                        }

                    }

                    if(af [ax[i]+1] [ay[i]] == '0' && vf [ax[i]+1] [ay[i]] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]+1 == ax[j] && ay[i] == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]+1;
                            ay[z] = ay[i];
                        }

                    }

                    if(af [ax[i]-1] [ay[i]] == '0' && vf [ax[i]-1] [ay[i]] != '!'){
                        int c = 0;
                        for(int j=0; j<=i; j++){
                            if(ax[i]-1 == ax[j] && ay[i] == ay[j]) c++;
                        }

                        if(c==0){
                            z++;
                            n++;
                            ax[z] = ax[i]-1;
                            ay[z] = ay[i];
                        }

                    }
                    i++;
                }
                if (debug) system("pause");
            }
            else{
                if(vf[x][y]=='!') continue;
                vf[x][y]=af[x][y];
            }
        }
    }
    return 0;
}
