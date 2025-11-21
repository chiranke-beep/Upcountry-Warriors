#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//structure to hold player information
struct Player {
    int registrationNumber;    //player's registration number
    string fName;              //player's first name
    string lName;              //player's last name
    string dob;                //player's date of birth
    int runsScored;            //runs scored by the player
    string teams[2];           //teams the player is part of(maximum 2)
};

//class to manage club operations
class Club {
private:
    Player players[100];    //array to hold players
    string teams[100];      //array to hold team names
    int playerCount;        //number of players currently in the club
    int teamCount;          //number of teams currently in the club

public:
    //constructor to initialize playerCount and teamCount
    Club() : playerCount(0), teamCount(0) {}

    //function to add a new player
    void addPlayer() {
    	int regNumber;
        if (playerCount >= 100) {
        	cout<<  "                                 "<<endl;
			cout << "\t\t-----------------------------" << endl;
            cout << "\t\tMaximum player limit reached!" << endl;
			cout << "\t\t-----------------------------" << endl;
            return;
        }
        Player player;
        cout << "\t\tEnter player registration number: ";
        cin >> player.registrationNumber;
        cout << "\t\tEnter first name: ";
        cin >> player.fName;
        cout << "\t\tEnter last name: ";
        cin >> player.lName;
        cout << "\t\tEnter date of birth (YYYY-MM-DD): ";
        cin >> player.dob;
        cout << "\t\tEnter runs scored: ";
        cin >> player.runsScored;

        //adding teams to the player
        for (int i = 0; i < 2; ++i) {
            cout << "\t\tEnter team name (or 'done' to finish): ";
            cin >> player.teams[i];
            if (player.teams[i] == "done") {
                player.teams[i] = ""; //mark as empty
                break;
            }
        }


        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tPlayer added successfully" << endl;
        cout << "\t\t-----------------------------" << endl;

        //add the player to the array and increment the count
        players[playerCount++] = player;
        savePlayersToFile();
    }

    //function to display all players
    void displayPlayers() {
    	if (playerCount <= 0){
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tNo Players Registered!" << endl;
        cout << "\t\t-----------------------------" << endl;
		}
        for (int i = 0; i < playerCount; ++i) {
            Player& player = players[i];
            cout << "\t\tRegistration Number: " << player.registrationNumber << endl;
            cout << "\t\tName: " << player.fName << " " << player.lName << endl;
            cout << "\t\tDate of Birth: " << player.dob << endl;
            cout << "\t\tRuns Scored: " << player.runsScored << endl;
            cout << "\t\tTeams: ";
            for (int j = 0; j < 2; ++j) {
                if (player.teams[j].empty()) break;
                cout << player.teams[j] << " ";
            }
            cout << endl << "\t\t-------------------------" << endl;
        }
    }

    //function to search for a player by registration number
    void searchPlayer() {
        int regNumber;
        cout << "\t\tEnter player registration number to search: ";
        cin >> regNumber;

        //search for the player in the array
        for (int i = 0; i < playerCount; ++i) {
            if (players[i].registrationNumber == regNumber) {
                Player& player = players[i];
                cout<<  "                                 "<<endl;
				cout << "\t\t-----------------------------" << endl;
                cout << "\t\tPlayer found!" << endl;
                cout << "\t\t-----------------------------" << endl;
                cout<<  "                                 "<<endl;
                cout << "\t\tRegistration Number: " << player.registrationNumber << endl;
                cout << "\t\tName: " << player.fName << " " << player.lName << endl;
                cout << "\t\tDate of Birth: " << player.dob << endl;
                cout << "\t\tRuns Scored: " << player.runsScored << endl;
                cout << "\t\tTeams: ";
                for (int j = 0; j < 2; ++j) {
                    if (player.teams[j].empty()) break;
                    cout << player.teams[j] << " ";
                }
                cout << endl << "\t\t-----------------------------" << endl;
                return;
            }
        }
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tPlayer not found!" << endl;
		cout << "\t\t-----------------------------" << endl;
    }

    //function to delete a player by registration number
    void deletePlayer() {
        int regNumber;
        cout << "\t\tEnter player registration number to delete: ";
        cin >> regNumber;

        for (int i = 0; i < playerCount; ++i) {
            if (players[i].registrationNumber == regNumber) {
                for (int j = i; j < playerCount - 1; ++j) {
                    players[j] = players[j + 1];
                }
                playerCount--;
                savePlayersToFile();
                cout<<  "                                 "<<endl;
				cout << "\t\t-----------------------------" << endl;
                cout << "\t\tPlayer deleted successfully!" << endl;
				cout << "\t\t-----------------------------" << endl;
                return;
            }
        }
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tPlayer not found!" << endl;
		cout << "\t\t-----------------------------" << endl;
    }



