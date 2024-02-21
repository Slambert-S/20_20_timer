// timerApp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <sstream> 
#include <string>
#include <windows.h>


enum class TimerType : int {
    Custum = 0,
    longer = 1,
    shorter = 2
};

void StartTimer(TimerType timerType);

/*
* Function in charge of displaying the notification window.
*
* Parameter:
* timerType : passing the TimerType of the timer that just finished, will be used to display correct text
*             and creat the proper folowing timer.
*
*/
int DisplayResourceNAMessageBox(TimerType timertype)
{

    // Fancy string type use to display text on the pop up box
    LPCWSTR custumString = L"defaultString";

    //Selecting the proper texte to use depending on the TimerType
    switch (timertype)
    {
    case TimerType::Custum:
        custumString = L"Ready to start a new Custum timer?";
        break;
    case TimerType::longer:
        custumString = L"Look away for 20 second.";
        break;
    case TimerType::shorter:
        custumString = L"A 20 minutes timer is ready to start.";
        break;
    default:
        break;
    }

    //Creating the MessageBox object and  passing the text to display
    int msgboxID = MessageBox(
        NULL,
        custumString,
        L"Time up",
        MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON3 | MB_SERVICE_NOTIFICATION
    );



    TimerType type = TimerType::Custum;
    //Selecting the proper TimerType that will be created.
    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        break;
    case IDOK:
        switch (timertype)
        {
        case TimerType::longer:
            type = TimerType::shorter;
            break;
        case TimerType::shorter:
            type = TimerType::longer;
            break;
        case TimerType::Custum:
            type = TimerType::Custum;
            break;
        default:
            break;
        }
        StartTimer(type);
        break;
    }

    return msgboxID;
}

//Helper function to check if their is time left on the timer.
//Tranfer the minute in second and add the second to it.
bool checkForTimeleft(int& minute, int& second)
{
    if ((minute * 60) + second > 0) {
        return  true;
    }
    return false;
}

// Helper function to display the time.
void displayTime(std::string& minute, std::string& second, std::string& TimerName) {
    std::cout << "|-- " << TimerName << " Timer --|" << std::endl;
    std::cout << "Time left : " << minute << " : " << second << std::endl;
}

//Helper function to display number betwen 0 and 9  as 0X
void cleanTimeText(std::string& minuteText, std::string& secondText, int secondInt, int minuteInt) {

    if (secondInt <= 9) {
        secondText = "0" + std::to_string(secondInt);
    }
    else {
        secondText = std::to_string(secondInt);
    }

    if (minuteInt <= 9) {
        minuteText = "0" + std::to_string(minuteInt);
    }
    else {
        minuteText = std::to_string(minuteInt);
    }
}

/*
* Function use to start a new timer.
* Parameter:
* timerType: use to indicate what time value and will be use as the setting of the timer.
*/
void StartTimer(TimerType timerType) {
    system("CLS");
    int secondSystem = 60, minuteSystem = 0;
    std::string timerName, secondDisplay, ligne, minutesDisplay = "00";
    bool ok = false;
    int n;


    /*
    * This switch statment is in charge of setting the secondSystem , minutesSystem and timerName value.
    */
    switch (timerType)
    {

    case TimerType::Custum:

        //Handling user input for the second | need to be x <= 59 et x >= 0
        do {
            ok = false;
            while (!ok)
            {
                std::cout << "Enter the number of second :: ";
                std::getline(std::cin, ligne);
                std::istringstream  tampon(ligne);
                if (tampon >> n) {
                    if (n <= 59 && n >= 0) {
                        ok = true;
                        secondSystem = n;
                    }
                    else {
                        std::cin.clear();
                    }
                }
                else {
                    ok = false;
                    ligne.clear();
                    std::cin.clear();
                }
            };

        } while (!ok);

        ok = false;
        ligne.clear();

        //Handling user input for the minutes | need to be x <= 59 et x >= 0

        do {
            ok = false;

            while (!ok)
            {
                std::cout << "Enter the number of minutes :: ";
                std::getline(std::cin, ligne);
                std::istringstream  tampon(ligne);
                if (tampon >> n) {
                    if (n <= 59 && n >= 0) {
                        ok = true;
                        minuteSystem = n;
                    }
                    else {
                        std::cin.clear();
                    }
                }
                else {
                    ok = false;
                    std::cin.clear();
                }

            };
        } while (!ok);

        //Reciving the timer name from the user , no need to handle the user input.
        std::cout << "Enter timer's name :";
        std::getline(std::cin, timerName);

        break;
        // setting the value for the 20 minutes timer
    case TimerType::longer:
        secondSystem = 0;
        minuteSystem = 20;
        timerName = "20 Minute";
        break;

        //setting the value for the 20 second timer
    case TimerType::shorter:
        secondSystem = 20;
        minuteSystem = 0;
        timerName = "20 Second";
        break;
    default:
        break;
    }

    //Timer countdown star here
    bool timeRemaining = false;

    // Chekking if the time is not empty
    timeRemaining = checkForTimeleft(minuteSystem, secondSystem);


    // countdown timer logic
    while (timeRemaining) {

        system("CLS"); // clear the screen
        cleanTimeText(minutesDisplay, secondDisplay, secondSystem, minuteSystem);
        displayTime(minutesDisplay, secondDisplay, timerName);

        //handle minute and second changing
        secondSystem--;
        if (secondSystem < 0) {
            if (minuteSystem >= 1) {
                minuteSystem--;
                secondSystem = 59;
            }
        }
        Sleep(1000);
        timeRemaining = checkForTimeleft(minuteSystem, secondSystem);

    }
    //Sleep(5000); // stop the system for 5 second
    system("CLS"); // clear the screen
    std::cout << "TimerEnded";

    //Open the message box to inform the user the timer is over
    //Passing the current TimerType to allow the code to start the folowing timer.
    DisplayResourceNAMessageBox(timerType);


}


int main()
{
    // Main loop to allow the user to go back to the main menu and start a different timer.
    bool masterBool = false;
    while (masterBool == false) {


        std::cout << "| Please select the type of timer\n";
        std::cout << "| 1 - Custom Timer\n";
        std::cout << "| 2 - 20 20 20 Timer \n";
        std::cout << "| 3 - Exit\n";

        int input = 0;

        bool ok = false;
        int valeur;
        std::string ligne;

        //Handling user input validation.
        //Making sure the value is 1 or 2 or 3 or 4 (secret timer)
        do {
            ok = false;

            while (!ok)
            {
                std::cout << "| Please enter your input :: ";
                std::getline(std::cin, ligne);
                std::istringstream  tampon(ligne);
                if (tampon >> valeur) {
                    if (valeur == 1 || valeur == 2 || valeur == 3 || valeur == 4) {
                        ok = true;
                        input = valeur;
                    }
                    else {
                        ok = false;
                        masterBool = true;
                    }
                }
                else {
                    ok = false;
                }

            };
        } while (!ok);


        TimerType timerType = TimerType::Custum;

        //using the int value from the user to set the proper TimerType
        switch (input)
        {
        case 1:
            timerType = TimerType::Custum;
            break;
        case 2:
            timerType = TimerType::longer;
            break;
        case 3:
            std::cout << "Have a nice day";
            Sleep(4000);
            exit(0);
            break;
        case 4:
            timerType = TimerType::shorter;
            break;
        default:
            break;
        }
        std::cout << input;

        StartTimer(timerType);

    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
