#include <iostream>
#include <string>
using namespace std;

struct PLAYER{
    char TEAM;
    int HEALTH;
    int POSITION; 
    int currentP;
    PLAYER(): TEAM('N'), HEALTH(0), POSITION(-1), currentP(-1){}

};


void RACE(int *position, int *health, string team, int num);
void count_sort(PLAYER *array, int size);
void takeEntry(int* myArray, int size);
void showEntry(int* myArray, int size);

struct Item{
    PLAYER hero;
    Item* next;
    Item(): hero(PLAYER()), next(nullptr){}
};

class Stack{
//Stack: push, pop, top, isEmpty, isFull, display, constructor, destructor
    private:
        Item* top;
        int counter;
        int capacity;

    public:
    Stack(): top(nullptr), counter(0), capacity(100000){}

    void push(PLAYER value);
    PLAYER pop();
    bool isEmpty();
    bool isFull();
    void setCapacity(int cap);
    PLAYER getTop();

    ~Stack(){
        Item* current = top;
        Item* next = top->next;
        while (current!=nullptr){
            next = current->next;
            delete current;
            current = next;     //////check for error
        }
    }
};

int main(){

    // taking inputs
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
    PLAYER raceline[num];

    // initializing new array called raceline of all 
    // players in increasing order of positions
    for (int idx = 0; idx < num; idx ++){
        PLAYER myPlayer;
        myPlayer.HEALTH = health[idx];
        myPlayer.POSITION = position[idx];
        myPlayer.TEAM = team[idx];
        myPlayer.currentP = -1;

        raceline[idx] = myPlayer;
    }

    count_sort(raceline, num);  // T(n) = O(n + k) where k is range
    int minPosition = raceline[0].POSITION;
    int maxPosition = raceline[num-1].POSITION;

    // two stacks - one to store players of R team
    // another to store players who have fought and survived, no longer battles are left
    Stack RADIANT;
    Stack ALIVE;

    int counter = num;

    // T(n) = O(n)
    for (int idx = 0; idx < num; idx ++){
        if (raceline[idx].TEAM == 'D'){
            while (!RADIANT.isEmpty() && (raceline[idx].HEALTH > RADIANT.getTop().HEALTH)){
                RADIANT.pop();
                raceline[idx].HEALTH -= 1;
                counter -= 1;
            }
            if (RADIANT.isEmpty()){
                ALIVE.push(raceline[idx]);
            }
            else if (RADIANT.getTop().HEALTH == raceline[idx].HEALTH){
                RADIANT.pop();
                counter -= 2;
            }
            else{
                PLAYER net = RADIANT.pop();
                net.HEALTH -= 1;
                RADIANT.push(net);
                counter -= 1;
            }
        }

        else {
            RADIANT.push(raceline[idx]);
        }
    }

    // any remaining players live.
    while (!RADIANT.isEmpty()){
        ALIVE.push(RADIANT.pop());
    }

    int tempArray[maxPosition - minPosition + 1] = {0};

    for (int idx = 0; idx < counter; idx ++){
        PLAYER myPlayer = ALIVE.pop();
        tempArray[myPlayer.POSITION - minPosition] = myPlayer.HEALTH;
    }
    
    int result[counter];
    int Ridx = 0;

    // arranging based on initial entry order given
    for (int i = 0; i < num; i++){
        if (tempArray[position[i] - minPosition] != 0){
            result[Ridx] = tempArray[position[i] - minPosition];
            Ridx += 1;
        }
    }

   showEntry(result, counter);
   exit(0);
}

void count_sort(PLAYER *array, int size){
    
    if (size == 0){
        return;
    }

    int maximum = array[0].POSITION;
    int minimum = array[0].POSITION;

    for (int i = 0; i < size; i++){
        if (array[i].POSITION > maximum){
            maximum = array[i].POSITION;
        }

        if (array[i].POSITION < minimum){
            minimum = array[i].POSITION;
        }
    }
    int range = (maximum- minimum + 1);

    PLAYER tempArray[range];

    for (int i = 0; i < range; i++){
        PLAYER nullplayer;
        nullplayer.HEALTH = 'N';
        tempArray[i] = nullplayer;
    }

    for (int i = 0; i < size; i++){
        tempArray[(array[i].POSITION) - minimum] = array[i];
    }

    int idx = 0;
    for (int j = 0; j < range; j++){
        if (tempArray[j].TEAM != 'N'){
            array[idx] = tempArray[j];
            array[idx].currentP = idx;
            idx++;
        }
    }

    
}

////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////
void Stack::push(PLAYER value){
    if (counter < capacity){
        Item* newItem = new Item();
        newItem->hero = value;
        newItem->next = top;
        top = newItem;
        counter += 1;
    }
    else{
        cout << "Capacity Full!";
    }
}

PLAYER Stack::pop(){
    if (counter > 0){
        Item* temp = top;
        PLAYER value = top->hero;
        top = top->next;
        delete temp;
        counter -= 1;
        return value;
    }
    else{
        cout << "Stack Empty!";
        return PLAYER();
    }
}

PLAYER Stack::getTop(){
    if (counter > 0){
        return (top->hero);
    }
    else{
        return PLAYER();
    }
}

bool Stack::isEmpty(){
    if (top==nullptr){
        return true;
    }
    return false;
}

bool Stack::isFull(){
    if (counter==capacity){
        return true;
    }
    return false;
}

void Stack::setCapacity(int cap){
    capacity = cap;
}
///////////////////////////////////////////////////////////////////////////////////////////







// ALTERNATIVELY, this piece of code can be used to solve the same problem, but with slightly increased time complexity