    //function to view team details
    void viewTeamDetails() {
        string teamName;
        cout << "\t\tEnter team name to view details: ";
        cin >> teamName;

        bool found = false;
        for (int i = 0; i < playerCount; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (players[i].teams[j] == teamName) {
                    Player& player = players[i];
                    cout << "\t\tRegistration Number: " << player.registrationNumber << endl;
                    cout << "\t\tName: " << player.fName << " " << player.lName << endl;
                    cout << "\t\tDate of Birth: " << player.dob << endl;
                    cout << "\t\tRuns Scored: " << player.runsScored << endl;
                    cout << "\t\t-------------------------" << endl;
                    found = true;
                }
            }
        }
        if (!found) {
        	cout<<  "                                 "<<endl;
			cout << "\t\t-----------------------------" << endl;
            cout << "\t\tNo players found in the team!" << endl;
			cout << "\t\t-----------------------------" << endl;
        }
    }

    //function to manage teams
    void manageTeams() {
        int choice;
        while (true) {
    		cout<<  "                                 " <<endl;
            cout << "\t\t=============================" << endl;
            cout << "\t\t          MANAGE TEAMS          " << endl;
            cout << "\t\t=============================" << endl;
            cout << "\t         1.Add Team" << endl;
            cout << "\t         2.Delete Team" << endl;
            cout << "\t         3.Display Teams" << endl;
            cout << "\t         4.Back to Main Menu" << endl;
            cout << "\t\t=============================" << endl;
            cout << "\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addTeam();
                    break;
                case 2:
                    deleteTeam();
                    break;
                case 3:
                    displayTeams();
                    break;
                case 4:
                    return;
                default:
                	cout<<  "                                 "<<endl;
					cout << "\t\t-----------------------------" << endl;
                    cout << "\t\tInvalid choice! Please try again." << endl;
					cout << "\t\t-----------------------------" << endl;
            }
        }
    }

    //function to add a team
    void addTeam() {
        if (teamCount >= 100) {
        	cout<<  "                                 "<<endl;
			cout << "\t\t-----------------------------" << endl;
            cout << "\t\tMaximum team limit reached!" << endl;
			cout << "\t\t-----------------------------" << endl;
            return;
        }

        string teamName;
        cout << "\t\tEnter team name: ";
        cin >> teamName;

        //check if the team already exists
        for (int i = 0; i < teamCount; ++i) {
            if (teams[i] == teamName) {
            	cout<<  "                                 "<<endl;
				cout << "\t\t-----------------------------" << endl;
                cout << "\t\tTeam already exists!" << endl;
				cout << "\t\t-----------------------------" << endl;
                return;
            }
        }

        //add the team to the array and increment the count
        teams[teamCount++] = teamName;
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tTeam added successfully!" << endl;
		cout << "\t\t-----------------------------" << endl;
    }

    //function to delete a team
    void deleteTeam() {
        string teamName;
        cout << "\t\tEnter team name to delete: ";
        cin >> teamName;

        for (int i = 0; i < teamCount; ++i) {
            if (teams[i] == teamName) {
                for (int j = i; j < teamCount - 1; ++j) {
                    teams[j] = teams[j + 1];
                }
                teamCount--;
                cout<<  "                                 "<<endl;
				cout << "\t\t-----------------------------" << endl;
                cout << "\t\tTeam deleted successfully!" << endl;
				cout << "\t\t-----------------------------" << endl;
                return;
            }
        }
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tTeam not found!" << endl;
        cout << "\t\t-----------------------------" << endl;

    }

    //function to display all teams
    void displayTeams() {

        cout << "\t\t=============================" << endl;
        cout << "\t\t          TEAMS LIST            " << endl;
        cout << "\t\t=============================" << endl;
        if (teamCount <= 0){
        cout<<  "                                 "<<endl;
		cout << "\t\t-----------------------------" << endl;
        cout << "\t\tNo Teams Registered!" << endl;
        cout << "\t\t-----------------------------" << endl;
		}
        for (int i = 0; i < teamCount; ++i) {
            cout << "\t\t" << teams[i] << endl;
        }
    }

    //function to load players from a file
    void loadPlayersFromFile() {
        ifstream inFile("players.txt");
        if (!inFile) return;

        playerCount = 0;
        //read player information from the file
        while (inFile >> players[playerCount].registrationNumber
                      >> players[playerCount].fName
                      >> players[playerCount].lName
                      >> players[playerCount].dob
                      >> players[playerCount].runsScored) {
            for (int j = 0; j < 2; ++j) {
                inFile >> players[playerCount].teams[j];
                if (players[playerCount].teams[j] == "end") {
                    players[playerCount].teams[j] = ""; // Mark as end
                    break;
                }
            }
            playerCount++;
        }
    }

    //function to save players to a file
    void savePlayersToFile() {
        ofstream outFile("players.txt");
        for (int i = 0; i < playerCount; ++i) {
            Player& player = players[i];
            outFile << player.registrationNumber << " "
                    << player.fName << " "
                    << player.lName << " "
                    << player.dob << " "
                    << player.runsScored << " ";
            for (int j = 0; j < 2; ++j) {
                if (player.teams[j].empty()) break;
                outFile << player.teams[j] << " ";
            }
            outFile << "end" << endl;
        }
    }
};

