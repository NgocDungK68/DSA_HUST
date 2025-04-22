#include <iostream>
using namespace std;

class Vote {
public:
    int voteID;
    int candidate;
    string time;
    int status;
};

const int MAX = 10;
class VoteList {
private:
    Vote voteList[MAX];
    int n;                    // num of elements
public:
    VoteList() { n = 0; }

    void insert(Vote vote);
    void changeStatus(int voteID);
    void removeInvalidVotes();
    int findWinner();
};

void VoteList::insert(Vote vote) {
    if (n == MAX) return;
    voteList[n] = vote;
    n++;
}

void VoteList::changeStatus(int voteID) {
    for (int i = 0; i < n; i++) {
        if (voteList[i].voteID == voteID) {
            voteList[i].voteID = !voteList[i].voteID;
            break;
        }
    }
}

void VoteList::removeInvalidVotes() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!voteList[i].status) {
            voteList[i].status = -1;
            count++;
        } else if (count > 0) {
            voteList[i - count] = voteList[i];
        }
    }

    n -= count;
}

int VoteList::findWinner() {

}