// #include <iostream>
// #include <string>
// using namespace std;

// struct PLAYER{
//     char TEAM;
//     int HEALTH;
//     int POSITION; 
//     PLAYER(): TEAM('N'), HEALTH(0), POSITION(-1){}
// };

// void RACE(int *position, int *health, string team, int num);
// int findMax(int* positions, int size);
// bool checkRACE(int *RADIANTcurr, int *DIREcurr, int size, int steps);
// void takeEntry(int* myArray, int size);
// void showEntry(int* myArray, int size);

// int main(){
//     int num;
//     cout << "Enter number of heroes, n: ";
//     cin >> num;

//     int position[num];
//     int health[num];
//     string team;

//     cout << "Enter position array: ";
//     takeEntry(position, num);

//     cout <<"Enter health array: ";
//     takeEntry(health, num);

//     cout <<"Enter team string: ";
//     cin >> team;

//     RACE(position, health, team, num);

//     return 0;
// }

// void RACE(int *position, int *health, string team, int num){
//     int ctrRAD=0, ctrDIR=0;
//     int size = (findMax(position, num) + 1);

//     PLAYER nullplayer;
//     PLAYER raceline[3*size] = {nullplayer};

//     int RADIANTcurr[size] = {0};
//     int DIREcurr[size] = {0};

//     for (int idx = 0; idx < num; idx ++){
//         raceline[size + position[idx]].HEALTH = health[idx];
//         raceline[size + position[idx]].POSITION = position[idx];
//         raceline[size + position[idx]].TEAM = team[idx];

//         if (health[idx] == 'R'){
//             RADIANTcurr[position[idx]] = 1;
//         }
//         else{
//             DIREcurr[position[idx]] = 1;
//         }
//     }

//     int steps = 0;

//     while (checkRACE(RADIANTcurr, DIREcurr, size, steps)){
//         steps+=1;
//         int idx = ((3*size)-1);
//         while (idx>0){
//             idx--;
//             if (raceline[idx].POSITION == -1){
//                 continue;
//             }

//             if (raceline[idx].TEAM == 'R'){
//                 if (raceline[idx+1].TEAM == 'N'){
//                     raceline[idx+1] = raceline[idx];
//                     raceline[idx] = nullplayer;
//                     continue;
//                 }
//                 else if ((raceline[idx+1]).TEAM == 'D'){
//                     if (raceline[idx].HEALTH > raceline[idx+1].HEALTH){
//                         DIREcurr[raceline[idx+1].POSITION] = 0;
//                         raceline[idx].HEALTH -= 1;
//                         raceline[idx+1] = raceline[idx];
//                         raceline[idx] = nullplayer;
//                         continue;
//                     }
//                     else if (raceline[idx].HEALTH < raceline[idx+1].HEALTH){
//                         RADIANTcurr[raceline[idx].POSITION] = 0;
//                         raceline[idx+1].HEALTH -=1;
//                         raceline[idx] = raceline[idx+1];
//                         raceline[idx+1] = nullplayer;
//                         continue;
//                     }
//                     else{
//                         raceline[idx] = raceline[idx+1] = nullplayer;
//                         DIREcurr[raceline[idx+1].POSITION] = 0;
//                         RADIANTcurr[raceline[idx].POSITION] = 0;
//                         continue;
//                     }
//                 }
//             }

//             if (raceline[idx].TEAM == 'D'){
//                 if (raceline[idx-1].TEAM == 'N'){
//                     raceline[idx-1] = raceline[idx];
//                     raceline[idx] = nullplayer;
//                     idx--;
//                     continue;
//                 }
//             }
//         }
//     }

//     int healthTEMP[size] = {0};
//     int count = 0;
//     for (int idx = 0; idx < (3*size); idx++){
//         if (raceline[idx].POSITION!=-1){
//             count ++;
//             healthTEMP[raceline[idx].POSITION] = raceline[idx].HEALTH;
//         }
//     }

//     int RESULT[count] = {0};
//     int RESidx = 0;
//     for (int idx = 0; idx < num; idx++){
//         if ((healthTEMP[position[idx]]) > 0){
//             RESULT[RESidx] = healthTEMP[position[idx]];
//             RESidx++;
//         }
//     }
//     // our result is RESidx;
//     showEntry(RESULT, count);
// }


// int findMax(int* positions, int size ){
// // assume n>0;

//     int maxi = positions[0];
//     for (int idx = 1; idx < size; idx++){
//         if (positions[idx] > maxi){
//             maxi = positions[idx];
//         }
//     }

//     return maxi;
// }

// bool checkRACE(int *RADIANTcurr, int *DIREcurr, int size, int steps){
//     int RADmin = -1;
//     int DIRmax = size;

//     for (int idx = 0; idx < size; idx++){
//         if (RADIANTcurr[idx] == 1){
//             RADmin = idx;
//             break;
//         }
//     }

//     for (int idx = size-1; idx >= 0; idx--){
//         if (DIREcurr[idx] == 1){
//             DIRmax = idx;
//             break;
//         }
//     }

//     if ((RADmin+steps)>(DIRmax-steps)){
//         return false;
//     }
//     return true;
// }

// void takeEntry(int* myArray, int size){
//     for (int idx = 0; idx < size; idx ++){
//         cin >> myArray[idx];
//     }
// }
// void showEntry(int* myArray, int size){
//     if (size==0){
//         cout << "[]";
//         return;
//     }
//     cout <<"[";
//     for (int idx = 0; idx < size-1; idx++){
//         cout << myArray[idx] <<",";
//     }
//     cout <<myArray[size-1] <<"]";
//     cout <<endl;
// }