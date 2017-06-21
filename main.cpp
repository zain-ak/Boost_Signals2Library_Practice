/**
 @author Zain Khalid
 @version 1.0
 */


#include <cstdlib>
#include <iostream>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

/**
 Sample class that'll be used for the testing of signal<T>
 Signal is called whenever a goal is scored
 */
class Player {
public:
    string name;
    int goals;
    Player(string name) : name(name) {
        goals = 0;
    }
    signal<void(string, int)> Scores; //takes the name and number of goals that are used for the lambda in main()
    
    void goalScored() {
        goals += 1;
        Scores(name, goals);
    }
};

int main(int argc, char** argv) {
    
    Player p("George Best");
    
    /*Creation of the lambda, it is assigned to auto c so that it can be disconnected later on*/
    auto c = p.Scores.connect([](string name, int goals) {
        if (goals == 1)
            cout << "Goal scored by " << name << "! He now has " << goals << " goal\n";
        else
            cout << "Goal scored by " << name << "! He now has " << goals << " goals\n";
    });
    
    p.goalScored();
    p.goalScored();
    
    /*Below is where c is disconnected, this causes it to not print what's in the lambda above*/
    {
      shared_connection_block b(c);
      p.goalScored();
      p.goalScored();
    }
    
    p.goalScored();

    return 0;
}

