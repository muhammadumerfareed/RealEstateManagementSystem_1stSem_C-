#include <iostream> // libraries
#include <conio.h>
#include <string>
#include <windows.h>
#include <limits>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

string currentLoggedInSellerID = "";
// File Handling Function Prototypes
void saveUsers(string username[], string password[], int role[], string sellerID[], bool approval[], int userCount, float userRating[], string userRatingComment[]);
void loadUsers(string username[], string password[], int role[], string sellerID[], bool approval[], int &userCount, int &pendingCount, float userRating[], string userRatingComment[]);
void saveProperties(string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string sellerID[], int propertyCount);
void loadProperties(string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string sellerID[], int &propertyCount);
void saveFeedbacks(string propertyFeedback[], int feedbackcount);
void loadFeedbacks(string propertyFeedback[], int &feedbackcount);
void saveComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int complainCount);
void loadComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int &complainCount);

// --- Function Prototypes with Parameters ---
void setcl(int text, int background = 0);
void startup();
void setBlackOnWhite();
void resetColor();
void gotoxy(int x, int y);
void showMovingBanner(int &pendingCount); // Added & to match definition
void header();
void footer();
void exitMenu();

// Authentication & Logic functions
int users();
bool signUpcheck(string name, string username[], int userCount, bool approval[]);
int signUp(string username[], string password[], int role[], string sellerID[], int &userCount, int &pendingCount, const int size, bool approval[], float userRating[], string userRatingComment[]);
bool signIncheck(string name, string pass, string username[], string password[], int role[], int userCount, int &rrr);
int signIn(string username[], string password[], int role[], bool approval[], int userCount, string sellerID[], int &rrr);
int loginmenu(string sellerID[], string username[], string password[], bool approval[], int role[], int &userCount, int &pendingCount, int &rrr, string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], int &propertyCount, string propertyFeedback[], int &feedbackcount, string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int &complainCount, const int size, float userRating[], string userRatingComment[]);