//class to manage user authentication
class User {
private:
    string username; //username
    string password; //password

public:
    //constructor to initialize username and password
    User(string usr, string pwd) : username(usr), password(pwd) {}

    //function to login a user
    bool login(string usr, string pwd) {
        return usr == username && pwd == password;
    }
};

//function to display the main menu and handle user choices
void mainMenu(Club& club) {
    int choice;
    while (true) {
    	cout<<  "                                 "<<endl;
        cout << "\t\t=============================" << endl;
        cout << "\t\t          MAIN MENU            " << endl;
        cout << "\t\t=============================" << endl;
        cout << "\t         1.Display Players" << endl;
        cout << "\t         2.Add New Player" << endl;
        cout << "\t         3.Search Player" << endl;
        cout << "\t         4.Delete Player" << endl;
        cout << "\t         5.Manage Teams" << endl;
        cout << "\t         6.View Team Details" << endl;
        cout << "\t         7.Logout" << endl;
        cout << "\t         8.Exit" << endl;
        cout << "\t\t=============================" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                club.displayPlayers();
                break;
            case 2:
                club.addPlayer();
                break;
            case 3:
                club.searchPlayer();
                break;
            case 4:
                club.deletePlayer();
                break;
            case 5:
                club.manageTeams();
                break;
            case 6:
                club.viewTeamDetails();
                break;
            case 7:
            	cout << "                                 "<<endl;
            	cout << "\t\t-----------------------------" << endl;
            	cout << "\t\tLogged out"<<endl;
            	cout << "\t\t-----------------------------" << endl;
            	cout << "                                 "<<endl;
                return;
            case 8:
            	cout<<"Exiting...";
                exit(0);
            default:
            	cout<<  "                                 "<<endl;
				cout << "\t\t-----------------------------" << endl;
                cout << "\t\tInvalid choice! Please try again." << endl;
				cout << "\t\t-----------------------------" << endl;
        }
    }
}

int main() {
    Club club; //create a club object
    club.loadPlayersFromFile(); //load players from file

    User user("chiran", "123"); //create a user object
    string username, password;

    while (true) {
        cout << "\t\t=============================" << endl;
        cout << "\t\t***** UPCOUNTRY WARRIORS *****" << endl;
        cout << "\t\t=============================" << endl;
        cout << "\t\t          LOGIN                " << endl;
        cout << "\t\t=============================" << endl;
        cout << "\t\tUsername: ";
        cin >> username;
        cout << "\t\tPassword: ";
        cin >> password;
        cout << "\t\t=============================" << endl;


        //check user credentials and display main menu if valid
        if (user.login(username, password)) {
        cout<<  "                                 "<<endl;
        cout << "\t\t-----------------------------" << endl;
        cout << "\t\tLogged successfully" << endl;
        cout << "\t\t-----------------------------" << endl;
        mainMenu(club);



        } else {
        	cout<<  "                                 "<<endl;
			cout << "\t\t-----------------------------" << endl;
            cout << "\t\tLogging Failed" << endl;
			cout << "\t\t-----------------------------" << endl;
			cout<<  "                                 "<<endl;
			main();
        }


    }
    return 0;
}

