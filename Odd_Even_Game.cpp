#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define _WIN32_WINNT 0x500
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")

// Global Variable Declaration
int resultcode,practice,launch=1,sound=1;
char *date;

// Functions Prototyping
void oddenface();
void play();
void gamelog();
int randompick();
void CheckWinner();
void logmaker();
void resetlog();
void help();
void datetime();
void music();

// Class Declaration
class Players
{
public:
    char name[30];
    unsigned int pick;
    char side;
    int score;
    char result[6];
    Players()
    {
        score=0;
    }
} user,sys;


// Function for Displaying Home Screen
int main()
{
    if(launch==1)
    {
        ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
        mciSendString("open \"bgm.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
        launch=0;
        music();

    }
    practice=0;

    char op[10];
    char choice;

    system("cls");
    oddenface();
    cout<<"\033[0m"<<"\n\t\t\t\t\t\t\t\t\t\t ========================================"<<"\033[1;32m";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32mWELCOME TO\n\t\t\t\t\t\t\t\t\t\t     ODDS AND EVENS GAME WITH ODDEN!\033[0m"<<"\033[0m";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================\n";

    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t [FULL SCREEN RECOMMENDED]\n\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t1 - Play Now\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t2 - View Game Log\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t3 - Help\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t4 - Toggle Game Music\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t5 - Quit\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t=================\n\t\t\t\t\t\t\t\t\t\tEnter Your Choice: ";
errorhandler_1:
    cin>>op;
    if(strlen(op)==1)                                           // Handling Accidental String Inputs
        choice=op[0];
    else
        choice='0';

    switch(choice)                                          // Switch for Navigation
    {
    case '1':
        play();
        break;
    case '2':
        gamelog();
        break;
    case '3':
        help();
        break;
    case '4':
        music();
        break;
    case '5':
        cout<<("\033[1;35m");
        cout<<("\n\t\t\t\t\t\t\t\t\tThank you for Checking Out the Game! Created by Govind Krishnan & Bibin P Daniel.\n\n");
        cout<<("\033[0m");
        Sleep(2000);
        exit(0);
        break;
    default:
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\033[0;31mOops! That's invalid.\n";
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\033[0mAnother Chance! Enter Valid Menu Index : ";
        goto errorhandler_1;                                    // Error Handler
    }

}
// Function to Start Game after asking Player Name & Side
void play()
{

    int n=1,t,randomside;
    char team[5];
    system("cls");
    user.score=sys.score=0;
    oddenface();
    cout<<"\033[0;36m"<<"\n\t\t\t\t\t\t\t\t\t\t    I'm Odden. What should I call you? "<<"\033[0m";

    cout<<"\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t Enter Your Name: ";
    cin.ignore();
    cin.getline(user.name,30);
    system("cls");
    oddenface();
    cout<<"\033[0;36m"<<"\n\t\t\t\t\t\t\t\t\t\t   \t    Which side are you? \n"<<"\033[0m";

    cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t Odds or Evens?\n\t\t\t\t\t\t\t\t\t\t1 - Odds\n\t\t\t\t\t\t\t\t\t\t2 - Evens\n";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t Enter Your Preference :  ";

    cin>>team;
    if(strlen(team)==1)                                           // Handling Accidental String Inputs
        user.side=team[0];
    else
        user.side='0';

    while(n<=25)                                    // Loop for 25 turns
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\n";
        oddenface();
        cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32m LET'S PLAY! \033[0m";
        cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";
        cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t Pick \"10\" to Abort The Game.";

        cout<<"\n\n \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;35mScorecard\n\033[0m";
        cout<<" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t=========\n";
        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<user.name<<" : "<<user.score<<" \n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tOdden : "<<sys.score<<endl;

        if (user.side!='1' && user.side!='2' || practice==1)                                       // Easter Egg Practice Mode if Invalid Side Selected
        {
            cout<<"\033[1;31m";
            cout<<"\n\t\t\t\t\t\t\t\t\t  YOU DID NOT CHOOSE A VALID SIDE! MYSTERY MODE ACTIVATED!";
            cout<<"\n\n\t\t\t\t\t\t\t\t\tNo Worries "<<user.name<<"! Don't forget to choose a Valid Side Next Time! \n";
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    LET'S CONSIDER THIS A PRACTICE MATCH. NO CHANGES TO GAME LOG! (^-^)\n"<<"\033[0m";

            practice=1;

            if (user.side!='1' && user.side!='2')
            {
                srand(time(0));
                randomside=(rand()%1)+1;

                if(randomside==1)
                    user.side='1';
                else
                    user.side='2';
            }

        }

        cout<<"\n\n\t\t\t\t\t\t\t\t\t\t Pick a Number between 0 & 9 : ";
unfair:
        cin>>user.pick;

        if (user.pick==10)                                                                  // Game Abortion
        {
            cout<<"\033[0;36m";
            cout<<"\n\n\t\t\t\t\t\t\t\t\t\t Game Aborted! Returning to Home Screen.";
            Sleep(2000);
            main();
        }
        else if (user.pick>9 || cin.fail())                                                               // Unfair Play.
        {
            cin.clear();
            cin.ignore();
            cout<<"\033[1;31m";
            cout<<"\n\n\t\t\t\t\t\t\t\t\tThat's Unfair "<<user.name<<"! Only Numbers from 0 to 9 Allowed. Read Help if New to Game.\n\t\t\t\t\t\t\t\t\t\033[0m Another Chance : ";
            goto unfair;
        }

        sys.pick=randompick();                                                          // Calling function for random number generation
        cout<<"\n\t\t\t\t\t\t\t\t\t\t Odin Picks : "<<sys.pick;
        Sleep(1000);
        t = user.pick+sys.pick;
        if (user.pick==sys.pick)                                                        // Game/Loop Ended when same numbers picked
            break;
        else if (t%2==0 && user.side=='2')
            user.score=user.score+t;
        else if (t%2==1 && user.side=='1')
            user.score=user.score+t;
        else
            sys.score=sys.score+t;
        n++;
    }

    CheckWinner();                                                                 // Calling Result Page

}

// Function to Generate Random Numbers from 0 to 9
int randompick()
{
    int numb;
    srand(time(0));
    numb= rand() % 9;

    return numb;
}

//Result Page Function
void CheckWinner()
{
    char navi[5],nav,r;

    system("cls");
    oddenface();
    cout<<("\n\t\t\t\t\t\t\t\t\t\t ========================================");
    cout<<("\n\t\t\t\t\t\t\t\t\t\t\t\t RESULTS ");
    cout<<("\n\t\t\t\t\t\t\t\t\t\t ========================================");

    if (user.pick==sys.pick)
        cout<<"\n\n\t\t\t\t\t\t\t\t\t\t  We picked the Same Number & That's Game Over! \n\n\t\t\t\t\t\t\t\t\t\t\t Now, let's see who won!";

    if (user.score>sys.score)
    {
        cout<<"\n\n\033[1;32m Kudos "<<user.name<<"! You have defeated me! (^-^) \033[0m\n\n\t\t\t\t\t\t\t\t\t\t Your Score : "<<user.score<<" \t Odden's Score : "<<sys.score;
        resultcode=1;
    }
    if (user.score<sys.score)
    {
        cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32m Well Played "<<user.name<<"! That was tougher than I thought! Come Back Anytime for a Rematch! (^-^) \033[0m\n\n\t\t\t\t\t\t\t\t\t\t Your Score : "<<user.score<<" \t Odden's Score : "<<sys.score<<endl;
        resultcode=0;
    }
    if (user.score==sys.score)
    {
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32m Scores are leveled & It's a Draw! That's splendid, "<<user.name<<".  (^-^) \033[0m\n\n\t\t\t\t\t\t\t\t\t\t Your Score : "<<user.score<<" \t Odden's Score : "<<sys.score<<endl;
        resultcode=2;
    }
    if (practice==0)                                                // Writing Log if not Practice Mode
        logmaker();


    // Navigation Menu
    cout<<"\n\n  Go back to Home Screen?\n";
    cout<<"\t 1 - Yes\n\t 2 - Quit Game\n\n\t";
    cout<<"\t Enter Your Choice: ";
errorhandler_2:
    cin>>navi;
    if(strlen(navi)==1)                                           // Handling Accidental String Inputs
        nav=navi[0];
    else
        nav='0';
    if (nav=='1')
        main();
    else if (nav=='2')
    {
        cout<<"\033[1;35m";
        cout<<"\n\t\t\t\t\t\t\t\tThank you for Checking Out the Game!\tCreated by Govind Krishnan & Bibin P Daniel.\n\n";
        cout<<"\033[0m";
        Sleep(2000);
        exit(0);
    }
    else
    {
        cout<<("\t\t\033[0;31mInvalid Menu Index. Another Chance!\n");
        cout<<("\n\t\t\033[0mEnter Valid Menu Index :");
        goto errorhandler_2;
    }
}

//Log File Writing Function
void logmaker()
{
    if (resultcode==1)
        strcpy(user.result,"Won");
    else if (resultcode==0)
        strcpy(user.result,"Lost");
    else if (resultcode==2)
        strcpy(user.result,"Drawn");

    datetime();

    ofstream log;
    log.open("gamelog.txt",ios::app);
    if(log.fail())                                                                // Error Handling
    {
        cout<<("\nGame Log File Not Found or Couldn't be Created!\n");
        Sleep(1000);
        main();
    }

    log<<"\n\n\t\t\t\t\t\t\t\t\t Date : "<<date<<"\n\t\t\t\t\t\t\t\t\t Name : "<<user.name<<"\n\t\t\t\t\t\t\t\t\t Score : "<<user.score<<"\n\t\t\t\t\t\t\t\t\t Result : "<<user.result<<"\n\t\t\t\t\t\t\t\t\t _______________________________\n";
    log.close();
}

// Game Log Page Function
void gamelog()
{
    char navi[5],nav;
    char c;
    system("cls");
    oddenface();
    cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32m GAME LOG \033[0m";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";
    ifstream log("gamelog.txt");

    if(log.fail())                                                                                        // Error Handling
    {
        cout<<"\033[0;36m";
        cout<<"\n\n\n\t\t\t\t\t\t\t\t\t    No Gaming History to Show. Returning to Main Menu \n";
        Sleep(2000);
        main();
    }
    else
    {
        while(log.get(c))                                                                           // Reading Log File
        {
            cout<<c;
        }

    }


    log.close();


    // Navigation Menu
    cout<<"\n\n\n  What To Do Next?\n";
    cout<<"\t 1 - Back to Home Screen\n\t 2 - Clear Game Log\n\t 3 - Quit\n\n\t";
    cout<<"\t Enter Your Choice: ";
errorhandler_3:
    cin>>navi;
    if(strlen(navi)==1)                                           // Handling Accidental String Inputs
        nav=navi[0];
    else
        nav='0';

    if (nav=='1')
        main();
    else if (nav=='2')
        resetlog();                                                                                         // Deleting Log
    else if (nav=='3')
    {
        cout<<"\033[1;35m";
        cout<<"\n\t\t\t\t\t\t\t\tThank you for Checking Out the Game!\tCreated by Govind Krishnan & Bibin P Daniel.\n\n";
        cout<<"\033[0m";
        Sleep(2000);
        exit(0);
    }
    else
    {
        cout<<"\t\t\033[0;31mInvalid Menu Index. Another Chance!\n";
        cout<<"\n\t\t\033[0mEnter Valid Menu Index :";
        goto errorhandler_3;
    }
}

//Function to Wipe Game Log
void resetlog()
{
    int status;
    status=remove("gamelog.txt");
    if(status!=0)                                                                                            // Error Handling
    {
        cout<<"\033[0;36m"<<"\nGame Log File Not Found or Couldn't be Cleared!\n"<<"\033[0m";
        Sleep(1000);
    }
    else
    {
        cout<<"\033[0;36m"<<"\nGame Log Cleared!\n"<<"\033[0m";
        Sleep(1000);
    }
    gamelog();              // Refreshing Game Log
}

// Function to Read External Help File
void help()
{
    char navi[5],nav;
    system("cls");
    oddenface();
    ifstream helpfile("help.txt");
    char c;
    cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32m   HELP \033[0m";
    cout<<"\n\t\t\t\t\t\t\t\t\t\t ========================================";

    if(helpfile.fail())                                                             // Error Handling
    {
        cout<<"\n\n\n\t\t\t\t\t\t\t\t\t\033[1;31m     Help File Not Found! Returning Back to Home Screen.\n";
        Sleep(2000);
        main();
    }

    while(helpfile.get(c))                                                // Reading Help File
    {
        cout<<c;
    }
    helpfile.close();
    cout<<"\n\n  Go back to Home Screen?\n";
    cout<<"\t 1 - Yes\n\t 2 - Quit Game\n\n\t";
    cout<<" Enter Your Choice: ";
errorhandler_4:
    cin>>navi;
    if(strlen(navi)==1)                                           // Handling Accidental String Inputs
        nav=navi[0];
    else
        nav='0';
    if (nav=='1')
        main();
    else if (nav=='2')
    {
        cout<<"\033[1;35m"<<"\n\t\t\t\t\t\t\t\tThank you for Checking Out the Game!\tCreated by Govind Krishnan & Bibin P Daniel.\n\n"<<"\033[0m";
        Sleep(2000);
        exit(0);
    }
    else
    {
        cout<<("\t\t\033[0;31mInvalid Menu Index. Another Chance!\n");
        cout<<("\n\t\t\033[0mEnter Valid Menu Index :");
        goto errorhandler_4;
    }
}

// Function to Find Date & Time of Gameplay
void datetime()
{
    time_t tm;
    time(&tm);
    date=ctime(&tm);
}

// Function for Drawing the Mascot
inline void oddenface()
{
    cout<<"\033[0;33m"<<"   \t\t\t\t\t\t\t\t\t\t\t\t==========\n\t\t\t\t\t\t\t\t\t\t\t\t|O\tO|\n\t\t\t\t\t\t\t\t\t\t\t\t|\033[1;31m  |--| \033[0;33m |\n\t\t\t\t\t\t\t\t\t\t\t\t==========\n";
    cout<<"\033[0m";
}

// Function for Playing Game Music
void music()
{
    if(sound==1)
    {
        mciSendString("play mp3 repeat", NULL, 0, NULL);
        sound=0;
    }
    else
    {
        mciSendString("pause mp3", NULL, 0, NULL);
        sound=1;
    }

        main();
}
