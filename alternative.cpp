
//ALTERNATIVELY, this piece of code can be used to solve the same problem, but with slightly increased time complexity




#include <iostream>
#include <string>
using namespace std;

struct PLAYER{
    char TEAM;
    int HEALTH;
    int POSITION; 
    PLAYER(): TEAM('N'), HEALTH(0), POSITION(-1){}
};

void RACE(int *position, int *health, string team, int num);
int findMax(int* positions, int size);
bool checkRACE(int *RADIANTcurr, int *DIREcurr, int size, int steps);
void takeEntry(int* myArray, int size);
void showEntry(int* myArray, int size);

int main(){
    int num;
    cout << "Enter number of heroes, n: ";
    cin >> num;

    int position[num];
    int health[num];
    string team;

    cout << "Enter position array: ";
    takeEntry(position, num);

    cout <<"Enter health array: ";
    takeEntry(health, num);

    cout <<"Enter team string: ";
    cin >> team;

    RACE(position, health, team, num);

    return 0;
}

void RACE(int *position, int *health, string team, int num){
    int ctrRAD=0, ctrDIR=0;
    int size = (findMax(position, num) + 1);

    PLAYER nullplayer;
    PLAYER raceline[3*size] = {nullplayer};

    int RADIANTcurr[size] = {0};
    int DIREcurr[size] = {0};

    for (int idx = 0; idx < num; idx ++){
        raceline[size + position[idx]].HEALTH = health[idx];
        raceline[size + position[idx]].POSITION = position[idx];
        raceline[size + position[idx]].TEAM = team[idx];

        if (health[idx] == 'R'){
            RADIANTcurr[position[idx]] = 1;
        }
        else{
            DIREcurr[position[idx]] = 1;
        }
    }

    int steps = 0;

    while (checkRACE(RADIANTcurr, DIREcurr, size, steps)){
        steps+=1;
        int idx = ((3*size)-1);
        while (idx>0){
            idx--;
            if (raceline[idx].POSITION == -1){
                continue;
            }

            if (raceline[idx].TEAM == 'R'){
                if (raceline[idx+1].TEAM == 'N'){
                    raceline[idx+1] = raceline[idx];
                    raceline[idx] = nullplayer;
                    continue;
                }
                else if ((raceline[idx+1]).TEAM == 'D'){
                    if (raceline[idx].HEALTH > raceline[idx+1].HEALTH){
                        DIREcurr[raceline[idx+1].POSITION] = 0;
                        raceline[idx].HEALTH -= 1;
                        raceline[idx+1] = raceline[idx];
                        raceline[idx] = nullplayer;
                        continue;
                    }
                    else if (raceline[idx].HEALTH < raceline[idx+1].HEALTH){
                        RADIANTcurr[raceline[idx].POSITION] = 0;
                        raceline[idx+1].HEALTH -=1;
                        raceline[idx] = raceline[idx+1];
                        raceline[idx+1] = nullplayer;
                        continue;
                    }
                    else{
                        raceline[idx] = raceline[idx+1] = nullplayer;
                        DIREcurr[raceline[idx+1].POSITION] = 0;
                        RADIANTcurr[raceline[idx].POSITION] = 0;
                        continue;
                    }
                }
            }

            if (raceline[idx].TEAM == 'D'){
                if (raceline[idx-1].TEAM == 'N'){
                    raceline[idx-1] = raceline[idx];
                    raceline[idx] = nullplayer;
                    idx--;
                    continue;
                }
            }
        }
    }

    int healthTEMP[size] = {0};
    int count = 0;
    for (int idx = 0; idx < (3*size); idx++){
        if (raceline[idx].POSITION!=-1){
            count ++;
            healthTEMP[raceline[idx].POSITION] = raceline[idx].HEALTH;
        }
    }

    int RESULT[count] = {0};
    int RESidx = 0;
    for (int idx = 0; idx < num; idx++){
        if ((healthTEMP[position[idx]]) > 0){
            RESULT[RESidx] = healthTEMP[position[idx]];
            RESidx++;
        }
    }
    // our result is RESidx;
    showEntry(RESULT, count);
}


int findMax(int* positions, int size ){
// assume n>0;

    int maxi = positions[0];
    for (int idx = 1; idx < size; idx++){
        if (positions[idx] > maxi){
            maxi = positions[idx];
        }
    }

    return maxi;
}

bool checkRACE(int *RADIANTcurr, int *DIREcurr, int size, int steps){
    int RADmin = -1;
    int DIRmax = size;

    for (int idx = 0; idx < size; idx++){
        if (RADIANTcurr[idx] == 1){
            RADmin = idx;
            break;
        }
    }

    for (int idx = size-1; idx >= 0; idx--){
        if (DIREcurr[idx] == 1){
            DIRmax = idx;
            break;
        }
    }

    if ((RADmin+steps)>(DIRmax-steps)){
        return false;
    }
    return true;
}

void takeEntry(int* myArray, int size){
    for (int idx = 0; idx < size; idx ++){
        cin >> myArray[idx];
    }
}
void showEntry(int* myArray, int size){
    if (size==0){
        cout << "[]";
        return;
    }
    cout <<"[";
    for (int idx = 0; idx < size-1; idx++){
        cout << myArray[idx] <<",";
    }
    cout <<myArray[size-1] <<"]";
    cout <<endl;
}