// Admin functions
string adminMenu(int pendingCount);
void verifyUsers(string username[], string password[], int role[], bool approval[], int userCount, int &pendingCount, string sellerID[], float userRating[], string userRatingComment[]);
void deleteProperty(string sellerID[], string propertySerial[], string propertyStatus[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int &propertyCount);
void soldRevenue(string propertyStatus[], string propertySerial[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount);
void viewUsers(string username[], string password[], int role[], bool approval[], int userCount);

// Seller Function
string sellerMenu();
void addListing(string sellerID[], string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], int &propertyCount, int userCount);
void viewListing(string sellerID[], string propertySerial[], string propertyStatus[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount);
void editListing(string sellerID[], string propertySerial[], string propertyOwner[], string propertyContact[], string propertyStatus[], string propertySize[], string propertyPrice[], int propertyCount, string propertyAddress[], bool propertyType[]);
void updateProperty(string sellerID[], string propertySerial[], string propertyStatus[], int propertyCount, string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[]);
void viewFeedback(string propertyFeedback[], int feedbackcount);
void viewComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplainContact[], string propertyComplain[], int complainCount);

// Buyer functions

string buyerMenu();
void allProperties(string propertySerial[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount);
void searchProperty(string propertySerial[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount);
void sortData(string propertySerial[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[]);
void sortDataAscending(string propertySerial[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[]);
void sortDataDescending(string propertySerial[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[]);
void makeComplain(string propertySerial[], int propertyCount, string sellerID[], string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplainContact[], string propertyComplain[], int &complainCount);
void giveFeedback(string propertyFeedback[], int &feedbackcount);
void soldHistory(string sellerID[], string propertySerial[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount);
// Rental Management Prototypes
void saveRentals(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount);
void loadRentals(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int &rentalCount);
void addRentalTenant(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int &rentalCount, string propertySerial[], int propertyCount, string sellerID[]);
void viewMyRentals(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount);
void checkRentDue(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount, string currentUsername);
void payRent(string rentalPropertyID[], string rentalBuyerUsername[], string rentalStatus[], string rentalStartDate[], string rentalEndDate[], int rentalCount, string currentUsername);
string getCurrentDate();
int calculateDaysDifference(string startDate, string endDate);

// Purchase Management Prototypes
void savePurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int purchasedCount);
void loadPurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount);
void registerPurchase(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string propertySerial[], int propertyCount, string sellerID[]);
void viewMyPurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int purchasedCount, string propertySerial[], string propertyAddress[], string propertySize[], string propertyPrice[], int propertyCount, string currentUsername);
void unregisterPurchase(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string currentUsername);
// User Rating Prototypes
void rateUser(string username[], float userRating[], string userRatingComment[], int userCount, string password[], int role[], string sellerID[], bool approval[]);
void deleteUser(string username[], string password[], int role[], string sellerID[], bool approval[], float userRating[], string userRatingComment[], int &userCount);
// systems
void adminSystem(string username[], string password[], int role[], bool approval[],
                 int &userCount, int &pendingCount, string propertySerial[],
                 string propertyStatus[], bool propertyType[], string propertyAddress[],
                 string propertySize[], string propertyPrice[], string propertyOwner[],
                 string propertyContact[], int &propertyCount, string sellerID[],
                 float userRating[], string userRatingComment[]);
void sellerSystem(string sellerID[], string propertySerial[], string propertyOwner[],
                  string propertyContact[], bool propertyType[], string propertyAddress[],
                  string propertyStatus[], string propertySize[], string propertyPrice[],
                  int &propertyCount, int userCount, string propertyFeedback[],
                  int feedbackcount, string complainSellerID[],
                  string propertyComplainSerial[], string propertyComplainName[],
                  string propertyComplain[], string propertyComplainContact[],
                  int complainCount,
                  string rentalPropertyID[], string rentalSellerID[],
                  string rentalBuyerUsername[], string rentalStartDate[],
                  string rentalEndDate[], string rentalStatus[],
                  string rentalAmount[], int &rentalCount,
                  string purchasedPropertyID[], string purchasedBuyerUsername[],
                  string purchasedDate[], int &purchasedCount,
                  string username[], float userRating[],
                  string userRatingComment[], int rrr);
void buyerSystem(string propertySerial[], bool propertyType[], string propertyAddress[],
                 string propertyStatus[], string propertySize[], string propertyPrice[],
                 string propertyOwner[], string propertyContact[], int &propertyCount,
                 string sellerID[], string complainSellerID[],
                 string propertyComplainSerial[], string propertyComplainName[],
                 string propertyComplainContact[], string propertyComplain[],
                 int &complainCount, string propertyFeedback[], int &feedbackcount,
                 string rentalPropertyID[], string rentalSellerID[],
                 string rentalBuyerUsername[], string rentalStartDate[],
                 string rentalEndDate[], string rentalStatus[],
                 string rentalAmount[], int rentalCount,
                 string purchasedPropertyID[], string purchasedBuyerUsername[],
                 string purchasedDate[], int &purchasedCount,
                 string username[], float userRating[],
                 string userRatingComment[], int rrr, int userCount);

int main()
{
    // count variables
    const int size = 100;
    int userCount = 3;
    int rrr = 0;
    int pendingCount = 0;
    int propertyCount = 3;
    int complainCount = 3;
    int feedbackcount = 2;
    const int maxRentals = 100;
    int rentalCount = 0;
    int purchasedCount = 0;
    float userRating[100];

    // authentication arrays
    string sellerID[size] = {"0987", "8873", "7535"};
    string complainSellerID[size] = {"0987", "8873", "7535"};
    string username[size] = {"AhmadIbraheem", "UmerFareed", "HamzaHassan"};
    string password[size] = {"hehe11", "hehe22", "hehe33"};
    bool approval[size] = {1, 1, 1};
    int role[size] = {1, 1, 2};

    // parallel arrays for property listings
    string propertySerial[size] = {"01", "02", "03"};
    string propertyOwner[size] = {"Ahmad Ibraheem", "Umer Fareed", "Hamza Hassan"};
    string propertyContact[size] = {"03016062180", "03420532650", "03291293223"};
    bool propertyType[size] = {1, 0, 1};
    string propertyAddress[size] = {"Faisalabad", "Islamabad", "Lahore"};
    string propertyStatus[size] = {"Sold", "For-Sale", "Sold"};
    string propertySize[size] = {"15", "30", "60"};
    string propertyPrice[size] = {"474554282525", "743647333", "7366652"};

    // for feedbacks and complains
    string propertyFeedback[size] = {"Your service exceeded my expectations...", "I had an amazing experience..."};
    string propertyComplainSerial[size] = {"01", "02", "03"};
    string propertyComplainName[size] = {"Huzaifa", "Hameed", "Hadia"};
    string propertyComplain[size] = {"Not properly responded", "Poor attitude of Seller", "waited so long "};
    string propertyComplainContact[size] = {"474554282525", "743647333", "7366652"};
    // for rental system
    string rentalPropertyID[maxRentals];
    string rentalSellerID[maxRentals];
    string rentalBuyerUsername[maxRentals];
    string rentalStartDate[maxRentals]; // Format: "DD-MM-YYYY"
    string rentalEndDate[maxRentals];   // Format: "DD-MM-YYYY"
    string rentalStatus[maxRentals];    // "Active", "Paid", "Pending"
    string rentalAmount[maxRentals];
    // Purchased properties tracking
    string purchasedPropertyID[100];
    string purchasedBuyerUsername[100];
    string purchasedDate[100];
    // User ratings

    string userRatingComment[100];

    for (int i = 0; i < 100; i++)
    {
        userRating[i] = 0.0;
        userRatingComment[i] = "No rating yet";
    }

    // file handling
    loadUsers(username, password, role, sellerID, approval, userCount, pendingCount, userRating, userRatingComment);
    loadProperties(propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, sellerID, propertyCount);
    loadFeedbacks(propertyFeedback, feedbackcount);
    loadComplains(complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplain, propertyComplainContact, complainCount);
    loadRentals(rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount);
    loadPurchases(purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount);

    // starting interface
    startup();

    int input;
    while (true) // loop to continue in the sign up , sign in unless exit
    {
        input = loginmenu(sellerID, username, password, approval, role, userCount, pendingCount, rrr, propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyCount, propertyFeedback, feedbackcount, complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplain, propertyComplainContact, complainCount, size, userRating, userRatingComment);

        if (input == 1)
        {
            adminSystem(username, password, role, approval, userCount, pendingCount, propertySerial, propertyStatus, propertyType, propertyAddress, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount, sellerID, userRating, userRatingComment);
        }
        if (input == 2)
        {
            sellerSystem(sellerID, propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyCount, userCount, propertyFeedback, feedbackcount, complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplain, propertyComplainContact, complainCount, rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount, purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount, username, userRating, userRatingComment, rrr);
        }
        if (input == 3)
        {
            buyerSystem(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount, sellerID, complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplainContact, propertyComplain, complainCount, propertyFeedback, feedbackcount, rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount, purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount, username, userRating, userRatingComment, rrr, userCount);

            input = 10;
        }
    }
    return 0;
}

// function definitions
// Save users data to CSV file
void saveUsers(string username[], string password[], int role[], string sellerID[], bool approval[], int userCount, float userRating[], string userRatingComment[])
{
    ofstream file("users.txt");
    if (file.is_open())
    {
        // Write header
        file << "Username,Password,Role,SellerID,Approval,Rating,Comment\n";

        // Write data
        for (int i = 0; i < userCount; i++)
        {
            file << username[i] << ","
                 << password[i] << ","
                 << role[i] << ","
                 << sellerID[i] << ","
                 << approval[i] << ","
                 << userRating[i] << ","
                 << userRatingComment[i] << "\n";
        }
        file.close();
    }
    else
    {
        setcl(4);
        cout << "Error: Unable to save users data!" << endl;
        resetColor();
    }
}

// Load users data from CSV file
void loadUsers(string username[], string password[], int role[], string sellerID[], bool approval[], int &userCount, int &pendingCount, float userRating[], string userRatingComment[])
{
    ifstream file("users.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip header

        userCount = 0;
        pendingCount = 0;

        while (getline(file, line) && userCount < 100)
        {
            stringstream ss(line);
            string temp;

            getline(ss, username[userCount], ',');
            getline(ss, password[userCount], ',');
            getline(ss, temp, ',');
            role[userCount] = stoi(temp);
            getline(ss, sellerID[userCount], ',');
            getline(ss, temp, ',');
            approval[userCount] = stoi(temp);
            getline(ss, temp, ',');
            userRating[userCount] = stof(temp);
            getline(ss, userRatingComment[userCount], ',');

            if (approval[userCount] == 0)
            {
                pendingCount++;
            }

            userCount++;
        }
        file.close();
    }
    else
    {
        setcl(8);
        cout << "Note: No previous users data found. Starting fresh." << endl;
        resetColor();
    }
}

// Save properties data to CSV file
void saveProperties(string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string sellerID[], int propertyCount)
{
    ofstream file("properties.txt");
    if (file.is_open())
    {
        // Write header
        file << "PropertySerial|PropertyOwner|PropertyContact|PropertyType|PropertyAddress|PropertyStatus|PropertySize|PropertyPrice|SellerID\n";

        // Write data
        for (int i = 0; i < propertyCount; i++)
        {
            file << propertySerial[i] << "|"
                 << propertyOwner[i] << "|"
                 << propertyContact[i] << "|"
                 << propertyType[i] << "|"
                 << propertyAddress[i] << "|"
                 << propertyStatus[i] << "|"
                 << propertySize[i] << "|"
                 << propertyPrice[i] << "|"
                 << sellerID[i] << "\n";
        }
        file.close();
    }
    else
    {
        setcl(4);
        cout << "Error: Unable to save properties data!" << endl;
        resetColor();
    }
}

// Load properties data from CSV file
void loadProperties(string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string sellerID[], int &propertyCount)
{
    ifstream file("properties.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip header

        propertyCount = 0;

        while (getline(file, line) && propertyCount < 100)
        {
            stringstream ss(line);
            string temp;

            getline(ss, propertySerial[propertyCount], '|');
            getline(ss, propertyOwner[propertyCount], '|');
            getline(ss, propertyContact[propertyCount], '|');
            getline(ss, temp, '|');
            propertyType[propertyCount] = stoi(temp);
            getline(ss, propertyAddress[propertyCount], '|');
            getline(ss, propertyStatus[propertyCount], '|');
            getline(ss, propertySize[propertyCount], '|');
            getline(ss, propertyPrice[propertyCount], '|');
            getline(ss, sellerID[propertyCount], '|');

            propertyCount++;
        }
        file.close();
    }
    else
    {
        setcl(8);
        cout << "Note: No previous properties data found. Starting fresh." << endl;
        resetColor();
    }
}

// Save complains to CSV file
void saveComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int complainCount)
{
    ofstream file("complains.txt");
    if (file.is_open())
    {
        // Write header
        file << "SellerID,PropertySerial,Name,Complain,Contact\n";

        // Write data
        for (int i = 0; i < complainCount; i++)
        {
            file << complainSellerID[i] << ","
                 << propertyComplainSerial[i] << ","
                 << propertyComplainName[i] << ","
                 << propertyComplain[i] << ","
                 << propertyComplainContact[i] << "\n";
        }
        file.close();
    }
    else
    {
        setcl(4);
        cout << "Error: Unable to save complains data!" << endl;
        resetColor();
    }
}

// Load complains from CSV file
void loadComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int &complainCount)
{
    ifstream file("complains.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip header

        complainCount = 0;

        while (getline(file, line) && complainCount < 100)
        {
            stringstream ss(line);

            getline(ss, complainSellerID[complainCount], ',');
            getline(ss, propertyComplainSerial[complainCount], ',');
            getline(ss, propertyComplainName[complainCount], ',');
            getline(ss, propertyComplain[complainCount], ',');
            getline(ss, propertyComplainContact[complainCount], ',');

            complainCount++;
        }
        file.close();
    }
    else
    {
        setcl(8);
        cout << "Note: No previous complains found. Starting fresh." << endl;
        resetColor();
    }
}
// Save feedbacks to CSV file
void saveFeedbacks(string propertyFeedback[], int feedbackcount)
{
    ofstream file("feedbacks.txt");
    if (file.is_open())
    {
        // Write header
        file << "Feedback\n";

        // Write data
        for (int i = 0; i < feedbackcount; i++)
        {
            file << propertyFeedback[i] << "\n";
        }
        file.close();
    }
    else
    {
        setcl(4);
        cout << "Error: Unable to save feedbacks data!" << endl;
        resetColor();
    }
}

// Load feedbacks from CSV file
void loadFeedbacks(string propertyFeedback[], int &feedbackcount)
{
    ifstream file("feedbacks.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip header

        feedbackcount = 0;

        while (getline(file, propertyFeedback[feedbackcount]) && feedbackcount < 100)
        {
            feedbackcount++;
        }
        file.close();
    }
    else
    {
        setcl(8);
        cout << "Note: No previous feedbacks found. Starting fresh." << endl;
        resetColor();
    }
}
void setcl(int text, int background) // function to change color
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}

void startup()
{
    system("chcp 65001");
    system("cls");
    setcl(8, 0);
    cout << endl
         << endl;
    cout << "                 #############################################################################################################################" << endl;
    setcl(9, 0);
    cout << R"(                 
                                                                                                                                          
                             ▄▄▄▄▄▄▄ ▄▄▄▄▄▄    ▄▄▄▄▄▄▄ ▄▄▄    ▄▄▄    ▄▄▄▄▄▄▄ ▄▄▄    ▄▄▄  ▄▄▄▄▄▄▄ ▄▄▄        ▄▄▄▄   ▄▄▄▄  ▄▄▄▄  ▄▄▄▄▄▄▄ 
                            ███▀▀▀▀▀ ███▀▀██▄ ███▀▀▀▀▀ ████▄  ███   ███▀▀▀▀▀ ████▄  ███ ███▀▀▀▀▀ ███      ▄██▀▀██▄ ▀███  ███▀ ███▀▀▀▀▀ 
                            ███▄▄    ███  ███ ███▄▄    ███▀██▄███   ███▄▄    ███▀██▄███ ███      ███      ███  ███  ███  ███  ███▄▄    
                            ███      ███  ███ ███      ███  ▀████   ███      ███  ▀████ ███      ███      ███▀▀███  ███▄▄███  ███      
                            ▀███████ ██████▀  ▀███████ ███    ███   ▀███████ ███    ███ ▀███████ ████████ ███  ███   ▀████▀   ▀███████ 
                                                                                                           
                                                                                                           
                                                       )"
         << endl;
    setcl(8, 0);
    cout << "                #############################################################################################################################" << endl;
    setcl(3, 0);
    cout << "                                                 R E A L   E S T A T E    M A N A G E M E N T   S Y S T E M                                          " << endl;
    setcl(8, 0);
    cout << "                #############################################################################################################################" << endl;
    setcl(4, 0);
    cout << "                Press ENTER to continue...";
    cin.get();
    setcl(7, 0);
}
// to change background white and text black
void setBlackOnWhite()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}
// for reset color
void resetColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
// gotoxy function
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// notification banner on admin menu
void showMovingBanner(int &pendingCount)
{
    setBlackOnWhite();
    if (pendingCount != 0)
    {
        cout << "                                                    ";
        resetColor();
        setcl(4);
        cout << "  NOTIFICATIONS : You have " << pendingCount << " new sign-ups waiting for approval !  ";
        setBlackOnWhite();
        cout << "                                                      " << endl
             << endl;
    }
    else
    {
        cout << "                                                                   ";
        resetColor();
        setcl(2);
        cout << "  NO NEW  NOTIFICATIONS !  ";
        setBlackOnWhite();
        cout << "                                                                              " << endl
             << endl;
    }
    resetColor();
}
// access selection (sign up & sign in interface)
int users()
{
here:
    system("cls");
    setcl(6, 0);
    string choice;
    int n;
    cout << R"(
                                   __________________________________________________________________________________________________________
                                   |                                                                                                        |
                                   |                                           ACCESS SELECTION                                             |
                                   | _______________________________________________________________________________________________________|
                                   |                                                                                                        |
                                   |                                  1 — SIGN UP                                                           |
                                   |                                  2 — SIGN IN                                                           |
                                   |                                  0 — EXIT                                                              |  
                                   |                                                                                                        |
                                   |________________________________________________________________________________________________________|
                                   |                                                                                                        |
                                   |                                  Select an option to continue…                                         |
                                   |________________________________________________________________________________________________________| )";
    setcl(4, 0);
    cout << "                                                                                                           Enter choice: ";
    setcl(7, 0);
    cin >> choice;
    if (choice == "1")
    {
        n = 1;
        return n;
    }
    else if (choice == "2")
    {
        n = 2;
        return n;
    }
    else if (choice == "0")
    {
        n = 0;
        return n;
    }
    else
    {
        cout << "                                                                     INVALID INPUT ! " << endl;
        Sleep(100);
        goto here;
    }
}
// header on each functionality
void header()
{
    system("cls");
    cout << endl
         << endl;
    setcl(8);
    cout << "                                          *****************************************************************************" << endl;
    setcl(3);
    cout << "                                                  R E A L     E S T A T E     M A N A G E M E N T     S Y S T E M                          " << endl;
    setcl(8);
    cout << "                                          *****************************************************************************" << endl
         << endl;
    setcl(7);
}
// footer on each functionality
void footer()
{
    setcl(8);
    cout << endl
         << "                                          *****************************************************************************" << endl
         << endl;

    setcl(8);
    cout << "                                                        Press ENTER to continue : ";
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    cin.get();
    setcl(7);
}
// login menu
int loginmenu(string sellerID[], string username[], string password[], bool approval[], int role[], int &userCount, int &pendingCount, int &rrr, string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], int &propertyCount, string propertyFeedback[], int &feedbackcount, string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int &complainCount, const int size, float userRating[], string userRatingComment[])
{
    string input = "3";
    int n;
    while (input != "0")
    {
        input = to_string(users());
        if (input == "1")
        {
            signUp(username, password, role, sellerID, userCount, pendingCount, size, approval, userRating, userRatingComment);
        }
        else if (input == "2")
        {
            n = signIn(username, password, role, approval, userCount, sellerID, rrr);
            if (n == 1 || n == 2 || n == 3)
            {
                return n;
            }
        }
        else if (input != "0")
        {
            setcl(4, 0);
            cout << endl
                 << "                                                        Enter a valid option. Try Again. " << endl;
            setcl(7, 0);
        }
        else if (input == "0")
        {
            exitMenu();
        }
    }
    return 0;
}
// check if there is already a user
bool signUpcheck(string name, string username[], int userCount, bool approval[])
{
    bool a = true;
    for (int i = 0; i < userCount; i++)
    {
        if (username[i] == name)
        {
            a = false;
            break;
        }
    }
    return a;
}
// to sign up
int signUp(string username[], string password[], int role[], string sellerID[], int &userCount, int &pendingCount, const int size, bool approval[], float userRating[], string userRatingComment[])
{

    header();
    setcl(4, 0);
    cout << "                                          SIGN UP " << endl;
    cout << "                                         ________________" << endl

         << endl;
    setcl(7, 0);

    string name;
    string pass;
    string id;
    setcl(3, 0);
    cout << endl
         << "                                                        Enter Username : ";
    setcl(7, 0);
    getline(cin >> ws, name);
    setcl(3, 0);
    cout << endl;

    cout << "                                                        Enter Password  : ";
    setcl(7, 0);
    getline(cin >> ws, pass);
    cout << endl;
    setcl(6, 0);
    string rol;
    cout << "                                                        1. Seller Account." << endl;
    cout << "                                                        2. Buyer Account. " << endl
         << endl;
here1:
    setcl(3);
    cout << "                                                         Enter your choice (1 or 2) : ";
    setcl(7, 0);
    cin >> rol;
    int n;
    if (rol != "1" && rol != "2")
    {
        setcl(4);
        cout << "                                                         Invalid ! " << endl;
        goto here1;
    }
    cout << endl;
    if (userCount >= size)
    {
        setcl(4, 0);
        cout << "                                                        We're out of storage right now. Try Again later." << endl;
        setcl(7, 0);
    }
    else if (signUpcheck(name, username, userCount, approval))
    {
        username[userCount] = name;
        password[userCount] = pass;
        approval[userCount] = 0; // pending approval
        if (rol == "1")
        {
            n = 1;
        }
        if (rol == "2")
        {
            n = 2;
        }
        role[userCount] = n;

        if (role[userCount] == 1)
        {
        here:
            bool b = false;
            setcl(3, 0);
            cout << "                                                        Set a specific Seller ID : ";
            setcl(7, 0);
            cin >> id;
            cout << endl;
            for (int i = 0; i < userCount; i++)
            {
                if (sellerID[i] == id)
                {
                    b = true;
                    break;
                }
            }
            if (b)
            {
                setcl(4, 0);
                cout << "                                                        SELLER ID ALREADY TAKEN! TRY AGAIN! " << endl
                     << endl;
                goto here;
            }

            else
            {
                sellerID[userCount] = id;
                cout << endl;
                setcl(2, 0);
                cout << "                                                        Successful ! Your Seller ID is " << id << endl
                     << endl;
            }
        }
        setcl(2, 0);
        userCount++;
        pendingCount++;
        saveUsers(username, password, role, sellerID, approval, userCount, userRating, userRatingComment);
        cout << "                                                        REQUEST SENT TO ADMIN, KINDLY WAIT FOR APPROVAL ! " << endl
             << endl;
    }

    else
    {
        setcl(4, 0);
        cout << "                                                        User already exists. Try Again. " << endl
             << endl;
    }
    setcl(6, 0);
    Sleep(1000);
    cout << "                                                        Press Any key to continue. ";
    setcl(7, 0);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
// check if a user exists
bool signIncheck(string name, string pass, string username[], string password[], int role[], int userCount, int &rrr)
{
    bool a = false;

    for (int i = 0; i < userCount; i++)
    {
        if ((username[i] == name) && (password[i] == pass))
        {
            a = true;
            rrr = i;
            break;
        }
    }
    return a;
}
// to dign in , function
int signIn(string username[], string password[], int role[], bool approval[], int userCount, string sellerID[], int &rrr)
{
    header();
    setcl(4, 0);
    cout << "                                          SIGN IN  " << endl;
    cout << "                                         _______________" << endl
         << endl;
    setcl(3, 0);
    string name, pass;
    cout << "                                                       Enter Username : ";
    setcl(7, 0);
    getline(cin >> ws, name);
    cout << endl;
    setcl(3, 0);
    cout << "                                                       Enter Password : ";
    setcl(7, 0);
    getline(cin >> ws, pass);
    cout << endl;
    int n;
    if (name == "admin" && pass == "admin123")
    {
        n = 1;
        setcl(2);
        cout << "                                                        Welcome Admin!" << endl;
        Sleep(1000);
        return n;
    }
    else if (signIncheck(name, pass, username, password, role, userCount, rrr))
    {
        if (role[rrr] == 1)
        {
            if (approval[rrr] == 1)
            {
                currentLoggedInSellerID = sellerID[rrr];
                setcl(2);
                cout << "                                                        You're our trusted Seller. " << endl;
                n = 2;
                Sleep(1000);
                return n;
            }
            else
            {
                setcl(4);
                cout << "                                                        Request Pending, Wait for Admin Approval ! " << endl;
            }
        }
        else if (role[rrr] == 2)
        {
            if (approval[rrr] == 1)
            {
                setcl(2);
                cout << "                                                        You're our valuable Buyer. " << endl;
                n = 3;
                Sleep(1000);
                return n;
            }
            else
            {
                setcl(4);
                cout << "                                                        Request Pending, Wait for Admin Approval ! " << endl;
            }
        }
    }
    else
    {
        setcl(4, 0);
        cout << "                                                        User Not Found. Try Again. " << endl;
    }
    cout << endl;
    setcl(6, 0);
    Sleep(1000);
    cout << "                                                        Press Any key to continue. ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    setcl(7, 0);
    return 0;
}
// ANY USER: View their reputation
void viewMyReputation(string username[], float userRating[], string userRatingComment[], int userCount, string currentUsername)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN >  MENU > VIEW MY REPUTATION" << endl;
    setcl(6);
    cout << "                                          _____________________________________________" << endl
         << endl;
    for (int i = 0; i < userCount; i++)
    {
        if (username[i] == currentUsername)
        {
            setcl(3);
            cout << "                                                        Username: ";
            setcl(7);
            cout << username[i] << endl;
            setcl(3);
            cout << "                                                        Rating: ";

            // Display stars
            setcl(6, 0);
            for (int j = 0; j < (int)userRating[i]; j++)
            {
                cout << "★ ";
            }
            for (int j = (int)userRating[i]; j < 5; j++)
            {
                cout << "☆ ";
            }
            cout << "(" << userRating[i] << "/5.0)" << endl;
            setcl(7, 0);

            setcl(3);
            cout << "                                                        Admin Comment: ";
            setcl(7);
            cout << userRatingComment[i] << endl;

            // Reputation status
            if (userRating[i] >= 4.5)
            {
                setcl(2, 0);
                cout << "                                                        Status: ⭐ EXCELLENT - Trusted User!" << endl;
                setcl(7, 0);
            }
            else if (userRating[i] >= 3.5)
            {
                setcl(3, 0);
                cout << "                                                        Status:  GOOD - Reliable User" << endl;
                setcl(7, 0);
            }
            else if (userRating[i] >= 2.0)
            {
                setcl(6, 0);
                cout << "                                                        Status:  AVERAGE - Needs Improvement" << endl;
                setcl(7, 0);
            }
            else
            {
                setcl(4, 0);
                cout << "                                                        Status:  POOR - Action Required" << endl;
                setcl(7, 0);
            }

            break;
        }
    }

    footer();
}
// admin menu & functionalities
string adminMenu(int pendingCount)
{
    header();
    setcl(4, 0);
    cout << "                                           SIGN IN > ADMIN MENU " << endl;
    setcl(6, 0);
    cout << "                                           ______________________________" << endl
         << endl;
    setcl(7, 0);
    string input;

    showMovingBanner(pendingCount);
    setcl(6, 0);
    cout << "                                                         1. View New Users Request." << endl;
    cout << "                                                         2. View all listings. " << endl;
    cout << "                                                         3. Delete a listing. " << endl;
    cout << "                                                         4. View all sold history. " << endl;
    cout << "                                                         5. View all users." << endl;
    cout << "                                                         6. Rate a User." << endl;
    cout << "                                                         7. Delete a User." << endl;
    cout << "                                                         8. Log Out." << endl;
    cout << "                                                         9. Exit." << endl

         << endl;
    setcl(6, 0);
    cout << "                                          _____________________________________________________________________________" << endl
         << endl;
    setcl(3, 0);
    cout << "                                                         Enter your choice : ";
    setcl(7, 0);
    cin >> input;

    return input;
}
// admin sysytem to call function correctly
void adminSystem(string username[], string password[], int role[], bool approval[], int &userCount, int &pendingCount, string propertySerial[], string propertyStatus[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int &propertyCount, string sellerID[], float userRating[], string userRatingComment[])
{
    string n = "100";
    while (n != "9")
    {
        n = adminMenu(pendingCount);

        if (n == "1")
        {
            verifyUsers(username, password, role, approval, userCount, pendingCount, sellerID, userRating, userRatingComment);
        }
        else if (n == "2")
        {
            allProperties(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (n == "3")
        {
            deleteProperty(sellerID, propertySerial, propertyStatus, propertyType, propertyAddress, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (n == "4")
        {
            soldRevenue(propertyStatus, propertySerial, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (n == "5")
        {
            viewUsers(username, password, role, approval, userCount);
        }
        else if (n == "6")
        {
            rateUser(username, userRating, userRatingComment, userCount, password, role, sellerID, approval);
        }
        else if (n == "7")
        {
            deleteUser(username, password, role, sellerID, approval, userRating, userRatingComment, userCount);
        }
        else if (n == "8")
        {
            break;
        }

        if (n != "1" && n != "2" && n != "3" && n != "4" && n != "5" &&
            n != "6" && n != "7" && n != "8" && n != "9")
        {
            setcl(4);
            cout << "                                          *****************************************************************************" << endl
                 << endl;
            cout << "                                                        The choice you entered is incorrect. " << endl;
            cout << "                                                        Press enter to try again. " << endl;
            setcl(7);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    if (n == "9")
    {
        exitMenu();
    }
}
// seller menu who will sale propoerties
string sellerMenu()
{
    header();
    setcl(4, 0);
    cout << "                                           SIGN IN > SELLER MENU " << endl;
    setcl(6, 0);
    cout << "                                           ______________________________" << endl
         << endl;
    string input;

    setcl(6);
    cout << "                                                         1. Add a listing. " << endl;
    cout << "                                                         2. View my all active listings. " << endl;
    cout << "                                                         3. Edit listings details. " << endl;
    cout << "                                                         4. Update listing status. " << endl;
    cout << "                                                         5. View all sold history. " << endl;
    cout << "                                                         6. View Feedbacks. " << endl;
    cout << "                                                         7. View Complains/Appeals & Requests. " << endl;
    cout << "                                                         8. Add Rental Tenant." << endl;
    cout << "                                                         9. View My Rental Properties." << endl;
    cout << "                                                         10. Register Property Purchase." << endl;
    cout << "                                                         11. View My Reputation." << endl;
    cout << "                                                         12. Log Out." << endl;
    cout << "                                                         13. Exit." << endl
         << endl;

    cout << "                                          _____________________________________________________________________________" << endl
         << endl;

    setcl(3);
    cout << "                                                         Enter your choice : ";
    setcl(7);
    cin >> input;

    return input;
}
// seller system to call specified function
void sellerSystem(string sellerID[], string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], int &propertyCount, int userCount, string propertyFeedback[], int feedbackcount, string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplain[], string propertyComplainContact[], int complainCount, string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int &rentalCount, string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string username[], float userRating[], string userRatingComment[], int rrr)
{
    string choice = "100";
    while (choice != "13")
    {
        choice = sellerMenu();
        if (choice == "1")
        {
            addListing(sellerID, propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyCount, userCount);
        }
        else if (choice == "2")
        {
            viewListing(sellerID, propertySerial, propertyStatus, propertyType, propertyAddress, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (choice == "3")
        {
            editListing(sellerID, propertySerial, propertyOwner, propertyContact, propertyStatus, propertySize, propertyPrice, propertyCount, propertyAddress, propertyType);
        }
        else if (choice == "4")
        {
            updateProperty(sellerID, propertySerial, propertyStatus, propertyCount, propertyOwner, propertyContact, propertyType, propertyAddress, propertySize, propertyPrice);
        }
        else if (choice == "5")
        {
            soldHistory(sellerID, propertySerial, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (choice == "6")
        {
            viewFeedback(propertyFeedback, feedbackcount);
        }
        else if (choice == "7")
        {
            viewComplains(complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplainContact, propertyComplain, complainCount);
        }
        else if (choice == "8")
        {
            addRentalTenant(rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount, propertySerial, propertyCount, sellerID);
        }
        else if (choice == "9")
        {
            viewMyRentals(rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount);
        }
        else if (choice == "10")
        {
            registerPurchase(purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount, propertySerial, propertyCount, sellerID);
        }
        else if (choice == "11")
        {
            viewMyReputation(username, userRating, userRatingComment, userCount, username[rrr]);
        }
        else if (choice == "12")
        {
            break;
        }

        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8" && choice != "9" && choice != "10" && choice != "11" && choice != "12" && choice != "13")
        {
            setcl(4);
            cout << endl
                 << "                                          *****************************************************************************" << endl
                 << endl;
            cout << "                                                        The choice you entered is incorrect. " << endl;
            cout << "                                                        Press enter to try again. " << endl;
            setcl(7);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    if (choice == "13")
    {
        exitMenu();
    }
}
// function to add listing
void addListing(string sellerID[], string propertySerial[], string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], int &propertyCount, int userCount)
{
    header();
    string listingID;
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > ADD LISTING " << endl;
    setcl(6);
    cout << "                                           ___________________________________________" << endl
         << endl;

    int idx = 1000;
    string id = currentLoggedInSellerID;
    for (int i = 0; i < userCount; i++)
    {
        if (id == sellerID[i])
        {
            idx = i;
        }
    }
    if (idx != 1000)
    {

    here:
        int check = 1000;
        setcl(3);
        cout << "                                                        Enter a unique Property ID : ";
        setcl(7);
        cin >> listingID;
        for (int j = 0; j < propertyCount; j++)
        {
            if (listingID == propertySerial[j])
            {

                check = j;
                break;
            }
        }
        if (check == 1000)
        {
            char a;
            sellerID[propertyCount] = id;
            propertySerial[propertyCount] = listingID;
            setcl(3);
            cout << "                                                        Enter Property Owner Name  : ";
            setcl(7);
            getline(cin >> ws, propertyOwner[propertyCount]);
            setcl(3);
            cout << "                                                        Enter Property Owner Contact : ";
            setcl(7);
            getline(cin >> ws, propertyContact[propertyCount]);
        back:
            setcl(6);
            cout << "                                                        Enter Property Type : " << endl;
            cout << "                                                        Enter '1' if for Sale :  " << endl;
            cout << "                                                        Enter '0' if for Rent : " << endl;
            setcl(7);
            cin >> a;
            if (a == '1' || a == '0')
            {
                propertyType[propertyCount] = (a == '1');
            }
            else
            {
                goto back;
            }
            setcl(3);
            cout << "                                                        Enter Property Address : ";
            setcl(7);
            getline(cin >> ws, propertyAddress[propertyCount]);
            setcl(3);
            cout << "                                                        Enter Property Status (Sold or For-Sale) : ";
            setcl(7);
            getline(cin >> ws, propertyStatus[propertyCount]);
            setcl(3);
            cout << "                                                        Enter Property Size (in marlas) : ";
            setcl(7);
            cin >> propertySize[propertyCount];
            setcl(3);
            cout << "                                                        Enter Property Worth (in Rupees) : ";
            setcl(7);
            getline(cin >> ws, propertyPrice[propertyCount]);
            propertyCount = propertyCount + 1;
            setcl(2);
            cout << "                                                        Property Added Successfully" << endl;
        }
        else if (check != 1000)
        {
            setcl(4);
            cout << "                                                        Property ID already exists. " << endl;
            goto here;
        }
    }
    if (idx == 1000)
    {
        setcl(4);
        cout << "                                                        SELLER ID NOT FOUND ! " << endl;
    }
    saveProperties(propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, sellerID, propertyCount);
    footer();
}
// to view all the listings of a particular seller
void viewListing(string sellerID[], string propertySerial[], string propertyStatus[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount)
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > VIEW ACTIVE LISTING " << endl;
    setcl(6);
    cout << "                                           ___________________________________________________" << endl
         << endl;

    string id = currentLoggedInSellerID;
    int j = 1000;
    for (int i = 0; i < propertyCount; i++)
    {
        if (sellerID[i] == id)
        {
            setcl(3);
            cout << "                                                        Property ID : ";
            setcl(7);
            cout << propertySerial[i] << endl;
            setcl(3);
            cout << "                                                        Property Status : ";
            setcl(7);
            cout << propertyStatus[i] << endl;
            setcl(3);
            cout << "                                                        Property Type : ";
            setcl(7);
            if (propertyType[i] == 1)
            {
                cout << "For-Sale" << endl;
            }
            else if (propertyType[i] == 0)
            {
                cout << "For Rent" << endl;
            }
            setcl(3);
            cout << "                                                        Property Address : ";
            setcl(7);
            cout << propertyAddress[i] << endl;
            setcl(3);
            cout << "                                                        Property Size (in Marlas) : ";
            setcl(7);
            cout << propertySize[i] << endl;
            setcl(3);
            cout << "                                                        Property Worth (in PKR.) : ";
            setcl(7);
            cout << propertyPrice[i] << endl;
            setcl(3);
            cout << "                                                        Property Owner Name : ";
            setcl(7);
            cout << propertyOwner[i] << endl;
            setcl(3);
            cout << "                                                        Property Owner Contact Info : ";
            setcl(7);
            cout << propertyContact[i] << endl
                 << endl;
            setcl(6);
            cout << "                                          _____________________________________________________________________________" << endl
                 << endl;
            j = i;
        }
    }
    if (j == 1000)
    {
        setcl(4);
        cout << "                                                        No active listing found. " << endl;
    }

    footer();
}
// function to edit listing
void editListing(string sellerID[], string propertySerial[], string propertyOwner[], string propertyContact[], string propertyStatus[], string propertySize[], string propertyPrice[], int propertyCount, string propertyAddress[], bool propertyType[])
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > UPDATE LISTING DETAILS " << endl;
    setcl(6);
    cout << "                                           _______________________________________________________" << endl;
    int idx;
    string choice;
    bool a = false;
    string id = currentLoggedInSellerID;
    string serial;
    setcl(3);
    cout << "                                                        Enter the Unique Property ID : ";
    setcl(7);
    cin >> serial;
    for (int i = 0; i < propertyCount; i++)
    {
        if (serial == propertySerial[i] && id == sellerID[i])
        {
            idx = i;
            a = true;
            break;
        }
    }

    if (a)
    {
        setcl(6);
        cout << "                                                        1. Edit the Owner Name. " << endl;
        cout << "                                                        2. Edit the Owner Contact. " << endl;
        cout << "                                                        3. Edit the Property Status. " << endl;
        cout << "                                                        4. Edit the Property land area. " << endl;
        cout << "                                                        5. Edit the Property Worth . " << endl
             << endl;
        setcl(3);
        cout << "                                                        Enter your choice : ";
        setcl(7);
        cin >> choice;

        if (choice == "1")
        {
            setcl(3);
            cout << "                                                        Enter the Owner Name : ";
            setcl(7);
            getline(cin >> ws, propertyOwner[idx]);
            setcl(2);
            cout << "                                                        Owner Name updated Successfully. ";
        }
        else if (choice == "2")
        {
            setcl(3);
            cout << "                                                        Enter the Owner Contact: ";
            setcl(7);
            getline(cin >> ws, propertyContact[idx]);
            setcl(2);
            cout << "                                                        Owner Contact info updated Successfully. ";
        }
        else if (choice == "3")
        {
            setcl(3);
            cout << "                                                        Enter the Property Status (Sold or For-Sale) : ";
            setcl(7);
            getline(cin >> ws, propertyStatus[idx]);
            setcl(2);
            cout << "                                                        Property Status updated Successfully. ";
        }
        else if (choice == "4")
        {
            setcl(3);
            cout << "                                                        Enter the Property land area (in Marlas) : ";
            setcl(7);
            getline(cin >> ws, propertySize[idx]);
            setcl(2);
            cout << "                                                        Property Land Area  updated Successfully. ";
        }
        else if (choice == "5")
        {
            setcl(3);
            cout << "                                                        Enter the Property Worth: ";
            setcl(7);
            getline(cin >> ws, propertyPrice[idx]);
            setcl(2);
            cout << "                                                        Property Worth updated Successfully. ";
        }
        else
        {
            setcl(4);
            cout << "                                                        Enter a valid input. " << endl;
        }
    }
    else
    {
        setcl(4);
        cout << "                                                        Property Not found. " << endl;
    }
    saveProperties(propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, sellerID, propertyCount);
    footer();
}
// function to update property
void updateProperty(string sellerID[], string propertySerial[], string propertyStatus[], int propertyCount, string propertyOwner[], string propertyContact[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[])
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > UPDATE PROPERTY STATUS " << endl;
    setcl(6);
    cout << "                                           _______________________________________________________" << endl;

    string id = currentLoggedInSellerID;
    int idx = 1000;
    bool a = false;
    string ser;
    setcl(3);
    cout << "                                                        Enter the property ID to change status : ";
    setcl(7);
    cin >> ser;
    for (int i = 0; i < propertyCount; i++)
    {
        if (id == sellerID[i] && ser == propertySerial[i])
        {
            idx = i;
            a = true;
            break;
        }
    }
    if (a)
    {

        if (propertyStatus[idx] == "For-Sale" || propertyStatus[idx] == "for-sale")
        {
            propertyStatus[idx] = "Sold";
            setcl(2);
            cout << "                                                        Status Changed Successfully ! " << endl;
        }
        else if (propertyStatus[idx] == "Sold" || propertyStatus[idx] == "sold")
        {
            propertyStatus[idx] = "For-Sale";
            setcl(2);
            cout << "                                                        Status Changed Successfully ! " << endl;
        }
        else
        {
            setcl(4);
            cout << "                                                        Status not justified ! " << endl;
        }
    }
    else
    {
        setcl(4);
        cout << "                                                        Property Not found. " << endl;
    }
    saveProperties(propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, sellerID, propertyCount);
    footer();
}
// function to view feedbacks
void viewFeedback(string propertyFeedback[], int feedbackcount)
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > seller MENU > FEEDBACKS " << endl;
    setcl(6);
    cout << "                                           ___________________________________________" << endl
         << endl;

    for (int i = 0; i < feedbackcount; i++)
    {
        setcl(7);
        cout << "\t" << propertyFeedback[i] << endl
             << endl;
        setcl(6);
        cout << "                                          _____________________________________________________________________________" << endl
             << endl;
    }

    Sleep(1000);
    footer();
}
// function yo view complains
void viewComplains(string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplainContact[], string propertyComplain[], int complainCount)
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > VIEW COMPLAINS / APPEALS " << endl;
    setcl(6);
    cout << "                                           _________________________________________________________" << endl
         << endl;

back:
    string id = currentLoggedInSellerID;
    int j = 1000;
    bool a = true;
    for (int i = 0; i < complainCount; i++)
    {

        if (complainSellerID[i] == id)
        {
            setcl(3);
            cout << "                                                        Property Serial Number : ";
            setcl(7);
            cout << propertyComplainSerial[i] << endl;
            setcl(3);
            cout << "                                                        Name : ";
            setcl(7);
            cout << propertyComplainName[i] << endl;
            setcl(3);
            cout << "                                                        Contact info : ";
            setcl(7);
            cout << propertyComplainContact[i] << endl;
            setcl(3);
            cout << "                                                        Details : ";
            setcl(7);
            cout << propertyComplain[i] << endl
                 << endl;
            setcl(6);
            cout << "                                          _____________________________________________________________________________" << endl
                 << endl;
            a = false;
        }
    }

    if (a)
    {
        setcl(4);
        cout << "                                                        No complains or appeals found. " << endl;
    }

    Sleep(1000);
    footer();
}
// function to see all specfied sold properties
void soldHistory(string sellerID[], string propertySerial[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount)
{
    header();
    setcl(4);
    cout << "                                           SIGN IN > SELLER MENU > SOLD HISTORY " << endl;
    setcl(6);
    cout << "                                           ____________________________________________" << endl
         << endl;

    bool a = true;
    string id = currentLoggedInSellerID;
    for (int i = 0; i < propertyCount; i++)
    {
        if (id == sellerID[i])
        {
            if (propertyStatus[i] == "Sold" || propertyStatus[i] == "sold")
            {
                setcl(3);
                cout << "                                                       Property Serial Number : ";
                setcl(7);
                cout << propertySerial[i] << endl;
                setcl(3);
                cout << "                                                        Property Status : ";
                setcl(7);
                cout << propertyStatus[i] << endl;
                setcl(3);
                cout << "                                                        Property Size (in Marlas) : ";
                setcl(7);
                cout << propertySize[i] << endl;
                setcl(3);
                cout << "                                                        Property Worth (in PKR.) : ";
                setcl(7);
                cout << propertyPrice[i] << endl;
                setcl(3);
                cout << "                                                        Property Owner Name : ";
                setcl(7);
                cout << propertyOwner[i] << endl;
                setcl(3);
                cout << "                                                        Property Owner Contact Info : ";
                setcl(7);
                cout << propertyContact[i] << endl
                     << endl;
                setcl(6);
                cout << "                                          _____________________________________________________________________________" << endl
                     << endl;
                a = false;
            }
        }
    }

    if (a)
    {
        setcl(4);
        cout << "                                                        You haven't sold anything yet ! " << endl;
    }
    footer();
}
// buyer menu who will buy properties
string buyerMenu()
{

    header();
    setcl(4, 0);
    cout << "                                          SIGN IN > BUYER MENU " << endl;
    setcl(6, 0);
    cout << "                                          _____________________________" << endl
         << endl;
    string input;

    setcl(6);
    cout << "                                                        1. View all Properties. " << endl;
    cout << "                                                        2. Search property by ID. " << endl;
    cout << "                                                        3. Filter Properties." << endl;
    cout << "                                                        4. Request information or visit or Register a complain. " << endl;
    cout << "                                                        5. Give Feedback. " << endl;
    cout << "                                                        6. Check Rent Due." << endl;
    cout << "                                                        7. Pay Rent." << endl;
    cout << "                                                        8. View My Purchased Properties." << endl;
    cout << "                                                        9. Unregister Property (Resale)." << endl;
    cout << "                                                        10. View My Reputation." << endl;
    cout << "                                                        11. Log Out." << endl;
    cout << "                                                        12. Exit." << endl
         << endl;
    cout << "                                          _____________________________________________________________________________" << endl
         << endl;

    setcl(3);
    cout << "                                                        Enter your choice : ";
    setcl(7);
    cin >> input;

    return input;
}
// buyer system to call each specific function
void buyerSystem(string propertySerial[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int &propertyCount, string sellerID[], string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplainContact[], string propertyComplain[], int &complainCount, string propertyFeedback[], int &feedbackcount, string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount, string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string username[], float userRating[], string userRatingComment[], int rrr, int userCount)
{
    string n = "100";
    while (n != "11")
    {
        n = buyerMenu();

        if (n == "1")
        {
            allProperties(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (n == "2")
        {
            searchProperty(propertySerial, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
        }
        else if (n == "3")
        {
            sortData(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount, sellerID);
        }
        else if (n == "4")
        {
            makeComplain(propertySerial, propertyCount, sellerID, complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplainContact, propertyComplain, complainCount);
        }
        else if (n == "5")
        {
            giveFeedback(propertyFeedback, feedbackcount);
        }
        else if (n == "6")
        {
            checkRentDue(rentalPropertyID, rentalSellerID, rentalBuyerUsername, rentalStartDate, rentalEndDate, rentalStatus, rentalAmount, rentalCount, username[rrr]);
        }
        else if (n == "7")
        {
            payRent(rentalPropertyID, rentalBuyerUsername, rentalStatus, rentalStartDate, rentalEndDate, rentalCount, username[rrr]);
        }
        else if (n == "8")
        {
            viewMyPurchases(purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount, propertySerial, propertyAddress, propertySize, propertyPrice, propertyCount, username[rrr]);
        }
        else if (n == "9")
        {
            unregisterPurchase(purchasedPropertyID, purchasedBuyerUsername, purchasedDate, purchasedCount, username[rrr]);
        }
        else if (n == "10")
        {
            viewMyReputation(username, userRating, userRatingComment, userCount, username[rrr]);
        }
        else if (n == "11")
        {
            break;
        }

        if (n != "1" && n != "2" && n != "3" && n != "4" && n != "5" &&
            n != "6" && n != "7" && n != "8" && n != "9" && n != "10" &&
            n != "11" && n != "12")
        {
            setcl(4);
            cout << endl
                 << "                                          *****************************************************************************" << endl
                 << endl;
            cout << "                                                        The choice you entered is incorrect. " << endl;
            cout << "                                                        Press enter to try again. " << endl;
            setcl(7);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        if (n == "12")
            exitMenu();
    }
}
// function to view all properties
void allProperties(string propertySerial[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > ALL LISTINGS " << endl;
    setcl(6);
    cout << "                                          ________________________________________________" << endl
         << endl;

    for (int i = 0; i < propertyCount; i++)
    {
        setcl(3);
        cout << "                                                        Property Serial Number : ";
        setcl(7);
        cout << propertySerial[i] << endl;
        setcl(3);
        cout << "                                                        Property Type : ";
        setcl(7);
        if (propertyType[i] == 1)
        {
            cout << "For-Sale" << endl;
        }
        else if (propertyType[i] == 0)
        {
            cout << "For Rent" << endl;
        }
        setcl(3);
        cout << "                                                        Property Address : ";
        setcl(7);
        cout << propertyAddress[i] << endl;
        setcl(3);
        cout << "                                                        Property Status : ";
        setcl(7);
        cout << propertyStatus[i] << endl;
        setcl(3);
        cout << "                                                        Property Size (in Marlas) : ";
        setcl(7);
        cout << propertySize[i] << endl;
        setcl(3);
        cout << "                                                        Property Worth (in PKR.) : ";
        setcl(7);
        cout << propertyPrice[i] << endl;
        setcl(3);
        cout << "                                                        Property Owner Name : ";
        setcl(7);
        cout << propertyOwner[i] << endl;
        setcl(3);
        cout << "                                                        Property Owner Contact Info : ";
        setcl(7);
        cout << propertyContact[i] << endl
             << endl;

        setcl(6);
        cout << "                                          _____________________________________________________________________________" << endl
             << endl;
    }

    footer();
}
// function ot serach properties
void searchProperty(string propertySerial[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount)
{

    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > SEARCH PROPERTY  " << endl;
    setcl(6);
    cout << "                                          _____________________________________________" << endl
         << endl;
    int idx = 1000;
    bool a = false;
    string id;
    setcl(3);
    cout << "                                                        Enter the property ID to view : ";
    setcl(7);
    cin >> id;
    for (int i = 0; i < propertyCount; i++)
    {
        if (id == propertySerial[i])
        {
            idx = i;
            a = true;
        }
    }
    if (a)
    {
        setcl(3);
        cout << "                                                        Property Serial Number : ";
        setcl(7);
        cout << propertySerial[idx] << endl;
        setcl(3);
        cout << "                                                        Property Status : ";
        setcl(7);
        cout << propertyStatus[idx] << endl;
        setcl(3);
        cout << "                                                        Property Size (in Marlas) : ";
        setcl(7);
        cout << propertySize[idx] << endl;
        setcl(3);
        cout << "                                                        Property Worth (in PKR.) : ";
        setcl(7);
        cout << propertyPrice[idx] << endl;
        setcl(3);
        cout << "                                                        Property Owner Name : ";
        setcl(7);
        cout << propertyOwner[idx] << endl;
        setcl(3);
        cout << "                                                        Property Owner Contact Info : ";
        setcl(7);
        cout << propertyContact[idx] << endl
             << endl;

        setcl(6);
        cout << "                                          _____________________________________________________________________________" << endl;
    }
    else
    {
        setcl(4);
        cout << "                                                        No Property Found with this ID. TRY AGAIN ! " << endl;
    }
    footer();
}
// function to sort data in ascending

void sortDataAscending(string propertySerial[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[])
{

    // Simple Bubble Sort to keep arrays synced
    for (int i = 0; i < propertyCount - 1; i++)
    {
        for (int j = 0; j < propertyCount - i - 1; j++)
        {

            if (propertySize[j] > propertySize[j + 1])
            {

                // to swap size
                string temp = propertySize[j];
                propertySize[j] = propertySize[j + 1];
                propertySize[j + 1] = temp;

                // to swap owner name
                string tempOwner = propertyOwner[j];
                propertyOwner[j] = propertyOwner[j + 1];
                propertyOwner[j + 1] = tempOwner;

                // to swap addresses
                string tempAddress = propertyAddress[j];
                propertyAddress[j] = propertyAddress[j + 1];
                propertyAddress[j + 1] = tempAddress;

                // to swap serial
                string tempSerial = propertySerial[j];
                propertySerial[j] = propertySerial[j + 1];
                propertySerial[j + 1] = tempSerial;

                // to swap status
                string tempstatus = propertyStatus[j];
                propertyStatus[j] = propertyStatus[j + 1];
                propertyStatus[j + 1] = tempstatus;

                // to swap contact
                string tempContact = propertyContact[j];
                propertyContact[j] = propertyContact[j + 1];
                propertyContact[j + 1] = tempContact;

                // to swap price
                string tempPrice = propertyPrice[j];
                propertyPrice[j] = propertyPrice[j + 1];
                propertyPrice[j + 1] = tempPrice;

                // to swap seller ID
                string tempID = sellerID[j];
                sellerID[j] = sellerID[j + 1];
                sellerID[j + 1] = tempID;
            }
        }
    }
}
// function to sort data in descending
void sortDataDescending(string propertySerial[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[])
{

    // Simple Bubble Sort to keep arrays synced
    for (int i = 0; i < propertyCount - 1; i++)
    {
        for (int j = 0; j < propertyCount - i - 1; j++)
        {

            if (propertySize[j] < propertySize[j + 1])
            {

                // to swap size
                string temp = propertySize[j];
                propertySize[j] = propertySize[j + 1];
                propertySize[j + 1] = temp;

                // to swap owner name
                string tempOwner = propertyOwner[j];
                propertyOwner[j] = propertyOwner[j + 1];
                propertyOwner[j + 1] = tempOwner;

                // to swap addresses
                string tempAddress = propertyAddress[j];
                propertyAddress[j] = propertyAddress[j + 1];
                propertyAddress[j + 1] = tempAddress;

                // to swap serial
                string tempSerial = propertySerial[j];
                propertySerial[j] = propertySerial[j + 1];
                propertySerial[j + 1] = tempSerial;

                // to swap status
                string tempstatus = propertyStatus[j];
                propertyStatus[j] = propertyStatus[j + 1];
                propertyStatus[j + 1] = tempstatus;

                // to swap contact
                string tempContact = propertyContact[j];
                propertyContact[j] = propertyContact[j + 1];
                propertyContact[j + 1] = tempContact;

                // to swap price
                string tempPrice = propertyPrice[j];
                propertyPrice[j] = propertyPrice[j + 1];
                propertyPrice[j + 1] = tempPrice;

                // to swap seller ID
                string tempID = sellerID[j];
                sellerID[j] = sellerID[j + 1];
                sellerID[j + 1] = tempID;
            }
        }
    }
}
// function to sort data
void sortData(string propertySerial[], bool propertyType[], string propertyAddress[], string propertyStatus[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount, string sellerID[])
{

    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > FILTER PROPERTIES. " << endl;
    setcl(6);
    cout << "                                          ____________________________________________________" << endl
         << endl;
    string choice;
    setcl(6);
    cout << "                                                        1. Filter by increasing size. " << endl;
    cout << "                                                        2. Filter by decreasing size. " << endl;
here:
    setcl(3);
    cout << "                                                        Enter your choice (1 or 2) : ";
    setcl(7);
    cin >> choice;
    if (choice == "1")
    {
        sortDataAscending(propertySerial, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount, sellerID);
        allProperties(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
    }
    else if (choice == "2")
    {
        sortDataDescending(propertySerial, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount, sellerID);
        allProperties(propertySerial, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, propertyOwner, propertyContact, propertyCount);
    }
    else
    {
        setcl(4);
        cout << "                                                        Invalid Option ! " << endl;
        goto here;
    }
}
// function to make complains
void makeComplain(string propertySerial[], int propertyCount, string sellerID[], string complainSellerID[], string propertyComplainSerial[], string propertyComplainName[], string propertyComplainContact[], string propertyComplain[], int &complainCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > COMPLAIN OR INQUIRE INFO. " << endl;
    setcl(6);
    cout << "                                          ____________________________________________________" << endl
         << endl;
    string id;
    int idx = 1000;
    bool a = false;
    setcl(3);
    cout << "                                                        Enter the property ID to inquire or to complain : ";
    setcl(7);
    cin >> id;
    for (int i = 0; i < propertyCount; i++)
    {
        if (id == propertySerial[i])
        {
            a = true;
            idx = i;
            break;
        }
    }
    if (a)
    {
        complainSellerID[complainCount] = sellerID[idx];
        propertyComplainSerial[complainCount] = id;
        setcl(3);
        cout << "                                                        Enter  name : ";
        setcl(7);
        getline(cin >> ws, propertyComplainName[complainCount]);
        setcl(3);
        cout << "                                                        Enter  Contact Info : ";
        setcl(7);
        getline(cin >> ws, propertyComplainContact[complainCount]);
        setcl(3);
        cout << "                                                        Enter  Details: ";
        setcl(7);
        getline(cin >> ws, propertyComplain[complainCount]);
        complainCount++;

        setcl(2);
        cout << "                                                        We have received your request. Our team will reach out to you soon. " << endl;
    }
    else
    {
        setcl(4);
        cout << "                                                        NO PROPERTY FOUND ! TRY AGAIN WITH CORRECT ID. " << endl;
    }
    saveComplains(complainSellerID, propertyComplainSerial, propertyComplainName, propertyComplain, propertyComplainContact, complainCount);
    footer();
}
// function to give feedacks
void giveFeedback(string propertyFeedback[], int &feedbackcount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > RATE US " << endl;
    setcl(6);
    cout << "                                          _______________________________________" << endl
         << endl;

    setcl(3);
    cout << "                                                        Please Enter your experience : ";
    setcl(7);
    getline(cin >> ws, propertyFeedback[feedbackcount]);
    feedbackcount++;

    setcl(2);
    cout << "                                                        Thanks for your FEEDBACK ! " << endl;
    saveFeedbacks(propertyFeedback, feedbackcount);
    footer();
}
// function to verify new sign ups by the admin
void verifyUsers(string username[], string password[], int role[], bool approval[], int userCount, int &pendingCount, string sellerID[], float userRating[], string userRatingComment[])
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > VERIFY USERS " << endl;
    setcl(6);
    cout << "                                          _______________________________________" << endl
         << endl;
    string approve;
    for (int i = 0; i < userCount; i++)
    {
        if (approval[i] == 0)
        {
            setcl(3);
            cout << "                                                        User Name : ";
            setcl(7);
            cout << username[i] << endl;
            setcl(3);
            cout << "                                                        Password : ";
            setcl(7);
            cout << password[i] << endl;
            setcl(3);
            cout << "                                                        Account Type : ";
            setcl(7);
            if (role[i] == 1)
            {
                cout << "Seller. " << endl;
            }
            if (role[i] == 2)
            {
                cout << "Buyer. " << endl;
            }
            setcl(6);
            cout << "                                                        Enter (y/n) to approve or dismiss the account : ";
            setcl(7);
            cin >> approve;
            if (approve == "y")
            {
                approval[i] = 1;
                setcl(2);
                cout << "                                                        USER APPROVED ! " << endl;
                pendingCount--;
            }
            else if (approve == "n")
            {
                approval[i] = 0;
                setcl(4);
                cout << "                                                        USER DISMISSED ! " << endl;
            }
            else
            {
                setcl(4);
                cout << "                                                        INVALID INPUT ! RUN THE TASK AGAIN " << endl;
            }
        }
    }
    saveUsers(username, password, role, sellerID, approval, userCount, userRating, userRatingComment);
    footer();
}
// function to delete property
void deleteProperty(string sellerID[], string propertySerial[], string propertyStatus[], bool propertyType[], string propertyAddress[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int &propertyCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > DELETE LISTING " << endl;
    setcl(6);
    cout << "                                          _______________________________________" << endl
         << endl;
    string serial;
    setcl(3);
    cout << "                                                        Enter the Unique Property ID : ";
    setcl(7);
    cin >> serial;
    int idx;
    bool a = false;
    for (int i = 0; i < propertyCount; i++)
    {
        if (serial == propertySerial[i])
        {
            idx = i;
            a = true;
            break;
        }
    }

    if (a)
    {

        for (int i = idx; i < propertyCount - 1; i++)
        {
            sellerID[i] = sellerID[i + 1];
            propertySerial[i] = propertySerial[i + 1];
            propertyStatus[i] = propertyStatus[i + 1];
            propertyType[i] = propertyType[i + 1];
            propertyAddress[i] = propertyAddress[i + 1];
            propertySize[i] = propertySize[i + 1];
            propertyPrice[i] = propertyPrice[i + 1];
            propertyOwner[i] = propertyOwner[i + 1];
            propertyContact[i] = propertyContact[i + 1];
        }
        propertyCount--;
        setcl(2);
        cout << "                                                        Property Deleted Successfully !" << endl;
    }
    else
    {
        setcl(4);
        cout << "                                                        No Property Found with Serial Number." << endl;
    }
    saveProperties(propertySerial, propertyOwner, propertyContact, propertyType, propertyAddress, propertyStatus, propertySize, propertyPrice, sellerID, propertyCount);
    footer();
}
// function to see all the sold properties on specified platform
void soldRevenue(string propertyStatus[], string propertySerial[], string propertySize[], string propertyPrice[], string propertyOwner[], string propertyContact[], int propertyCount)
{

    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > Sold History " << endl;
    setcl(6);
    cout << "                                          _______________________________________" << endl
         << endl;
    for (int i = 0; i < propertyCount; i++)
    {

        {
            if (propertyStatus[i] == "Sold" || propertyStatus[i] == "sold")
            {
                setcl(3);
                cout << "                                                        Property Serial Number : ";
                setcl(7);
                cout << propertySerial[i] << endl;
                setcl(3);
                cout << "                                                        Property Status : ";
                setcl(7);
                cout << propertyStatus[i] << endl;
                setcl(3);
                cout << "                                                        Property Size (in Marlas) : ";
                setcl(7);
                cout << propertySize[i] << endl;
                setcl(3);
                cout << "                                                        Property Worth (in PKR.) : ";
                setcl(7);
                cout << propertyPrice[i] << endl;
                setcl(3);
                cout << "                                                        Property Owner Name : ";
                setcl(7);
                cout << propertyOwner[i] << endl;
                setcl(3);
                cout << "                                                        Property Owner Contact Info : ";
                setcl(7);
                cout << propertyContact[i] << endl
                     << endl;
                setcl(6);
                cout << "                                          _____________________________________________________________________________" << endl
                     << endl;
            }
        }
    }
    footer();
}
// function to view all users
void viewUsers(string username[], string password[], int role[], bool approval[], int userCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > VIEW USERS " << endl;
    setcl(6);
    cout << "                                          _______________________________________" << endl
         << endl;
    for (int i = 0; i < userCount; i++)
    {
        if (approval[i] == 1)
        {
            setcl(3);
            cout << "                                                        " << i + 1 << ". User Name : ";
            setcl(7);
            cout << username[i] << endl;
            setcl(3);
            cout << "                                                           Password : ";
            setcl(7);
            cout << password[i] << endl;
            setcl(3);
            cout << "                                                           Account Type : ";
            setcl(7);
            if (role[i] == 1)
            {
                cout << "Seller" << endl;
            }
            else if (role[i] == 2)
            {
                cout << "Buyer" << endl;
            }

            setcl(6);
            cout << "                                                        _________________________________" << endl
                 << endl;
        }
    }
    footer();
}
// Get current date
string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string day = to_string(ltm->tm_mday);
    string month = to_string(1 + ltm->tm_mon);
    string year = to_string(1900 + ltm->tm_year);

    if (day.length() == 1)
        day = "0" + day;
    if (month.length() == 1)
        month = "0" + month;

    return day + "-" + month + "-" + year;
}

// Calculate days between two dates
int calculateDaysDifference(string startDate, string endDate)
{
    // Parse dates (format: DD-MM-YYYY)
    int startDay = stoi(startDate.substr(0, 2));
    int startMonth = stoi(startDate.substr(3, 2));
    int startYear = stoi(startDate.substr(6, 4));

    int endDay = stoi(endDate.substr(0, 2));
    int endMonth = stoi(endDate.substr(3, 2));
    int endYear = stoi(endDate.substr(6, 4));

    // Simplified calculation (30 days per month average)
    int totalDays = (endYear - startYear) * 365 +
                    (endMonth - startMonth) * 30 +
                    (endDay - startDay);

    return totalDays;
}

// Save rentals to file
void saveRentals(string rentalPropertyID[], string rentalSellerID[],
                 string rentalBuyerUsername[], string rentalStartDate[],
                 string rentalEndDate[], string rentalStatus[],
                 string rentalAmount[], int rentalCount)
{
    ofstream file("rentals.txt");
    if (file.is_open())
    {
        file << "PropertyID,SellerID,BuyerUsername,StartDate,EndDate,Status,Amount\n";

        for (int i = 0; i < rentalCount; i++)
        {
            file << rentalPropertyID[i] << ","
                 << rentalSellerID[i] << ","
                 << rentalBuyerUsername[i] << ","
                 << rentalStartDate[i] << ","
                 << rentalEndDate[i] << ","
                 << rentalStatus[i] << ","
                 << rentalAmount[i] << "\n";
        }
        file.close();
    }
    else
    {
        setcl(4);
        cout << "                                                        Error: Unable to save rentals data!" << endl;
        resetColor();
    }
}

// Load rentals from file
void loadRentals(string rentalPropertyID[], string rentalSellerID[],
                 string rentalBuyerUsername[], string rentalStartDate[],
                 string rentalEndDate[], string rentalStatus[],
                 string rentalAmount[], int &rentalCount)
{
    ifstream file("rentals.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line);

        rentalCount = 0;

        while (getline(file, line) && rentalCount < 100)
        {
            stringstream ss(line);

            getline(ss, rentalPropertyID[rentalCount], ',');
            getline(ss, rentalSellerID[rentalCount], ',');
            getline(ss, rentalBuyerUsername[rentalCount], ',');
            getline(ss, rentalStartDate[rentalCount], ',');
            getline(ss, rentalEndDate[rentalCount], ',');
            getline(ss, rentalStatus[rentalCount], ',');
            getline(ss, rentalAmount[rentalCount], ',');

            rentalCount++;
        }
        file.close();
    }
    else
    {
        setcl(8);
        cout << "                                                        Note: No previous rentals found. Starting fresh." << endl;
        resetColor();
    }
}

// SELLER: Add tenant to rental property
void addRentalTenant(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int &rentalCount, string propertySerial[], int propertyCount, string sellerID[])
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > ADD RENTAL TENANT" << endl;
    setcl(6);
    cout << "                                          ___________________________________________" << endl
         << endl;

    string propID;
    setcl(3);
    cout << "                                                        Enter Property ID for Rent: ";
    setcl(7);
    cin >> propID;

    // Verify property exists and belongs to seller
    bool found = false;
    for (int i = 0; i < propertyCount; i++)
    {
        if (propertySerial[i] == propID && currentLoggedInSellerID == sellerID[i])
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        Property not found or doesn't belong to you!" << endl;
        footer();
        return;
    }

    rentalPropertyID[rentalCount] = propID;
    rentalSellerID[rentalCount] = currentLoggedInSellerID;

    setcl(3);
    cout << "                                                        Enter Tenant Username: ";
    setcl(7);
    getline(cin >> ws, rentalBuyerUsername[rentalCount]);

    setcl(3);
    cout << "                                                        Enter Monthly Rent Amount (PKR): ";
    setcl(7);
    getline(cin >> ws, rentalAmount[rentalCount]);

    // Auto-set dates
    rentalStartDate[rentalCount] = getCurrentDate();

    // Calculate end date (30 days from now)
    string current = getCurrentDate();
    int day = stoi(current.substr(0, 2));
    int month = stoi(current.substr(3, 2));
    int year = stoi(current.substr(6, 4));

    day += 30;
    if (day > 30)
    {
        day -= 30;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    string newDay = to_string(day);
    string newMonth = to_string(month);
    if (newDay.length() == 1)
        newDay = "0" + newDay;
    if (newMonth.length() == 1)
        newMonth = "0" + newMonth;

    rentalEndDate[rentalCount] = newDay + "-" + newMonth + "-" + to_string(year);
    rentalStatus[rentalCount] = "Active";

    rentalCount++;

    setcl(2);
    cout << "                                                        Tenant added successfully!" << endl;
    setcl(3);
    cout << "                                                        Rent due date: ";
    setcl(7);
    cout << rentalEndDate[rentalCount - 1] << endl;

    saveRentals(rentalPropertyID, rentalSellerID, rentalBuyerUsername,
                rentalStartDate, rentalEndDate, rentalStatus,
                rentalAmount, rentalCount);

    footer();
}

// SELLER: View all rental tenants
void viewMyRentals(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > VIEW MY RENTALS" << endl;
    setcl(6);
    cout << "                                          ________________________________________" << endl
         << endl;

    bool found = false;
    for (int i = 0; i < rentalCount; i++)
    {
        if (rentalSellerID[i] == currentLoggedInSellerID)
        {
            found = true;
            setcl(3);
            cout << "                                                        Property ID: ";
            setcl(7);
            cout << rentalPropertyID[i] << endl;
            setcl(3);
            cout << "                                                        Tenant: ";
            setcl(7);
            cout << rentalBuyerUsername[i] << endl;
            setcl(3);
            cout << "                                                        Rent Amount: PKR ";
            setcl(7);
            cout << rentalAmount[i] << endl;
            setcl(3);
            cout << "                                                        Start Date: ";
            setcl(7);
            cout << rentalStartDate[i] << endl;
            setcl(3);
            cout << "                                                        Due Date: ";
            setcl(7);
            cout << rentalEndDate[i] << endl;
            setcl(3);
            cout << "                                                        Status: ";
            setcl(7);
            cout << rentalStatus[i] << endl;

            // Check if overdue
            int daysDiff = calculateDaysDifference(rentalStartDate[i], getCurrentDate());
            if (daysDiff >= 30 && rentalStatus[i] == "Active")
            {
                setcl(4, 0);
                cout << "                                                         RENT OVERDUE!" << endl;
                setcl(7, 0);
            }

            setcl(6);
            cout << "                                          _____________________________________________________________________________" << endl
                 << endl;
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        No rental records found." << endl;
    }

    footer();
}

// BUYER: Check rent due notifications
void checkRentDue(string rentalPropertyID[], string rentalSellerID[], string rentalBuyerUsername[], string rentalStartDate[], string rentalEndDate[], string rentalStatus[], string rentalAmount[], int rentalCount, string currentUsername)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > BUYER MENU > RENT DUE NOTIFICATIONS" << endl;
    setcl(6);
    cout << "                                          ______________________________________________" << endl
         << endl;

    bool found = false;
    for (int i = 0; i < rentalCount; i++)
    {
        if (rentalBuyerUsername[i] == currentUsername)
        {
            found = true;

            int daysDiff = calculateDaysDifference(rentalStartDate[i], getCurrentDate());

            setcl(3);
            cout << "                                                        Property ID: ";
            setcl(7);
            cout << rentalPropertyID[i] << endl;
            setcl(3);
            cout << "                                                        Rent Amount: PKR ";
            setcl(7);
            cout << rentalAmount[i] << endl;
            setcl(3);
            cout << "                                                        Start Date: ";
            setcl(7);
            cout << rentalStartDate[i] << endl;
            setcl(3);
            cout << "                                                        Due Date: ";
            setcl(7);
            cout << rentalEndDate[i] << endl;
            setcl(3);
            cout << "                                                        Days Elapsed: ";
            setcl(7);
            cout << daysDiff << " days" << endl;

            if (daysDiff >= 30)
            {
                setcl(4, 0);
                cout << "                                                        RENT PAYMENT DUE! Please pay immediately." << endl;
                setcl(7, 0);
            }
            else
            {
                setcl(2, 0);
                cout << "                                                        Payment up to date. " << (30 - daysDiff) << " days remaining." << endl;
                setcl(7, 0);
            }

            setcl(6);
            cout << "                                          _____________________________________________________________________________" << endl
                 << endl;
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        No rental records found for your account." << endl;
    }

    footer();
}

// BUYER: Pay rent
void payRent(string rentalPropertyID[], string rentalBuyerUsername[], string rentalStatus[], string rentalStartDate[], string rentalEndDate[], int rentalCount, string currentUsername)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > BUYER MENU > PAY RENT" << endl;
    setcl(6);
    cout << "                                          ________________________________" << endl
         << endl;

    string propID;
    setcl(3);
    cout << "                                                        Enter Property ID to pay rent: ";
    setcl(7);
    cin >> propID;

    bool found = false;
    for (int i = 0; i < rentalCount; i++)
    {
        if (rentalPropertyID[i] == propID && rentalBuyerUsername[i] == currentUsername)
        {
            found = true;

            // Update dates for next month
            rentalStartDate[i] = getCurrentDate();

            string current = getCurrentDate();
            int day = stoi(current.substr(0, 2));
            int month = stoi(current.substr(3, 2));
            int year = stoi(current.substr(6, 4));

            day += 30;
            if (day > 30)
            {
                day -= 30;
                month++;
                if (month > 12)
                {
                    month = 1;
                    year++;
                }
            }

            string newDay = to_string(day);
            string newMonth = to_string(month);
            if (newDay.length() == 1)
                newDay = "0" + newDay;
            if (newMonth.length() == 1)
                newMonth = "0" + newMonth;

            rentalEndDate[i] = newDay + "-" + newMonth + "-" + to_string(year);
            rentalStatus[i] = "Paid";

            setcl(2, 0);
            cout << "                                                        Rent paid successfully!" << endl;
            cout << "                                                        Next due date: " << rentalEndDate[i] << endl;
            setcl(7, 0);

            break;
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        Property not found in your rentals!" << endl;
    }

    footer();
}
// Save purchases to file
void savePurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int purchasedCount)
{
    ofstream file("purchases.txt");
    if (file.is_open())
    {
        file << "PropertyID,BuyerUsername,PurchaseDate\n";

        for (int i = 0; i < purchasedCount; i++)
        {
            file << purchasedPropertyID[i] << ","
                 << purchasedBuyerUsername[i] << ","
                 << purchasedDate[i] << "\n";
        }
        file.close();
    }
}

// Load purchases from file
void loadPurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount)
{
    ifstream file("purchases.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line);

        purchasedCount = 0;

        while (getline(file, line) && purchasedCount < 100)
        {
            stringstream ss(line);

            getline(ss, purchasedPropertyID[purchasedCount], ',');
            getline(ss, purchasedBuyerUsername[purchasedCount], ',');
            getline(ss, purchasedDate[purchasedCount], ',');

            purchasedCount++;
        }
        file.close();
    }
}

// SELLER: Register a buyer's purchase
void registerPurchase(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string propertySerial[], int propertyCount, string sellerID[])
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > SELLER MENU > REGISTER PURCHASE" << endl;
    setcl(6);
    cout << "                                          __________________________________________" << endl
         << endl;

    string propID;
    setcl(3);
    cout << "                                                        Enter Property ID: ";
    setcl(7);
    cin >> propID;

    // Verify property exists and belongs to seller
    bool found = false;
    for (int i = 0; i < propertyCount; i++)
    {
        if (propertySerial[i] == propID && currentLoggedInSellerID == sellerID[i])
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        Property not found or doesn't belong to you!" << endl;
        footer();
        return;
    }

    purchasedPropertyID[purchasedCount] = propID;

    setcl(3);
    cout << "                                                        Enter Buyer Username: ";
    setcl(7);
    getline(cin >> ws, purchasedBuyerUsername[purchasedCount]);

    purchasedDate[purchasedCount] = getCurrentDate();

    purchasedCount++;

    setcl(2);
    cout << "                                                        Purchase registered successfully!" << endl;
    setcl(3);
    cout << "                                                        Buyer can now view this property in their account." << endl;

    savePurchases(purchasedPropertyID, purchasedBuyerUsername,
                  purchasedDate, purchasedCount);

    footer();
}

// BUYER: View purchased properties
void viewMyPurchases(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int purchasedCount, string propertySerial[], string propertyAddress[], string propertySize[], string propertyPrice[], int propertyCount, string currentUsername)

{
    header();
    setcl(4);
    cout << "                                          SIGN IN > BUYER MENU > MY PURCHASED PROPERTIES" << endl;
    setcl(6);
    cout << "                                          ______________________________________________" << endl
         << endl;

    bool found = false;
    for (int i = 0; i < purchasedCount; i++)
    {
        if (purchasedBuyerUsername[i] == currentUsername)
        {
            found = true;

            // Find property details
            for (int j = 0; j < propertyCount; j++)
            {
                if (propertySerial[j] == purchasedPropertyID[i])
                {
                    setcl(3);
                    cout << "                                                        Property ID: ";
                    setcl(7);
                    cout << propertySerial[j] << endl;
                    setcl(3);
                    cout << "                                                        Address: ";
                    setcl(7);
                    cout << propertyAddress[j] << endl;
                    setcl(3);
                    cout << "                                                        Size: ";
                    setcl(7);
                    cout << propertySize[j] << " Marlas" << endl;
                    setcl(3);
                    cout << "                                                        Purchase Price: PKR ";
                    setcl(7);
                    cout << propertyPrice[j] << endl;
                    setcl(3);
                    cout << "                                                        Purchase Date: ";
                    setcl(7);
                    cout << purchasedDate[i] << endl;
                    setcl(6);
                    cout << "                                                _____________________________________________________________________________" << endl
                         << endl;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        setcl(4);
        cout << "                                                        No purchased properties found." << endl;
    }

    footer();
}

// BUYER: Unregister property (resale)
void unregisterPurchase(string purchasedPropertyID[], string purchasedBuyerUsername[], string purchasedDate[], int &purchasedCount, string currentUsername)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > BUYER MENU > UNREGISTER PROPERTY (RESALE)" << endl;
    setcl(6);
    cout << "                                          ____________________________________________________" << endl
         << endl;

    string propID;
    setcl(3);
    cout << "                                                        Enter Property ID to unregister: ";
    setcl(7);
    cin >> propID;

    int idx = -1;
    for (int i = 0; i < purchasedCount; i++)
    {
        if (purchasedPropertyID[i] == propID && purchasedBuyerUsername[i] == currentUsername)
        {
            idx = i;
            break;
        }
    }

    if (idx != -1)
    {
        // Shift elements
        for (int i = idx; i < purchasedCount - 1; i++)
        {
            purchasedPropertyID[i] = purchasedPropertyID[i + 1];
            purchasedBuyerUsername[i] = purchasedBuyerUsername[i + 1];
            purchasedDate[i] = purchasedDate[i + 1];
        }

        purchasedCount--;

        setcl(2);
        cout << "                                                        Property unregistered successfully!" << endl;
        setcl(3);
        cout << "                                                        You have marked this property as resold." << endl;

        savePurchases(purchasedPropertyID, purchasedBuyerUsername,
                      purchasedDate, purchasedCount);
    }
    else
    {
        setcl(4);
        cout << "                                                        Property not found in your purchases!" << endl;
    }

    footer();
}
// ADMIN: Rate a user
void rateUser(string username[], float userRating[], string userRatingComment[],
              int userCount, string password[], int role[], string sellerID[],
              bool approval[])
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > RATE USER" << endl;
    setcl(6);
    cout << "                                          _________________________________" << endl
         << endl;

    string uname;
    setcl(3);
    cout << "                                                        Enter username to rate: ";
    setcl(7);
    getline(cin >> ws, uname);

    int idx = -1;
    for (int i = 0; i < userCount; i++)
    {
        if (username[i] == uname)
        {
            idx = i;
            break;
        }
    }

    if (idx != -1)
    {
        setcl(3);
        cout << "                                                        Current Rating: ";
        setcl(7);
        cout << userRating[idx] << "/5.0" << endl;
        setcl(3);
        cout << "                                                        Current Comment: ";
        setcl(7);
        cout << userRatingComment[idx] << endl
             << endl;

        float rating;
        do
        {
            setcl(6);
            cout << "                                                        Enter new rating (0-5): ";
            setcl(7);
            cin >> rating;
            if (rating < 0 || rating > 5)
            {
                setcl(4);
                cout << "                                                        Invalid rating! Must be between 0 and 5." << endl;
            }
        } while (rating < 0 || rating > 5);

        userRating[idx] = rating;

        setcl(3);
        cout << "                                                        Enter comment: ";
        setcl(7);
        getline(cin >> ws, userRatingComment[idx]);

        setcl(2);
        cout << "                                                        User rated successfully!" << endl;
        saveUsers(username, password, role, sellerID, approval, userCount, userRating, userRatingComment);
    }
    else
    {
        setcl(4);
        cout << "                                                        User not found!" << endl;
    }

    footer();
}

// ADMIN: Delete a user
void deleteUser(string username[], string password[], int role[], string sellerID[],
                bool approval[], float userRating[], string userRatingComment[],
                int &userCount)
{
    header();
    setcl(4);
    cout << "                                          SIGN IN > ADMIN MENU > DELETE USER" << endl;
    setcl(6);
    cout << "                                          ___________________________________" << endl
         << endl;

    string uname;
    setcl(3);
    cout << "                                                        Enter username to delete: ";
    setcl(7);
    getline(cin >> ws, uname);

    int idx = -1;
    for (int i = 0; i < userCount; i++)
    {
        if (username[i] == uname)
        {
            idx = i;
            break;
        }
    }
    if (idx != -1)
    {
        setcl(3);
        cout << "                                                        User: ";
        setcl(7);
        cout << username[idx] << endl;
        setcl(3);
        cout << "                                                        Role: ";
        setcl(7);
        cout << (role[idx] == 1 ? "Seller" : "Buyer") << endl;

        string confirm;
        setcl(6);
        cout << "                                                        Are you sure you want to delete this user? (yes/no): ";
        setcl(7);
        cin >> confirm;

        if (confirm == "yes" || confirm == "YES")
        {
            // Shift all elements
            for (int i = idx; i < userCount - 1; i++)
            {
                username[i] = username[i + 1];
                password[i] = password[i + 1];
                role[i] = role[i + 1];
                sellerID[i] = sellerID[i + 1];
                approval[i] = approval[i + 1];
                userRating[i] = userRating[i + 1];
                userRatingComment[i] = userRatingComment[i + 1];
            }

            userCount--;

            setcl(2);
            cout << "                                                        User deleted successfully!" << endl;
            saveUsers(username, password, role, sellerID, approval, userCount, userRating, userRatingComment);
        }
        else
        {
            setcl(3);
            cout << "                                                        Deletion cancelled." << endl;
        }
    }
    else
    {
        setcl(4);
        cout << "                                                        User not found!" << endl;
    }

    footer();
}

// exit function
void exitMenu()
{
    system("cls");
    setcl(3);
    cout << "\n\n\n\n\n\n\n\n\n";
    cout << R"(    
                              _____ _                 _     __   __            _  
                             |_   _| |               | |    \ \ / /           | | 
                               | | | |__   __ _ _ __ | | __  \ V /___  _   _  | | 
                               | | | '_ \ / _` | '_ \| |/ /   \ // _ \| | | | | | 
                               | | | | | | (_| | | | |   <    | | (_) | |_| | |_| 
                               \_/ |_| |_|\__,_|_| |_|_|\_\   \_/\___/ \__,_| (_) 
                                                     
                                                     
                                _____                 _  ______              _      
                               |  __ \               | | | ___ \            | |     
                               | |  \/ ___   ___   __| | | |_/ /_   _  ___  | |     
                               | | __ / _ \ / _ \ / _` | | ___ \ | | |/ _ \ | |     
                               | |_\ \ (_) | (_) | (_| | | |_/ / |_| |  __/ |_|     
                                \____/\___/ \___/ \__,_| \____/ \__, |\___| (_)     
                                                                 __/ |              
                                                                |___/               )";
    cout << endl
         << endl;
    setcl(7);
    exit(0);
}